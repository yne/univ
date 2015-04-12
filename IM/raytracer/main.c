#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector3d.c"
#include "color.c"
#include "ray.c"//vec+col
#include "diff_geom.c"//vec
#include "bsdf.c"//vec
#include "isect.c"//df+bsdf
#include "geometry.c"//vec
#include "geometry.plane.c"
//#include "geometry.sphere.c"
#include "material.c"//

#include "primitive.c"//geo+mat
#include "camera.c"//vec
#include "light.c"//vec+col
#include "scene.c"//cam+light+prim
#include "output.bmp.c"

Color direct_lighting (Light * light,Ray ray, Isect isect) {
	return light->color;
/*
	Vector3D dir_to_light = vec(light->pos - isect.dg.pos).normalize();
	
	return bsdf_evaluate(isect.bsdf,-ray_.dir(), dir_to_light)
	* light->le()
	* fabsf (isect_.dg().normal().dot (dir_to_light));
*/
}

Color get_lighting (Scene*scene,Ray ray, Isect isect) {
	Color color = color_new(0,0,0);
	int i;
	for (i=0; i<scene->nb_lights; i++){
		if (scene_test_visibility (scene, isect.dg.pos, scene->lights[i]))
			color = color_add(color,direct_lighting (scene->lights[i],ray, isect));
	}
	return color;
}

void raytrace(Scene*scene,int w,int h,
	                void (*open_cb)(int,int,void*),
	                void (*write_cb)(Color c,int,int,void*),
	                void (*close_cb)(void*),
	                void* data_cb){
	int y,x,i=0;
	Isect isect;
	if(open_cb)open_cb(w,h,data_cb);
	for(y=0;y<h;y++){
		for(x=0;x<w;x++,i++){
			Color color;
			float dx=(float)((x + .5f) - w * .5f) / (w * .5f);
			float dy=(float)((y + .5f) - h * .5f) / (h * .5f);
			
			Ray ray=camera_ray(scene->camera,dx,dy);
			if(!scene_intersect(scene,&ray, &isect))//no intersection => blue sky
				color = color_new(0,.3,.8);//1.4-dy*.9,1.4-dy*.8,1.4-dy*.5);
			else
				color = get_lighting (scene,ray, isect);
			if(write_cb)write_cb(color,x,y,data_cb);
		}
	}
	if(close_cb)close_cb(data_cb);
}

int main (int argc,char**argv) {
	Scene scene=scene_new();
	scene.camera=&camera_new(
		vector3d_new(0.f, 2.f,-6.f),
		vector3d_new(0.f, 0.f, 0.f),
		vector3d_new(0.f, 1.f, 0.f),
		90.f, 16.f/9.f);
	//scene_add_primitive(&scene,&primitive_new_sphere());
	scene_add_primitive(&scene,&primitive_new(&geometry_plane_new(
		vector3d_new(0.f,-1.f, 0.f),
		vector3d_new(0.f, 1.f, 0.f)
	),NULL));
	
	scene_add_light(&scene,&light_new(vector3d_new(5,-5,2),color_new(128,255,32)));
	
	int fd=1;
	raytrace(&scene,
		argc>=3?atoi(argv[1]):1600,
		argc>=3?atoi(argv[2]):900,
		argc>=4?color2bmp_open:NULL,
		color2bmp_write,
		argc>=4?color2bmp_close:NULL,
		&fd
	);
	return 0;
}

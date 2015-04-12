typedef struct{
	Camera*camera;
	
	Light*lights[32];
	int nb_lights;
	
	Primitive*primitives[128];
	int nb_primitives;
	
}Scene;

Scene scene_new(){
	Scene scene={.nb_lights = 0, .nb_primitives = 0 };
	return scene;
}

scene_set_camera(Scene*scene,Camera*camera){
	scene->camera=camera;
}

scene_add_light(Scene*scene,Light*light){
	if(scene->nb_lights<sizeof(scene->lights)/sizeof(Light*))
		scene->lights[scene->nb_lights++]=light;
}

scene_add_primitive(Scene*scene,Primitive*primitive){
	if(scene->nb_primitives<sizeof(scene->primitives)/sizeof(Primitive*))
		scene->primitives[scene->nb_primitives++]=primitive;
}

int scene_intersect(Scene*scene,Ray*ray,Isect*isect){
	Isect isect_tmp;
	int nb_isect = 0;
	int i;
	
	for(i=0;i<scene->nb_primitives;i++) {
		if (primitive_intersect (scene->primitives[i],ray, &isect_tmp)) {
			nb_isect++;
			*isect = isect_tmp;
		}
	}
	return nb_isect;
}

int scene_test_visibility(Scene*scene,Vector3D pos, Light * light){
	Ray ray = ray_new(pos, vector3d_normalize(vector3d_sub(light->pos,pos)));
	Isect isect_tmp;
	int i;
	
	for(i=0;i<scene->nb_primitives;i++) {
		if (primitive_intersect (scene->primitives[i],&ray, &isect_tmp)) {
			return 1;
		}
	}
	return 0;
}

//Ray
typedef struct{
	Vector3D ori;
	Vector3D dir;
	int depth;
	Color importance;
	float max_t;
}Ray;

Ray ray_new(Vector3D ori,Vector3D dir){
	Ray ray;
	ray.ori=ori;
	ray.dir=dir;
	ray.max_t = 34028234663852886e22;//32bit float limit
	ray.depth = 0;
	return  ray;
}

Vector3D ray_at (Ray*ray,float t){
	return vector3d_add(ray->ori,vector3d_mul_float(ray->dir,t));
}

float ray_epsilon() {
	return 0.001f;
}

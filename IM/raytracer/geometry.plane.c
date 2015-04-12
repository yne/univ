int geometry_plane_intersect(Geometry*geom,Ray*ray){
	float t = (-geom->f[0] - vector3d_dot(ray->ori,geom->v[0])) / vector3d_dot(ray->dir,geom->v[0]);
	
	if (t < ray_epsilon() || t >= ray->max_t)
		return 0;
	ray->max_t=t;

	//Diff_Geom*p_diff_geom_ = Diff_Geom_new(ray.at(t),normal);
	return 1;
}

Geometry geometry_plane_new(Vector3D pos,Vector3D normal){
	Geometry geometry={.intersect=geometry_plane_intersect};
	geometry.v[0]=vector3d_normalize(normal);//normal
	geometry.f[0]=vector3d_dot(vector3d_inv(geometry.v[0]),pos);//offset
	return geometry;
}


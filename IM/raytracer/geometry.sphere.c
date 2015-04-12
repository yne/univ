//UNFINISHED
//http://www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm

int geometry_sphere_intersect (Geometry*geo,Ray& ray, Diff_Geom * diff_geom){
	Vector3D centerToRay = ray.ori - m_base;
	Vector3D intersectionPlane = ray.dir().cross_product(geo->v[1]);
	float ln = intersectionPlane.norm();
	
	if  ( ln < ray_epsilon() ) {	/* ray parallel to sphere	*/
		if ((centerToRay - geo->v[1]*centerToRay.dot(geo->v[1])).norm() > geo->f[0])return 0;
		if  (ray.dir().dot(geo->v[1]) > 0)/* intersect base cap */
			Plane cap(m_base+geo->v[1]*-geo->f[1], geo->v[1]*-1.f);
		else/* intersect top cap */
			Plane cap(m_base+geo->v[1]* geo->f[1], geo->v[1]);
		return cap.intersect(ray, diff_geom);
	}

	intersectionPlane = intersectionPlane.normalize();
	float d = fabs(centerToRay.dot(intersectionPlane));
	if(!d <= geo->f[0])return 0;//don't hit
	float t = - centerToRay.cross_product(geo->v[1]).dot(intersectionPlane)/ln;
	float s = fabs(sqrtf(geo->f[0]*geo->f[0] - d*d) / ray.dir().dot(intersectionPlane.cross_product(geo->v[1]).normalize()) );
	float tin = t-s;
	float tout = t+s;
	if ((tout < ray_epsilon()) || (tin > ray.max_t()))return 0;

	/* Compute intersection point and normal. Beware of capping */
	float isect_t;

	float isect_h = geo->v[1].dot(ray.at (isect_t) - m_base);

	if (tin >= ray_epsilon()) {
		if ( (isect_h <= geo->f[1]) && (isect_h >= -geo->f[1]) ) {/*side is intersected*/
			ray.set_max_t (tin);
			*diff_geom = Diff_Geom (ray.at (isect_t), ((ray.at (isect_t) - m_base) - (geo->v[1]*isect_h)).normalize());
			return 1;
		}
		if (tout > ray.max_t())return 0;
		float isect_h_len = geo->v[1].dot(ray.at (tout) - m_base);
		if ( (isect_h_len > geo->f[1]) || (isect_h_len <-geo->f[1]) )return 0;
		if (isect_h < -geo->f[1])
			Plane cap(m_base+geo->v[1]*-geo->f[1], geo->v[1]*-1.f);/* intersect base cap */
		else
			Plane cap(m_base+geo->v[1]*geo->f[1], geo->v[1]);/* intersect top cap */
		return cap.intersect(ray, diff_geom);
	}
	/* intersect only cap */
	if ( (ray.dir().dot(geo->v[1]) > 0) &&  (isect_h > -geo->f[1])) {
		return intersect(
			geometry_plane_new(m_base+geo->v[1]*-geo->f[1], geo->v[1]*-1.f),/* intersect base cap */
			ray, diff_geom);
	} else if ( (ray.dir().dot(geo->v[1]) <= 0) &&  (isect_h < geo->f[1])) {
		return intersect(
			geometry_plane_new(m_base+geo->v[1]*geo->f[1], geo->v[1]),/* intersect base cap */
			ray, diff_geom);
	}
	return 0;
}

Geometry geometry_sphere_new(Vector3D center, Vector3D axis, float radius, float length){
	Geometry geometry={.intersect=geometry_sphere_intersect};
	
	geometry.v[0] = center;//.base
	geometry.v[1] = Vector3D_normalize(axis);//.axis
	geometry.f[0] = radius;//.radius
	geometry.f[1] = length/2.f;//.length
	
	return geometry;
}

//Camera
typedef struct{
	Vector3D m_pos; 
	Vector3D m_center; 
	Vector3D x, y;
	int x_res;
	int y_res;//should be removed
}Camera;

Camera camera_new(Vector3D pos,Vector3D aim,Vector3D up,float fov,float ratio){
	Camera camera;
	camera.m_pos = pos;

	Vector3D z = vector3d_normalize(vector3d_sub(aim,pos));
	camera.x = vector3d_normalize(vector3d_cross_product(z,up));
	camera.y = vector3d_mul_float(vector3d_cross_product(camera.x,z),1.f/ratio);
	camera.m_center = vector3d_add(camera.m_pos,vector3d_mul_float(z,(1.f / tan((fov * 3.14159265358979323846 / 180.f) * 0.5f))));
	
	return camera;
}

Ray camera_ray(Camera*camera,float x, float y){//x,y {-1~+1}
	//ray_center = ((cam_center - (cam_x * x) - (cam_y * y)) - cam_pos)
	Vector3D center= vector3d_sub(vector3d_sub(camera->m_center,vector3d_mul_float(camera->x,x)),vector3d_mul_float(camera->y,y));
	return ray_new(camera->m_pos,vector3d_normalize(vector3d_sub(center,camera->m_pos)));
}

/*
Ray ray_for_pixel (int x_, int y_) const {
	float delta_x = float((x_ + 0.5f) - x_res * 0.5f) / (x_res * 0.5f);
	float delta_y = float((y_ + 0.5f) - y_res * 0.5f) / (y_res * 0.5f);

	//-delta_y to have the first row correspond to the top of the image
	return Ray (m_pos, ((m_center - (x * delta_x) - (y * delta_y)) - m_pos).normalize());
}

Ray ray_for_screen_coords (float x_, float y_) const {
	float delta_x = (x_ - x_res * 0.5f) / (x_res * 0.5f);
	float delta_y = (y_ - y_res * 0.5f) / (y_res * 0.5f);

	//-delta_y to have the first row correspond to the top of the image
	return Ray (m_pos, ((m_center - (x * delta_x) - (y * delta_y)) - m_pos).normalize());
}
*/
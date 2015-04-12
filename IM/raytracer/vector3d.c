
//Vector3D
typedef struct{
	float x;
	float y;
	float z;
}Vector3D;

Vector3D vector3d_new(float x,float y,float z){
	Vector3D vec={.x=x,.y=y,.z=z};
	return vec;
}
void vector3d_print(Vector3D a){
	printf("vec3<%f,%f,%f>\n",a.x,a.y,a.z);
}
float vector3d_norm(Vector3D a){
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vector3D vector3d_mul(Vector3D a,Vector3D b){
	return vector3d_new(a.x*b.x, a.y*b.y, a.z*b.z);
}

Vector3D vector3d_mul_float(Vector3D a,float b){
	return vector3d_new(a.x*b, a.y*b, a.z*b);
}

Vector3D vector3d_normalize(Vector3D a){
	float n=1.f/vector3d_norm(a);
	return vector3d_mul_float(a,n);
}

Vector3D vector3d_sub(Vector3D a,Vector3D b){
	return vector3d_new(a.x-b.x, a.y-b.y, a.z-b.z);
}
Vector3D vector3d_add(Vector3D a,Vector3D b){
	return vector3d_new(a.x+b.x, a.y+b.y, a.z+b.z);
}
Vector3D vector3d_inv(Vector3D a){
	return vector3d_new(-a.x, -a.y, -a.z);
}
float vector3d_dot(Vector3D a,Vector3D b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector3D vector3d_cross_product (Vector3D a,Vector3D b){
	return vector3d_new(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}
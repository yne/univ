//Light
typedef struct{
	Vector3D pos;
	Color color;
}Light;
Light light_new (Vector3D pos,Color color){
	Light light={pos,color};
	return light;
}

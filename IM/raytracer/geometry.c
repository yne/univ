typedef struct Geometry{
	int (*intersect)(struct Geometry*,Ray*);
	//private heap
	float f[6];
	Vector3D v[6];
}Geometry;
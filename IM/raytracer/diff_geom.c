typedef struct{
	Vector3D pos;
	Vector3D normal;
}Diff_Geom;

Diff_Geom Diff_Geom_new(Vector3D pos,Vector3D normal){
	Diff_Geom dg;
	dg.pos=pos;
	dg.normal=normal;
	return dg;
}

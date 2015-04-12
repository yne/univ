typedef struct{
	Geometry * geom;
	Material * material;
}Primitive;

Primitive primitive_new(Geometry * geom,Material * material){
	Primitive primitive={.geom=geom,.material=material};
	return primitive;
}

int primitive_intersect (Primitive*primitive,Ray*ray,Isect*isect_tmp){
//	Diff_Geom dg;
	if(!primitive->geom)return 0;
	if(!primitive->geom->intersect(primitive->geom,ray)) {
		return 0;
	}
	
	//BSDF bsdf = m_p_material->evaluate (dg);

	//*p_isect_ = Isect (dg, bsdf);

	return 1;
}

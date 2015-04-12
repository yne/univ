BSDF material_plastic_evaluate(Material*material,Diff_Geom diff_geom){
	return BSDF_init_blinn_phong (diff_geom_normal(diff_geom), material->kd, material->ks, material->shininess);
}
Material material_matte_new(Color kd,Color kr,float shininess){
	Material material;
	material.kd=kd;
	material.kr=kr;
	material.shininess=shininess;
	return material;
}
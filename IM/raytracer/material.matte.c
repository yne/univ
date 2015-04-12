BSDF material_matte_evaluate(Material*material,Diff_Geom diff_geom){
	return BSDF_init_diffuse (diff_geom_normal(diff_geom), material->kd);
}
Material material_matte_new(Color kd){
	Material material;
	material.kd=kd;
	return material;
}
BSDF material_metal_evaluate(Material*material,Diff_Geom diff_geom){
	return BSDF_init_pure_refl(diff_geom_normal(diff_geom), material->kd, material->kr);
}
Material material_metal_new(Color kd,Color kr){
	Material material;
	material.kd=kd;
	material.kr=kr;
	return material;
}
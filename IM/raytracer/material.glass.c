BSDF material_plastic_evaluate(Material*material,Diff_Geom diff_geom){
	return BSDF::init_fresnel (diff_geom_normal(diff_geom), material->kr, material->kt, material->ior);
}
Material material_matte_new(Color kr,Color kt,float ior){
	Material material;
	material.kr=kr;
	material.kt=kt;
	material.ior=ior;
	return material;
}
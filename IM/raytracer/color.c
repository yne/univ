//Color
typedef struct{
	float r,g,b;
}Color;

Color color_new (float r,float g,float b){
	Color color={r,g,b};
	return color;
}
Color color_add (Color a,Color b){
	Color color={a.r+b.r, a.g+b.g , a.b+b.b};
	return color;
}
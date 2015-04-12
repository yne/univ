#include <fcntl.h>

void color2bmp_open(int w,int h,void*data){
	int s = 54 + 3*w*h;
	unsigned char header[54] = {'B','M',
	s,s>>8,s>>16,s>>24,
	0,0, 0,0,
	54,0,0,0,
	40,0,0,0,
	 w, w>>8, w>>16, w>>24,
	-h,-h>>8,-h>>16,-h>>24,//negativ DIB height = top-bottom
	1,0, 24,0};

	int fd = open("img.bmp",O_CREAT|O_TRUNC|O_WRONLY,0777);
	write(fd,header,sizeof(header));
	*data=fd;
}
#define MAX(A,B) (A>B?A:B)
#define MIN(A,B) (A<B?A:B)
void color2bmp_write(Color c,int x,int y,void*data){
	int fd=*data;
	unsigned char 
		r=MIN(MAX(0.f,c.r),1.f)*255,
		g=MIN(MAX(0.f,c.g),1.f)*255,
		b=MIN(MAX(0.f,c.b),1.f)*255;
	unsigned rgb = r<<16 | g<<8 | b;
	write(fd,&rgb,3);
	//printf("write [%i,%i] <%f,%f%,%f>\n",x,y,c.r,c.g,c.b);
}
void color2bmp_close(void*data){
	int fd=*data;
	close(fd);
}
typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8 ;
typedef   signed long  s32;
typedef   signed short s16;
typedef   signed char  s8 ;

typedef struct{
	u8  chunkId[4];
	u32 chunkSize;
	u8  format[4];
	u8  subChunkId[4];
	u32 subChunkSize;
	u16 audioFormat;
	u16 numChannels;
	u32 sampleRate;
	u32 bytesPerSecond;
	u16 blockAlign;
	u16 bitsPerSample;
	u8  dataChunkId[4];
	u32 dataSize;
}Wav;

gsl_matrix* wavMatrix(char*path,void**ctx,unsigned*rows,unsigned*cols){
	*ctx=(Wav*)malloc(sizeof(Wav));
	Wav*header=*(Wav**)ctx;
	
	FILE*f=fopen(path,"rb");
	fread(header,sizeof(Wav),1,f);
	*cols = header->numChannels;
	if(*cols!=1){printf("must be mono !\n");return NULL;}
	*rows = header->dataSize/(header->subChunkSize/8);
	gsl_matrix* mat=gsl_matrix_alloc(*rows,1);
	u32 i,j;
	s16 sample;
	for(i=0;i<*rows && fread(&sample,sizeof(sample),1,f)>0;i++){
		gsl_matrix_set(mat,i,0,sample);
	}
	//printf("%u sample imported",rows);
	fclose(f);
	return mat;
}

void dumpWavMatrix(char*path,void*ctx,gsl_matrix*mat){
	Wav*header=(Wav*)ctx;
	header->chunkSize=sizeof(Wav)+header->dataSize;
	FILE*f=fopen(path,"wb+");
	fwrite(header,sizeof(Wav),1,f);
	u32 i,rows = header->dataSize/(header->subChunkSize/8);
	for(i=0;i<rows;i++){
		s16 sample = gsl_matrix_get(mat,i,0);
		fwrite(&sample,sizeof(sample),1,f);
	}
	fclose(f);
}
/*
dumpWavMatrix(char*path,void*data,void*ctx){
	Wav*header=(Wav*)ctx;
	s16*m=(s16*)data;
	u32 i,len = header->dataSize/(header->subChunkSize/8);
	
	
	for(i=0;i<len;i++)m[i]+=0x3000;

	FILE*f=fopen(path,"wb+");
	fwrite(ctx,sizeof(Wav),1,f);
	fwrite(m,header->dataSize,1,f);
	fclose(f);
	
	free(header);
	free(m);
}
*/
/*
int main(){
	void*ctx;// image/audio context
	void*data=wavMatrix("test.wav",&ctx);
	dumpWavMatrix("out.wav",data,ctx);
	
}
*/



class FurTexture{
	public:
	GLubyte* furTexture;
	int FUR_TEXTURE_WIDTH;
	int FUR_TEXTURE_HEIGHT;
	int FUR_LAYERS;
	float FUR_DENSITY;
	
	FurTexture(int ftw, int fth, int fl, float fd){
		FUR_TEXTURE_WIDTH = ftw;
		FUR_TEXTURE_HEIGHT = fth;
		FUR_LAYERS = fl;
		FUR_DENSITY = fd;
		
		furTexture = new GLubyte[4*FUR_TEXTURE_WIDTH*FUR_TEXTURE_HEIGHT];
		
		//initialize all colors to black
		for(int iter = 0 ; iter < FUR_TEXTURE_WIDTH*FUR_TEXTURE_HEIGHT; iter++){
			
			int i, j;
			i = iter / FUR_TEXTURE_WIDTH;
			j = iter % FUR_TEXTURE_WIDTH;
			
			glm::dvec4 furTexColor = glm::dvec4(0.0f, 0.0f, 0.0f, 0.0f);
			
			furTexture[iter * 4] = (furTexColor[0])*255.f;
			furTexture[(iter * 4) + 1] = (furTexColor[1])*255.f;
			furTexture[(iter * 4) + 2] = (furTexColor[2])*255.f;
			furTexture[(iter * 4) + 3] = (furTexColor[3])*255.f;	
			
		}
		
		int numStrands = (int)(fd * ftw * fth);
		
		int strandsPerLayer = numStrands/fl;
		
		for(int i = 0; i < numStrands; i++){
			int x = rand()%fth;
			int y = rand()%ftw;
			
			float maxLayer = pow((float)(i /strandsPerLayer)/ (float)fl, 0.7);
			
			furTexture[x*4* FUR_TEXTURE_WIDTH + y*4] = maxLayer*255;
			furTexture[x*4* FUR_TEXTURE_WIDTH + y*4 + 1] = 0;
			furTexture[x*4* FUR_TEXTURE_WIDTH + y*4 + 2] = 0;
			furTexture[x*4* FUR_TEXTURE_WIDTH + y*4 + 3] = 255; 
		
		}
		
		
	} 
};




#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tuple>
#include <vector>
#include <stb_image.h>
#include "shader.h"
#include "furTexture.cpp"
using namespace std;

void framebuffer_size_callback(GLFWwindow*, int, int);
void key_callback(GLFWwindow*, int, int, int, int);

int FUR_TEXTURE_WIDTH = 1024;
int FUR_TEXTURE_HEIGHT = 1024;
int FUR_LAYERS = 40;
int FUR_HEIGHT = 1.0;
float FUR_DENSITY = 0.4f;

float radius = 30.0f;
float heightTop = 20.0f;       
float camX   = radius;
float camY = heightTop + radius;
float camZ   =  radius;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraDirection;
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraRight;
glm::vec3 cameraUp;

int main(int argc, char* argv[]){
	
	
	
	int SCR_WIDTH = 800;
	int SCR_HEIGHT =800;
	
	if(argc >= 3){
		SCR_WIDTH = stoi(argv[1]);
		SCR_HEIGHT = stoi(argv[2]);
	}
	
			
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Minor Project", NULL, NULL);
	if(window == NULL){
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//To be notified when a physical key is pressed
	glfwSetKeyCallback(window, key_callback);
	
	//Shader furShader("furShader.vs", "furShader.fs");
	
	
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout<< "Failed to initialize GLAD" << endl;
		return -1;
	}
	
	Shader furShader("floor.vs", "floor.fs");
	
	
	/*
    float vertices[] = {
        // positions          // texture coords   //3 vertices normals
         1.0f,  0.0f, 1.0f,   1.0f, 1.0f,  0.0f,  1.0f,  0.0f,// top right
         1.0f, 0.0f, -1.0f,   1.0f, 0.0f,  0.0f,  1.0f,  0.0f,// bottom right
        -1.0f, 0.0f, -1.0f,   0.0f, 0.0f,  0.0f,  1.0f,  0.0f,// bottom left
        -1.0f,  0.0f, 1.0f,   0.0f, 1.0f,   0.0f,  1.0f,  0.0f,// top left 
    };
    
    /*
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    unsigned int VBO2, VAO2, EBO;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	
	
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    */
	//create the blood vessel
	std::ifstream inputFile;
    	inputFile.open("bv3.txt");
    
    	//int numDVert = 10080;
    	int numDVert = 3120;
    	float vertices[numDVert*8];
   	int count1 = 0;
    	while(count1 < numDVert*8 && inputFile >>vertices[count1]){
    		count1++;
    	}
    	inputFile.close();
    	
    	/*
    	float newVertices[sizeof(float)*9*numDVert*FUR_LAYERS];
	
	for(int i = 0; i < FUR_LAYERS; i++){
		float layer = (float)i/ (float)(FUR_LAYERS - 1);
		float layerHairLength = FUR_HEIGHT * layer;
		int gap = numDVert;
		for(int j = 0; j < numDVert; j++){
			
			//vertices[j*8] = vertices[j*8] + vertices[j*8+5] * layerHairLength;
			float a = vertices[j*8] + vertices[j*8+5] * layerHairLength;
			//vertices[j*8+1] = vertices[j*8+1] + vertices[j*8+6] * layerHairLength;
			float b = vertices[j*8+1] + vertices[j*8+6] * layerHairLength;
			//vertices[j*8+2] = vertices[j*8+2] + vertices[j*8+7] * layerHairLength;
			float c = vertices[j*8+2] + vertices[j*8+7] * layerHairLength;			
						
			//newVertices[i*9*numDVert+j*9] = vertices[j*8];
			newVertices[i*9*numDVert+j*9] = a;
			//newVertices[i*9*numDVert+j*9+1] = vertices[j*8+1];
			newVertices[i*9*numDVert+j*9+1] = b;
			
			//newVertices[i*9*numDVert+j*9+2] = vertices[j*8+2];
			newVertices[i*9*numDVert+j*9+2] = c;
			
			newVertices[i*9*numDVert+j*9+3] = vertices[j*8+3];
			newVertices[i*9*numDVert+j*9+4] = vertices[j*8+4];
			newVertices[i*9*numDVert+j*9+5] = vertices[j*8+5];
			newVertices[i*9*numDVert+j*9+6] = vertices[j*8+6];
			newVertices[i*9*numDVert+j*9+7] = vertices[j*8+7];
			newVertices[i*9*numDVert+j*9+8] = layer;
			
			cout<<vertices[j*8]<<" "<<vertices[j*8+1]<<" "<<vertices[j*8+2]<<" "<< vertices[j*8+5]<<" "<<vertices[j*8+6]<<" "<<vertices[j*8+7]<<endl;
			//newVertices.push_back({vertices[j*8], vertices[j*8+1], vertices[j*8+2],vertices[j*8+3], vertices[j*8+4], vertices[j*8+5], vertices[j*8+6], vertices[j*8+7], layer});	
			
		}
	}
	*/
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*newVertices.size()*newVertices[0].size(), newVertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//initialize VAO
	glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VAO);
	
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(5 * sizeof(float)));
    	glEnableVertexAttribArray(2);
    	
    
    	
	
	//We create fur Texture 
	/*FurTexture ftx(FUR_TEXTURE_WIDTH, FUR_TEXTURE_HEIGHT, FUR_LAYERS, FUR_DENSITY);
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, ftx.furTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	*/
	/* unsigned int texture;
	 glGenTextures(1, &texture);
    	glBindTexture(GL_TEXTURE_2D, texture);
    	// set the texture wrapping parameters
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    	// set texture filtering parameters
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	// load image, create texture and generate mipmaps
    	int width2, height2, nrChannels2;
    	
    	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    	unsigned char *data2 = stbi_load("images.jpeg", &width2, &height2, &nrChannels2, 0);
    	if (data2){
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        	glGenerateMipmap(GL_TEXTURE_2D);
    	}else{
        	std::cout << "Failed to load texture" << std::endl;
    	}
    	
    	stbi_image_free(data2);*/
	//Next we load the texture color image
	 /*unsigned int texture2;
	 glGenTextures(1, &texture2);
    	glBindTexture(GL_TEXTURE_2D, texture2);
    	// set the texture wrapping parameters
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    	// set texture filtering parameters
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	// load image, create texture and generate mipmaps
    	int width, height, nrChannels;
    	
    	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    	unsigned char *data = stbi_load("1286146771.png", &width, &height, &nrChannels, 0);
    	if (data){
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        	glGenerateMipmap(GL_TEXTURE_2D);
    	}else{
        	std::cout << "Failed to load texture" << std::endl;
    	}
    	
    	stbi_image_free(data);
    	
    	FurTexture ftx(FUR_TEXTURE_WIDTH, FUR_TEXTURE_HEIGHT, FUR_LAYERS, FUR_DENSITY);
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, ftx.furTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
    	//create the fur geometry
    	//FurGe furGeom(vertices3, furShader, FUR_LAYERS, FUR_HEIGHT);
    	*/
    	
	/*
	//Generate Fur layers
	vector<float> vertices {
		20.0, -20.0, 0.0,	0.0, 0.0, 1.0, 	1.0, 0.0,
		30.0, 20.0, 0.0, 	0.0, 0.0, 1.0, 	1.0, 1.0,
		-30.0, 20.0, 0.0,	0.0, 0.0, 1.0,		0.0, 1.0,
		-30.0, 20.0, 0.0,	0.0, 0.0, 1.0,		0.0, 1.0,
		-20.0, -20.0, 0.0,	0.0, 0.0, 1.0,		1.0, 0.0, 
	};
	*/
	
	furShader.use();
	
	//furShader.setInt("fur", 0);
	
        
        //furShader.setInt("color", 1);
        
        
	
	
	glEnable(GL_MULTISAMPLE);
  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
  	
  	
  	
  	cameraDirection = glm::normalize(cameraPos - cameraTarget);
   	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
   	
   	cameraUp = glm::cross(cameraDirection, cameraRight);
   	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        //view = glm::lookAt(glm::vec3(camX, camY, camZ), cameraTarget, cameraUp);
  	
	while(!glfwWindowShouldClose(window)){
		
		
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
  	
		/*glActiveTexture(GL_TEXTURE0);
        	glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
        	glBindTexture(GL_TEXTURE_2D, texture2);
        	*/
        	
		furShader.use();
		
		glm::mat4 model = glm::mat4(1.0f);
  		glm::mat4 view = glm::mat4(1.0f);
  		glm::mat4 projection = glm::mat4(1.0f);
  		
  		model = glm::scale(glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(0.5f, 0.5f, 0.5f));
        
        	view  = glm::translate(view, glm::vec3(0.0f, -20.0f, -100.0f)) ;
        
        	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
         	glUniformMatrix4fv(glGetUniformLocation(furShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
  		glUniformMatrix4fv(glGetUniformLocation(furShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    		furShader.setMat4("projection", projection);
    		
    		//glm::vec3 gravity(0.0f, 0.0f, 0.0f);
    		//glm::vec3 force(0.0f, sin(glfwGetTime()) * 0.5f, 0.0f);
    		//glm::vec3 disp = gravity + force;
    		//glUniform3f(glGetUniformLocation(furShader.ID, "displacement"), disp.x, disp.y, disp.z);
		
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0.0, 0.0, SCR_WIDTH, SCR_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, ftx.furTexture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, numDVert);
		/*
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
		glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		*/
		
		//glBindVertexArray(VAO2);
        	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)	
		glfwSetWindowShouldClose(window, true);
	
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);

}

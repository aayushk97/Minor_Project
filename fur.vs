#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in float layer;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 displacement;

out vec2 TexCoord;
out float fragLayer;

void main(){

	fragLayer = layer;
	vec3 layerDisplacement = pow(layer , 3.0) * displacement;
	vec4 newPos = vec4(aPos + layerDisplacement, 1.0);
	
	//gl_Position = projection * view * model * vec4(aPos, 1.0);
	gl_Position = projection * view * model * newPos;
	
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);

}

/*
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float layer;

out vec2 TexCoord;
out float fragLayer;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}*/

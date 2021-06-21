#version 330

in vec2 TexCoord;
in float fragLayer;

uniform sampler2D fur;
uniform sampler2D color;

out vec4 FragColor;

void main(){
	
	float shadow = mix(0.4, 1.0, fragLayer);
	
	vec4 furData = texture(fur, TexCoord);
	vec4 furColor = texture(color, TexCoord) * shadow;
	
	float visibility = (fragLayer > furData.r) ? 0.0 : furData.a;
	furColor.a = (fragLayer == 0.0) ? 1.0 : visibility;
	
	FragColor = furColor;
	//fragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	//FragColor = mix(texture(fur, TexCoord), texture(color, TexCoord), 0.2);
}

#version 430 core
uniform samplerCube colorMap;

in vec3 fragTexCoord;
out vec4 color;

void main (void) 
{
	// samplerCube utilise la direction d'intersection avec la texture comme paramètre
	color = texture(colorMap,fragTexCoord);
}

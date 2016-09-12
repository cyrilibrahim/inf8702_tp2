#version 430 core
uniform samplerCube colorMap;

in vec3 fragTexCoords;
out vec4 color;

void main (void) 
{
   // compléter le nuanceur ici pour texturer le cube
   color = texture(colorMap,fragTexCoords);
}

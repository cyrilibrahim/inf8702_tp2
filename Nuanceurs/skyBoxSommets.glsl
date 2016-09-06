#version 430 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform samplerCube colorMap;
uniform mat4 MVP;
out vec3 fragTexCoord;

void main (void)
{
    // À compléter:
    // effectuons la base : la transformation du vertex
    gl_Position = (MVP * vec4(vp, 1.0));
    
    // ...
}

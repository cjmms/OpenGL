#shader vertex
#version 330 core

layout(Location = 0) in vec3 aPos;
layout(Location = 1) in vec3 aNormal;
layout(Location = 2) in vec2 aTextureCoord;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0f);
}



#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(0.4f, 0.1f, 0.7f, 1.0f);
}
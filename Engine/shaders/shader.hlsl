#vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}

#fragment
#version 330 core

out vec4 f_color;
uniform vec4 u_color;

void main()
{
	f_color = u_color;
}
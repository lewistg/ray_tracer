//#version 120
#version 130

in vec4 position;
void main()
{
	//in vec4 position;
	//gl_Position = position;
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}

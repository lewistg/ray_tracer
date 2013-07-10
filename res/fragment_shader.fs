#version 130 

out vec4 outputColor;

void main()
{
	//outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);	
	//gl_FragColor = vec4(0.4, 0.4, 0.8, 1.0);
	float lerpValue = gl_FragCoord.y / 500.0f;
	outputColor = mix( vec4(1.0f, 1.0f, 1.0f, 1.0f), 
				vec4(0.2f, 0.2f, 0.2f, 1.0f), 
				lerpValue);
}

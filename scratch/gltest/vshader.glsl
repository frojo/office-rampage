#version 330 core

layout(location = 0) in vec3 vpos_modelspace;


void main() {
	gl_Position.xyz = vpos_modelspace;
	gl_Position.w = 1.0;
}

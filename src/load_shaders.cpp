#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

//#include <shader.hpp>

std::string get_code_from_stream(std::ifstream shader_stream)
{
	std::string shader_code;
	std::string line = "";
	while (getline(shader_stream, line))
		shader_code += "\n" + line;
	return shader_code;
}

std::string get_shader_code(const char *shader_file_path)
{
	std::ifstream shader_stream(shader_file_path, std::ios::in);

	//TODO: Do I need to destroy this string object??
	std::string shader_code;
	if (shader_stream.is_open()) {
//		shader_code = get_code_from_stream(shader_stream);
		std::string line = "";
		while (getline(shader_stream, line))
			shader_code += "\n" + line;
		return shader_code;
		shader_stream.close();
	} else {
		printf("Impossible to open %s. Are you in the right directory? \
				Dont't forget to read the FAQ!\n",
				shader_file_path);
		getchar();
	}
	return shader_code;
}

/* Returns true if success, false on failure */
bool compile_shader(GLuint shader_id, std::string shader_source)
{
	char const *seek = shader_source.c_str();
	glShaderSource(shader_id, 1, &seek, NULL);
	glCompileShader(shader_id);

	GLint result = GL_FALSE;
	int info_log_length = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (info_log_length > 0) {
		std::vector<char> err_msg(info_log_length+1);
		glGetShaderInfoLog(shader_id, info_log_length, NULL, 
				&err_msg[0]);
		printf("%s\n", &err_msg[0]);
		return false;
	}
	
	return true;
}

GLuint load_shaders(const char *vertex_file_path, 
		const char *fragment_file_path)
{
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertex_shader_code = 
		get_shader_code(vertex_file_path);
	

	std::string fragment_shader_code =
		get_shader_code(fragment_file_path);

	compile_shader(vertex_shader_id, vertex_shader_code);
	compile_shader(fragment_shader_id, fragment_shader_code);

	printf("Linking shaders\n");
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
	
	GLint result = GL_FALSE;
	int info_log_length = 0;

	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (info_log_length) {
		std::vector<char> err_msg(info_log_length+1);
		glGetProgramInfoLog(program_id, info_log_length, NULL, 
				&err_msg[0]);
		printf("%s\n", &err_msg[0]);
	}

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}


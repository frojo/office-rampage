#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "load_shaders.hpp"

int main()
{

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	// TODO: Should probobaly not multisample if we're trying to do a
	// pixel art game
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window
	window = glfwCreateWindow(1024, 768, "Test", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to opwn GLFW window. If you have Intel GPU, they are not 3.3 compatible");
		getchar();
		glfwTerminate();
		return -1;
	}

	// TODO: BUG? Might need to call glfwWaitEvents() or something before
	// MakeContextCurrent() to prevent race with monitor/window switching

	glfwMakeContextCurrent(window);
	glewExperimental=true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to Init GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.4f, 0.0f, 0.0f);
	
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	GLuint program_id = load_shaders("vshader.glsl", "fshader.glsl");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
			g_vertex_buffer_data, GL_STATIC_DRAW);


	glm::mat4 my_identity_mat = glm::mat4(1.0f);
	glm::mat4 my_scaling_mat = 
		glm::scale(my_identity_mat, glm::vec3(2.0f, 2.0f, 2.0f));

	glm::mat4 my_matrix = 
		glm::translate(my_identity_mat, 
				glm::vec3(10.0f, 0.0f, 0.0f));
	glm::vec4 my_vector(10.0f, 10.0f, 10.0f, 0.0f);

	glm::vec4 transformed_vector = my_matrix * my_vector;

	

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(program_id);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &vertex_array_id);
	glDeleteProgram(program_id);

glfwTerm:
	glfwTerminate();

	return 0;
}

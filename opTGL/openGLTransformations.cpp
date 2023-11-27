#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "shades.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main()
{
	std::cout << "2nd HeLOO\n";

	//Setting up a window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating window
	GLFWwindow* window = glfwCreateWindow(500, 600, "19 November", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "FAILED to create a window...";
		glfwTerminate();
		return -1;
	}

	//Setting the window as the current one
	glfwMakeContextCurrent(window);

	//Loading GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED to load GLAD";
		glfwTerminate();
		return -1;
	}

	//Setting viewport
	glViewport(0, 0, 500, 600);

	//For resinzing thw window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Vertices for a square
	float square[] = {
		-0.8f,  0.8f, //Top left 
		-0.8f, -0.8f, //Bottom left 
		 0.8f,  0.8f, //Top right 
		 0.8f, -0.8f, //Bottom right 
	};

	GLuint squre[] = {
		0, 1, 2,
		3, 2, 1
	};

	Shader shades("C:\\Users\\litia\\OneDrive\\Documents\\opTGL\\opTGL\\ranso.vert", "C:\\Users\\litia\\OneDrive\\Documents\\opTGL\\opTGL\\ranso.fs");

	//Creating array objects
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Binding the array object for use
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//Buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squre), squre, GL_STATIC_DRAW);

	//Vertex array data
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	//Enabling the vertex attribute and using the shader(s)
	glEnableVertexAttribArray(0);

	//How the primitives will look like
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shades.use();

	//For moving the object
	glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));

	GLuint transforme = glGetUniformLocation(shades.ID, "transformer");
	glUniformMatrix4fv(transforme, 1, GL_FALSE, glm::value_ptr(trans));

	trans = glm::scale(trans, glm::vec3(0.5, 0.8, 0.0));
	trans = glm::translate(trans, glm::vec3(0.2, 0.0, 0.0));

	float rui = 1.0f;
	int junk = 0;
	float slick = 1.0;

	while (!glfwWindowShouldClose(window))
	{

		//Setting the color for the background
		glClearColor(0.1f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Rendering
		shades.use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (junk == 19)
		{
			junk = 0;
			if (slick == 1.0f)
			{
				slick = -1.0f;
			}
			else {
				slick = 1.0f;
			}			
		}
		else {
			junk++;	

			if (slick == 1.0f)
			{
				if (junk == 10)
				{
					rui = 0.0f;
				}
				rui -= 0.1f;
			}
			else if (slick == -1.0f)
			{
				if (junk == 10)
				{
					rui = 0.0f;
				}
				rui += 0.1f;
			}
		}

		trans = glm::translate(trans, glm::vec3(rui, rui, 0.0));
		glUniformMatrix4fv(transforme, 1, GL_FALSE, glm::value_ptr(trans));

		std::cout << junk << " " << rui << "\n";
		Sleep(100);

		//Swaps the frame buffers to avoid lag ans=d and polls all pending events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	//Closing by freeing the memory used
	glfwTerminate();

	return 0;
}

//For resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
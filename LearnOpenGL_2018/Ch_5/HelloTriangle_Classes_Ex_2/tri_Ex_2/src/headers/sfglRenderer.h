#pragma once
#ifndef SFGLRENDERER_H
#define SFGLRENDERER_H

// Preprocessor directives
#include "glPreprocessors.h"
#include "sfglShaderRenderer.h"

class sfglRenderer
{
public:
	// ----------------------------------------
	// Class constructors
	sfglRenderer();


	// ---------------------------------------
	// public functions
	/////////////////////

	// Sets the window value
	void setWindow(GLFWwindow* window);

	// Initiates the renderer in this class
	void initiateRenderer();


private:
	// -------------------------------------------
	// Private variables


	GLFWwindow* window; // reference to the window in the main sfgl class
	sfglShaderRenderer shader;	// Reference to the shader class

	unsigned int VBOs[2];	// Initializes the variable to store the current buffer - array for each triangle
	unsigned int VAOs[2];	// Initializes the Vertex array object - array for each triangle


	// Vertices variables

	// drawing triangles
	// First triangle
	float triOneVerts[9] =
	{
		-0.9f, -0.5f, 0.0f, // left
		-0.0f, -0.5f, 0.0f, // right
		-0.45f, 0.5f, 0.0f, // top
	};

	// second triangle
	float triTwoVerts[9] =
	{
		0.0f, -0.5f, 0.0f, // left
		0.9f, -0.5f, 0.0f, // right
		0.45f, 0.5f, 0.0f, // top
	};

	/////////////////////
	// Shader variables
	/////////////////////
	int shaderProgram;	// creates shader program object
	

	// shader sources
	// Use const char to store shader source
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
			"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";
	

	// -------------------------------------------
	// Private functions

	// Render shapes
	void setupTwoSeparateTrianglesToRender();

	void renderTriangle();

	/////////////////////
	// Main GL Renderer
	/////////////////////

	void glUpdate(); 		// Updates the gl renderer
	void processInput();	// glfw Input Checks	


};


#endif

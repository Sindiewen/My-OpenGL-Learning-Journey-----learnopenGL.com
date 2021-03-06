#include "headers/sfglRenderer.h"


/////////////////////
// Class Constructors
/////////////////////
// Default Constructor 
sfglRenderer::sfglRenderer()
{
	// Defines variable values
	
}


////////////////////////
// GLFW - Initialize renderer
////////////////////////
void sfglRenderer::initiateRenderer()
{
	// TODO: Add shader stuff here
	shader.assignShaderSource(vertexShaderSource, fragmentShaderSource);
	shader.compileShaders();
	shader.createShaderProgram(shaderProgram);

	// Updates the renderer
	glUpdate();
}


////////////////////////
// Setters and getters
////////////////////////
void sfglRenderer::setWindow(GLFWwindow* newwindow)
{
	window = newwindow;
}


// ----------------------------------------------------
// render shapes
void sfglRenderer::setupTriangleRender()
{
	// ---------------------------------------------------
	// 1: bind vertex array object
	glBindVertexArray(VAO);

	// 2: copy vertices array into the buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Binds the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(twoTriSbSVerts), twoTriSbSVerts, GL_STATIC_DRAW);	// Copies previous defined vertex data into the buffer memory

	// 3: set vertex attribute pointers
	// Linking vertex attributes: pg41 of LeanOpenGL Book
	// Determines how OpenGL should interpret the vertex data
	// 1: location 0 from vertex shader, 
	// 2: size of vertex is 3, 
	// 3: telling opengl that float is being used,
	// 4: Do not want the data to be normalized (allows anything between -1 - 1),
	// 5: determines the "stride distance" between vertex sets [x,y,z|x,y,z|x,y,z] each pair is 12 bytes (4 bytes per float)
	// so each stride costs 12 bytes
	// 6: Offset where the position data begins in the buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// Can unbind vertex array afterward to ensure no accedental modifications of the VAO.
	// Seems optional as this is a rare case anyway.
	glBindVertexArray(0);
}

void sfglRenderer::setupRectRenderer()
{
	// ----------------------------------------------
	// 1: bind vertex array object
	glBindVertexArray(VAO);	

	// 2: copy vertices array into the buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Binds the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);	// Copies previous defined vertex data into the buffer memory

	// 3: Copy indices into the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	// Binds the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	// Places the indices into the EBO

	// 4: Set vertex attribute pointers (Identical to the triangle above
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void sfglRenderer::renderTriangleSingle()
{
	// Draws the triangle using glDrawArrays
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void sfglRenderer::renderTriangleDouble()
{
	// NOTE:
	// Because the final value in the gldrawarrays is 6 instead of 3, this tells it that there are more
	// vertices. thus it will draw the extra vertices (first 3 verticest are the first triangle, 2nd set are the 2nd triangle).
	// Basically it defines how many vertices there are in the world
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

void sfglRenderer::renderRectSingle()
{
	// Draws rect using drawElements
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

// ----------------------------------------------------
// GLFW - Renderer Update
////////////////////////
void sfglRenderer::glUpdate()
{
	// Initialization(done once unless object changes)


	// Define graphics buffer
	glGenVertexArrays(1, &VAO);			// Generates vertex array
	glGenBuffers(1, &VBO);				// Generates the buffer
	glGenBuffers(1, &EBO);				// Generates the buffer - element buffer for indices
	
	// ---------------------------------------------------
	setupTriangleRender();	// Sets up the triangle renderer
	//setupRectRenderer();	// Sets up the rect to be rendered

	 
	while (!glfwWindowShouldClose(window))
	{
		// Check and process input
		processInput();



		// Renders to the viewport
		glClearColor(0.3f, 0.1f, 0.6f, 1.0f);
		// Clears the buffer readying for the next frame
		glClear(GL_COLOR_BUFFER_BIT);




		// Draw the shapes on screen
		glUseProgram(shaderProgram);	// use our shader program when we want to render object
		glBindVertexArray(VAO);

		// Draws shapes
		//renderTriangleSingle();
		renderTriangleDouble();
		//renderRectSingle();




		// Check for any call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}




void sfglRenderer::processInput()
{
	// Checks to see if the escape key has been pressed. If presed, set property to true to initiate window close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

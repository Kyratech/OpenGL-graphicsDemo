/* General includes */
#include <iostream>
#include <vector>

#include "Include/CubeGeometry.h"
#include "Include/PlaneGeomtery.h"
#include "Include/UVSphereGeometry.h"
#include "Include/Mesh.h"
#include "Include/GraphicsObject.h"
#include "Include/BLCamera.h"

/* Screen parameters */
const int width = 1200;
const int height = 600;

/* Functions to handle input */
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_movement(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);

/* Stuff to read the mouse input to move the camera */
GLfloat lastX = width / 2.0;
GLfloat lastY = height / 2.0;

bool firstMouseInput = true;

//Mouse button flags
bool middleMouse = false;

//Key pressed flags
bool keys[1024];

/* Set up the camera */
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

ThreeD_Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(void)
{
    /* Attempt to initialise GLFW3, the window manager */
	if(!glfwInit())
	{
		std::cout << "Failed to start GLFW3" << std::endl;
		exit(EXIT_FAILURE);
	}

	/* Set up the main window */
	GLFWwindow* window = glfwCreateWindow(width, height, "Coursework 1", NULL, NULL);
	if(!window)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/* Set the required callback functions */
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_movement);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	/*Draw wireframes */
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/* Set up GLEW before using any OpenGL functions */
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialise GLEW." << std::endl;
		return -1;
	}

	/* Tell OpenGL the size of the rendering window */
	glViewport(0, 0, width, height);

	/* Turn on depth testing to make stuff in front actually look like it's in front. */
	glEnable(GL_DEPTH_TEST);

    /* Load the shader program */
	Shader textureShader("Shaders/TexturedDefault.vert", "Shaders/TexturedDefault.frag");
	Shader phongShader("Shaders/UntexturedPhong.vert", "Shaders/UntexturedPhong.frag");

	/* Create a cube object*/
    GLfloat red[3] = {1.0f, 1.0f, 1.0f};
    Mesh cubeMesh(GetSpherePhong(10, 10, 1.0), "Images/crate.png", red);
    GraphicsObject cubeObject(&cubeMesh, glm::vec3(0.0f), glm::quat());

	/* Main loop */
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		/* Rendering commands */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        phongShader.Use();

		/* Generate the view matrix */
		glm::mat4 view;
		view = camera.GetViewMatrix();
		/* Generate the projection matrix */
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Fov), (GLfloat)width / (GLfloat)width, 0.1f, 100.0f);

		cubeObject.Draw(phongShader, view, projection);

		glfwSwapBuffers(window);
	}

	/* Terminate properly */
	glfwTerminate();
	return 0;
}

/*
* Record the states of keys when one changes
*/
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Check to see if a new key has been pressed or released
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.scroll_input(yoffset);
}

/*
* Record the changes in position of the mouse, use it to update the camera
*/
void mouse_movement(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouseInput)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouseInput = false;
	}

	//Difference between current moose position and previous
	GLfloat deltaX = xPos - lastX;
	GLfloat deltaY = lastY - yPos;

	//Update previous
	lastX = xPos;
	lastY = yPos;

	if (middleMouse)
	{
		if (keys[GLFW_KEY_LEFT_SHIFT])
			camera.pan_camera(deltaX, deltaY);
		else
			camera.move_camera(deltaX, deltaY);
	}
}

/*
* Record the state of the middle mouse when it changes
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		middleMouse = true;
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
		middleMouse = false;
}

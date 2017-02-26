/* General includes */
#include <iostream>
#include <vector>

//GUI
#include "Include/ImGUI/imgui.h"
#include "Include/ImGUI/imgui_impl_glfw_gl3.h"

#include "Include/CubeGeometry.h"
#include "Include/PlaneGeomtery.h"
#include "Include/UVSphereGeometry.h"
#include "Include/ConeGeometry.h"
#include "Include/TriangleMesh.h"
#include "Include/LineArray.h"
#include "Include/GraphicsObject.h"
#include "Include/OBJMesh.h"

/* Screen parameters */
const int width = 800;
const int height = 800;

/* Functions to handle input */
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_movement(GLFWwindow *window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);

/* Render functions */
void renderAnimation(std::vector<GraphicsObject> objects, Shader shader, glm::mat4 view, glm::mat4 projection);

/* Stuff to read the mouse input to move the camera */
GLfloat lastX = width / 2.0;
GLfloat lastY = height / 2.0;

bool firstMouseInput = true;

//Mouse button flags
bool middleMouse = false;

//Key pressed flags
bool keys[1024];



//For calculating delta time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//For scene selection
static int e = 0;
bool stillRunning = true;

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

    /* Set up ImGUI*/
	ImGui_ImplGlfwGL3_Init(window, false);
	bool show_guiWindow = true;

    /* Load the shader program */
	Shader textureShader("Shaders/TexturedDefault.vert", "Shaders/TexturedDefault.frag");
	Shader phongShader("Shaders/UntexturedPhong.vert", "Shaders/UntexturedPhong.frag");
	Shader unshadedShader("Shaders/UnshadedDefault.vert", "Shaders/UnshadedDefault.frag");

    /* Some colours to use later */
    GLfloat red[3] = {1.0f, 0.0f, 0.0f};
    GLfloat yellow[3] = {1.0f, 1.0f, 0.0f};
    GLfloat green[3] = {0.0f, 0.8f, 0.0f};
    GLfloat cyan[3] = {0.0f, 0.5f, 1.0f};
    GLfloat white[3] = {1.0f, 1.0f, 1.0f};

	/* Create a sphere object*/
	int segments = 30;
	int rings = 10;
	double radius = 2.0;
    TriangleMesh sphereMesh(GetSpherePhong(segments, rings, radius), "Images/crate.png", white);
    GraphicsObject sphereObject(&sphereMesh, glm::vec3(0.0f), glm::quat());
    /* Create the normals object for the sphere */
    Lines sphereNormalsMesh(GetSphereNormalLines(segments, rings, radius, 0.4), red);
    GraphicsObject sphereNormalsObject(&sphereNormalsMesh, glm::vec3(0.0f), glm::quat());

    /* Create some spheres for a solar system */
    std::vector<GraphicsObject> solarSystem;

    TriangleMesh sun(GetSpherePhong(20, 20, 1.0), "_", yellow);
    solarSystem.push_back(GraphicsObject(&sun, glm::vec3(0.0f), glm::quat()));

    TriangleMesh smallPlanet(GetSpherePhong(10, 10, 0.3), "_", red);
    solarSystem.push_back(GraphicsObject(&smallPlanet, glm::vec3(2.0f, 0.0f, 0.0f), glm::quat()));

    TriangleMesh smallCone(GetConePhong(10, 1.0, 0.5), "_", white);
    solarSystem.push_back(GraphicsObject(&smallCone, glm::vec3(2.0f, 0.0f, 0.0f), glm::quat()));

    TriangleMesh bigPlanet(GetSpherePhong(10, 10, 0.5), "_", cyan);
    solarSystem.push_back(GraphicsObject(&bigPlanet, glm::vec3(4.0f, 0.0f, 0.0f), glm::quat()));

    TriangleMesh moon(GetSpherePhong(5, 5, 0.1), "_", green);
    solarSystem.push_back(GraphicsObject(&moon, glm::vec3(4.8f, 0.0f, 0.0f), glm::quat()));

    TriangleMesh tinyPlanet(GetSpherePhong(8, 8, 0.2), "_", white);
    solarSystem.push_back(GraphicsObject(&tinyPlanet, glm::vec3(7.0f, 0.0f, 0.0f), glm::quat()));

    /* Create a textured box */
    TriangleMesh cubeMesh(GetCubeGeometry(3), "Images/glowstone.png", white);
    GraphicsObject cubeObject(&cubeMesh, glm::vec3(0.0f), glm::quat());

    /* Load in a obj file */
    OBJMesh thunderbirdMesh("Images/thunderbird.obj", "Images/thunderbird.png", white);
    GraphicsObject thunderbirdObject(&thunderbirdMesh, glm::vec3(0.0f), glm::quat());

	/* Main loop */
	while(!glfwWindowShouldClose(window) && stillRunning)
	{
	    //Calculate the time since the last frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		/*ImGUI UI code*/
		ImGui_ImplGlfwGL3_NewFrame();

		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Menu", &show_guiWindow);

		ImGui::Text("Scene selection");


        ImGui::RadioButton("A: Sphere", &e, 0);
        ImGui::RadioButton("B: Sphere normals", &e, 1);
        ImGui::RadioButton("C: Shaded sphere", &e, 2);
        ImGui::RadioButton("D: Animated scene", &e, 3);
        ImGui::RadioButton("E: Textured box", &e, 4);
        ImGui::RadioButton("F: Imported mesh", &e, 5);

		ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
		ImGui::End();

		/* Rendering commands */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Generate the view matrix */
		glm::mat4 view;
		view = camera.GetViewMatrix();
		/* Generate the projection matrix */
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Fov), (GLfloat)width / (GLfloat)width, 0.1f, 100.0f);

		/* Scene switcher */
		//Get it? Because it's a switch statement.
		switch(e)
		{
        case 0:
            /*Draw wireframes */
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            unshadedShader.Use();
            sphereObject.Draw(unshadedShader, view, projection);
            break;
        case 1:
            /*Draw wireframes */
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            unshadedShader.Use();
            sphereObject.Draw(unshadedShader, view, projection);
            sphereNormalsObject.Draw(unshadedShader, view, projection);
            break;
        case 2:
            phongShader.Use();
            sphereObject.Draw(phongShader, view, projection);
            break;
        case 3:
            renderAnimation(solarSystem, unshadedShader, view, projection);
            break;
        case 4:
            textureShader.Use();
            cubeObject.Draw(textureShader, view, projection);
            break;
        case 5:
            textureShader.Use();
            thunderbirdObject.Draw(textureShader, view, projection);
		}
		//...sorry.

        // ImGui functions end here
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		ImGui::Render();

		glfwSwapBuffers(window);
	}

	/* Terminate properly */
	glfwTerminate();
	return 0;
}

/*
 * Draw a solar system
 * Order: Sun - Small planet - Large planet - LP moon - Tiny planet
 */
void renderAnimation(std::vector<GraphicsObject> objects, Shader shader, glm::mat4 view, glm::mat4 projection)
{
    if(objects.size() >= 6)
    {
        /*Draw wireframes */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader.Use();

        glm::mat4 smallPlanet_Model;
        smallPlanet_Model = glm::rotate(smallPlanet_Model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        smallPlanet_Model = glm::translate(smallPlanet_Model, glm::vec3(2.0f, 0.0f, 0.0f));
        //smallPlanet_Model = glm::rotate(smallPlanet_Model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 1.0f));
        //smallPlanet_Model = glm::rotate(smallPlanet_Model, (float)glfwGetTime() * 10, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 smallCone_Model;
        smallCone_Model = glm::rotate(smallCone_Model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        smallCone_Model = glm::translate(smallCone_Model, glm::vec3(0.0f, -2.0f, 0.0f));

        glm::mat4 largePlanet_Model;
        largePlanet_Model = glm::rotate(largePlanet_Model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        largePlanet_Model = glm::translate(largePlanet_Model, glm::vec3(4.0f, 0.0f, 0.0f));

        glm::mat4 moon_Model;
        moon_Model = glm::rotate(largePlanet_Model, (float)glfwGetTime() * glm::radians(60.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
        moon_Model = glm::translate(moon_Model, glm::vec3(0.8f, 0.0f, 0.0f));

        glm::mat4 tinyPlanet_Model;
        tinyPlanet_Model = glm::rotate(tinyPlanet_Model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        tinyPlanet_Model = glm::rotate(tinyPlanet_Model, (float)glfwGetTime() * glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        tinyPlanet_Model = glm::translate(tinyPlanet_Model, glm::vec3(7.0f, 0.0f, 0.0f));

        objects[0].Draw(shader, view, projection);
        objects[1].Draw(shader, smallPlanet_Model, view, projection);
        objects[2].Draw(shader, smallCone_Model, view, projection);
        objects[3].Draw(shader, largePlanet_Model, view, projection);
        objects[4].Draw(shader, moon_Model, view, projection);
        objects[5].Draw(shader, tinyPlanet_Model, view, projection);
    }
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

		//Additional checks for scene selection
		if(keys[GLFW_KEY_A])
            e = 0;
        else if(keys[GLFW_KEY_B])
            e = 1;
        else if(keys[GLFW_KEY_C])
            e = 2;
        else if(keys[GLFW_KEY_D])
            e = 3;
        else if(keys[GLFW_KEY_E])
            e = 4;
        else if(keys[GLFW_KEY_Q] || keys[GLFW_KEY_ESCAPE])
            stillRunning = false; //Set the flag to close next frame
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

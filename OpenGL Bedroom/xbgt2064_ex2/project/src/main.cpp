#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <vector>
#include <iostream>

#include "framework/app.h"
#include "framework/camera_flying.h"
#include "angle_util/matrix.h"
#include "angle_util/vector.h"
#include "scene_ex2.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "XBGT2064 [Exercise 2]"

#pragma region Draw Modes

/*
*  These additions are utilities to help you debug your code,
*  to ensure your polygons are in correct order (CCW), and to
*  allow the lecturer to view your 3D scene in wireframe or fill.
*/

struct DrawModeGroup {
	virtual const char* getModeName() = 0;
	virtual void apply() = 0;
};

struct DrawMode_Default : DrawModeGroup
{
	const char* getModeName() { return "[FrontFace: Fill] [Backface: Fill]"; }

	void apply() {
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
};

struct DrawMode_WireframeBackFace : DrawModeGroup
{
	const char* getModeName() { return "[FrontFace: Fill] [Backface: Wireframe]"; }

	void apply() {
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
	}
};

struct DrawMode_FrontFaceOnly : DrawModeGroup
{
	const char* getModeName() { return "[FrontFace: Fill] [Backface: Culled]"; }

	void apply() {
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
};

struct DrawMode_Wireframe : DrawModeGroup
{
	const char* getModeName() { return "[FrontFace: Wireframe] [Backface: Wireframe]"; }

	void apply() {
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
};

std::vector<DrawModeGroup*> drawModes = {
	new DrawMode_WireframeBackFace(),
	new DrawMode_Default(),
	new DrawMode_FrontFaceOnly(),
	new DrawMode_Wireframe()
};

unsigned int drawModeIndex = 0;
DrawModeGroup* currentDrawMode;

void setDrawMode(unsigned int index)
{
	// ensure mode is within drawModes range
	drawModeIndex = index % drawModes.size();
	currentDrawMode = drawModes[drawModeIndex];
	std::cout << "Draw Mode: " << currentDrawMode->getModeName() << std::endl;
}

#pragma endregion

int currentWindowWidth, currentWindowHeight;
static int lastX = -1, lastY = -1;
bool isWindowFocused = false;

CameraFlying gCamera;

GLFWwindow* initializeWindow(int width, int height, const char* title);
void processKeyboardInput(GLFWwindow* window, const float deltaTime);
void onFramebufferResized(GLFWwindow* window, int width, int height);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseCursorMove(GLFWwindow* window, double x, double y);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	GLFWwindow* window = initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	if (window == nullptr) exit(EXIT_FAILURE);

	App::init(window);

	// Initialize OpenGL
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	// Initialize camera
	gCamera.setPosition(10.0f, 6.0f, 10.0f);
	gCamera.lookAtPoint(Vector3(0.0, 2.0, 0.0));

	std::cout << "Press F1 to toggle Polygon mode." << std::endl;
	std::cout << "WASD to fly around, and mouse to orient" << std::endl;

	// Initialize demo.
	SceneBase* scene = new SceneEx2();
	scene->init();

	// Set initial draw mode
	setDrawMode(0);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		App::processTime(glfwGetTime());
		App::processInput();

		// CameraFlying keyboard controls
		processKeyboardInput(window, App::getDeltaTime());

		scene->update();

		// OpenGL rendering goes here...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply draw mode before scene drawing
		currentDrawMode->apply();

		scene->draw(gCamera.getViewMatrix());

		// Swap front and back rendering buffers
		glfwSwapBuffers(window);

		// Check for events and continue with the next loop iteration
		glfwPollEvents();
	}

	scene->deinit();
	delete scene;

	// Close window and terminate GLFW
	glfwTerminate();
}

GLFWwindow* initializeWindow(int width, int height, const char* title)
{
	// Initialize the GLFW library
	if (!glfwInit())
		return nullptr;

	// Set the minimum OpenGL version for next window creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Create a window with an OpenGL 2.1 context
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	// Make the window's OpenGL context current
	// This means OpenGL calls will be applied on the window's OpenGL context
	// and not any other window (if the program uses multi-window)
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	// This makes OpenGL 2.1 API available for usage!
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return nullptr;
	}

	// Hook callback functions
	glfwSetFramebufferSizeCallback(window, onFramebufferResized);
	glfwSetKeyCallback(window, onKeyCallback);
	glfwSetMouseButtonCallback(window, onMouseButtonCallback);
	glfwSetCursorPosCallback(window, onMouseCursorMove);

	glfwSwapInterval(1);

	// Call this once to set up camera projection.
	onFramebufferResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	return window;
}

void processKeyboardInput(GLFWwindow* window, const float deltaTime)
{
	if (isWindowFocused)
	{
		Vector3 translate(0.0f, 0.0f, 0.0f);
		float mv = deltaTime;

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) mv *= 4.0f;

		if (glfwGetKey(window, 'A')) translate.x -= mv;
		if (glfwGetKey(window, 'D')) translate.x += mv;
		if (glfwGetKey(window, 'W')) translate.z -= mv;
		if (glfwGetKey(window, 'S')) translate.z += mv;
		if (glfwGetKey(window, 'Q')) translate.y += mv;
		if (glfwGetKey(window, 'E')) translate.y -= mv;
		gCamera.translateLocal(translate.x, 0.0f, translate.z);
		gCamera.translate(0, translate.y, 0);
	}
}

void onFramebufferResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One
	currentWindowWidth = width;
	currentWindowHeight = height;

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate perspective projection
	float aspect = (float)width / (float)height;
	float fov = 45.0f;
	float zNear = 0.1f;
	float zFar = 100.0f;
	Matrix4 projection = Matrix4::perspective(fov, aspect, zNear, zFar);
	glLoadMatrixf(projection.data);						// Upload the calculated matrix to the projection matrix

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		setDrawMode(drawModeIndex + 1);
	}

	// Escape when focused releases mouse
	// Escape when unfocused exits application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (isWindowFocused)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			lastX = currentWindowWidth * 0.5;
			lastY = currentWindowHeight * 0.5;
			glfwSetCursorPos(window, lastX, lastY);
			isWindowFocused = false;
		}
		else
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (!isWindowFocused)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		isWindowFocused = true;
	}
}

void onMouseCursorMove(GLFWwindow* window, double x, double y)
{
	if (!isWindowFocused) {
		lastX = x; lastY = y;
		return;
	}

	if (lastX == -1 && lastY == -1)
	{
		lastX = x;
		lastY = y;
		return;
	}

	int offsetX = lastX - x;
	int offsetY = lastY - y;
	lastX = x; lastY = y;

	gCamera.rotate(offsetX * 0.1f, Vector3(0.0f, 1.0f, 0.0f));
	gCamera.rotateLocal(offsetY * 0.1f, Vector3(1.0f, 0.0f, 0.0f));
}
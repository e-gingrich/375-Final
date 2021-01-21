/// \file Main.cpp
/// \brief Declaration of main function, helper functions, and helper classes.
/// \author Gary M. Zopetti, Chad Hogg, && Ethan Gingrich
/// \version A02
///
/// This is a fairly simple program that uses OpenGL 3.3 to draw a scene.


/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>

/******************************************************************/
// Local includes
#include "RealOpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "MyScene.hpp"
#include "Camera.hpp"
#include "KeyBuffer.hpp"
#include "Transform.hpp"
#include "MouseBuffer.hpp"

/******************************************************************/
// Global variables

/// \brief The OpenGLContext through which all OpenGL calls will be made.
///
/// This should be allocated in ::init and deallocated in ::releaseGlResources.
OpenGLContext* g_context;

/// \brief A collection of the Meshes for each of the objects we want to draw.
///
/// This will be filled in initScene, and its contents need to be deleted in
///   releaseGlResources.
Scene* myScene;

/// \brief The ShaderProgram that transforms and lights the primitives.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_colorShader;

ShaderProgram* g_normShader;

/// \brief The Camera that views the Scene.
///
/// This should be allocated in ::initCamera and deallocated in
///   ::releaseGlResources.
Camera* g_camera;

/// \brief The keyBuffer that keeps track of which key is being pressed
KeyBuffer* g_keyBuffer;

MouseBuffer* g_mouseBuffer;

/// the field of vision and aspect ratio
double fov, aspectRatio;

/******************************************************************/
// Function prototypes

/// \brief Initializes all libraries and global variables.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
///
/// This should be called once at the beginning of the application.
void
init (GLFWwindow*& window);

/// \brief Initializes the GLFW library.  Should only be called by ::init.
void
initGlfw ();

/// \brief Initializes the GLEW library.  Should only be called by ::init.
void
initGlew ();

/// \brief Creates and initializes the window.  Should only be called by
///   ::init.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
void
initWindow (GLFWwindow*& window);

/// \brief Re-renders the window.  This should be called whenever the window
///   size changes.
/// \param[in] window The GLFWwindow to reset.
/// \param[in] width The new width of the window.
/// \param[in] height The new height of the window.
void
resetViewport (GLFWwindow* window, int width, int height);

/// \brief Creates the Scene.  Should only be called by ::init.
void
initScene ();

/// \brief Creates the ShaderProgram.  Should only be called by ::init.
void
initShaders ();

/// \brief Initializes the Camera.  Should only be called by ::init.
void
initCamera ();

/// \brief Moves geometric objects around using game logic.  This should be
///   called for every frame.
/// \param[in] time The number of seconds since the previous update.
void
updateScene (double time);

/// \brief Draws the Scene onto the window.  This should be called for every
///   frame.
/// \param[in] window The GLFWwindow to draw in.
void
drawScene (GLFWwindow* window);

/// \brief Responds to any user input.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] key The key that was pressed or released.
/// \param[in] scanCode The system-specific scancode of the key.
/// \param[in] action What happened to the key.
/// \param[in] modifiers Which modifier keys were depressed.
void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers);

/// \brief Cleans up all resources as program exits.
void
releaseGlResources ();

/// \brief Prints an error from GLFW.
/// \param[in] error The error code.
/// \param[in] description The error text.
void
outputGlfwError (int error, const char* description);

void
processKeys ();

void
recordMouseMvmt (GLFWwindow* window, double xpos, double ypos);

void
recordMouseButtons (GLFWwindow* window, int button, int action, int mods);

void
changePerspective (std::string projectionType, double fovOrLeft, double aspRatioOrRight,
      double nearZ, double farZ, double bottom = 0, double top = 0);

void
recordScroll (GLFWwindow* window, double xoffset, double yoffset);
/******************************************************************/

/// \brief Runs our program.
/// \param[in] argc The number of command-line arguments, which we ignore.
/// \param[in] argv The array of command-line-arguments, which we ignore.
int
main (int argc, char* argv[])
{
  g_keyBuffer = new KeyBuffer ();
  g_mouseBuffer = new MouseBuffer ();
  GLFWwindow* window;
  init (window);

  // Game/render loop
  double previousTime = glfwGetTime ();
  while (!glfwWindowShouldClose (window))
  {
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
    processKeys ();
  }

  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
  g_context = new RealOpenGLContext ();
  // Always initialize GLFW before GLEW
  initGlfw ();
  initWindow (window);
  initGlew ();
  initShaders ();
  initCamera ();
  initScene ();
}

/******************************************************************/

void
initGlfw ()
{
  glfwSetErrorCallback (outputGlfwError);
  if (!glfwInit ())
  {
    fprintf (stderr, "Failed to init GLFW -- exiting\n");
    exit (EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow (800, 600, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf (stderr, "Failed to init the window -- exiting\n");
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }
  glfwSetWindowPos (window, 200, 100);

  glfwMakeContextCurrent (window);
  // Swap buffers after 1 frame
  glfwSwapInterval (1);
  glfwSetKeyCallback (window, recordKeys);
  glfwSetCursorPosCallback (window, recordMouseMvmt);
  glfwSetMouseButtonCallback (window, recordMouseButtons);
  glfwSetScrollCallback (window, recordScroll);
  glfwSetFramebufferSizeCallback (window, resetViewport);

  // Specify background color
  g_context->clearColor (0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  g_context->enable (GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  g_context->enable (GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  g_context->frontFace (GL_CCW);
  g_context->cullFace (GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  g_context->viewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
	     " (%s).\n",
	     glewGetErrorString (status));
    exit (EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString (GLEW_VERSION);
  fprintf (stderr, "Using GLEW version %s.\n", version);
  version = g_context->getString (GL_VERSION);
  fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  aspectRatio = width/height;
  g_camera->setProjectionSymmetricPerspective (fov, aspectRatio, 0.01, 40.0);
  g_context->viewport (0, 0, width, height);
}

/******************************************************************/

void
initScene ()
{
  // Initialize a new Scene
  myScene = new MyScene(g_context, g_colorShader, g_normShader);
}

/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_colorShader = new ShaderProgram (g_context);
  g_colorShader->createVertexShader ("Vec3.vert");
  g_colorShader->createFragmentShader ("Vec3.frag");
  g_colorShader->link ();

  g_normShader = new ShaderProgram (g_context);
  g_normShader->createVertexShader ("Vec3Norm.vert");
  g_normShader->createFragmentShader ("Vec3.frag");
  g_normShader->link ();
}

/******************************************************************/

void
initCamera ()
{
  fov = 50;
  // Define the projection, which will remain constant
  aspectRatio = 1200.0f / 900;
  // Near plane
  float nearZ = 0.01f;
  // Far plane
  float farZ = 40.0f;
  // Camera position
  Vector3 position (0, 0, 12.0f);
  // Create a new camera
  g_camera = new Camera (position, Vector3(0, 0, 1.0f), nearZ, farZ, aspectRatio, fov);
}

/******************************************************************/

void
updateScene (double time)
{
  // No updates in this simple program.
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{
  g_context->clear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const Transform modelView = g_camera->getViewMatrix();
  const Matrix4 projectionView = g_camera->getProjectionMatrix();

  // draw all Meshes in this Scene
  myScene->draw (modelView, projectionView);
  glfwSwapBuffers (window);
}

/******************************************************************/

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  } 
  else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
  {
    myScene->activatePreviousMesh ();
    myScene->getActiveMesh ();
  }
  else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
  {
    myScene->activateNextMesh ();
    myScene->getActiveMesh ();
  }
  else if (key == GLFW_KEY_P && action == GLFW_PRESS)
  {
    changePerspective ("Symm", fov, aspectRatio, 0.01, 40.0);
  }
  else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
  {
    changePerspective ("Asymm", -1.0, 1.0, 0.01, 30.0, -1.3, 1.3);
  }
  else if (key == GLFW_KEY_O && action == GLFW_PRESS)
  {
    changePerspective ("Ortho", -20.0, 20.0, 0.01, 40.0, -15.0, 15.0);
  }
  else if (action == GLFW_PRESS)
  {
    g_keyBuffer->setKeyDown(key);
  } 
  else if (action == GLFW_RELEASE)
  {
    g_keyBuffer->setKeyUp(key);
  }
}

/******************************************************************/

void
recordMouseMvmt (GLFWwindow* window, double xpos, double ypos)
{
  const float ROTATION_DELTA = 1.0f;
  double x, y;

  g_mouseBuffer->setPosition (xpos, ypos);
  glfwGetCursorPos (window, &x, &y);
  if (g_mouseBuffer->getLeftButton () == true && (x - g_mouseBuffer->getX ()) > 0) 
    g_camera->yaw (ROTATION_DELTA);
    //4Debug: std::cout << g_camera->getViewMatrix () << "\n";
  else if (g_mouseBuffer->getLeftButton () == true && (x - g_mouseBuffer->getX ()) < 0)
    g_camera->yaw (-ROTATION_DELTA);
  else if (g_mouseBuffer->getLeftButton () == true && (y - g_mouseBuffer->getY ()) > 0)
    g_camera->pitch (ROTATION_DELTA);
  else if (g_mouseBuffer->getLeftButton () == true && (y - g_mouseBuffer->getY ()) < 0)
    g_camera->pitch (-ROTATION_DELTA);
  if (g_mouseBuffer->getRightButton () == true && (x - g_mouseBuffer->getX ()) > 0)
    g_camera->roll (ROTATION_DELTA);
  else if (g_mouseBuffer->getRightButton () == true && (x - g_mouseBuffer->getX ()) < 0)
    g_camera->roll (-ROTATION_DELTA);
}

/******************************************************************/

void
recordMouseButtons (GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
  {
    g_mouseBuffer->setRightButton (true);
  }
  else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
  {
    g_mouseBuffer->setRightButton (false);
  }
  else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  {
    g_mouseBuffer->setLeftButton (true);
  }
  else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
  {
    g_mouseBuffer->setLeftButton (false);
  }
}

/******************************************************************/

void
recordScroll (GLFWwindow* window, double xoffset, double yoffset)
{
  changePerspective ("Symm", fov, aspectRatio, 0.01, 40.0);

  if (yoffset > 0 && fov < 120)
  {
    changePerspective ("Symm", fov += 2, aspectRatio, 0.01, 40.0);
  }
  else if (yoffset < 0 && fov > 1)
  {
    changePerspective ("Symm", fov -= 2, aspectRatio, 0.01, 40.0);
  } 
}

/******************************************************************/

void
processKeys ()
{
  const float MOVEMENT_DELTA = 0.05f;
  const float ROTATION_DELTA = 1.00f;

  if (g_keyBuffer->isKeyDown(GLFW_KEY_W))
    g_camera->moveBack(-MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_S))
    g_camera->moveBack(MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_A))
    g_camera->moveRight(-MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_D))
    g_camera->moveRight(MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_C))
    g_camera->moveUp(-MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_F))
    g_camera->moveUp(MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_R))
    g_camera->resetPose();  
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_J))
    myScene->getActiveMesh ()->yaw (ROTATION_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_L))
    myScene->getActiveMesh ()->yaw(-ROTATION_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_I))
    myScene->getActiveMesh ()->pitch(ROTATION_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_K))
    myScene->getActiveMesh ()->pitch(-ROTATION_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_N))
    myScene->getActiveMesh ()->roll(ROTATION_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_M))
    myScene->getActiveMesh ()->roll(-ROTATION_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_1))
    myScene->getActiveMesh ()->moveRight (MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_2))
    myScene->getActiveMesh ()->moveRight (-MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_3))
    myScene->getActiveMesh ()->moveUp (MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_4))
    myScene->getActiveMesh ()->moveUp (-MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_5))
    myScene->getActiveMesh ()->moveBack (MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_6))
    myScene->getActiveMesh ()->moveBack (-MOVEMENT_DELTA);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_7))
    myScene->getActiveMesh ()->scaleLocal (1.01f);
  else if (g_keyBuffer->isKeyDown(GLFW_KEY_8))
    myScene->getActiveMesh ()->scaleLocal (0.99f);
} 

/******************************************************************/

/// \brief Changes the perspective type of the Projection Matrix
/// \param[in] projectionType The type of projection we are switching to
/// \param[in] fovOrLeft Ethier the field of vision or the leftmost x value of the projection, dependent on the projection
/// \param[in] aspRatioOrRight Either the aspect ratio or the rightmost x value of the projection
/// \param[in] nearZ The distance to the near plane
/// \param[in] farZ The distance to the far plane
/// \param[in] bottom The bottommost y value on the projection, default set to 0.
/// \param[in] top The topmost y value on the projection, default set to 0.
void
changePerspective (std::string projectionType, double fovOrLeft, double aspRatioOrRight,
      double nearZ, double farZ, double bottom, double top)
{
  if (projectionType == "Symm")
  {
    g_camera->setProjectionSymmetricPerspective (fovOrLeft, aspRatioOrRight, nearZ, farZ);
  }
  else if (projectionType == "Asymm")
  {
    g_camera->setProjectionAsymmetricPerspective (fovOrLeft, aspRatioOrRight, top, bottom, nearZ, farZ);
  }
  else if (projectionType == "Ortho")
  {
    g_camera->setProjectionOrthographic (fovOrLeft, aspRatioOrRight, top, bottom, nearZ, farZ);
  }
}

/******************************************************************/

void
releaseGlResources ()
{
  delete myScene;
  delete g_camera;
  delete g_colorShader;
  delete g_normShader;
  delete g_context;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/

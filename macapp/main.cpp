/* Ask for an OpenGL Core Context */
#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"
#include "CEGUIView.h"

int main(int argc, char** argv)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if ( !glfwInit() )
    {
        return -1;
    }
    
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.2 context on OS X */
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RED_BITS,   GLFW_DONT_CARE);
    glfwWindowHint(GLFW_GREEN_BITS, GLFW_DONT_CARE);
    glfwWindowHint(GLFW_BLUE_BITS,  GLFW_DONT_CARE);
    glfwWindowHint(GLFW_ALPHA_BITS, 0);
#endif
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow( 1280, 720, "Hello World", NULL, NULL );
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(0);

    CEGUIView::getInstance(window);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

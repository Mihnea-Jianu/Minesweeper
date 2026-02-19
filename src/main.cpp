#include <GLFW/glfw3.h>

#include "game.h"

_game game;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	double windowI, windowJ;

    glfwGetCursorPos(window, &windowJ, &windowI);

    _position position;

    position.i = globalVerticalOffset + windowI * windowPX / px;
    position.j = globalHorizontalOffset + windowJ * windowPX / px;

    game.processMouseEvent(button, action, position);
}

int main(void)
{
    game.init();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSize, windowSize, "Minesweeper", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Resize the window */
    int resizeHeight = windowSize - unusedVerticalSpace   * px / windowPX;
    int resizeWidth  = windowSize - unusedHorizontalSpace * px / windowPX;
    glfwSetWindowSize(window, resizeWidth, resizeHeight);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set buffer swap interval to 1 */
    glfwSwapInterval(1);

    /* Set mouse button callback */
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        game.drawSprites();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Wait for and process events */
        glfwWaitEventsTimeout(1);

        /* Upade game timer sprite */
        game.timer.loadSprite();
    }

    glfwTerminate();
    return 0;
}
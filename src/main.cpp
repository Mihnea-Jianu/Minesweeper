#include <GLFW/glfw3.h>

#include "utilities.h"
#include "game.h"

Game game;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	double windowI, windowJ;

    glfwGetCursorPos(window, &windowJ, &windowI);

    Position position;

    position.i = globalVerticalOffset   + windowI * windowPX / px;
    position.j = globalHorizontalOffset + windowJ * windowPX / px;

    game.processMouseEvent(button, action, position);
}

int main()
{
    game.init();

    GLFWwindow* window;

    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(windowSize, windowSize, "Minesweeper", NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    int resizeHeight = windowSize - unusedVerticalSpace   * px / windowPX;
    int resizeWidth  = windowSize - unusedHorizontalSpace * px / windowPX;

    glfwSetWindowSize(window, resizeWidth, resizeHeight);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        game.drawSprites();
        
        glfwSwapBuffers(window);
        glfwWaitEventsTimeout(1);

        game.timer.loadSprite();
    }

    glfwTerminate();
}
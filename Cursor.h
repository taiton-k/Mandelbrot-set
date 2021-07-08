#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Cursor
{
    private :

        //ウィンドウのポインタ
        GLFWwindow *const window;

        //1フレーム経ったかの判定に使用
        GLboolean frame=0;
    public :

        //コンストラクタ
        //WINDOW :ウィンドウのポインタ
        Cursor(GLFWwindow *const WINDOW)
            :window(WINDOW)
        {}

        //現在のカーソルの座標
        GLdouble mCoordinate[2];

        //wCoordinateに座標を格納する
        void setMouseCoordinate()
        {
            glfwGetCursorPos(window,&mCoordinate[0],&mCoordinate[1]);
        }

        //マウスが左クリックされたかどうか
        bool mLPorR(bool flag)
        {
            if(flag)
                return (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);
            else
                if(frame==1)
                {
                    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
                        frame=false;
                    return false;
                    }
                else
                {
                    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
                        frame=true;
                    return (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);
                }
        }

        //マウスが右クリックされたかどうか
        bool mRPorR(bool flag)
        {
            if(flag)
                return (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS);
            else
                if(frame==1)
                {
                    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
                        frame=false;
                    return false;
                    }
                else
                {
                    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
                        frame=true;
                    return (glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS);
                }
        }

};

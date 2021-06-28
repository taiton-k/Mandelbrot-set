#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

//ウィンドウ関連の処理
class Window
{
    private :

        //ウィンドウのハンドル
        GLFWwindow *const window;

    public :

        //コンストラクタ
        Window(int width = 1280, int height = 720, const char *title = "Mandelbrot")
            : window(glfwCreateWindow(width, height, title, NULL,NULL))
        {
            if(window == NULL)
            {
                //ウィンドウの作成に失敗
                cerr << "ウィンドウの作成に失敗しました。Can't create GLFW window." << endl;
                exit(1);
            }

            //作成したウィンドウをOpenGLの処理対象にする
            glfwMakeContextCurrent(window);

            //GLEWの初期化
            glewExperimental = GL_TRUE;
            if(glewInit() != GLEW_OK)
            {
                //もし失敗したら
                cerr << "GLEWの初期化に失敗しました。Can't initialize GLEW." << endl;
                exit(1);
            }

            //垂直同期のタイミングを指定する
            glfwSwapInterval(1);            
        }

        //デストラクタ
        virtual ~Window()
        {
            glfwDestroyWindow(window);
        }

        //描画ループの継続判定
        explicit operator bool ()
        {
            //イベントを取り出す
            glfwPollEvents();

            //ウィンドウを閉じる必要がなければ true を返す
            return !glfwWindowShouldClose(window);
        }

        void swapBuffers() const
        {
            //カラーバッファを入れ替える
            glfwSwapBuffers(window);
        }
};

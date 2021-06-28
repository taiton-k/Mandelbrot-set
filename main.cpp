#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Window.h"
#include "Cursor.h"
#include "Mandelbrot.h"
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

int main()
{
    //GLFWの初期化
    if(glfwInit() == GL_FALSE)
    {
        //もし失敗したら
        cerr << "GLFWの初期化に失敗しました。Can't initialize GLFW." << endl;
        return 1;
    }

    //プログラムの終了時処理の登録
    atexit(glfwTerminate);

    //OpenGL Version 3.2 Core Profile を選択する
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //ウィンドウをリサイズ禁止にする
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //ステレオモードにする
    //glfwWindowHint(GLFW_STEREO, GL_TRUE);

    //ウィンドウの作成
    Window window;

    //背景色の指定
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //ビューポートの設定
    //glViewport()

    //プログラムオブジェクトを作成する
    Shader shader("point.vert","point.frag");

    //Mandelbrotクラスの宣言
    Mandelbrot mandelbrot;

    //ウィンドウが開いている間繰り返す
    while(window)
    {
        //ウィンドウのクリア
        glClear(GL_COLOR_BUFFER_BIT);

        //シェーダプログラムの使用開始
        glUseProgram(shader.program);

        //ここから描画処理
        //
        //
        //図形の描画
        mandelbrot.draw();
        //
        //ここまで描画処理

        //カラーバッファを入れ替える
        window.swapBuffers();

        //usleep(100000);
    }
}

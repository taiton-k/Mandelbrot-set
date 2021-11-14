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

    // uniform 変数 size の場所を格納する変数
    GLuint usize = glGetUniformLocation(shader.program, "size");

    // uniform 変数 origin の場所を格納する変数
    GLuint uorigin = glGetUniformLocation(shader.program, "origin");

    // uniform 変数 order の場所を格納する変数
    GLuint uorder = glGetUniformLocation(shader.program, "order");

    //Mandelbrotクラスの宣言
    Mandelbrot mandelbrot;

    //uniform変数sizeに渡す値
    GLint size = 320;

    //uniform変数originに渡す値
    GLint origin[2] = {0,0};

    int order=120;

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

        if(window.key[0]==true)
        {
            origin[0]+=window.point[0];
            origin[1]-=window.point[1];
            size*=2;
            origin[0]*=2;
            origin[1]*=2;
        }            
        if(window.key[1]==true)
        {
            origin[0]+=window.point[0];
            origin[1]-=window.point[1];
            size/=2;
            origin[0]/=2;
            origin[1]/=2;
        }
        if(window.key[2]==true)
            origin[1]+=150;
        if(window.key[3]==true)
            origin[1]-=150;
        if(window.key[4]==true)
            origin[0]-=150;
        if(window.key[5]==true)
            origin[0]+=150;
        if(window.key[6]==true)
        {
            size*=2;
            origin[0]*=2;
            origin[1]*=2;
        }
        if(window.key[7]==true)
        {
            size/=2;
            origin[0]/=2;
            origin[1]/=2;
        }
        glUniform1i(usize,size);
        glUniform2i(uorigin,origin[0],origin[1]);
        if(window.key[10]==true)
            cin >> order;
        glUniform1i(uorder,order);
        mandelbrot.draw();

        //
        //ここまで描画処理
        //cout << window.point[0] << ' ' << window.point[1] << ' ' << size << endl;
        //カラーバッファを入れ替える
        window.swapBuffers();

        

        //usleep(100000);
    }
}

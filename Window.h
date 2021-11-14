#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

//ウィンドウ関連の処理（カーソル、キーの処理も含まれる
class Window
{
    private :

        //キーが前フレームでも押されてたか
        bool keystate[11] ={0,0,0,0,0,0,0,0,0,0,0};

    public :

        //コンストラクタ
        Window(int width = 1440, int height = 900, const char *title = "Mandelbrot")
            :window(glfwCreateWindow(width, height, title, NULL,NULL))
            ,point{0,0}
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

        //ウィンドウのハンドル
        GLFWwindow *const window;

        //カーソルの座標
        GLint point[2];
        
        //キーが押されたかどうか
        //0,1:左右クリック 2,3,4,5:上下左右キー 6,7:エンター、バックスペース,1,2,space
        bool key[11];

        //描画ループの継続判定
        explicit operator bool ()
        {
            //イベントを取り出す
            glfwWaitEvents();

            //カーソルの座標
            double x,y;
            glfwGetCursorPos(window, &x,&y);
            point[0]=x-640;
            point[1]=y-360;

            //マウスの状態を調べる
            //key配列の操作
            if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
            {
                if(keystate[0]==false)
                {
                    key[0]=true;
                    keystate[0]=true;
                }
                else
                    key[0]=false;
            }
            else 
                if(keystate[0]==true)
                    {
                        key[0]=false;
                        keystate[0]=false;
                    }
            if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
            {
                if(keystate[1]==false)
                {
                    key[1]=true;
                    keystate[1]=true;
                }
                else
                    key[1]=false;
            }
            else
                if(keystate[1]==true)
                {
                    key[1]=false;
                    keystate[1]=false;
                }

            //方向キーの状態を調べる
            if(glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)
            {
               if(keystate[2]==false)
                {
                    key[2]=true;
                    keystate[2]=true;
                }
                else
                    key[2]=false;
            }
            else
                if(keystate[2]==true)
                {
                    key[2]=false;
                    keystate[2]=false;
                }
            if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)
            {
               if(keystate[3]==false)
                {
                    key[3]=true;
                    keystate[3]=true;
                }
                else
                    key[3]=false;
            }
            else
                if(keystate[3]==true)
                {
                    key[3]=false;
                    keystate[3]=false;
                }
            if(glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS)
            {
               if(keystate[4]==false)
                {
                    key[4]=true;
                    keystate[4]=true;
                }
                else
                    key[4]=false;
            }
            else
                if(keystate[4]==true)
                {
                    key[4]=false;
                    keystate[4]=false;
                }
            if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS)
            {
               if(keystate[5]==false)
                {
                    key[5]=true;
                    keystate[5]=true;
                }
                else
                    key[5]=false;
            }
            else
                if(keystate[5]==true)
                {
                    key[5]=false;
                    keystate[5]=false;
                }

            //エンターキーとバックスペースキーの状態を調べる
            if(glfwGetKey(window,GLFW_KEY_ENTER)==GLFW_PRESS)
            {
               if(keystate[6]==false)
                {
                    key[6]=true;
                    keystate[6]=true;
                }
                else
                    key[6]=false;
            }
            else
                if(keystate[6]==true)
                {
                    key[6]=false;
                    keystate[6]=false;
                }
            if(glfwGetKey(window,GLFW_KEY_BACKSPACE)==GLFW_PRESS)
            {
               if(keystate[7]==false)
                {
                    key[7]=true;
                    keystate[7]=true;
                }
                else
                    key[7]=false;
            }
            else
                if(keystate[7]==true)
                {
                    key[7]=false;
                    keystate[7]=false;
                }
            if(glfwGetKey(window,GLFW_KEY_1)==GLFW_PRESS)
            {
               if(keystate[8]==false)
                {
                    key[8]=true;
                    keystate[8]=true;
                }
                else
                    key[8]=false;
            }
            else
                if(keystate[8]==true)
                {
                    key[8]=false;
                    keystate[8]=false;
                }
            if(glfwGetKey(window,GLFW_KEY_2)==GLFW_PRESS)
            {
               if(keystate[9]==false)
                {
                    key[9]=true;
                    keystate[9]=true;
                }
                else
                    key[9]=false;
            }
            else
                if(keystate[9]==true)
                {
                    key[9]=false;
                    keystate[9]=false;
                }
            if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)
            {
               if(keystate[10]==false)
                {
                    key[10]=true;
                    keystate[10]=true;
                }
                else
                    key[10]=false;
            }
            else
                if(keystate[10]==true)
                {
                    key[10]=false;
                    keystate[10]=false;
                }

            //ウィンドウを閉じる必要がなければ true を返す
            return !glfwWindowShouldClose(window); 
        }

        void swapBuffers() const
        {
            //カラーバッファを入れ替える
            glfwSwapBuffers(window);
        }

};

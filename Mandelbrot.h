#pragma once
#include <vector>
#include <utility>
#include <GL/glew.h>
using namespace std;

class Mandelbrot
{
    private :

        //頂点バッファオブジェクトと頂点配列オブジェクト
        GLuint vertex_vbo,vao;

        //頂点？のデータを格納する配列
        GLfloat vertices[4][2] =
        {
            {1.0,1.0},
            {-1.0,1.0},
            {-1.0,-1.0},
            {1.0,-1.0}
        };

    public :

        //コンストラクタ
        Mandelbrot()
        {
            //頂点配列オブジェクト
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            //頂点バッファオブジェクト
            glGenBuffers(1, &vertex_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW);

            //結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
            glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);
        }

        //デストラクタ
        ~Mandelbrot()
        {
            //頂点配列オブジェクトを削除する
            glDeleteVertexArrays(1, &vao);

            //頂点バッファオブジェクトを削除する
            glDeleteBuffers(1, &vertex_vbo);
        }

        void draw()
        {
            //頂点配列オブジェクトの結合
            //描画する頂点配列オブジェクトを指定する
            glBindVertexArray(vao);

            //描画
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
};

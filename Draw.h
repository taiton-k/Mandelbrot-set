#pragma once
#include <GL/glew.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
//using namespace std;

//図形の描画
class Draw
{
    private :

        //頂点配列オブジェクト
        GLuint vao;

        //頂点バッファオブジェクト
        GLuint vertex_vbo;

        //呪文
        void Incantation()
        {
            //バッファの更新
            glNamedBufferSubData(vertex_vbo, 0, sizeof(vertices), &vertices);

            // uniform 変数　color に色のデータを送る
            glUniform4f(color,rgba[0],rgba[1],rgba[2],rgba[3]);

            //頂点配列オブジェクトの結合
            //描画する頂点配列オブジェクトを指定する
            glBindVertexArray(vao);
        }

        //コピーコンストラクタによるコピー禁止
        Draw(const Draw &d);

        //代入によるコピー禁止
        Draw &operator=(const Draw &d);

    public :

        // uniform 変数の場所を格納した変数
        const GLuint color;

        //頂点の座標データを格納する配列
        GLfloat vertices[4][2] =
        {
            {90.0, 90.0},
            {-90.0, 90.0},
            {-90.0,-90.0},
            { 90.0,-90.0}
        };

        // coordinate にデータを格納する関数
        // vertices :座標データ（ -320 <= x < 320, -180 <= y < 180 )
        void setVertices(GLfloat vertexes[4][2])
        {
            rep(i,4)
                rep(j,2)
                    vertices[i][j]=vertexes[i][j];
        }

        //色のデータ（RGBA値）
        GLfloat rgba[4] = {1.0,1.0,1.0,1.0};

        //2次元配列colorにrgba値を入れてくれる関数
        //r,g,b,aの値が引数
        void setColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
        {
            rgba[0]=r;
            rgba[1]=g;
            rgba[2]=b;
            rgba[3]=a;
        }

        //2次元配列colorに値を入れてくれる関数
        //r,g,b,aの値を入れた配列が引数
        void setColor(GLfloat RGBA[4])
        {
            rep(i,4)
                rgba[i]=RGBA[i];
        }

        //コンストラクタ
        // shader :プログラムオブジェクト
        Draw(const GLuint &shader)
            : color(glGetUniformLocation(shader, "color"))
        {
            //頂点配列オブジェクト
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            //頂点バッファオブジェクト
            glGenBuffers(1, &vertex_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),NULL,GL_DYNAMIC_DRAW);

            //結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
            glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);
        }

        //デストラクタ
        ~Draw()
        {
            //頂点配列オブジェクトを削除する
            glDeleteVertexArrays(1, &vao);

            //頂点バッファオブジェクトを削除する
            glDeleteBuffers(1, &vertex_vbo);
        }

        //ドットを描画する（基本的には上と同じ）
        //引数なしバージョン
        void Dot()
        {
            //呪文
            Incantation();

            //ドットの描画
            glDrawArrays(GL_POINTS,0,1);
        }

        //線の描画
        void Line()
        {
            //呪文
            Incantation();

            //線の描画
            glDrawArrays(GL_LINES,0,2);
        }

        //三角形の描画
        void Triangle()
        {
            //呪文
            Incantation();

            //三角形の描画
            glDrawArrays(GL_TRIANGLES,0,3);
        }

        //四角形の描画
        void Rect()
        {
            //呪文
            Incantation();

            //四角形の描画
            glDrawArrays(GL_TRIANGLE_FAN,0,4);
        }
};

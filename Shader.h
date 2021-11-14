#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

class Shader
{
    private:
        
        // シェーダオブジェクトのコンパイル結果を表示する
        // shader: シェーダオブジェクト名
        // str: コンパイルエラーが発生した場所を示す文字列
        GLboolean printShaderInfoLog(GLuint shader, const char *str)
        {
            // コンパイル結果を取得する
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE) cerr << "Compile Error in " << str << endl;
    
            // シェーダのコンパイル時のログの長さを取得する
            GLsizei bufSize;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);

            if (bufSize > 1)
            {
                // シェーダのコンパイル時のログの内容を取得する
                vector<GLchar> infoLog(bufSize);
                GLsizei length;
                glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
                cerr << &infoLog[0] << endl;
            }

            return static_cast<GLboolean>(status);
        }

        // プログラムオブジェクトのリンク結果を表示する
        // program: プログラムオブジェクト名
        GLboolean printProgramInfoLog(GLuint program)
        {
            // リンク結果を取得する
            GLint status;
            glGetProgramiv(program, GL_LINK_STATUS, &status);
            if (status == GL_FALSE) cerr << "Link Error." << endl;

            // シェーダのリンク時のログの長さを取得する
            GLsizei bufSize;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

            if (bufSize > 1)
            {
                // シェーダのリンク時のログの内容を取得する
                vector<GLchar> infoLog(bufSize);
                GLsizei length;
                glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
                cerr << &infoLog[0] << endl;
            }
            return static_cast<GLboolean>(status);
        }

        // プログラムオブジェクトを作成する
        // vsrc: バーテックスシェーダのソースプログラムの文字列
        // fsrc: フラグメントシェーダのソースプログラムの文字列
        GLuint createProgram(const char *vsrc, const char *fsrc)
        {
            // 空のプログラムオブジェクトを作成する
            const GLuint program(glCreateProgram());

            if (vsrc != NULL)
            {
                // バーテックスシェーダのシェーダオブジェクトを作成する
                const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
                glShaderSource(vobj, 1, &vsrc, NULL);
                glCompileShader(vobj);

                // バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
                if (printShaderInfoLog(vobj, "vertex shader"))
                    glAttachShader(program, vobj);
                glDeleteShader(vobj);
            }

            if (fsrc != NULL)
            {
                // フラグメントシェーダのシェーダオブジェクトを作成する
                const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
                glShaderSource(fobj, 1, &fsrc, NULL);
                glCompileShader(fobj);

                // フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
                if (printShaderInfoLog(fobj, "fragment shader"))
                    glAttachShader(program, fobj);
                glDeleteShader(fobj);
            }

            // プログラムオブジェクトをリンクする
            glBindAttribLocation(program, 0, "position");
            glBindFragDataLocation(program, 0, "fragment");
            glLinkProgram(program);
    
            // 作成したプログラムオブジェクトを返す
            if (printProgramInfoLog(program))
                return program;

            // プログラムオブジェクトが作成できなければ 0 を返す
            glDeleteProgram(program);
            return 0;
        }

        // シェーダのソースファイルを読み込んだメモリを返す
        // name: シェーダのソースファイル名
        // buffer: 読み込んだソースファイルのテキスト
        bool readShaderSource(const char *name, vector<GLchar> &buffer)
        {
            // ファイル名が NULL だった
            if (name == NULL) return false;
    
            // ソースファイルを開く
            ifstream file(name, ios::binary);
            if (file.fail())
            {
                // 開けなかった
                cerr << "Error: Can't open source file: " << name << endl;
                return false;
            }

            // ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
            file.seekg(0L, ios::end);
            GLsizei length = static_cast<GLsizei>(file.tellg());
    
            // ファイルサイズのメモリを確保
            buffer.resize(length + 1);
    
            // ファイルを先頭から読み込む
            file.seekg(0L, ios::beg);
            file.read(buffer.data(), length);
            buffer[length] = '\0';

            if (file.fail())
            {
                // うまく読み込めなかった
                cerr << "Error: Could not read souce file: " << name << endl;
                file.close();
                return false;
            }
    
            // 読み込み成功
            file.close();
            return true;
        }
        
        // シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
        // vert: バーテックスシェーダのソースファイル名
        // frag: フラグメントシェーダのソースファイル名
        GLuint loadProgram(const char *vert, const char *frag)
        {
            // シェーダのソースファイルを読み込む
            vector<GLchar> vsrc;
            const bool vstat(readShaderSource(vert, vsrc));
            vector<GLchar> fsrc;
            const bool fstat(readShaderSource(frag, fsrc));
    
            // プログラムオブジェクトを作成する
            return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
        }

        //コピーコンストラクタによるコピー禁止
        Shader(const Shader &s);

        //代入によるコピー禁止
        Shader &operator=(const Shader &s);

    public :

        //プログラムオブジェクト
        const GLuint program;
        
        //コンストラクタ
        //プログラムオブジェクトを作成する
        Shader(const char *vertFile,const char *fragFile) : program(loadProgram(vertFile, fragFile))
        {
        }

};


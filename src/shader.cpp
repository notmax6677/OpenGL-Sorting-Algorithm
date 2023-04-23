#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <iostream>

#include "headers/shader.hpp"

using namespace std;

string loadFile(const char* path) {
    // count the amount of lines read
    int count = 0;

    // write each line to this
    string text;

    ifstream fileIn(path);

    // if the file is open
    if(fileIn.is_open()) {
        // file filestream hasn't failed or reached the end
        do {
            // temporary line variable
            string line;

            // get current line of fileIn stream and write it into line string
            getline(fileIn, line);

            // if reading the first line
            if(count == 0)
                text += line;
            // if not reading the first line and not the last line (blank)
            else if(line != "")
                text += "\n" + line; // add a newline before appending line
            
            // if hasn't failed yet or reached the end
            if(!fileIn.fail()) {
                // increment count by one
                count++;
            }

        } while(!fileIn.fail());

        fileIn.close();
    }
    else {
        cout << "ERROR - FILE AT `" << path << "` COULD NOT BE OPENED." << endl;
        return NULL;
    }

    // return text
    return text;
}

// out-of-class definitions for Shader class

// default constructor
Shader::Shader() {
    ID = 0;
};

// normal constructor
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // success
    int success;

    // info log
    char infoLog[512];

    // load vertex and fragment shader source as strings
    string vertexSourceStr = loadFile(vertexPath);
    string fragmentSourceStr = loadFile(fragmentPath);

    // get vertex and fragment shader source as c strings (char*)
    const char* vertexSource = vertexSourceStr.c_str();
    const char* fragmentSource = fragmentSourceStr.c_str();

    // create vertex and fragment shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // load vertex shader source
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // compile vertex shader
    glCompileShader(vertexShader);
    // check for errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // load error log into infoLog
        cout << "ERROR - VERTEX SHADER COMPILATION FAILED: " << infoLog << endl; // print error log
    }

    // load fragment shader source
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // compile fragment shader
    glCompileShader(fragmentShader);
    // check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // load error log into infoLog
        cout << "ERROR - FRAGMENT SHADER COMPILATION FAILED: " << infoLog << endl; // print error log
    }

    // create shader program
    unsigned int program = glCreateProgram();

    // attach shaders to program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    // link attached shaders to program
    glLinkProgram(program);

    // check for linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog); // load error log into infoLog
        cout << "ERROR - SHADER PROGRAM LINKING FAILED: " << infoLog << endl; // print error log
    }

    // cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set id to program
    ID = program;
}

void Shader::Use() {
    glUseProgram(ID);
}

// uniform setters
void Shader::SetUniform1f(const char* name, float value) {
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::SetUniform2f(const char* name, float value1, float value2) {
    glUniform2f(glGetUniformLocation(ID, name), value1, value2);
}
void Shader::SetUniform3f(const char* name, float value1, float value2, float value3) {
    glUniform3f(glGetUniformLocation(ID, name), value1, value2, value3);
}
void Shader::SetUniform4f(const char* name, float value1, float value2, float value3, float value4) {
    glUniform4f(glGetUniformLocation(ID, name), value1, value2, value3, value4);
}
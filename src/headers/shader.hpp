#ifndef _SHADER_HPP_
#define _SHADER_HPP_

// shader class
class Shader {
    public:
        // default constructor
        Shader();

        // constructor
        Shader(const char* vertexPath, const char* fragmentPath);

        // the shader program ID
        unsigned int ID;

        // use the shader program
        void Use();

        // set 1 uniform float value
        void SetUniform1f(const char* name, float value);

        // set 2 uniform float values
        void SetUniform2f(const char* name, float value1, float value2);

        // set 3 uniform float values
        void SetUniform3f(const char* name, float value1, float value2, float value3);

        // set 4 uniform float values
        void SetUniform4f(const char* name, float value1, float value2, float value3, float value4);
};

#endif
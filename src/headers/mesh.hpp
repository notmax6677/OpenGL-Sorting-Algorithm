#ifndef _MESH_HPP_
#define _MESH_HPP_

// this is a header only system so there's no cpp file corresponding to this header

#include "shader.hpp"

// contains data for drawing an object
struct Mesh {
    // vertex array object
    unsigned int VAO;
    // vertex buffer object
    unsigned int VBO;
    // element buffer object
    unsigned int EBO;

    // shader object
    Shader* SHADER;
};

#endif
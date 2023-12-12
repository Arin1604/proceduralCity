#include "Cube.h"

void Cube::updateParams(int param1) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    setVertexData();
}

void Cube::makeTile(glm::vec3 topLeft,
                    glm::vec3 topRight,
                    glm::vec3 bottomLeft,
                    glm::vec3 bottomRight) {
    // Task 2: create a tile (i.e. 2 triangles) based on 4 given points.
    glm::vec3 norm = glm::cross(topLeft - topRight,bottomRight - topRight);
    glm::vec3 realNorm = glm::normalize(norm);
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, realNorm);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, realNorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, realNorm);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, realNorm);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, realNorm);
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, realNorm);
}

void Cube::makeFace(glm::vec3 topLeft,
                    glm::vec3 topRight,
                    glm::vec3 bottomLeft,
                    glm::vec3 bottomRight) {
    glm::vec3 lenx = (1.0f/m_param1)*(topRight - topLeft);
    glm::vec3 leny = (1.0f/m_param1)*(bottomLeft - topLeft);
    for(int i = 0; i < m_param1; i++){
        for(int j = 0; j < m_param1; j++){
            glm::vec3 topL = topLeft+lenx*(float)j + leny*(float)i;
            glm::vec3 topR = topLeft+lenx*(j+1.0f) + leny*(float)i;
            glm::vec3 botL = topLeft+lenx*(float)j + leny*(i + 1.0f);
            glm::vec3 botR = topLeft+lenx*(j+1.0f) + leny*(i + 1.0f);
            makeTile(topL,topR,botL,botR);
        }
    }

}
void Cube::setVertexData() {

    makeFace(glm::vec3( 0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f,  0.5f, -0.5f),
             glm::vec3( 0.5f, -0.5f, -0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f));

    makeFace(glm::vec3(0.5f,  0.5f, 0.5f),
             glm::vec3(0.5f,  0.5f, -0.5f),
             glm::vec3( 0.5f, -0.5f, 0.5f),
             glm::vec3( 0.5f, -0.5f, -0.5f));

    makeFace(glm::vec3(-0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f,  0.5f,  0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f),
             glm::vec3(-0.5f, -0.5f,  0.5f));

    makeFace(glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3( 0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f, 0.5f),
             glm::vec3( 0.5f, -0.5f, 0.5f));

    makeFace(glm::vec3(-0.5f,  0.5f, -0.5f),
             glm::vec3( 0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3( 0.5f,  0.5f, 0.5f));

    makeFace(glm::vec3( 0.5f, -0.5f, -0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f),
             glm::vec3( 0.5f, -0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f, 0.5f));
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void Cube::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

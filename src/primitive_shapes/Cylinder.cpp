#include "Cylinder.h"
#include <iostream>

void Cylinder::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    m_param2 = param2;
    setVertexData();
}
void Cylinder::makeTile(glm::vec3 topLeft,glm::vec3 bottomLeft,glm::vec3 right){
    glm::vec3 norm = glm::cross(topLeft - right,bottomLeft - right);
    insertVec3(m_vertexData,topLeft);
    insertVec3(m_vertexData,glm::normalize(norm));
    insertVec3(m_vertexData,bottomLeft);
    insertVec3(m_vertexData,glm::normalize(norm));
    insertVec3(m_vertexData,right);
    insertVec3(m_vertexData,glm::normalize(norm));
}

void Cylinder::makeTile2(glm::vec3 topLeft,glm::vec3 bottomLeft,glm::vec3 right){
    insertVec3(m_vertexData,topLeft);
    insertVec3(m_vertexData,glm::normalize(glm::vec3(topLeft[0],0.0f,topLeft[2])));
    insertVec3(m_vertexData,bottomLeft);
    insertVec3(m_vertexData,glm::normalize(glm::vec3(bottomLeft[0],0.0f,bottomLeft[2])));
    insertVec3(m_vertexData,right);
    insertVec3(m_vertexData,glm::normalize(glm::vec3(right[0],0.0f,right[2])));
}

void Cylinder::makeFace(float current,float next){
    glm::vec3 center1(0.0f,0.5f,0.0f);
    glm::vec3 center2(0.0f,-0.5f,0.0f);
    float len = 0.5f/m_param1;
    for(int i = 0; i < m_param1; i++){
        glm::vec3 upL = glm::vec3(len*i*glm::sin(current),0.5f,len*i*glm::cos(current));
        glm::vec3 botL = glm::vec3(len*(i+1)*glm::sin(current),0.5f,len*(i+1)*glm::cos(current));
        glm::vec3 upR = glm::vec3(len*i*glm::sin(next),0.5f,len*i*glm::cos(next));
        glm::vec3 botR = glm::vec3(len*(i+1)*glm::sin(next),0.5f,len*(i+1)*glm::cos(next));
        makeTile(upL,botL,upR);
        makeTile(upR,botL,botR);
    }
    for(int i = 0; i < m_param1; i++){
        glm::vec3 upL = glm::vec3(len*i*glm::sin(current),-0.5f,len*i*glm::cos(current));
        glm::vec3 botL = glm::vec3(len*(i+1)*glm::sin(current),-0.5f,len*(i+1)*glm::cos(current));
        glm::vec3 upR = glm::vec3(len*i*glm::sin(next),-0.5f,len*i*glm::cos(next));
        glm::vec3 botR = glm::vec3(len*(i+1)*glm::sin(next),-0.5f,len*(i+1)*glm::cos(next));
        makeTile(upR,botL,upL);
        makeTile(botR,botL,upR);
    }
    float len2 = 1.0f/m_param1;
    for(int i = 0; i < m_param1; i++){
        glm::vec3 upL = glm::vec3(0.5f*glm::sin(current),0.5f-i*len2,0.5f*glm::cos(current));
        glm::vec3 upR = glm::vec3(0.5f*glm::sin(next),0.5f-i*len2,0.5f*glm::cos(next));
        glm::vec3 botL = glm::vec3(0.5f*glm::sin(current),0.5f-(i+1)*len2,0.5f*glm::cos(current));
        glm::vec3 botR = glm::vec3(0.5f*glm::sin(next),0.5f-(i+1)*len2,0.5f*glm::cos(next));
        makeTile2(upR,upL,botL);
        makeTile2(botL,botR,upR);
    }

}

void Cylinder::makeCylinder(){
    float t = 2.0f*M_PI/m_param2;
    for(int i = 0; i < m_param2; i++){
        makeFace(0.0f+t*i,0.0f+t*(i+1));
    }
}

void Cylinder::setVertexData() {
    makeCylinder();
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void Cylinder::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

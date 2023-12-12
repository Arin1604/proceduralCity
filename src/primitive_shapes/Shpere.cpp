#include "Sphere.h"
#include <math.h>
void Sphere::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    m_param2 = param2;
    setVertexData();
}

void Sphere::makeTile(glm::vec3 topLeft,
                      glm::vec3 topRight,
                      glm::vec3 bottomLeft,
                      glm::vec3 bottomRight) {
    // Task 5: Implement the makeTile() function for a Sphere
    // Note: this function is very similar to the makeTile() function for Cube,
    //       but the normals are calculated in a different way!
    insertVec3(m_vertexData,topLeft);
    insertVec3(m_vertexData,glm::normalize(topLeft));
    insertVec3(m_vertexData,bottomLeft);
    insertVec3(m_vertexData,glm::normalize(bottomLeft));
    insertVec3(m_vertexData,bottomRight);
    insertVec3(m_vertexData,glm::normalize(bottomRight));
    insertVec3(m_vertexData,bottomRight);
    insertVec3(m_vertexData,glm::normalize(bottomRight));
    insertVec3(m_vertexData,topRight);
    insertVec3(m_vertexData,glm::normalize(topRight));
    insertVec3(m_vertexData,topLeft);
    insertVec3(m_vertexData,glm::normalize(topLeft));
}

void Sphere::makeWedge(float currentTheta, float nextTheta) {
    float f = M_PI/m_param1;
    for(int i = 0; i < m_param1; i++){
        glm::vec3 topL = glm::vec3( glm::sin(0.0f+i*f)*glm::sin(currentTheta), glm::cos(0.0f+i*f), glm::sin(0.0f+i*f)*glm::cos(currentTheta) )*0.5f;
        glm::vec3 topR = glm::vec3( glm::sin(0.0f+i*f)*glm::sin(nextTheta), glm::cos(0.0f+i*f), glm::sin(0.0f+i*f)*glm::cos(nextTheta) )*0.5f;
        glm::vec3 botL = glm::vec3( glm::sin(0.0f+(i+1)*f)*glm::sin(currentTheta), glm::cos(0.0f+(i+1)*f), glm::sin(0.0f+(i+1)*f)*glm::cos(currentTheta) )*0.5f;
        glm::vec3 botR = glm::vec3( glm::sin(0.0f+(i+1)*f)*glm::sin(nextTheta), glm::cos(0.0f+(i+1)*f), glm::sin(0.0f+(i+1)*f)*glm::cos(nextTheta) )*0.5f;
        makeTile(topL,topR,botL,botR);
    }

}

void Sphere::makeSphere() {
    float t = 2.0f*M_PI/m_param2;
    for(int i = 0; i < m_param2; i++){
        // Sphere::makeWedge(0.0f+t*i,0.0f+t*(i+1));
        Sphere::makeWedge(0.0f+t*i,0.0f+t*(i+1));
    }
}

void Sphere::setVertexData() {

    makeSphere();
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void Sphere::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

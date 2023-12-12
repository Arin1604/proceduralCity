#pragma once

#include <vector>
#include <glm/glm.hpp>

class Cylinder
{
public:
    void updateParams(int param1, int param2);
    std::vector<float> generateShape() { return m_vertexData; }

private:
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    void setVertexData();
    void makeTile(glm::vec3 topLeft,glm::vec3 bottomLeft, glm::vec3 right);
    void makeTile2(glm::vec3 topLeft,glm::vec3 bottomLeft,glm::vec3 right);
    void makeFace(float current,float next);
    void makeCylinder();
    std::vector<float> m_vertexData;
    int m_param1;
    int m_param2;
    float m_radius = 0.5;
};


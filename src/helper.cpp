#include "realtime.h"
#include "primitive_shapes/cone.h"
#include "primitive_shapes/Cube.h"
#include "primitive_shapes/Cylinder.h"
#include "primitive_shapes/Sphere.h"
#include <random>

void Realtime::updateParam(int param1, int param2){
    Sphere sphere;
    Cylinder cylinder;
    Cone cone;
    Cube cube;
    if(param2 < 3){
        sphere.updateParams(param1,3);
        if(param1 < 2){sphere.updateParams(2,3);}
        cylinder.updateParams(param1,3);
        cone.updateParams(param1,3);
    }
    else{
        sphere.updateParams(param1,param2);
        if(param1 < 2){sphere.updateParams(2,param2);}
        cylinder.updateParams(param1,param2);
        cone.updateParams(param1,param2);
    }
    cube.updateParams(param1);
    m_sphereData = sphere.generateShape();
    m_cylinderData = cylinder.generateShape();
    m_coneData = cone.generateShape();
    m_cubeData = cube.generateShape();
}

// -------------------------------- This is only for final project testing: ------------------------------------ //

// -------------------------------------------------------------------------------------------------------------- //

void Realtime::updateParam2(int screenW, int screenH, float farP, float nearP){
    float w_h_ratio = (screenW+0.0f)/screenH;
    float tanH = glm::tan(hAngle*0.5);
    //std::cout<<tanH<<std::endl;
    float tanW = w_h_ratio*tanH;
    float c_ratio = - nearP/farP;
    glm::mat4 Mpp(1.0f,0.0f,0.0f,0.0f,
                  0.0f,1.0f,0.0f,0.0f,
                  0.0f,0.0f,1.0f/(1.0f+c_ratio),-1.0f,
                  0.0f,0.0f,-c_ratio/(1.0f+c_ratio),0.0f);
    glm::mat4 remapM(1.0f,0.0f,0.0f,0.0f,
                     0.0f,1.0f,0.0f,0.0f,
                     0.0f,0.0f,-2.0f,0.0f,
                     0.0f,0.0f,-1.0f,1.0f);
    glm::mat4 scaleM(1.0f/(farP*tanW),0.0f,0.0f,0.0f,
                     0.0f,1.0f/(farP*tanH),0.0f,0.0f,
                     0.0f,0.0f,1.0f/farP,0.0f,
                     0.0f,0.0f,0.0f,1.0f);
    m_proj = remapM * Mpp * scaleM;
}

glm::mat4 Realtime::getViewMatrix(glm::vec4 pos,glm::vec4 look,glm::vec4 up){
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    glm::mat4 Mt = glm::mat4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,-px,-py,-pz,1.0);
    glm::vec4 w = -glm::normalize(look);
    float upw = glm::dot(up,w);
    glm::vec4 v = glm::normalize(up-upw*w);
    glm::vec3 u = glm::cross(glm::vec3(v),glm::vec3(w));
    glm::mat4 Mr = glm::mat4(u[0],v[0],w[0],0.0,u[1],v[1],w[1],0.0,u[2],v[2],w[2],0.0,0.0,0.0,0.0,1.0);
    return  Mr*Mt;
}

glm::mat4 Realtime::createTranslationMatrix(float x, float y, float z) {
    return glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     x,    y,    z,    1.0f);
}

glm::mat4 Realtime::createRotationMatrix(float angle, glm::vec3 axis) {
    axis = glm::normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0f - c;

    return glm::mat4(
        oc * axis.x * axis.x + c,         oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s, 0.0f,
        oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c,          oc * axis.y * axis.z - axis.x * s, 0.0f,
        oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,         0.0f,
        0.0f,                             0.0f,                             0.0f,                            1.0f
        );
}

float Realtime::getRandomFloat(float min, float max) {
    // Use the Mersenne Twister random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(min, max); // Define the range

    return distr(eng);
}

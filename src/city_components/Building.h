#pragma once
#include <utility>
#include <glm/glm.hpp>

class Building
{
public:
    // constructor
    Building(glm::vec3 pos, glm::vec3 size);
    ~Building() = default; // deconstructor
    Building(const Building&) = default; // default copy constructor
    bool checkOverlap(Building& B);
    glm::mat4 CTM; // The CTM that scale&translate the unit cube to destination
    glm::vec3 position; // The translate vector that translate the unit cube to the destination
    glm::vec3 size; // The scale vector
    std::pair<float, float> boundX; // the x-axis bound of the building
    std::pair<float, float> boundZ; // the z-axis bound of the building
};

#include "sceneparser.h"
#include "scenefilereader.h"
#include <glm/gtx/transform.hpp>

#include <chrono>
#include <iostream>

bool SceneParser::parse(std::string filepath, RenderData &renderData) {
    ScenefileReader fileReader = ScenefileReader(filepath);
    bool success = fileReader.readJSON();
    if (!success) {
        return false;
    }

    renderData.globalData = fileReader.getGlobalData();
    renderData.cameraData = fileReader.getCameraData();

    SceneNode* root = fileReader.getRootNode();
    renderData.shapes.clear();
    renderData.lights.clear();
    return SceneParser::traverse(root, renderData.shapes, renderData.lights, glm::mat4(1.0f));
}

bool SceneParser::traverse(SceneNode* node, std::vector<RenderShapeData>& shapes, std::vector<SceneLightData>& lights, glm::mat4 ctm){
    if(node == nullptr){
        std::cout<<2<<std::endl;
        return true;
    }
    else{

        glm::mat4 copy = glm::mat4(1.0f);
        copy = copy*ctm;
        std::vector<ScenePrimitive*> pList = node->primitives;
        std::vector<SceneTransformation*> stList = node->transformations;
        std::vector<SceneLight*> lightList = node->lights;

        for(SceneTransformation* element : stList){
            switch(element->type){
            case TransformationType::TRANSFORMATION_TRANSLATE:
                copy = copy*glm::translate(element->translate);
                break;
            case TransformationType::TRANSFORMATION_ROTATE:
                copy = copy*glm::rotate(element->angle,element->rotate);
                break;
            case TransformationType::TRANSFORMATION_SCALE:
                copy = copy*glm::scale(element->scale);
                break;
            case TransformationType::TRANSFORMATION_MATRIX:
                copy = copy*element->matrix;
                break;
            }
        }

        for(SceneLight* light : lightList){


            lights.push_back(SceneLightData{light->id, light->type, light->color, light->function, copy*glm::vec4(0.0,0.0,0.0,1.0) ,copy*light->dir ,light->penumbra, light->angle, light->width, light->height});
        }

        for(ScenePrimitive* p : pList){
            shapes.push_back(RenderShapeData{*p,copy});
        }

        std::vector<SceneNode*> children = node->children;
        for(SceneNode* node : children){
            SceneParser::traverse(node, shapes, lights, copy);
        }
    }
    return true;
}

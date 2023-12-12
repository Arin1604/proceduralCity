#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>
#include "utils/sceneparser.h"
#include "city_components/Building.h"
class Realtime : public QOpenGLWidget
{
public:
    Realtime(QWidget *parent = nullptr);
    void finish();                                      // Called on program exit
    void sceneChanged();
    void settingsChanged();
    void saveViewportImage(std::string filePath);
    void updateParam(int param1, int param2);
    void updateParam2(int screenW, int screenH, float farP, float nearP);
    glm::mat4 getViewMatrix(glm::vec4 pos,glm::vec4 look,glm::vec4 up);
    glm::mat4 createTranslationMatrix(float x, float y, float z);
    glm::mat4 createRotationMatrix(float angle, glm::vec3 axis);
    void makeFBO();
    void paintTexture(GLuint texture);

    // helper functions for final project:
    float getRandomFloat(float min, float max);    
    std::vector<float> generateRandomCubes();

public slots:
    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

protected:
    void initializeGL() override;                       // Called once at the start of the program
    void paintGL() override;                            // Called whenever the OpenGL context changes or by an update() request
    void resizeGL(int width, int height) override;      // Called when window size changes

private:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // Tick Related Variables
    int m_timer;                                        // Stores timer which attempts to run ~60 times per second
    QElapsedTimer m_elapsedTimer;                       // Stores timer which keeps track of actual time between frames

    // Input Related Variables
    bool m_mouseDown = false;                           // Stores state of left mouse button
    glm::vec2 m_prev_mouse_pos;                         // Stores mouse position
    std::unordered_map<Qt::Key, bool> m_keyMap;         // Stores whether keys are pressed or not

    // Device Correction Variables
    int m_devicePixelRatio;

    //memeber that I created:
    RenderData m_data;    
    std::vector<SceneLightData> m_dir_lights;
    std::vector<SceneLightData> m_point_lights;
    std::vector<SceneLightData> m_spot_lights;
    std::vector<RenderShapeData> m_shapes;

    GLuint m_shader;    // Stores id of shader program
    GLuint m_texture_shader; // Stores id of the texture shader
    GLuint m_fbo_texture;
    GLuint m_fbo_renderbuffer;
    GLuint m_fbo;
    GLuint m_fullscreen_vao;
    GLuint m_fullscreen_vbo;
    GLuint m_vbo_sphere; // Stores id of vbo
    GLuint m_vao_sphere; // Stores id of vao
    GLuint m_vbo_cube; // Stores id of vbo
    GLuint m_vao_cube; // Stores id of vao
    GLuint m_vbo_cone; // Stores id of vbo
    GLuint m_vao_cone; // Stores id of vao
    GLuint m_vbo_cylinder; // Stores id of vbo
    GLuint m_vao_cylinder; // Stores id of vao

    std::vector<float> m_sphereData;
    std::vector<float> m_cubeData;
    std::vector<float> m_coneData;
    std::vector<float> m_cylinderData;    

    glm::vec4 m_cam_pos;
    glm::vec4 m_cam_look;
    glm::vec4 m_cam_up;

    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_proj;
    float hAngle;
    float m_ka;
    float m_kd;
    float m_ks;
    float m_shininess;
    bool upload = false;
    int m_defaultFBO;

    // below are fields for final project:
    std::vector<glm::mat4> m_CTM_collection; // stores different CTMs for the cubes
    std::vector<Building> m_building_arr; // stores the buildings
};

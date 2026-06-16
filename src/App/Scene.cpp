#include "Scene.h"
#include "config.h"
#include "Core/Renderer.h"
#include "Entities/Lamp.h"


const char* vertexShader =
#include "../../Assets/Shaders/common.vert.glsl"
;

const char* fragmentShader =
#include "../../Assets/Shaders/common.frag.glsl"
;

long double ball_dy = 0;
long double ball_ddy = -0.002;
int hit_times = 0;

Scene::Scene(float aspectRadio)
    : m_ball(nullptr),
    m_shader(nullptr),
    m_floor_texture(nullptr),
    m_floor(nullptr),
    m_lamp(nullptr),
    m_camera(aspectRadio) {}

Scene::~Scene() = default;

void Scene::boostrap() {
    m_shader = std::make_unique<Shader>(vertexShader, fragmentShader);
    m_floor = std::make_unique<Floor>();
    m_ball = std::make_unique<Ball>();
    m_floor_texture = std::make_unique<Texture>("Assets/Textures/floor.png");
    m_ball_texture = std::make_unique<Texture>("Assets/Textures/kav.png");
    m_lamp = std::make_unique<Lamp>();


    m_camera.MoveUp(2.5);
    m_camera.MoveRight(1.07);
    m_camera.MoveForward(3);

    m_lamp->m_transform.translate(glm::vec3(6, 4, 1));
    m_ball->m_transform.translate(glm::vec3(0, 10, 0));
    m_ball->m_transform.setScale(glm::vec3(0.5));
}

void Scene::run() {
    Renderer::clear();

    m_lamp->Draw(m_camera);
    m_shader->bind();
    m_shader->setInt("u_texture", 0);
    m_shader->setVec4("u_light", glm::vec4(1, 1, 1, 1));
    m_shader->setVec3("u_light_pos", m_lamp->m_transform.position);
    m_shader->setVec3("u_camera_pos", m_camera.position);
    m_floor_texture->bind(0);
    m_floor->Draw(m_camera, *m_shader);

    m_ball_texture->bind(0);
    m_ball->m_transform.translate(glm::vec3(0, ball_dy, 0));
    m_ball->m_transform.rotate(glm::vec3(0, 0, 0.3*(ball_dy < 0 ? -ball_dy : ball_dy)));
    m_ball->Draw(m_camera, *m_shader);


    ball_dy += ball_ddy;

    if (m_ball->m_transform.position.y+ball_dy < 1.01) {
        ball_dy = -ball_dy*0.5;
        m_ball->m_transform.translate(glm::vec3(0, ball_dy, 0));
        hit_times += 1;
    }

    if (hit_times > 4) {
        ball_ddy = 0;
        ball_dy = 0;
    }
}

void Scene::updateAspect(float aspectRadio) {
    m_camera.updateAspect(aspectRadio);
    m_camera.updateView();
    m_camera.updateProjection();
}
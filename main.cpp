#define GLEW_STATIC
#include <iostream>
#include <chrono>
#include "camera.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "window.h"
#include "planet.h"

float lastX;
float lastY;
bool firstMouse;
float yaw;
float pitch;
Camera c;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    c.forward = glm::normalize(front);
}

int main(int argc, char* argv[])
{
    int res_x;
    int res_y;
    int vsync;
    float fov;
    if(argc != 5)
    {
        std::cout << "args: <res_x> <res_y> <vsync> <fov>\n";
        res_x = 1280;
        res_y = 720;
        vsync = 1;
        fov = 90.0f;
    }
    else
    {
        std::sscanf(argv[1], "%d", &res_x);
        std::sscanf(argv[2], "%d", &res_y);
        std::sscanf(argv[3], "%d", &vsync);
        std::sscanf(argv[4], "%f", &fov);
    }
    std::cout << "res_x: " << res_x << "\n";
    std::cout << "res_y: " << res_y << "\n";
    std::cout << "vsync: " << vsync << "\n";
    std::cout << "fov: " << fov << "\n";
    lastX = res_x / 2;
    lastY = res_y / 2;
    firstMouse = false;

    window w(res_x, res_y, "OpenGL", vsync);

    Shader s("./shader");
    Shader s2("./shader2");
    Texture earth("./earth.jpg");
    Texture moon("./moon.jpg");
    Texture sun("./sun.jpg");
    Texture jupiter("./jupiter.jpg");
    Texture jupiter2("./jupiter.jpg");
    Texture space("./space.jpg");
    Transform trans(glm::vec3(), glm::vec3(), glm::vec3(1.0f, 1.0f, 1.0f));
    float camera_x = 0;
    float camera_y = 0;
    float camera_z = -300;
    c = Camera(glm::vec3(camera_x, camera_y, camera_z), glm::radians(fov), (float)(res_x) / (float)(res_y), 0.01f, 4000.0f);
    Mesh ball("ball4.obj");

    glfwSetInputMode(w.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(w.GetWindow(), &mouse_callback);

    Mesh cube("cube.obj");
    double counter = 0.0;

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    Planet jup(&s, &jupiter2, &ball, glm::vec3(0, 0, 0), glm::vec3(30, 30, 30), glm::vec3(490, 420, 120), 3.0);

    while(!glfwWindowShouldClose(w.GetWindow()))
    {
        end = start;
        start = std::chrono::steady_clock::now();
        auto diff = start - end;
        float frametime = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()) / 1000000;
        counter += 0.08 * (frametime / 1000);

        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glfwGetKey(w.GetWindow(), GLFW_KEY_W))
            c.position += (float)(200 * (frametime / 1000)) * c.forward;
        if(glfwGetKey(w.GetWindow(), GLFW_KEY_S))
            c.position -= (float)(200 * (frametime / 1000)) * c.forward;
        if(glfwGetKey(w.GetWindow(), GLFW_KEY_A))
            c.position -= (float)(200 * (frametime / 1000)) * glm::normalize(glm::cross(c.forward, c.up));
        if(glfwGetKey(w.GetWindow(), GLFW_KEY_D))
            c.position += (float)200 * (frametime / 1000) * glm::normalize(glm::cross(c.forward, c.up));
        if(glfwGetKey(w.GetWindow(), GLFW_KEY_ESCAPE))
            return 0;

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BACK);
        trans.GetScale() = glm::vec3(3000, 3000, 3000);
        trans.GetRotation() = glm::vec3(90, 0, 0);
        s2.Bind();
        s2.Update(trans, c);
        space.Bind(0);
        ball.Draw();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BACK);

        jup.Update(counter, c);


        trans.GetPosition().z = (0 + 490 * cosf(3 * counter));
        trans.GetPosition().x = (0 + 420 * sinf(3 * counter));
        trans.GetPosition().y = 120 * cosf(3 * counter);
        trans.GetScale() = glm::vec3(30, 30, 30);
        trans.GetRotation() = glm::vec3(0, 0, 0);
        trans.GetRotation().y = 3 * counter;
        s.Bind();
        s.Update(trans, c);
        jupiter.Bind(0);
        ball.Draw();

        trans.GetPosition().z = (0 + 150 * cosf(5 * counter));
        trans.GetPosition().x = (0 + 150 * sinf(5 * counter));
        trans.GetPosition().y = 40 * sinf(5 * counter);
        trans.GetScale() = glm::vec3(10, 10, 10);
        float e_z = trans.GetPosition().z;
        float e_y = trans.GetPosition().y;
        float e_x = trans.GetPosition().x;
        trans.GetRotation() = glm::vec3(0, 0, 0);
        trans.GetRotation().y = 25 * counter;
        s.Bind();
        s.Update(trans, c);
        earth.Bind(0);
        ball.Draw();

        trans.GetPosition().z = (e_z + 25 * cosf(9 * counter));
        trans.GetPosition().x = (e_x + 25 * sinf(9 * counter));
        trans.GetPosition().y = e_y + 40 * sinf(9 * counter);
        e_z = trans.GetPosition().z;
        e_y = trans.GetPosition().y;
        e_x = trans.GetPosition().x;
        trans.GetScale() = glm::vec3(5, 5, 5);
        trans.GetRotation() = glm::vec3(0, 0, 0);
        trans.GetRotation().y = 9 * counter;
        s.Bind();
        s.Update(trans, c);
        moon.Bind(0);
        ball.Draw();

        trans.GetPosition().z = (e_z + 15 * cosf(25 * counter));
        trans.GetPosition().x = (e_x + 15 * sinf(25 * counter));
        trans.GetPosition().y = e_y;
        trans.GetScale() = glm::vec3(2, 2, 2);
        trans.GetRotation() = glm::vec3(0, 0, 0);
        trans.GetRotation().y = 3 * counter;
        s.Bind();
        s.Update(trans, c);
        moon.Bind(0);
        ball.Draw();

        trans.GetPosition().z = (0 + 600 * cosf(5 * counter));
        trans.GetPosition().x = (0 + 800 * sinf(5 * counter));
        trans.GetPosition().y = 0;
        trans.GetScale() = glm::vec3(40, 40, 40);
        trans.GetRotation() = glm::vec3(0, 0, 0);
        trans.GetRotation().y = 3 * counter;
        s.Bind();
        s.Update(trans, c);
        moon.Bind(0);
        ball.Draw();


        trans.GetPosition() = glm::vec3(0, 0, 0);
        trans.GetScale() = glm::vec3(100, 100, 100);
        trans.GetRotation().x = 0.6f;
        trans.GetRotation().z = 0;
        trans.GetRotation().y = counter;
        s2.Bind();
        s2.Update(trans, c);
        sun.Bind(0);
        ball.Draw();

        w.Update();
    }
}

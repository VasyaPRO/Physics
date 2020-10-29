#include <iostream>
#include <vector>
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Vec.h"
#include "Mat.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const double dt = 1.0 / 60.0;

struct Circle
{
    Vec2 center;
    double radius;
    Vec2 velocity;
    double mass;

    Circle(Vec2 c, double r, Vec2 v, double m) : center(c), radius(r), velocity(v), mass(m) {}
};

pair<Vec2, double> collide(const Circle& a, const Circle& b)
{
    return {normalize(a.center - b.center), a.radius + b.radius - distance(a.center, b.center)};
}

double determinant(double a, double b, double c, double d)
{
    return a * d - b * c;
}

void solve(Circle& a, Circle& b, Vec2 contact_normal)
{
    double den = determinant(1, -1, a.mass, b.mass);
    double alpha = determinant(
        2 * dot(b.velocity, contact_normal) - 2 * dot(a.velocity, contact_normal), -1,
        0, b.mass)
        / den;

    double beta = determinant(
        1, 2 * dot(b.velocity, contact_normal) - 2 * dot(a.velocity, contact_normal),
        a.mass, 0)
        / den;
    a.velocity = a.velocity + contact_normal * alpha;
    b.velocity = b.velocity + contact_normal * beta;
}

void processCollisions(vector<Circle>& circles)
{
    for (int i = 0; i < circles.size(); i++)
    {
        for (int j = i + 1; j < circles.size(); j++)
        {
            auto& A = circles[i];
            auto& B = circles[j];
            auto res = collide(A, B);
            if (res.second >= 0)
            {
                solve(A, B, res.first);
            }
        }
    }
    for (int i = 0; i < circles.size(); i++)
    {
        if (circles[i].center.x - circles[i].radius < -SCREEN_WIDTH / 2 && circles[i].velocity.x < 0 ||
            circles[i].center.x + circles[i].radius > SCREEN_WIDTH / 2 && circles[i].velocity.x > 0)
        {
            circles[i].velocity.x = -circles[i].velocity.x;
        }
        if (circles[i].center.y - circles[i].radius < -SCREEN_HEIGHT / 2 && circles[i].velocity.y < 0 ||
            circles[i].center.y + circles[i].radius > SCREEN_HEIGHT / 2 && circles[i].velocity.y > 0)
        {
            circles[i].velocity.y = -circles[i].velocity.y;
        }
        circles[i].center = circles[i].center + circles[i].velocity * dt;
    }
}

void APIENTRY debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    cerr << "OpenGL error: " << message << endl;
    cout << id << endl;
    assert(false);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);  

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(debug_message_callback, nullptr);

    glfwSwapInterval(1); // VSync

    Shader shader;
    shader.loadFromFile("shaders/main.vert", "shaders/main.frag");
    useProgram(shader);

    vector<Vec2> vertices = {
        {-0.5, 0.5},
        {0.5, 0.5},
        {0.5, -0.5},

        {0.5, -0.5},
        {-0.5, -0.5},
        {-0.5, 0.5}
    };
    VertexBuffer VBO(vertices.data(), vertices.size() * sizeof(Vec2));
    VertexArray VAO;
    VAO.attachBuffer<Vec2>(VBO);

    Mat3 proj;
    proj[0][0] = 2.0 / SCREEN_WIDTH;
    proj[1][1] = 2.0 / SCREEN_HEIGHT;
    proj[0][2] = 2.0 / SCREEN_WIDTH;
    proj[1][2] = 2.0 / SCREEN_HEIGHT;
    shader.setUniform(2, proj);

    vector<Circle> circles;
    circles.emplace_back(Vec2(-50, 0), 35, Vec2(9, 42), 1.5);
    circles.emplace_back(Vec2(50, 0), 30, Vec2(-45, 7), 1);
    circles.emplace_back(Vec2(0, -40), 15, Vec2(60, 86), 0.4);
    circles.emplace_back(Vec2(80, -200), 50, Vec2(4, 66), 4.4);
    circles.emplace_back(Vec2(-120, 50), 40, Vec2(-27, 72), 3);
    circles.emplace_back(Vec2(-77, -40), 10, Vec2(130, 15), 0.2);
    circles.emplace_back(Vec2(6, 40), 22, Vec2(17, 86), 0.9);
    circles.emplace_back(Vec2(256, -75), 78, Vec2(-18, 34), 15);
    circles.emplace_back(Vec2(178, 178), 89, Vec2(45, 78), 10.9);

    int iter = 0;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        processCollisions(circles);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& c : circles)
        {
            shader.setUniform(0, c.center);
            shader.setUniform(1, c.radius);
            Mat3 model = Mat3::translate(c.center) * Mat3::scale(c.radius * 2);
            shader.setUniform(7, model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
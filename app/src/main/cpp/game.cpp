#include "game.h"
#include "glwrapper.h"
#include "ExFreeType.h"
#include "math_3d.h"

#include <iostream>
#include <math.h>
#include <string.h>

#include "Pipeline.h"

ExFreeType g_freeType;

GLuint VBO;
GLuint IBO;
GLuint vertexSh;
GLuint fragSh;
GLuint shaderProgram;
Matrix4f world;

Pipeline pipeline;

const char* strVSh =
        "#version 300 es\n"
        "uniform float gScale;\n"
        "uniform mat4 gWorld;\n"
        "layout (location = 0) in vec3 Position;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = gWorld * vec4(Position, 1.0);\n"
        "   color = vec4(clamp(Position, 0.0, 1.0), 1.0);\n"
        "}\n\0";

const char* const strFSh =
                "#version 300 es\n"
                "out vec4 FragColor;\n"
                "in vec4 color;\n"
                "void main()\n"
                "{\n"
                "   FragColor = color;\n"
                "}\n\0";

void on_surface_created() {
    g_freeType.Init();

    //Triangle
    //Vector3f vertices[3];
    //vertices[0] = Vector3f(-0.5f, -0.5f, 0.0f);
    //vertices[1] = Vector3f(0.0f,   0.5f, 0.0f);
    //vertices[2] = Vector3f(0.5f,  -0.5f, 0.0f);

    //Quad
    Vector3f vertices[5];
    vertices[0] = Vector3f(  0.5f,  0.5f, 0.0f);
    vertices[1] = Vector3f( -0.5f,  0.5f, 0.0f);
    vertices[2] = Vector3f( -0.5f, -0.5f, 0.0f);
    vertices[3] = Vector3f(  0.5f, -0.5f, 0.0f);
    vertices[4] = Vector3f(  0.0f,  0.0f, 1.f);

    unsigned int indices[18];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    indices[6] = 2;
    indices[7] = 4;
    indices[8] = 3;

    indices[9]  = 3;
    indices[10] = 4;
    indices[11] = 0;

    indices[12] = 0;
    indices[13] = 1;
    indices[14] = 4;

    indices[15] = 1;
    indices[16] = 4;
    indices[17] = 2;



    world.m[0][0] = 1.0f; world.m[0][1] = 0.0f; world.m[0][2] = 0.0f; world.m[0][3] = 0.0f;
    world.m[1][0] = 0.0f; world.m[1][1] = 1.0f; world.m[1][2] = 0.0f; world.m[1][3] = 0.0f;
    world.m[2][0] = 0.0f; world.m[2][1] = 0.0f; world.m[2][2] = 1.0f; world.m[2][3] = 0.0f;
    world.m[3][0] = 0.0f; world.m[3][1] = 0.0f; world.m[3][2] = 0.0f; world.m[3][3] = 1.0f;

    //shaders
    vertexSh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexSh, 1, &strVSh, NULL);
    glCompileShader(vertexSh);

    int success = 0;
    glGetShaderiv(vertexSh,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char InfoLog[512];
        glGetShaderInfoLog(vertexSh, sizeof(InfoLog), NULL, InfoLog);
        std::cout << "Error compiling shader " << InfoLog << std::endl;
    }

    fragSh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragSh, 1, &strFSh, NULL);
    glCompileShader(fragSh);

    glGetShaderiv(fragSh, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char InfoLog[512];
        glGetShaderInfoLog(fragSh, sizeof(InfoLog), NULL, InfoLog);
        std::cout << "Error compiling shader " << InfoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexSh);
    glAttachShader(shaderProgram, fragSh);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char InfoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", InfoLog);
    }

    glValidateProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    Vector3f pos(0.0f, 0.0f, 2.0f);
    Vector3f tar(0.0f, 0.0f, 1.0f);
    Vector3f up(0.0f, 1.0f, 0.0f);

    pipeline.SetCamera(pos, tar, up);
}

void on_surface_changed(int width, int height) {
    // No-op
    SProjection& proj = pipeline.GetProjection();
    proj.m_width = width;
    proj.m_height = height;
}

void on_draw_frame() {
    glClearColor(1.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float fScale = 0.0f;
    fScale += 0.01f;

    pipeline.WorldPos(0.0f, 0.0f, -1.5f);
    //pipeline.Scale(sinf(fScale * 0.1f), sinf(fScale * 0.1f), sinf(fScale * 0.1f));
    pipeline.Rotate(-120.0f, sinf(fScale) * 360.0f ,0.0f);
    const Matrix4f* trans = pipeline.GetTrans();

    GLuint pos = glGetUniformLocation(shaderProgram,"gScale");
    GLuint worldPos = glGetUniformLocation(shaderProgram, "gWorld");

    if(pos < 0 || worldPos < 0)
    {
        printf("Assert here");
    }

    glUniformMatrix4fv(worldPos, 1, GL_TRUE, &trans->m[0][0]);
    glUniform1f(pos, sin(fScale));

    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void on_touch_down(int x, int y)
{

}

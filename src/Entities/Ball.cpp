#include "Ball.h"

std::vector<Vertex> GenerateBallVertices(
    float radius = 1.0f,
    uint32_t stacks = 32,
    uint32_t sectors = 32)
{
    std::vector<Vertex> vertices;

    constexpr float PI = 3.14159265358979323846f;

    for (uint32_t i = 0; i <= stacks; ++i)
    {
        float stackAngle = PI * 0.5f - (float)i * PI / (float)stacks;

        float xy = radius * std::cos(stackAngle);
        float y  = radius * std::sin(stackAngle);

        for (uint32_t j = 0; j <= sectors; ++j)
        {
            float sectorAngle =
                (float)j * 2.0f * PI / (float)sectors;

            float x = xy * cos(sectorAngle);
            float z = -xy * sin(sectorAngle);

            Vertex v{};

            // Position
            v.position[0] = x;
            v.position[1] = y;
            v.position[2] = z;

            // Color
            v.color[0] = 1.0f;
            v.color[1] = 1.0f;
            v.color[2] = 1.0f;
            v.color[3] = 1.0f;

            // UV
            v.texture_coord[0] = 1.0 - (float)j / (float)sectors;
            v.texture_coord[1] = 1.0 - (float)i / (float)stacks;

            // Normal
            float invRadius = 1.0f / radius;

            v.normal[0] = x * invRadius;
            v.normal[1] = y * invRadius;
            v.normal[2] = z * invRadius;

            vertices.push_back(v);
        }
    }

    return vertices;
}

std::vector<uint32_t> GetBallIndices(
    uint32_t stacks = 32,
    uint32_t sectors = 32)
{
    std::vector<uint32_t> indices;

    for (uint32_t i = 0; i < stacks; ++i)
    {
        uint32_t currentRow = i * (sectors + 1);
        uint32_t nextRow    = currentRow + sectors + 1;

        for (uint32_t j = 0; j < sectors; ++j)
        {
            uint32_t a = currentRow + j;
            uint32_t b = nextRow    + j;
            uint32_t c = currentRow + j + 1;
            uint32_t d = nextRow    + j + 1;

            // Upper triangle
            if (i != 0)
            {
                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(c);
            }

            // Lower triangle
            if (i != stacks - 1)
            {
                indices.push_back(c);
                indices.push_back(b);
                indices.push_back(d);
            }
        }
    }

    return indices;
}

Ball::Ball()
    : Entity(GenerateBallVertices(), GetBallIndices())
{
    m_transform.scale = glm::vec3(1.0);
    m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
}



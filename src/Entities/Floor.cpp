#include "Floor.h"

std::vector<Vertex> GenerateFloorVertices() {
    // Half-dimensions for a 6 (Width) x 1 (Height) x 6 (Depth) block
    constexpr float w = 6.0f / 2.0f;  // 3.0f
    constexpr float h = 1.0f / 2.0f;  // 0.5f
    constexpr float d = 6.0f / 2.0f;  // 3.0f

    // Tiling factors: How many times the bricks repeat across the faces
    constexpr float tileXZ = 3.0f;
    constexpr float tileY  = 0.5f;

    return {
        // --- TOP FACE ---
        {{-w,  h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   tileXZ}, {0.0f, 1.0f, 0.0f}},
        {{-w,  h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   0.0f  }, {0.0f, 1.0f, 0.0f}},
        {{ w,  h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, 0.0f  }, {0.0f, 1.0f, 0.0f}},
        {{ w,  h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, tileXZ}, {0.0f, 1.0f, 0.0f}},

        // --- FRONT FACE ---
        {{-w, -h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   0.0f  }, {0.0f, 0.0f, 1.0f}},
        {{ w, -h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, 0.0f  }, {0.0f, 0.0f, 1.0f}},
        {{ w,  h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, tileY }, {0.0f, 0.0f, 1.0f}},
        {{-w,  h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   tileY }, {0.0f, 0.0f, 1.0f}},

        // --- BACK FACE ---
        {{-w, -h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, 0.0f  }, {0.0f, 0.0f, -1.0f}},
        {{-w,  h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, tileY }, {0.0f, 0.0f, -1.0f}},
        {{ w,  h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   tileY }, {0.0f, 0.0f, -1.0f}},
        {{ w, -h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   0.0f  }, {0.0f, 0.0f, -1.0f}},

        // --- LEFT FACE ---
        {{-w, -h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   0.0f  }, {-1.0f, 0.0f, 0.0f}},
        {{-w, -h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, 0.0f  }, {-1.0f, 0.0f, 0.0f}},
        {{-w,  h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, tileY }, {-1.0f, 0.0f, 0.0f}},
        {{-w,  h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   tileY }, {-1.0f, 0.0f, 0.0f}},

        // --- RIGHT FACE ---
        {{ w, -h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, 0.0f  }, {1.0f, 0.0f, 0.0f}},
        {{ w,  h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, tileY }, {1.0f, 0.0f, 0.0f}},
        {{ w,  h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   tileY }, {1.0f, 0.0f, 0.0f}},
        {{ w, -h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   0.0f  }, {1.0f, 0.0f, 0.0f}},

        // --- BOTTOM FACE ---
        {{-w, -h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   tileXZ}, {0.0f, -1.0f, 0.0f}},
        {{ w, -h, -d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, tileXZ}, {0.0f, -1.0f, 0.0f}},
        {{ w, -h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {tileXZ, 0.0f  }, {0.0f, -1.0f, 0.0f}},
        {{-w, -h,  d}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f,   0.0f  }, {0.0f, -1.0f, 0.0f}}
    };
}

std::vector<uint32_t> getFloorIndices() {
    return {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };
}


Floor::Floor() : Entity(GenerateFloorVertices(), getFloorIndices()){
    m_transform.scale = glm::vec3(1.0);
    m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
}

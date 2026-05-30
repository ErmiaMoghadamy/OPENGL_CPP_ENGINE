#include "Renderer.h"

#include "config.h"

namespace Renderer
{
    void clear() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void draw(Mesh* mesh) {
        mesh->bind();
        mesh->draw();
    }
}
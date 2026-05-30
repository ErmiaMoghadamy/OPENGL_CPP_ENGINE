#include "App/App.h"
#include "config.h"
using std::cout;

int main() {
    App app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
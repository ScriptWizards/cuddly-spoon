#include <Small/All.hpp>

#include <game/MyScene.hpp>

int main(int argc, char** argv)
{
    const sgl::Settings settings = {
        /* width */ 640,
        /* height */ 480
    };
    sgl::Application app(settings);

    app.setTitle("CuddlySpoon")
        .setVSync(false)
        .setFPSLimit(60)
        .setDebug(false);

    app.add<MyScene>();
    app.setCurrentScene<MyScene>();

    app.run();

    return 0;
}

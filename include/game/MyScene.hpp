#ifndef INCLUDE_GAME_MYSCENE_HPP
#define INCLUDE_GAME_MYSCENE_HPP

#include <Small/Core/Scene.hpp>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id);

    void onEvent(const sf::Event& event);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

private:
};

#endif

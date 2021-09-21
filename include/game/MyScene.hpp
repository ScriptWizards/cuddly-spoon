#ifndef INCLUDE_GAME_MYSCENE_HPP
#define INCLUDE_GAME_MYSCENE_HPP

#include <Small/Core/Scene.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class MyScene : public sgl::Scene
{
public:
    MyScene(int id, int test_argument);

    void onEvent(const sf::Event& event);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

private:
    int m_argument;
    sf::CircleShape m_octagon;
};

#endif

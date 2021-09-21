#ifndef INCLUDE_GAME_MYSCENE_HPP
#define INCLUDE_GAME_MYSCENE_HPP

#include <Small/Core/Scene.hpp>
#include <array>
#include <SFML/Graphics.hpp>

constexpr std::size_t Width = 640;
constexpr std::size_t Height = 480;
constexpr std::size_t PixSize = 2;
constexpr std::size_t WidthPx = Width / PixSize;
constexpr std::size_t HeightPx = Height / PixSize;

class MyScene : public sgl::Scene
{
public:
    MyScene(int id);

    void onEvent(const sf::Event& event);
    void onUpdate(const sf::Time dt);
    void onRender(sf::RenderTarget& screen, const sf::Transform& transform);

private:
    char* pixAt(int x, int y);
    void setPixel(int x, int y);

    std::array<char, WidthPx * HeightPx> m_pixels;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::array<sf::Uint8, Width * Height * 4> m_pixelsData;
};

#endif

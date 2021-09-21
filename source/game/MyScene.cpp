#include <game/MyScene.hpp>

#include <Small/Core/SceneManager.hpp>
#include <Small/GameObjects/Manager.hpp>
#include <iostream>

constexpr char VoidVal = 1;  // No collider
constexpr char SandVal = 2;
constexpr char WaterVal = 3;
constexpr char TerrainVal = 4;  // Terrain collider
constexpr char DirtyFlag = -128;

MyScene::MyScene(int id) :
    sgl::Scene(id)
{
    m_pixels.fill(VoidVal);
    m_pixelsData.fill(0);

    m_texture.create(Width, Height);
    m_sprite.setTexture(m_texture);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sgl::GameObjects::FontManager::get().add("arial", std::move(font));

    sgl::GameObjects::TextManager::get().add("mouse", sf::Text("mouse:", sgl::GameObjects::FontManager::get()["arial"]));
}

void MyScene::onEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        int x = event.mouseButton.x / PixSize,
            y = event.mouseButton.y / PixSize;

        if (event.mouseButton.button == sf::Mouse::Button::Left)
            m_pixels[x + y * WidthPx] = SandVal;
        else if (event.mouseButton.button == sf::Mouse::Button::Right)
            m_pixels[x + y * WidthPx] = WaterVal;
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        int x = event.mouseMove.x / PixSize,
            y = event.mouseMove.y / PixSize;
        sgl::GameObjects::TextManager::get()["mouse"].setString("mouse: " + std::to_string(x) + "," + std::to_string(y));
    }
}

void MyScene::onUpdate(const sf::Time dt)
{
    for (std::size_t x = 0; x < WidthPx; ++x)
    {
        for (std::size_t y = 0; y < HeightPx; ++y)
        {
            const std::size_t pos = x + y * WidthPx;
            char& val = m_pixels[pos];

            if (char* pix = pixAt(x, y + 1); pix && *pix == VoidVal && (val == SandVal || val == WaterVal))
            {
                *pix = val | DirtyFlag;
                val = VoidVal | DirtyFlag;
                setPixel(x, y);
                setPixel(x, y + 1);
            }
            else if (char* pix = pixAt(x - 1, y + 1); pix && *pix == VoidVal && (val == SandVal || val == WaterVal))
            {
                *pix = val | DirtyFlag;
                val = VoidVal | DirtyFlag;
                setPixel(x, y);
                setPixel(x - 1, y + 1);
            }
            else if (char* pix = pixAt(x + 1, y + 1); pix && *pix == VoidVal && (val == SandVal || val == WaterVal))
            {
                *pix = val | DirtyFlag;
                val = VoidVal | DirtyFlag;
                setPixel(x, y);
                setPixel(x + 1, y + 1);
            }
            else if (char* pix = pixAt(x + 1, y); pix && *pix == VoidVal && val == WaterVal)
            {
                *pix = val | DirtyFlag;
                val = VoidVal | DirtyFlag;
                setPixel(x, y);
                setPixel(x + 1, y);
            }
            else if (char* pix = pixAt(x + 1, y); pix && *pix == VoidVal && val == WaterVal)
            {
                *pix = val | DirtyFlag;
                val = VoidVal | DirtyFlag;
                setPixel(x, y);
                setPixel(x + 1, y);
            }
        }
    }

    for (std::size_t i = 0; i < WidthPx * HeightPx; ++i)
        m_pixels[i] &= ~DirtyFlag;

    m_texture.update(m_pixelsData.data());
}

void MyScene::onRender(sf::RenderTarget& screen, const sf::Transform& transform)
{
    screen.draw(m_sprite, transform);
    screen.draw(sgl::GameObjects::TextManager::get()["mouse"], transform);
}

char* MyScene::pixAt(int x, int y)
{
    if (x >= 0 && y >= 0 && x < WidthPx && y < HeightPx)
        return m_pixels.data() + (x + y * WidthPx);
    return nullptr;
}

void MyScene::setPixel(int x, int y)
{
    std::size_t i = x + y * WidthPx;
    char pix = m_pixels[i] & ~DirtyFlag;

    sf::Color color = sf::Color::Transparent;
    switch (pix)
    {
        case VoidVal:
            color = sf::Color::Transparent;
            break;

        case SandVal:
            color = sf::Color(194, 178, 128);
            break;

        case WaterVal:
            color = sf::Color(28, 163, 236);
            break;

        case TerrainVal:
            color = sf::Color::Transparent;
            break;

        default:
            color = sf::Color::Magenta;
            break;
    }

    auto colorIt = [this, &color](int i) {
        if (i * 4 >= m_pixelsData.size())
            return;
        m_pixelsData[i * 4] = color.r;
        m_pixelsData[i * 4 + 1] = color.g;
        m_pixelsData[i * 4 + 2] = color.b;
        m_pixelsData[i * 4 + 3] = color.a;
    };

    colorIt(x * PixSize + y * PixSize * Width);
    colorIt(x * PixSize + 1 + y * PixSize * Width);
    colorIt(x * PixSize + (y * PixSize + 1) * Width);
    colorIt(x * PixSize + 1 + (y * PixSize + 1) * Width);
}

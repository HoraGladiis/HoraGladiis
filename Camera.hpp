#include <SFML/Graphics.hpp>

class Camera : public sf::View
{
private:
    float zoomFactor = 1.0;
    sf::Vector2f center;
    sf::RenderWindow *window;
    void updateWindow();

public:
    void assign(sf::RenderWindow &window);
    void resizeCamera(sf::Event event);
    void setZoomFactor(float zoomFactor);
    void setPosition(sf::Vector2f position);
    void setPosition();
    void move(sf::Vector2f &offset);
};

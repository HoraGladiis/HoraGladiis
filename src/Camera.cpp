#include "Camera.hpp"

void Camera::updateWindow()
{
    if (this->window == nullptr)
        return;

    this->window->setView(*this);
}

void Camera::assign(sf::RenderWindow &window)
{
    this->window = &window;
    this->updateWindow();
}

void Camera::resizeCamera(sf::Event event)
{
    if (event.type != sf::Event::Resized)
        return;

    this->setSize(event.size.width, event.size.height);
    this->zoom(this->zoomFactor);
    this->updateWindow();
}

void Camera::setZoomFactor(float zoomFactor)
{
    this->zoomFactor = zoomFactor;
}

void Camera::setPosition(sf::Vector2f position)
{
    this->setCenter(position);
    this->updateWindow();
}

void Camera::setPosition()
{
    this->setCenter(sf::Vector2f(0.0, 0.0));
}

void Camera::move(sf::Vector2f &offset)
{
    sf::View::move(offset); // call base method
    this->updateWindow();
}
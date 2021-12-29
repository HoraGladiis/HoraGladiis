#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class EventHandler
{
private:
    std::unordered_map<sf::Event::EventType, std::vector<std::function<void(sf::Event)>>> _handlers;
    tgui::Gui *gui = nullptr;
    tgui::Gui *invgui = nullptr;

public:
    EventHandler();
    ~EventHandler();
    void handleEvent(sf::RenderWindow &window);
    void addHandler(sf::Event::EventType eventType, std::function<void(sf::Event)> handler);
    void setGui(tgui::Gui *gui)
    {
        this->gui = gui;
    }

    void setInvGui(tgui::Gui *gui)
    {
        this->invgui = gui;
    }
};

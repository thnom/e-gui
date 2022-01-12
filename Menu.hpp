//
//  Menu.hpp
//  e-gui
//
//  Created by Thomas Courtman on 21/12/2021.
//

#ifndef Menu_hpp
#define Menu_hpp

#include "Component.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "include/rapidjson/rapidjson.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"

#include <map>
#include <string>
#include <unordered_map>

using ComponentPtr = std::shared_ptr<Component>;

class Menu
{
public:
    Menu(ComponentDisplay cd);
    
    std::vector<ComponentPtr> GetComponents();
    ComponentPtr GetClickedComponent(sf::Vector2i screen_selected);
    
private:
    std::unordered_map<std::string, ComponentPtr> m_components{};
    std::map<std::pair<int,int>, std::shared_ptr<Component> > m_pixel_screen_components{};
    std::vector<std::string> m_order{};
};

#endif /* Menu_hpp */

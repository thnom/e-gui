//
//  Menu.cpp
//  e-gui
//
//  Created by Thomas Courtman on 21/12/2021.
//

#include "Menu.hpp"

Menu::Menu(ComponentDisplay cd) : m_components(cd.m_map), m_pixel_screen_components(cd.m_screen), m_order(cd.m_order)
{
}

std::vector<ComponentPtr> Menu::GetComponents()
{
    std::vector<ComponentPtr> components;
    
    for (auto& comp : m_order) {
        
        components.push_back(m_components.find(comp)->second);
    }
    
    return components;
}

ComponentPtr Menu::GetClickedComponent(sf::Vector2i screen_selected)
{
    return m_pixel_screen_components.find(std::make_pair(screen_selected.x-1, screen_selected.y-1) )->second;
}

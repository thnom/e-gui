//
//  Menu.hpp
//  e-gui
//
//  Created by Thomas Courtman on 21/12/2021.
//

#ifndef GUI_hpp
#define GUI_hpp

#include "Parser.hpp"
#include "Component.hpp"
#include "Menu.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

class GUI
{
public:
    
    // Constructor
    GUI();
    
    // Functions
    void Update();
    std::shared_ptr<Menu> FindMenu(std::string menu_name);
    
private:
    // Variables
    sf::RenderWindow m_rw{};
    std::unordered_map<std::string, std::shared_ptr<Menu> > m_menus{};
    std::map<uint32_t, std::string> m_menus_z{};
};

#endif /* GUI_hpp */

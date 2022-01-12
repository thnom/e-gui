//
//  Component.hpp
//  e-gui
//
//  Created by Thomas Courtman on 21/12/2021.
//

#ifndef Component_hpp
#define Component_hpp

#include "EnumStruct.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "include/rapidjson/rapidjson.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"

#include <string>
#include <unordered_map>

class Component
{
public:
    Component(sf::RenderWindow& rw, std::string name, std::string img, Shaping size, Shaping pos, sf::Color colour, std::shared_ptr<Component> parent);
    
    std::shared_ptr<sf::Shape> GetGenericShape();
    //std::unique_ptr<sf::Texture> GetTexture();
    
    sf::Vector2f GetSize();
    sf::Vector2f GetPosition();
    
    std::string GetName() { return m_name; }
    
private:
    std::string m_name{};
    sf::Texture m_img;
    Shaping m_size{};
    Shaping m_position{};
    sf::Color m_colour{};
    
    sf::RenderWindow& m_rw;
    
    std::shared_ptr<sf::RectangleShape> m_rectangle{};
    
    std::shared_ptr<Component> m_parent{};
    
    sf::Vector2f SetSize();
    sf::Vector2f SetPosition();
};

#endif /* Menu_hpp */

//
//  Menu.cpp
//  e-gui
//
//  Created by Thomas Courtman on 21/12/2021.
//

#include "Component.hpp"

Component::Component(sf::RenderWindow& rw, std::string name, std::string img, Shaping size, Shaping pos, sf::Color colour, std::shared_ptr<Component> parent)
    : m_rw(rw), m_name(name), m_size(size), m_position(pos), m_colour(colour), m_parent(parent)
{
    sf::RectangleShape rect{};
    rect.setPosition(SetPosition() );
    rect.setSize(SetSize() );
    rect.setFillColor(colour);
    
    if (img != "") {
        m_img.loadFromFile(img);
        rect.setTexture(&m_img);
    }

    m_rectangle = std::make_shared<sf::RectangleShape>(rect);
}

std::shared_ptr<sf::Shape> Component::GetGenericShape()
{
    return m_rectangle;
}

sf::Vector2f Component::SetSize()
{
    std::uint32_t x{0};
    std::uint32_t y{0};
    
    if (m_size.m_type == RelativeType::Percent) {
        
        if (m_parent) {
            x = m_parent->GetSize().x;
            y = m_parent->GetSize().y;
        } else {
            x = m_rw.getSize().x;
            y = m_rw.getSize().y;
        }
        
        m_size.m_x = x * m_size.m_def_x;
        m_size.m_y = y * m_size.m_def_y;
    } else {
        
        if (m_parent) {
            x = m_parent->GetSize().x;
            y = m_parent->GetSize().y;
        }
        
        m_size.m_x = x + m_size.m_def_x;
        m_size.m_y = y + m_size.m_def_y;
    }
    
    return sf::Vector2f{m_size.m_x, m_size.m_y};
}

sf::Vector2f Component::SetPosition()
{
    std::uint32_t x{0};
    std::uint32_t y{0};
    
    if (m_position.m_type == RelativeType::Percent) {
        
        if (m_parent) {
            x = m_parent->GetPosition().x;
            y = m_parent->GetPosition().y;
        }
        
        m_position.m_x = x * m_position.m_def_x;
        m_position.m_y = y * m_position.m_def_y;
    } else {
        
        if (m_parent) {
            x = m_parent->GetPosition().x;
            y = m_parent->GetPosition().y;
        }
        
        m_position.m_x = x + m_position.m_def_x;
        m_position.m_y = y + m_position.m_def_y;
    }
    
    return sf::Vector2f{m_position.m_x, m_position.m_y};
}

sf::Vector2f Component::GetSize()
{
    return sf::Vector2f{m_size.m_x, m_size.m_y};
}

sf::Vector2f Component::GetPosition()
{
    return sf::Vector2f{m_position.m_x, m_position.m_y};
}

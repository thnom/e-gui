//
//  Menu.cpp
//  e-gui
//
//  Created by Thomas Courtman on 21/12/2021.
//

#include "GUI.hpp"

GUI::GUI()
{
    // Create the main window
    m_rw.create(sf::VideoMode(800, 600),"");
    
    m_menus = Parser::ParseMenu(m_rw, "../main.json");
    
    auto S{"S"};
}

void GUI::Update()
{
    // Start the game loop
    while (m_rw.isOpen() ) {
        
        // Process events
        sf::Event event;
        while (m_rw.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                m_rw.close();
            } else if (event.type == sf::Event::Resized) {
                
            } else if (event.type == sf::Event::MouseButtonPressed) {
                
                auto t = m_menus.find("main")->second->GetClickedComponent(sf::Mouse::getPosition(m_rw));
                std::cout << t->GetName() << "\n";
            }
            
        }
        // Clear screen
        m_rw.clear();
        
        for (auto& m : m_menus) {
            
            auto x = m.second->GetComponents();
            
            for (auto& s : x) {

                auto h = s->GetGenericShape().get();
                
                m_rw.draw(*h);
                
                auto p{"S"};
            }
             
        }

        // Update the window
        m_rw.display();
    }
}

std::shared_ptr<Menu> GUI::FindMenu(std::string menu_name)
{
    return m_menus.find(menu_name)->second;
}

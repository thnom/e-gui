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

    ParseMenu("main.json");
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
            if (event.type == sf::Event::Closed)
                m_rw.close();
        }
        // Clear screen
        m_rw.clear();
        
        for (auto& m : m_menus_z) {
            
            //m_rw.draw(m_menus.find(m.second)->second->GetRect() );
        }

        // Update the window
        m_rw.display();
    }
}

std::shared_ptr<Menu> GUI::FindMenu(std::string menu_name)
{
    return m_menus.find(menu_name)->second;
}

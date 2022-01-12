//
//  Parser.cpp
//  e-gui
//
//  Created by Thomas Courtman on 30/12/2021.
//

#include "Parser.hpp"

std::unordered_map<std::string, std::shared_ptr<Menu> > Parser::ParseMenu(sf::RenderWindow& rw, std::string menu_file)
{
    std::unordered_map<std::string, std::shared_ptr<Menu> > menus{};
    
    FILE* fp = fopen(menu_file.c_str(), "r");
    {
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer) );
         
        rapidjson::Document d;
        
        d.ParseStream(is);

        auto obj{d.GetObject()};
        
        std::string menu_name{ParseStringMember(obj, "name") };
        std::vector<Component> c{};
        if (obj.HasMember("components") ) {
            
            auto pc = ParseComponents(rw, obj["components"].GetArray() );
            menus.emplace(menu_name, std::make_shared<Menu>(pc) );
        }
    }
    fclose(fp);
    
    return menus;
}

sf::Color Parser::ParseBackgroundColour(JSONComponent comp)
{
    if (! (comp.HasMember("background_colour") || comp.HasMember("background_color") ) ) {
        return sf::Color{255,255,255,255};
    }
    
    std::string obj_name = (comp.HasMember("background_colour") ) ? "background_colour" : "background_color";
    
    int8_t r{static_cast<int8_t>(255)};
    int8_t g{static_cast<int8_t>(255)};
    int8_t b{static_cast<int8_t>(255)};
    int8_t a{static_cast<int8_t>(255)};
    
    bool has_colour{false};
    
    if (comp[obj_name.c_str()].IsObject() ) {
        auto bc = comp[obj_name.c_str()].GetObject();
        
        r = (bc.HasMember("r") ) ? bc["r"].GetInt() : 255;
        g = (bc.HasMember("g") ) ? bc["g"].GetInt() : 255;
        b = (bc.HasMember("b") ) ? bc["b"].GetInt() : 255;
        a = (bc.HasMember("a") ) ? bc["a"].GetInt() : 255;
                
        has_colour = true;
    } else {
        auto bc = comp[obj_name.c_str()].GetArray();
        
        if (bc.Size() >= 3) {
            r = bc[0].GetInt();
            g = bc[1].GetInt();
            b = bc[2].GetInt();
            
            if (bc.Size() == 4) {
                a = bc[3].GetInt();
            }
                   
            has_colour = true;
        } else {
            assert("Colour array has less than three colours");
        }
    }
    
    sf::Color colour{};
    if (has_colour) {
        colour = sf::Color{static_cast<sf::Uint8>(r)
                          ,static_cast<sf::Uint8>(g)
                          ,static_cast<sf::Uint8>(b)
                          ,static_cast<sf::Uint8>(a)};
    }
    
    return colour;
}

ComponentDisplay Parser::ParseComponents(sf::RenderWindow& rw, rapidjson::Document::Array obj)
{
    ComponentDisplay cd{};
    
    for (auto &component : obj) {
        
        bool has_name{false};
        bool has_parent{false};
        bool has_image{false};
        
        std::string type{ParseStringMember(component, "type") };
        std::string name{ParseStringMember(component, "name") };
        std::string parent{ParseStringMember(component, "parent") };
        std::string image{ParseStringMember(component, "image") };
        
        sf::Color colour{ParseBackgroundColour(component) };
        
        Shaping size{ParseShaping(component, ShapingType::Size) };
        Shaping pos{ParseShaping(component, ShapingType::Position) };
        
        std::shared_ptr<Component> pParent = (parent != "") ? cd.m_map.find(parent)->second : nullptr;
        
        auto comp = std::make_shared<Component>(rw, name, image, size, pos, colour, pParent);
        
        cd.m_order.push_back(name);
        cd.m_map.emplace(name, comp);
        
        auto p_x = comp->GetPosition().x;
        auto p_y = comp->GetPosition().y;
        auto s_x = comp->GetSize().x;
        auto s_y = comp->GetSize().y;
        
        for (int x = comp->GetPosition().x; x < comp->GetSize().x; x++) {
            
            for (int y = comp->GetPosition().y; y < comp->GetSize().y; y++) {
                
                std::pair<int, int> coords{x, y};
                cd.m_screen[coords] = comp;
            }
        }
    }
    
    return cd;
}


std::unique_ptr<sf::Texture> Parser::ParseImage(std::string img_path)
{
    sf::Texture t;
    t.loadFromFile(img_path);
    return std::make_unique<sf::Texture>(t);
}

/*
sf::RectangleShape Parser::ParseRectangle(rapidjson::Document::ConstObject obj)
{
    if (itr->value.IsObject() ) {
        
        auto obj = itr->value.GetObject();
    
        if (obj.HasMember("position") ) {
            
            Shaping position;
            auto pos = obj["position"].GetObject();
            
            position.m_x = (pos.HasMember("x") ) ? pos["x"].GetFloat() : 0;
            position.m_y = (pos.HasMember("y") ) ? pos["y"].GetFloat() : 0;
            
            if (pos.HasMember("type") && pos["type"] == "percent") {
                
                position.m_type = RelativeType::Percent;
                
                position.m_x *= m_rw.getSize().x;
                position.m_y *= m_rw.getSize().y;
            } else {
                position.m_type = RelativeType::Absolute;
            }
            
            rect.setPosition(sf::Vector2f(static_cast<float>(position.m_x), static_cast<float>(position.m_y) ) );
        } else {
            assert("Rectangle is missing position information");
        }
        
        if (obj.HasMember("size") ) {
            
            Shaping size;
            auto sz = obj["size"].GetObject();
        
            size.m_x = (sz.HasMember("x") ) ? sz["x"].GetFloat() : 0;
            size.m_y = (sz.HasMember("y") ) ? sz["y"].GetFloat() : 0;
            
            if (sz.HasMember("type") && sz["type"] == "percent") {
                
                size.m_type = RelativeType::Percent;
                
                // Multiply sizes by window sizes
                size.m_x *= m_rw.getSize().x;
                size.m_y *= m_rw.getSize().y;
            } else {
                
                size.m_type = RelativeType::Absolute;
            }
            
            rect.setSize(sf::Vector2f(static_cast<float>(size.m_x), static_cast<float>(size.m_y) ) );

        } else {
            assert("Rectangle is missing sizing information");
        }
        
        if (obj.HasMember("background_colour") || obj.HasMember("background_color")) {
            
            rect.setFillColor(ParseBackgroundColour(obj) );
        }
    }
}
*/

std::string Parser::ParseStringMember(JSONObject obj, std::string member)
{
    std::string s{(obj.HasMember(member.c_str() )) ? obj[member.c_str()].GetString() : ""};
    
    return s;
}

std::string Parser::ParseStringMember(JSONComponent comp, std::string member)
{
    std::string s{(comp.HasMember(member.c_str() )) ? comp[member.c_str()].GetString() : ""};
    
    return s;
}

Shaping Parser::ParseShaping(JSONComponent comp, ShapingType type)
{
    Shaping shape{};
    
    auto mem{(type == ShapingType::Size) ? "size" : "position"};
    
    if (comp.HasMember(mem) ) {
        
        if (comp[mem].IsObject() ) {
            
            auto o = comp[mem].GetObject();
            
            shape.m_def_x = (o.HasMember("x") ) ? o["x"].GetFloat() : 0;
            shape.m_def_y = (o.HasMember("y") ) ? o["y"].GetFloat() : 0;
            shape.m_type = (o.HasMember("type") && o["type"] == "percent") ? RelativeType::Percent : RelativeType::Absolute;
            
        } else if (comp[mem].IsArray() ) {
            
            auto s = comp[mem].GetArray();
            
            shape.m_def_x = s[0].GetFloat();
            shape.m_def_y = s[1].GetFloat();
            
            if (s.Capacity() > 2) {
                shape.m_type = (static_cast<std::string>(s[2].GetString() ) == "percent") ? RelativeType::Percent : RelativeType::Absolute;
            } else {
                
                if ( (shape.m_def_x >= 0 && shape.m_def_x <= 1)
                        && (shape.m_def_y >= 0 && shape.m_def_y <= 1) ) {
                    shape.m_type = RelativeType::Percent;
                } else {
                    shape.m_type = RelativeType::Absolute;
                }
            }
            
        } else {
            
            auto s = comp[mem].GetFloat();
            
            shape.m_type = (s >= 0 && s <= 1) ? RelativeType::Percent : RelativeType::Absolute;
            
            shape.m_def_x = s;
            shape.m_def_y = s;
        }
        
        return shape;
    }
}

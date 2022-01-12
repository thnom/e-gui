//
//  Parser.hpp
//  e-gui
//
//  Created by Thomas Courtman on 30/12/2021.
//

#ifndef Parser_hpp
#define Parser_hpp

#include "EnumStruct.hpp"
#include "Component.hpp"
#include "Menu.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "include/rapidjson/rapidjson.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"

#include <string>

namespace Parser
{
    using JSONComponent = const rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &;
    using JSONObject = rapidjson::GenericObject<false, rapidjson::GenericValue<rapidjson::UTF8<>>>;

    std::unordered_map<std::string, std::shared_ptr<Menu> > ParseMenu(sf::RenderWindow& rw, std::string menu_file);
    sf::Color ParseBackgroundColour(JSONComponent comp);
    ComponentDisplay ParseComponents(sf::RenderWindow& rw, rapidjson::Document::Array obj);
    std::unique_ptr<sf::Texture> ParseImage(std::string img_path);
    Shaping ParseShaping(JSONComponent comp, ShapingType type);
    //std::pair<ShapeType,std::unique_ptr<sf::Shape> > ParseShape(Component c);

    std::string ParseStringMember(JSONObject obj, std::string member);
    std::string ParseStringMember(JSONComponent comp, std::string member);
}

#endif /* Parser_hpp */

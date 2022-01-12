//
//  EnumStruct.hpp
//  e-gui
//
//  Created by Thomas Courtman on 30/12/2021.
//

#ifndef EnumStruct_hpp
#define EnumStruct_hpp

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum class RelativeType
{
    Absolute,
    Percent
};

enum class ShapeType
{
    Not_Defined = -1,
    Rectangle = 0,
    Circle,
    Convex
};

enum class ShapingType
{
    Size,
    Position
};

struct Shaping
{
    RelativeType m_type;
    float m_def_x;
    float m_def_y;
    float m_x;
    float m_y;
};

class Component;
struct ComponentDisplay
{
    std::unordered_map<std::string, std::shared_ptr<Component> > m_map;
    std::map<std::pair<int,int>, std::shared_ptr<Component> > m_screen;
    std::vector<std::string> m_order;
};

#endif /* EnumStruct_hpp */

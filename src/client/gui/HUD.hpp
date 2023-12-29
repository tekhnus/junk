#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

namespace sfg {
typedef std::function<void(void)> Delegate;
}

namespace junk
{

class HUD
{
public:
    void addState(std::string name, sfg::Delegate delegate);
    sfg::Delegate getEvent(std::string name);
private:
    std::map<std::string, sfg::Delegate> bindings;
};

}

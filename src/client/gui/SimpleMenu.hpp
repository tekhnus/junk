#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

namespace junk
{

class SimpleMenu
{
public:
  SimpleMenu(sfg::Desktop& desktop, std::string title);
  void addItem(std::string name, sfg::Delegate slot);
  sfg::Window::Ptr getWindow();
private:
  sfg::Window::Ptr window;
  sfg::Box::Ptr box;
  sfg::Desktop m_desktop;
};

}
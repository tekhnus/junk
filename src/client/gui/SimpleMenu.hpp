#pragma once

#include <SFGUI/Box.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>
#include <SFML/Graphics.hpp>

namespace sfg {
typedef std::function<void(void)> Delegate;
}

namespace junk {

class SimpleMenu {
 public:
  SimpleMenu(sfg::Desktop& desktop, std::string title, sf::Window& topWindow);
  void addItem(std::string name, sfg::Delegate slot);
  sfg::Window::Ptr getWindow();

 private:
  sfg::Window::Ptr window;
  sfg::Box::Ptr box;
  sfg::Desktop& m_desktop;
};

}  // namespace junk

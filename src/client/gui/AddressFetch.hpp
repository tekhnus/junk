#pragma once

#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Button.hpp>
#include <SFML/Graphics.hpp>
#include <client/config/ClientConfig.hpp>

namespace sfg {
typedef std::function<void(void)> Delegate;
}

namespace junk
{

class AddressFetch
{
public:
  AddressFetch(sfg::Desktop& desktop, sf::Window& topWindow);
  void onOK(sfg::Delegate slot);
  sf::String getAddress();
  sfg::Window::Ptr getWindow();
private:
  void updateHistory();
  sfg::Window::Ptr window;
  sfg::Box::Ptr box;
  sfg::Entry::Ptr field;
  sfg::Button::Ptr ok;
  junk::ClientConfig config;
  sfg::Desktop& m_desktop;
};

}

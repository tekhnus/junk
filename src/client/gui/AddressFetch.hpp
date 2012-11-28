#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include <client/config/ClientConfig.hpp>

namespace junk
{

class AddressFetch
{
public:
  AddressFetch(sfg::Desktop& desktop);
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
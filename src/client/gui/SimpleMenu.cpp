#include "SimpleMenu.hpp"
#include <SFGUI/Button.hpp>

namespace junk
{

SimpleMenu::SimpleMenu(sfg::Desktop& desktop, std::string title, sf::Window& topWindow) :  window(sfg::Window::Create()),
                            box(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
			    m_desktop(desktop)
{

  window->Add(box);
  window->SetTitle(title);
  sf::Vector2<unsigned int> desiredSize;
  desiredSize = topWindow.getSize() / 4u;
  window->SetRequisition(sf::Vector2<float>(desiredSize));  
  window->SetPosition(sf::Vector2<float>((topWindow.getSize() - desiredSize) / 2u));
  m_desktop.Add(window);
}

void SimpleMenu::addItem(std::string name, sfg::Delegate slot)
{
  sfg::Button::Ptr button(sfg::Button::Create(name));
  button->GetSignal(sfg::Widget::OnLeftClick).Connect(slot);
  box->Pack(button);
}

sfg::Window::Ptr SimpleMenu::getWindow()
{
  return window;
}

}

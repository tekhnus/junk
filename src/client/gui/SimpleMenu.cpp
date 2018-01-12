#include "SimpleMenu.hpp"
#include <SFGUI/Button.hpp>

namespace junk
{

SimpleMenu::SimpleMenu(sfg::Desktop& desktop, std::string title) :  window(sfg::Window::Create()),
                            box(sfg::Box::Create(sfg::Box::Orientation::VERTICAL)),
			    m_desktop(desktop)
{

  window->Add(box);
  window->SetTitle(title);
  window->SetRequisition(sf::Vector2f(200.0f, 200.0f));  
  window->SetPosition(sf::Vector2f(200.0f, 200.0f));
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

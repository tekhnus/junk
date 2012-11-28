#include "SimpleMenu.hpp"

namespace junk
{

SimpleMenu::SimpleMenu(sfg::Desktop& desktop) :  window(sfg::Window::Create()),
                            box(sfg::Box::Create(sfg::Box::VERTICAL)),
                            m_desktop(desktop)
{
  window->Add(box);
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
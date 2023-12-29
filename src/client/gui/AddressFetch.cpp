#include "AddressFetch.hpp"

namespace junk {

AddressFetch::AddressFetch(sfg::Desktop& desktop, sf::Window& topWindow)
    : window(sfg::Window::Create()),
      box(sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL)),
      field(sfg::Entry::Create("enter server address here")),
      ok(sfg::Button::Create("OK")),
      m_desktop(desktop) {
  window->Add(box);
  window->SetTitle("Enter server address");
  box->Pack(field);
  box->Pack(ok);

  sf::Vector2<unsigned int> desiredSize{topWindow.getSize().x / 2, 70};
  window->SetRequisition(sf::Vector2<float>(desiredSize));
  window->SetPosition(
      sf::Vector2<float>((topWindow.getSize() - desiredSize) / 2u));

  try {
    config.load("/tmp/client_config.json");
  } catch (std::exception ex) {
  }

  if (!config.recent.empty()) {
    field->SetText(config.recent.back());
  }

  ok->GetSignal(sfg::Widget::OnLeftClick)
      .Connect(std::bind(&AddressFetch::updateHistory, this));
  field->SetRequisition(sf::Vector2f(300.f, 0.f));

  m_desktop.Add(window);
}

void AddressFetch::onOK(sfg::Delegate slot) {
  ok->GetSignal(sfg::Widget::OnLeftClick).Connect(slot);
}

sf::String AddressFetch::getAddress() {
  return field->GetText();
}

sfg::Window::Ptr AddressFetch::getWindow() {
  return window;
}

void AddressFetch::updateHistory() {
  config.recent.push_back(getAddress());
  config.save("/tmp/client_config.json");
}

}  // namespace junk

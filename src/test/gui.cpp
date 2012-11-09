#include "client/gui/SimpleMenu.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

void test()
{
  std::cout << "Hello, world!" << std::endl;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(512, 256), "GUI test");
  window.resetGLStates();
  sfg::SFGUI sfgui;
  junk::SimpleMenu menu;
  menu.addItem("Say hello!", test);
  sf::Clock clock;
  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      menu.getWindow()->HandleEvent(event);
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    menu.getWindow()->Update(clock.restart().asSeconds());
    window.clear();
    sfgui.Display(window);
    window.display();
  }
  return 0;
}
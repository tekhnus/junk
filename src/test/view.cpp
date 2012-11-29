#include "client/view/ClientView.hpp"
#include "client/model/ClientModel.hpp"
#include "client/config/ClientConfig.hpp"
#include "client/gui/AddressFetch.hpp"
#include "client/gui/HUD.hpp"
#include "client/gui/SimpleMenu.hpp"
#include "common/logger/Logger.hpp"
#include <SFML/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <mutex>
#include <iostream>

junk::client::view::ClientView view;
junk::client::model::ClientModel model;

sfg::SFGUI sfgui;
sfg::Desktop desktop;
sf::ContextSettings settings(0, 0, 2);
sf::RenderWindow window(sf::VideoMode(720, 720), "Title", sf::Style::Default, settings);
junk::SimpleMenu mainMenu(desktop);
junk::AddressFetch fetcher(desktop);
junk::HUD hud;

void init()
{
  mainMenu.getWindow()->Show(true);
}

void play()
{
  mainMenu.getWindow()->Show(false);
  fetcher.getWindow()->Show(true);
}

void connect()
{
  model.connectToServer(fetcher.getAddress(), 7777);
  fetcher.getWindow()->Show(false);
  view.wake();
}

void quit()
{
  window.close();
}

sf::Shader effect;
sf::RenderTexture tex;

void drawWorld()
{
  model.update();
  view.update();
  tex.clear();
  tex.draw(view);
  tex.display();
  sf::Sprite screen(tex.getTexture());
  window.draw(screen, sf::RenderStates(&effect));
}

int main(int argc, char** argv)
{
  if(!desktop.LoadThemeFromFile("Theme.theme"))
  {
    junk::dbg << "Theme was not loaded";
  }
  hud.addState("init", init);
  hud.addState("connect", play);
  hud.addState("game", connect);
  hud.addState("exit", quit);
  model.shutdownSignal.connect(boost::bind(init));
  mainMenu.addItem("Play", hud.getEvent("connect"));
  mainMenu.addItem("Exit", hud.getEvent("exit"));
  fetcher.onOK(hud.getEvent("game"));
  fetcher.getWindow()->Show(false);
  view.window = &window;
  tex.create(720, 720);

  junk::dbg.debug("antialiasing: ", window.getSettings().antialiasingLevel);

  if (!effect.loadFromFile("fx.frag", sf::Shader::Type::Fragment))
  {
    junk::dbg << "Superweak. shader not loaded";
  }

  window.resetGLStates();

  view.setModel(&model);
  window.setFramerateLimit(60);

  sf::Clock clock;
  for (int counter = 0; window.isOpen(); ++counter)
  {
    view.safe.lock();

    sf::Event event;
    while(window.pollEvent(event))
    {
      //desktop.HandleEvent(event);
      mainMenu.getWindow()->HandleEvent(event);
      fetcher.getWindow()->HandleEvent(event);
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    double t = clock.restart().asSeconds();

    window.clear();

    if (model.alive)
    {
      drawWorld();
    }

    fetcher.getWindow()->Update(t);
    mainMenu.getWindow()->Update(t);
    sfgui.Display(window);

    window.display();

    view.safe.unlock();
    sf::sleep(sf::milliseconds(30));
  }

  return 0;
}

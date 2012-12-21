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
junk::SimpleMenu mainMenu(desktop, "Main menu");
junk::SimpleMenu deadMenu(desktop, "You are dead");
junk::SimpleMenu pauseMenu(desktop, "Game menu");
junk::AddressFetch fetcher(desktop);
junk::HUD hud;
bool showPause = true;

void init()
{
  deadMenu.getWindow()->Show(false);
  mainMenu.getWindow()->Show(true);
  fetcher.getWindow()->Show(false);
}

void play()
{
  mainMenu.getWindow()->Show(false);
  fetcher.getWindow()->Show(true);
}

void connect()
{
  model.reset();
  view.reset();
  model.connectToServer(fetcher.getAddress(), 7777);
  fetcher.getWindow()->Show(false);
  view.wake();
}

void quit()
{
  window.close();
}

void drawWorld()
{
  model.update();
  view.update();
  window.draw(view);
  // window.update();
}

void changePause()
{
  showPause = !showPause;
  pauseMenu.getWindow()->Show(showPause);
}

void dead()
{
  deadMenu.getWindow()->Show(true);
  if (showPause) {
    changePause();
  }
}


int main(int argc, char** argv)
{
  if(!desktop.LoadThemeFromFile("/usr/share/junk/Theme.theme"))
  {
    junk::dbg << "Theme was not loaded";
  }
  hud.addState("init", init);
  hud.addState("connect", play);
  hud.addState("game", connect);
  hud.addState("exit", quit);
  hud.addState("dead", dead);

  model.shutdownSignal.connect(boost::bind(dead));
  mainMenu.addItem("Play", hud.getEvent("connect"));
  mainMenu.addItem("Exit", hud.getEvent("exit"));
  fetcher.onOK(hud.getEvent("game"));
  deadMenu.addItem("Return to main menu", hud.getEvent("init"));
  view.window = &window;

  pauseMenu.addItem("Continue playing", changePause);

  junk::dbg.debug("antialiasing: ", window.getSettings().antialiasingLevel);

  window.resetGLStates();

  view.setModel(&model);
  window.setFramerateLimit(60);

  init();
  changePause();

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
      deadMenu.getWindow()->HandleEvent(event);
      pauseMenu.getWindow()->HandleEvent(event);

      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape && model.alive) {
          changePause();
        }
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
    deadMenu.getWindow()->Update(t);
    pauseMenu.getWindow()->Update(t);
    sfgui.Display(window);

    window.display();

    view.safe.unlock();
    sf::sleep(sf::milliseconds(30));
  }

  return 0;
}

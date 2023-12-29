#include "client/view/ClientView.hpp"
#include "client/model/ClientModel.hpp"
#include "client/config/ClientConfig.hpp"
#include "client/gui/AddressFetch.hpp"
#include "client/gui/HUD.hpp"
#include "client/gui/SimpleMenu.hpp"
#include "common/logger/Logger.hpp"
#include "common/utils/Resource.hpp"
#include <SFML/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <libgen.h>
#include <mutex>
#include <iostream>

class App {

junk::client::view::ClientView view;
junk::client::model::ClientModel model;

sfg::SFGUI sfgui;
sfg::Desktop desktop;
sf::ContextSettings settings;
sf::RenderWindow window;
junk::SimpleMenu mainMenu;
junk::SimpleMenu deadMenu;
junk::SimpleMenu pauseMenu;
junk::AddressFetch fetcher;
junk::HUD hud;
bool showPause;

void init()
{
  deadMenu.getWindow()->Show(false);
  mainMenu.getWindow()->Show(true);
  fetcher.getWindow()->Show(false);
}

void play()
{
  // printf("%d\n", mainMenu.getWindow() == nullptr);
  mainMenu.getWindow()->Show(false);
  fetcher.getWindow()->Show(true);
  // printf("%d\n", mainMenu.getWindow() == nullptr);
}

void connectXXX()
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
public:
App() : settings(0, 0, 2),
        window(sf::VideoMode(view.getWindowWidth(), view.getWindowHeigth()), "Junk", sf::Style::Default, settings),
	mainMenu(desktop, "Main menu", window),
	deadMenu(desktop, "You are dead", window),
	pauseMenu(desktop, "Game menu", window),
	fetcher(desktop, window),
	showPause(true)
{
  if(!desktop.LoadThemeFromFile(get_resource_path("Theme.theme")))
  {
    junk::dbg << "Theme was not loaded";
  }
  hud.addState("init", std::bind(&App::init, this));
  hud.addState("connect", std::bind(&App::play, this));
  hud.addState("game", std::bind(&App::connectXXX, this));
  hud.addState("exit", std::bind(&App::quit, this));
  hud.addState("dead", std::bind(&App::dead, this));

  // model.shutdownSignal.connect(boost::bind(&App::dead, this));
  mainMenu.addItem("Play", hud.getEvent("connect"));
  mainMenu.addItem("Exit", hud.getEvent("exit"));
  fetcher.onOK(hud.getEvent("game"));
  deadMenu.addItem("Return to main menu", hud.getEvent("init"));
  view.window = &window;

  pauseMenu.addItem("Continue playing", std::bind(&App::changePause, this));

  junk::dbg.debug("antialiasing: ", window.getSettings().antialiasingLevel);

  window.resetGLStates();

  view.setModel(&model);
  window.setFramerateLimit(60);

  // printf("Before init: %d\n", mainMenu.getWindow() == nullptr);
  init();
  // printf("After init, before changePause: %d\n", mainMenu.getWindow() == nullptr);
  changePause();

  // printf("After changePause: %d\n", mainMenu.getWindow() == nullptr);
  sf::Clock clock;
  for (; window.isOpen(); )
  {
	
    view.processInput();

    sf::Event event;
    while(window.pollEvent(event))
    {
      desktop.HandleEvent(event);
      //mainMenu.getWindow()->HandleEvent(event);
      //fetcher.getWindow()->HandleEvent(event);
      //deadMenu.getWindow()->HandleEvent(event);
      //pauseMenu.getWindow()->HandleEvent(event);

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

    // printf("After events: %d\n", mainMenu.getWindow() == nullptr);
    double t = clock.restart().asSeconds();

    desktop.Update(t);
    window.clear();


  // printf("After updating and clearing: %d\n", mainMenu.getWindow() == nullptr);

    if (model.alive)
    {
      drawWorld();
    }

  // printf("Before sfgui display: %d\n", mainMenu.getWindow() == nullptr);
    //fetcher.getWindow()->Update(t);
    //mainMenu.getWindow()->Update(t);
    //deadMenu.getWindow()->Update(t);
    //pauseMenu.getWindow()->Update(t);
    sfgui.Display(window);

  // printf("Before window display: %d\n", mainMenu.getWindow() == nullptr);
    window.display();

    sf::sleep(sf::milliseconds(30));
  }

}


};

int main(int , char** argv)
{
  resource_root = std::string(dirname(dirname(argv[0]))) + "/share/junk";
  junk::client::view::loadFont();
  std::cerr << "(1) Resource root is " << resource_root << std::endl;
  App app{};
  return 0;
}

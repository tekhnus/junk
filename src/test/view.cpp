#include "client/view/ClientView.hpp"
#include "client/model/ClientModel.hpp"
#include "client/config/ClientConfig.hpp"
#include "client/gui/AddressFetch.hpp"
#include <SFML/Window.hpp>
#include <SFGUI/SFGUI.hpp>
#include <mutex>

sf::Vector2f getDiff(float time, bool up, bool down, bool left, bool right)
{
  time = 1;
  float dx = 0;
  float dy = 0;
  if (up)
    dy += -time;

  if (down)
    dy += time;

  if (left)
    dx += -time;

  if (right)
    dx += time;

  if (fabs(dx) > 0.0 && fabs(dy) > 0.0)
  {
    dx /= sqrt(2.0);
    dy /= sqrt(2.0);
  }
  return sf::Vector2f(dx, dy);
}

bool prevUp, prevDown, prevLeft, prevRight;
bool prevClicked;
junk::client::view::ClientView view;
junk::client::model::ClientModel model;

std::mutex updateLock;

int32_t id = -1;

//sf::RenderWindow window(sf::VideoMode(512, 512), "Title", sf::Style::Fullscreen);
sfg::SFGUI sfgui;
sf::RenderWindow window(sf::VideoMode(720, 720), "Title");
junk::AddressFetch fetcher;

void processInput()
{
  while (true)
  {
    if (id == -1)
      continue;

    updateLock.lock();

    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    sf::Vector2f diff = getDiff(1.0, up, down, left, right);
    if (up != prevUp || down != prevDown || left != prevLeft || right != prevRight)
    {
      view.move(diff);
      prevUp = up;
      prevDown = down;
      prevLeft = left;
      prevRight = right;
    }

    bool clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if (clicked != prevClicked) {
      if(clicked)
        view.fire();
      prevClicked = clicked;
    }

    sf::Vector2i posI = sf::Mouse::getPosition(window);
    sf::Vector2f pos = sf::Vector2f(posI.x, posI.y);
    view.rotate(pos);

    updateLock.unlock();

    std::chrono::milliseconds tm(30);
    std::this_thread::sleep_for(tm);
  }
}

void connect()
{
  id = model.connectToServer(fetcher.getAddress(), 7777);
  fetcher.getWindow()->Show(false);
}

void drawWorld()
{
  model.update();
  window.draw(view);
}

int main(int argc, char** argv)
{
  
  fetcher.onOK(connect);
  window.resetGLStates();

  // std::string address;
  // if (!config.recent.empty()) {
  //   std::cout << "Enter server address (hit ENTER for " << config.recent.back() << "): ";
  //   getline(std::cin, address);
  //   if (address.empty()) {
  //     address = config.recent.back();
  //   }
  // } else {
  //   std::cout << "Enter server address: ";
  //   std::cin >> address;
  // }
  // config.recent.push_back(address);
  // config.save("client_config.json");

  view.setModel(&model);
  window.setFramerateLimit(60);

  std::thread t(&processInput);

  sf::Clock clock;
  for (int counter = 0; window.isOpen(); ++counter)
  {
    updateLock.lock();

    sf::Event event;
    while(window.pollEvent(event))
    {
      fetcher.getWindow()->HandleEvent(event);
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    double t = clock.restart().asSeconds();

    window.clear();

    if (id != -1)
    {
      drawWorld();
    }

    fetcher.getWindow()->Update(t);
    sfgui.Display(window);

    window.display();

    updateLock.unlock();
    sf::sleep(sf::milliseconds(30));
  }

  return 0;
}

#include "client/view/ClientView.hpp"
#include "client/model/ClientModel.hpp"
#include <SFML/Window.hpp>

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
junk::client::view::ClientView view;
junk::client::model::ClientModel model;

std::mutex updateLock;

int32_t id = -1;

//sf::RenderWindow window(sf::VideoMode(512, 512), "Title", sf::Style::Fullscreen);
sf::RenderWindow window(sf::VideoMode(512, 512), "Title");

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

    /*if (view.players.find(id) != view.players.end())
    {
      sf::Vector2i posI = sf::Mouse::getPosition(window);
      sf::Vector2f pos = sf::Vector2f(posI.x, posI.y);
      sf::Vector2f player = view.players.at(id).getPosition();
      sf::Vector2f rot = player - pos;
      view.rotate(-rot);
    }*/

    updateLock.unlock();

    std::chrono::milliseconds tm(30);
    std::this_thread::sleep_for(tm);
  }
}

int main(int argc, char** argv)
{
  //sf::RenderWindow window(sf::VideoMode(512, 512), "Title", sf::Style::Fullscreen);
  //window.show();
  std::string address("localhost");
  //std::string address("192.168.1.36");
  if (argc > 1)
  {
    address = std::string(argv[1]);
  }
  view.setModel(&model);
  id = model.connectToServer(address, 7777);
  window.setFramerateLimit(60);

  // u.setPosition(sf::Vector2f(100.0, 100.0));
  //sf::Font font = sf::Font::getDefaultFont();

  std::thread t(&processInput);

  sf::Clock clock;
  clock.restart();
  int counter;

  while (window.isOpen())
  {
    std::cerr << "HERE" << std::endl;
    updateLock.lock();

    window.clear();
    model.update();
    view.update();
    window.draw(view);

    window.display();
    counter++;
    std::cerr << " FPS: " << float(counter) / clock.getElapsedTime().asSeconds() << std::endl;

    updateLock.unlock();
    sf::sleep(sf::milliseconds(30));
  }

  return 0;
}

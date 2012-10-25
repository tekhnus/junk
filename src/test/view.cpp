#include "client/view/ClientView.hpp"
#include "client/controller/ClientController.hpp"
#include "client/model/ClientModel.hpp"
#include <SFML/Window.hpp>

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


int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Title");
	//window.show();
	junk::ClientView view;
	junk::ClientModel model;
	junk::ClientController control(view, model);
	// junk::View view;

	//model.connectToServer("localhost", 7777);
	model.connectToServer("192.168.1.34", 7777);
	window.setFramerateLimit(60);

	//junk::PlayerUnit u("Unit", sf::Vector2f(0.0, 0.0), sf::Vector2f(1.0, 1.0));
	// view.addPlayer(sf::Vector2f(100.0, 100.0), sf::Vector2f(100.0, 100.0));

	// u.setPosition(sf::Vector2f(100.0, 100.0));
	//sf::Font font = sf::Font::getDefaultFont();

	bool prevUp, prevDown, prevLeft, prevRight;

	while (window.isOpen())
	{
		window.clear();
		model.update();
		view.update();
		window.draw(view);

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
   	
   		//sf::sleep(sf::seconds(0.01f));

		//u.update();
		//window.draw(u);
		//window.draw(sf::Text("Hello", font));
		window.display();
	}

	return 0;
}

#include "client/view/Unit.hpp"
#include <SFML/Window.hpp>

int main ()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Title");
	//window.show();

	// junk::View view;
	junk::PlayerUnit u("Unit", sf::Vector2f(100.0, 100.0), sf::Vector2f(100.0, 100.0));
	// view.addPlayer(sf::Vector2f(100.0, 100.0), sf::Vector2f(100.0, 100.0));

	// u.setPosition(sf::Vector2f(100.0, 100.0));
	sf::Font font;
	font.loadFromFile("/Users/mekagem/junk/bin/arial.ttf");

	while (window.isOpen())
	{
		window.clear();
		u.update();
		window.draw(u);
		window.draw(sf::Text("Hello", font));
		window.display();
	}

	return 0;
}

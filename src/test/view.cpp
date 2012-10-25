#include "client/view/ClientView.hpp"
#include "client/controller/ClientController.hpp"
#include "client/model/ClientModel.hpp"
#include <SFML/Window.hpp>




int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Title", sf::Style::Fullscreen);
	//window.show();
	junk::ClientView view;
	junk::ClientModel model;
	junk::ClientController control(view, model);
	// junk::View view;

	model.connectToServer("localhost", 7777);
	//model.connectToServer("192.168.1.34", 7777);
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

		
   	
   		//sf::sleep(sf::seconds(0.01f));

		//u.update();
		//window.draw(u);
		//window.draw(sf::Text("Hello", font));
		window.display();
	}

	return 0;
}

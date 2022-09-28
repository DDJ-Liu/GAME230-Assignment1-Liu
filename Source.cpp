/* SFML Includes             *
 * Add to every SFML project */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>


/*
Features:
1, Maintain a sub window to show the status of paintbrush //so much strange bugs, so abandoned
2, Can change shape, color, size of the brush
3, Screenshot, clear
4, Maybe erasor?
5, Any other interesting ideas?

*/



 // Our global parameters, shapes of the brush
const int BrushRadius = 10;
float scale = 1;
sf::Color BrushColor = sf::Color::Green;
sf::CircleShape shape1(BrushRadius);
sf::RectangleShape shape2(sf::Vector2f(BrushRadius, BrushRadius));
sf::ConvexShape shape3(3);
sf::RectangleShape shape4(sf::Vector2f(0.5 * BrushRadius, 2 * BrushRadius));

bool KeyboardInput(sf::Event event, sf::Shape& shape);//function to handle the keyboard input and make changes to the brush
void UpdateSubWindow(sf::RenderWindow& window);//abandoned
void Screenshot(sf::RenderWindow& window);//realize the Screenshot saving feature

// Main, our applicaiton entry function
int main()
{
	// Create the window for the game
	// All rendering happens here
	sf::RenderWindow window(sf::VideoMode(800, 600), "Assignment1 by Liu");

	//Initialization of the brush and some brush shape
	sf::Shape& shape = shape1;
	shape.setFillColor(BrushColor);
	shape.setScale(scale, scale);

	shape3.setPoint(0, sf::Vector2f(0, 0));
	shape3.setPoint(1, sf::Vector2f(BrushRadius, 0));
	shape3.setPoint(2, sf::Vector2f(0, BrushRadius));

	//sth goes wrong with the input reading when the sub window is on, so I abort it :(
	//sf::RenderWindow subWindow(sf::VideoMode(600, 400), "",0);




	 
	// This is our game loop!
	// All input, logic, and rendering should be handled here
	while (window.isOpen())
	{
		//set the position of the sub window to follow the main window
		//sf::Vector2i subWindowPos(window.getPosition().x + window.getSize().x, window.getPosition().y + 50);
		//subWindow.setPosition(subWindowPos);

		// Check for events from the window
		// E.g., is the window being closed?
		sf::Event event;
		while (window.pollEvent(event))
		{
			//listening to the keyboard input and handle it
			if (event.type == sf::Event::KeyPressed) {
				KeyboardInput(event, shape);
				shape.setFillColor(BrushColor);
				shape.setScale(scale, scale);
			}
			//Clear the window when press "Esc"
			if (event.key.code == sf::Keyboard::Escape) {
				window.clear();
			}
			//Take a screenshot when press spacebar
			if (event.key.code == sf::Keyboard::Space) {
				Screenshot(window);
			}
			if (event.type == sf::Event::Closed)
				window.close();

		}



		// This clears the window at the beginning of every frame
		// If we comment this out, it is a very simple way to create a paintbrush effect since the window is never cleared
		//window.clear();




		// Set the position of our "brush" to the mouse position
		// Don't forget to offset by the "brush" radius to center it on the mouse position
		shape.setPosition(sf::Mouse::getPosition(window).x - BrushRadius, sf::Mouse::getPosition(window).y - BrushRadius);

		// Draw our "brush" to the window buffer when left clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			window.draw(shape);
		}

		// Display the window buffer for this frame
		window.display();
		//subWindow.display();
	}

	// The game has exited normally so send a normal exit status integer back
	return 0;
}


bool KeyboardInput(sf::Event event, sf::Shape& shape) {
	switch (event.key.code) {
		//Brush color
		case sf::Keyboard::Q:
			BrushColor = sf::Color::Red;
			std::cout << "Red Color" << std::endl;
			return true;
		case sf::Keyboard::W:
			BrushColor = sf::Color::Green;
			std::cout << "Green Color" << std::endl;
			return true;
		case sf::Keyboard::E:
			BrushColor = sf::Color::Blue;
			std::cout << "Blue Color" << std::endl;
			return true;
		case sf::Keyboard::R:
			BrushColor = sf::Color::White;
			std::cout << "White Color" << std::endl;
			return true;
		case sf::Keyboard::T:
			BrushColor = sf::Color::Black;
			std::cout << "Black Color" << std::endl;
			return true;
		//Brush size
		case sf::Keyboard::Up:
			scale += 0.2;
			std::cout << "Bursh Size Up" << std::endl;
			return true;
		case sf::Keyboard::Down:
			if (scale > 0.3) {
				scale -= 0.2;
				std::cout << "Bursh Size Down" << std::endl;
			}
			else {
				std::cout << "Bursh Size Minimum" << std::endl;
			}
			return true;
		//Brush shape
		case sf::Keyboard::Num1:
			shape = sf::CircleShape(shape1);
			std::cout << "Bursh Shape 1" << std::endl;
			return true;
		case sf::Keyboard::Num2:
			shape = sf::RectangleShape(shape2);
			std::cout << "Bursh Shape 2" << std::endl;
			return true;
		case sf::Keyboard::Num3:
			shape = sf::ConvexShape(shape3);
			std::cout << "Bursh Shape 3" << std::endl;
			return true;
		case sf::Keyboard::Num4:
			shape = sf::RectangleShape(shape4);
			std::cout << "Bursh Shape 4" << std::endl;
			return true;
		default:
		return false;
	}
	return false;
}

void Screenshot(sf::RenderWindow& window) {
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	if (texture.copyToImage().saveToFile("Homework 1 Screenshot.png"))
	{
		std::cout << "Screenshot saved to Homework 1 Screenshot.png" << std::endl;
	}
}

void UpdateSubWindow(sf::RenderWindow window) {
	return;
}
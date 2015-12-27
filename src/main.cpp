/* Memesnake Game
 * Copyright (C) 2015 Rubyist
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "gamestate.hpp"

#include <cstdlib>
#include <iostream>

void process_events(sf::RenderWindow& win, Memesnake& snake)
{
	sf::Event event;
	while (win.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			win.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Left:
				snake.set_direction(Direction::left);
				break;
			case sf::Keyboard::Right:
				snake.set_direction(Direction::right);
				break;
			case sf::Keyboard::Up:
				snake.set_direction(Direction::up);
				break;
			case sf::Keyboard::Down:
				snake.set_direction(Direction::down);
				break;
			default:
				break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	const char *word;
	if (argc < 2) word = "MEMESNAKE";
	else word = argv[1];

	sf::RenderWindow win(sf::VideoMode(640, 480), "Memesnake");
	sf::Font font;

	if (!font.loadFromFile("BPmono.ttf")) {
		std::cerr << "Could not load font file\n";
		return EXIT_FAILURE;
	}

	Memesnake snake(font, word[0]);

	GameState::init(word, snake, win, font);

	while (win.isOpen()) {
		// Handle keyboard events
		process_events(win, snake);

		// Clear previous data from screen
		win.clear(sf::Color::Black);

		// Update game
		GameState::update();

		// Update screen
		win.display();

		if (GameState::lost()) {
			std::cout << "You have lost. Your score was: "
			          << GameState::score() << std::endl;
			win.close();
		}
	}

	return EXIT_SUCCESS;
}
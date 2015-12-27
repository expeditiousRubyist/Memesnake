/* Memesnake Game State Module Header
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

#include <ctime>
#include <cstdlib>

namespace GameState {

	static Memesnake *snake;
	static sf::RenderWindow *window;   // Display Window

	static std::string word;           // The word to make the snake from
	static bool game_over;             // False until we lose
	static unsigned game_score;        // Current score (length of snake)
	static unsigned tick;              // Current game tick
	static unsigned ticks_per_advance; // Num game ticks per move of snake
	static unsigned char_index;        // Index in word
	static sf::Text next_char;

	constexpr int MAX_ROWS = WINDOW_WIDTH / LETTER_WIDTH;
	constexpr int MAX_COLS = WINDOW_HEIGHT / LETTER_HEIGHT;

	void init(const char *str, Memesnake& memesnake,
	          sf::RenderWindow& win, const sf::Font& font)
	{
		srand(time(nullptr));

		word = str;
		game_over = false;
		game_score = 1;
		tick = 1;
		ticks_per_advance = 120;
		char_index = 1 % word.size();

		snake = &memesnake;
		window = &win;

		next_char.setString(word.substr(char_index, 1));
		next_char.setColor(sf::Color::Red);
		next_char.setFont(font);
		next_char.setCharacterSize(LETTER_HEIGHT);

		do {
			int x = (rand() % MAX_ROWS) * LETTER_WIDTH;
			int y = (rand() % MAX_COLS) * LETTER_HEIGHT;
			next_char.setPosition(x, y);
		} while (snake->contains(next_char.getPosition()));
	}

	bool lost()
	{
		return game_over;
	}

	unsigned score()
	{
		return game_score;
	}

	void update()
	{
		// Move the snake on the right tick
		if (++tick >= ticks_per_advance) {
			tick = 1;
			game_over = snake->advance();
		}

		// Check for a collision with the letter
		if (snake->collides(next_char.getPosition())) {
			snake->add_letter(word[char_index]);
			char_index = (char_index + 1) % word.size();

			// Create the next letter
			next_char.setString(word.substr(char_index, 1));
			do {
				int x = (rand() % MAX_ROWS) * LETTER_WIDTH;
				int y = (rand() % MAX_COLS) * LETTER_HEIGHT;
				next_char.setPosition(x, y);
			} while (snake->contains(next_char.getPosition()));

			game_score++;
		}

		// Draw snake and text
		snake->draw(*window);
		window->draw(next_char);
	}
}
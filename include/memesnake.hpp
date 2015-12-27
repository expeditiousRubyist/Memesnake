/* Memesnake Class Header
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

#ifndef __MEMESNAKE_HPP__
#define __MEMESNAKE_HPP__

#include "constants.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class Memesnake {
	Direction _direction;
	sf::Font _font;
	std::vector<sf::Text> _letters;
public:
	Memesnake(const sf::Font& font, char c);
	void add_letter(char c);
	bool advance();
	bool collides(const sf::Vector2f& pos) const;
	void draw(sf::RenderWindow& win);
	void set_direction(Direction d);
};

#endif // __MEMESNAKE_HPP__
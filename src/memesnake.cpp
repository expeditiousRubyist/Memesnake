/* Memesnake Class Implementation
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

#include "memesnake.hpp"

Memesnake::Memesnake(const sf::Font& font, char c) : 
	_direction(Direction::right),
	_font(font),
	_letters(std::vector<sf::Text>())
{
	std::string s(1, c);
	_letters.emplace_back(s, _font, LETTER_HEIGHT);
	_letters[0].setColor(sf::Color::Red);
}

// Add a character to the end of a snake
void Memesnake::add_letter(char c)
{
	std::string s(1, c);
	sf::Text text(s, _font, LETTER_HEIGHT);
	text.setColor(sf::Color::Red);

	// Where to place the next character is based on the last two letters
	// in the current snake. If we only have one, we base purely on the
	// direction the snake is traveling. 
	if (_letters.size() == 1) {
		auto pos = _letters[0].getPosition();
		switch (_direction) {
		case Direction::left:
			pos.x += LETTER_WIDTH;
			break;
		case Direction::right:
			pos.x -= LETTER_WIDTH;
			break;
		case Direction::up:
			pos.y += LETTER_HEIGHT;
			break;
		case Direction::down:
			pos.y -= LETTER_HEIGHT;
			break;
		}
		text.setPosition(pos);
	}

	// Otherwise we want to continue whatever pattern is used with the
	// last two letters. If the second to last is to the right of the
	// right of the last, the last is to the right of the new letter,
	// and so on...
	else {
		auto lpos = _letters[_letters.size() - 1].getPosition();
		auto spos = _letters[_letters.size() - 2].getPosition();
		sf::Vector2f npos;

		if (spos.x > lpos.x) npos.x = lpos.x - LETTER_WIDTH;
		else if (spos.x < lpos.x) npos.x = lpos.x + LETTER_WIDTH;
		else npos.x = lpos.x;

		if (spos.y > lpos.y) npos.y = lpos.y - LETTER_HEIGHT;
		else if (spos.y < lpos.y) npos.y = lpos.y + LETTER_HEIGHT;
		else npos.y = lpos.y;		

		text.setPosition(npos);
	}

	_letters.push_back(text);
}

// Advance all characters of the snake one stage.
// Return true iff snake collides with itself or with walls.
bool Memesnake::advance()
{
	auto npos = _letters[0].getPosition();

	// Move the head
	switch (_direction) {
		case Direction::left:
			_letters[0].move(-LETTER_WIDTH, 0);
			break;
		case Direction::right:
			_letters[0].move(LETTER_WIDTH, 0);
			break;
		case Direction::up:
			_letters[0].move(0, -LETTER_HEIGHT);
			break;
		case Direction::down:
			_letters[0].move(0, LETTER_HEIGHT);
			break;
	}

	// Move everything else
	for (size_t i = 1; i < _letters.size(); ++i) {
		auto opos = _letters[i].getPosition();
		_letters[i].setPosition(npos);
		npos = opos;
	}

	// Check if head collides with any walls
	npos = _letters[0].getPosition();
	if (npos.x < 0 || npos.y < 0) {
		return true;
	}

	if (npos.x + LETTER_WIDTH > WINDOW_WIDTH ||
	    npos.y + LETTER_HEIGHT > WINDOW_HEIGHT) {
		return true;
	}

	// Check if head collides with any other part of the snake
	for (size_t i = 1; i < _letters.size(); ++i) {
		auto pos = _letters[i].getPosition();
		if (pos == npos) return true;
	}

	return false;
}

// Check if the head of the snake collides with a position
bool Memesnake::collides(const sf::Vector2f& pos) const
{
	return (pos == _letters[0].getPosition());
}

// Check if any of the letters in the snake collide with a position
bool Memesnake::contains(const sf::Vector2f& pos) const
{
	for (const auto& l : _letters) {
		if (l.getPosition() == pos) return true;
	}
	return false;
}

// Draw all of the letters in the snake
void Memesnake::draw(sf::RenderWindow& win)
{
	for (const auto& l : _letters) {
		win.draw(l);
	}
}

// Set the direction the snake travels
void Memesnake::set_direction(Direction d)
{
	_direction = d;
}
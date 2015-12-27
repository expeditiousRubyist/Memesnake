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

#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__

#include "memesnake.hpp"

namespace GameState {
	void init(const char *str, Memesnake& memesnake,
	          sf::RenderWindow& win, const sf::Font& font);
	bool lost();
	unsigned score();
	void update();
}

#endif
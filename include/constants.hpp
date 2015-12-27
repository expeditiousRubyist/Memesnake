/* Memesnake Constants
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

#ifndef __MEMESNAKE_CONSTANTS_HPP__
#define __MEMESNAKE_CONSTANTS_HPP__

enum class Direction { up, down, left, right };

constexpr int LETTER_HEIGHT     = 20;
constexpr int LETTER_WIDTH      = 13;
constexpr int WINDOW_HEIGHT     = 480;
constexpr int WINDOW_WIDTH      = 640;
constexpr int MAX_TICKS_RATE    = 120;
constexpr int MIN_TICKS_RATE    = 30;

#endif // __MEMESNAKE_CONSTANTS_HPP__
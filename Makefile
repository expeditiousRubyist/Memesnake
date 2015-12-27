# Memesnake Makefile
# Copyright (C) 2015 Rubyist

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CXX = g++
RM  = rm

# Source folders
SRCDIR = src
OBJDIR = obj
INCDIR = include

# Compiler flags
# Use of D_GLIBCXX_USE_CXX11_ABI=0 due to sfml being compatible with gcc 4.x
# and not gcc 5.x. If this changes, get rid of it. 
CXXFLAGS = -Wall -Werror -Wpedantic -O2 -std=c++14 -D_GLIBCXX_USE_CXX11_ABI=0
INCFLAGS = -I $(INCDIR)
LDFLAGS  = -lsfml-window -lsfml-graphics -lsfml-system

# Targets
TARGET  = memesnake
CPPSRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS    = $(addprefix $(OBJDIR)/, $(notdir $(CPPSRCS:.cpp=.o)))
VPATH   = $(SRCDIR)

all: $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
##
#
# makefile : build instructions for the project.
#
# See `LICENSE' for full license.
# See `README.md' for project details.
#
##

##
#
# Copyright (C) 2021 Kevin Matthes
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
##

################################################################################

##
#
# Variables.
#
##

APP      := mkcws
CC       := gcc
CFLAGS   := -std=c99 -Wall -Werror -Wextra -Wpedantic
LFLAGS   := -L. -lstring
PANDOC   := pandoc
REMOVE   := rm
SOURCES  := ./main.c
TOREMOVE := $(wildcard ./*.code-workspace) $(wildcard ./*.pdf)
VALGRIND := valgrind.log
VFLAGS   := --leak-check=full --redzone-size=200 --show-leak-kinds=all



##
#
# Build instructions.
#
##

.PHONY: default
default: $(VALGRIND) tidy

$(APP): $(SOURCES)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

.PHONY: tidy
tidy: $(APP) $(TOREMOVE)
	$(REMOVE) $^

$(VALGRIND): $(APP)
	valgrind $(VFLAGS) ./$^ -lC -ntest -p./ 2>  $@
	valgrind $(VFLAGS) ./$^ -ntest -p./     2>> $@
	valgrind $(VFLAGS) ./$^ -ntest -p./ -L  2>> $@
	valgrind $(VFLAGS) ./$^ -L              2>> $@
	valgrind $(VFLAGS) ./$^                 2>> $@

CC     = clang++
CFLAGS = -Wall -Wextra -pedantic-errors -std=c++17
SRCDIR = src
BINDIR = bin
OBJS   = $(SRCDIR)/*.cpp
NAME   = mazeGenerator

main : $(OBJS)
	$(CC) $^ $(CFLAGS) -o $(BINDIR)/$(NAME)

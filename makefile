CC     = clang++
CFLAGS = -Wall -pedantic -std=c++17
SRCDIR = src
BINDIR = bin
OBJS   = $(SRCDIR)/*.cpp
NAME   = mazeGenerator

main : $(OBJS)
	$(CC) $^ $(CFLAGS) -o $(BINDIR)/$(NAME)


#include <cstdio>

#include "maze.hpp"

#define BLOCK "\u2588\u2588"

auto
drawRow(maze::Nodes &row) -> void
{
	printf(BLOCK);
	for (auto &cell : row)
		printf("%s" BLOCK, cell[maze::Up] ? "  " : BLOCK);
	std::printf("\n" BLOCK);
	for (auto &cell : row)
		printf("  %s", cell[maze::Right] ? "  " : BLOCK);
}

auto
drawMap(maze::Map m) -> void
{
	for (auto &row : m) {
		drawRow(row);
		std::putchar('\n');
	}

	for (size_t i = 0; i <= m.size() * 2; i++)
		printf(BLOCK);
	putchar('\n');
}

auto
main(int argc, char **argv) -> int
{
	auto map{maze::genMap(20)};
	drawMap(map);
}

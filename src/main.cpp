#include <cctype>
#include <cstring>
#include <iostream>

#include "maze.hpp"

#define BLOCK "\u2588\u2588"

auto
draw_map(maze::Map map) -> void
{
	for (auto &row : map) {
		for (auto cell : row)
			std::cout << (cell ? "  " : BLOCK);
		std::cout << '\n';
	}
}

auto
draw_solution(maze::Map map, maze::Map solution) -> void
{
	for (size_t h{0}; h < map.size(); h++) {
		for (size_t j{0}; j < map[0].size(); j++) {
			if (!map[h][j])
				std::cout << BLOCK;
			else
				std::cout << (solution[h][j] ? "@@" : "  ");
		}
		std::cout << '\n';
	}
}

auto
is_num(std::string str) -> bool
{
	for (auto c : str)
		if (!std::isdigit(c))
			return false;
	return true;
}

auto
print_usage(char *name) -> void
{
	std::cout
	    << "Usage:\n"
	       "\t"
	    << name
	    << " [height] [length] [-sh]\n\n"
	       "\theight and length are optional; maze defaults to 20x20\n"
	       "\tpassing just one integer X will result in a X x X maze\n\n"
	       "\t-s: print maze and solution\n"
	       "\t-h: show this message\n";
}

auto
main(int argc, char **argv) -> int
{
	int length{20};
	int height{20};

	bool l_set{false};
	bool h_set{false};

	bool solution_flag{false};

	auto bad_args = [&] {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	};

	if (argc > 4)
		bad_args();

	for (int i = 1; i < argc; i++) {
		if (is_num(argv[i])) {
			if (!h_set) {
				h_set  = true;
				height = std::stoi(argv[i]);
			} else if (!l_set) {
				l_set  = true;
				length = std::stoi(argv[i]);
			} else {
				bad_args();
			}
		} else if (!std::strcmp(argv[i], "-s")) {
			solution_flag = true;
		} else if (!std::strcmp(argv[i], "-h")) {
			print_usage(argv[i]);
			exit(EXIT_SUCCESS);
		} else {
			bad_args();
		}
	}

	if (h_set && !l_set)
		length = height;

	auto random_maze{maze::gen_maze(height, length)};
	draw_map(random_maze);

	if (solution_flag) {
		std::cout << '\n';
		auto solution{maze::solve_maze(random_maze)};
		draw_solution(random_maze, solution);
	}
}

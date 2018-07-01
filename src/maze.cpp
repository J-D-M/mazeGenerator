#include <algorithm>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <optional>

#include "./maze.hpp"

namespace maze
{

static auto
addPos(Pos p1, Pos p2) -> Pos
{
	return {std::get<0>(p1) + std::get<0>(p2),
	        std::get<1>(p1) + std::get<1>(p2)};
}

static auto
get_moves(const Pos p, size_t max_h, size_t max_l, size_t dist = 2)
    -> std::vector<Pos>
{
	const Pos moves[]{{dist, 0}, {-dist, 0}, {0, dist}, {0, -dist}};

	auto inBounds = [&](auto h, auto l) -> bool {
		return h < max_h && l < max_l;
	};

	std::vector<Pos> ret;
	for (auto move : moves) {
		auto [h, l]{addPos(p, move)};

		if (inBounds(h, l))
			ret.push_back({h, l});
	}

	return ret;
}

static auto
get_rand_move(const Pos p, const Map &visited) -> std::optional<Pos>
{
	std::vector<Pos> ret;

	const size_t max_h{visited.size() - 1};
	const size_t max_l{visited[0].size() - 1};

	for (auto move : get_moves(p, max_h, max_l)) {
		auto [h, l]{move};

		if (!visited[h][l])
			ret.push_back({h, l});
	}

	auto size{ret.size()};
	if (size > 0)
		return ret[std::rand() % size];
	else
		return {};
}

static auto
rand_walk(Map &map, Map &visited, Pos p) -> void
{
	while (auto newPos{get_rand_move(p, visited)}) {
		auto [h, l]{newPos.value()};
		auto [h_mid, l_mid]{p};

		h_mid = (h_mid + h) / 2;
		l_mid = (l_mid + l) / 2;

		visited[h][l]     = true;
		map[h][l]         = true;
		map[h_mid][l_mid] = true;

		rand_walk(map, visited, {h, l});
	}
}

auto
gen_maze(size_t height, size_t length, Pos p) -> Map
{
	std::srand(std::time(nullptr));

	height = height * 2 + 1;
	length = length * 2 + 1;

	Map ret(height, Nodes(length, false));
	Map visited = ret;

	for (size_t i{1}; i < height; i += 2)
		for (size_t j{1}; j < length; j += 2)
			ret[i][j] = true;

	// make entrance/exit
	ret[0][1]                   = true;
	ret[height - 1][length - 2] = true;

	rand_walk(ret, visited, p);

	return ret;
}

static auto
walk_maze(const Map &       maze,
          std::vector<Map> &solutions,
          Map               visited,
          Pos               current_pos,
          Pos               end)
{
	auto [h, l]{current_pos};
	const auto max_h{maze.size()};
	const auto max_l{maze[0].size()};

	visited[h][l] = true;

	if (current_pos == end) {
		solutions.push_back(visited);
		return;
	}

	for (auto move : get_moves(current_pos, max_h, max_l, 1)) {
		auto [h_new, l_new]{move};
		if (!visited[h_new][l_new] && maze[h_new][l_new])
			walk_maze(maze, solutions, visited, move, end);
	}
}

auto
solve_maze(const Map &maze) -> Map
{
	std::vector<Map> solutions;
	auto             m_height{maze.size()};
	auto             m_length{maze[0].size()};

	Map visited(m_height, Nodes(m_length, false));

	// assumes start and end
	walk_maze(
	    maze, solutions, visited, {0, 1}, {m_height - 1, m_length - 2});

	auto sum_step = [](const auto &path) {
		size_t ret{0};

		for (auto row : path)
			for (auto c : row)
				ret += c;

		return ret;
	};

	return *std::min_element(
	    std::begin(solutions),
	    std::end(solutions),
	    [&](auto a, auto b) -> bool { return sum_step(a) < sum_step(b); });
}
} // namespace maze

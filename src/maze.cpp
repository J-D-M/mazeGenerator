#include <cstdio>
#include <ctime>
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
getMove(const Pos p, const Nodes &visited) -> std::optional<Pos>
{

	const Pos moves[]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	auto inBounds = [&](auto y, auto x) -> bool {
		const auto size{visited.size()};
		return (y < size) && (x < size);
	};

	std::vector<Pos> ret;
	for (auto move : moves) {
		auto [y, x]{addPos(p, move)};

		if (inBounds(y, x) && !visited[y][x])
			ret.push_back({y, x});
	}

	auto size{ret.size()};
	if (size > 0)
		return ret[std::rand() % size];
	else
		return {};
}

static auto
connect(Map &m, Pos p1, Pos p2) -> void
{
	auto [y1, x1]{p1};
	auto [y2, x2]{p2};

	auto &node_1{m[y1][x1]};
	auto &node_2{m[y2][x2]};

	if (y1 != y2) {
		if (y1 > y2)
			node_1[Up] = true;
		else
			node_2[Up] = true;
	} else {
		if (x1 < x2)
			node_1[Right] = true;
		else
			node_2[Right] = true;
	}
}

static auto
randWalk(Map &m, Nodes &visited, Pos p) -> void
{
	while (auto newPos{getMove(p, visited)}) {
		auto [y, x] = newPos.value();

		visited[y][x] = true;
		connect(m, p, {y, x});
		randWalk(m, visited, {y, x});
	}
}

auto
genMap(size_t x, Pos p) -> Map
{

	std::srand(std::time(nullptr));

	Map   ret(x, Nodes(x, Node(2, false)));
	Nodes visited(x, Node(x, false));

	randWalk(ret, visited, p);

	return ret;
}

} // namespace maze

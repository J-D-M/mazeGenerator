#ifndef MAZE_
#define MAZE_

#include <tuple>
#include <vector>

namespace maze
{

using Pos   = std::tuple<size_t, size_t>;
using Nodes = std::vector<bool>;
using Map   = std::vector<Nodes>;

enum Direction { Up, Right };

auto gen_maze(size_t, size_t, Pos = {1, 1}) -> Map;
auto solve_maze(const Map &) -> Map;

} // namespace maze

#endif

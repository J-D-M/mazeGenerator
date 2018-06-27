#ifndef MAZE_
#define MAZE_

#include <tuple>
#include <vector>

namespace maze
{

using Pos   = std::tuple<size_t, size_t>;
using Node  = std::vector<bool>;
using Nodes = std::vector<Node>;
using Map   = std::vector<std::vector<std::vector<bool>>>;

enum Direction { Up, Right };

auto genMap(size_t, Pos = {0, 0}) -> Map;

} // namespace maze

#endif

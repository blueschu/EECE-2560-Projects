/**
 * Project 5b main file.
 *
 * Authors: Brian Schubert  <schubert.b@northeastern.edu>
 *          Chandler Cree   <cree.d@northeastern.edu>
 * Date:    2020-12-13
 *
 */

#include <algorithm>            // for std::transform
#include <array>                // for std::array
#include <iostream>             // for I/O stream definitions

#include "eece2560_io.h"
#include "graph_walker.h"
#include "maze.h"

namespace {
constexpr auto k_maze_files = std::array{
    "resources/maze1.txt",
    "resources/maze2.txt",
    "resources/maze3.txt"
};

using MazeGraph = Graph<Maze::Coordinate, Maze::PathWeight>;

using MazeGraphWalker = GraphWalker<Maze::Coordinate, Maze::PathWeight>;

std::vector<Maze::Coordinate> graph_path_to_directions(
    const MazeGraph& graph,
    const std::vector<MazeGraph::size_type>& graph_path
)
{
    std::vector<Maze::Coordinate> temp;
    std::transform(
        std::cbegin(graph_path),
        std::cend(graph_path),
        std::back_inserter(temp),
        [&](const auto index) { return *graph[index]; }
    );
    return temp;
}

} // end namespace



int main()
{
    const std::string k_maze_divider(52, '=');
    for (const auto file_name : k_maze_files) {
        std::cout << k_maze_divider << '\n' << file_name << ":\n" << k_maze_divider << '\n';
        const auto maze = Maze::read_file(file_name);
        const MazeGraph graph = maze.make_graph();

        MazeGraphWalker walker;

        {
            const auto bfs_result = walker.find_path_bfs(graph, *std::begin(graph), *(std::end(graph) - 1));
            if (bfs_result) {
                const auto[directions, map] = maze.human_directions(
                    graph_path_to_directions(graph, bfs_result.path)
                );

                std::cout << "BFS Shortest Path (weight=" << bfs_result.weight << "):\n";
                eece2560::print_sequence(std::cout, std::cbegin(directions), std::cend(directions), "\n- ", "- ", "");
                std::cout << '\n' << map;
            } else {
                std::cout << "Failed to locate path with BFS\n";
            }
        }
        std::cout << '\n';
        {
            const auto dijkstra_result = walker.find_path_dijkstra(graph, *std::begin(graph), *(std::end(graph) - 1));
            if (dijkstra_result) {
                const auto[directions, map] = maze.human_directions(
                    graph_path_to_directions(graph, dijkstra_result.path)
                );

                std::cout << "Dijkstra Shortest Path (weight=" << dijkstra_result.weight << "):\n";
                eece2560::print_sequence(std::cout, std::cbegin(directions), std::cend(directions), "\n- ", "- ", "");
                std::cout << '\n' << map;
            } else {
                std::cout << "Failed to locate path with Dijkstra's algorithm\n";
            }
        }

        std::cout << "\n\n";
    }

}

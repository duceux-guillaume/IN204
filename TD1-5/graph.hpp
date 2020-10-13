#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T> struct Equal {
  bool operator()(T const &l, T const &r) {
    return l == r;
  }
};

template <typename Node, typename EqualNode = Equal<Node>,
          typename Edge = std::pair<Node, Node>, bool Oriented = false>
class Graph {
public:
  void add(Node const &n) {
    if (!has(n)) {
      _nodes.emplace_back(n);
    }
  }

  bool has(Node const &n) {
      for(auto const& node : _nodes)
      {
          if (Equal<Node>()(node, n)) {
              return true;
          }
      }
      return false;
  }

  std::vector<Node> const &nodes() const { return _nodes; }

  std::vector<Edge> const &edges() const { return _edges; }

private:
  std::vector<Node> _nodes;
  std::vector<Edge> _edges;
};

template <typename Node, typename Edge, typename EqualNode, bool Oriented>
std::ostream &operator<<(std::ostream &out,
                         Graph<Node, Edge, EqualNode, Oriented> const &graph) {
  out << "Nodes \n";
  for (auto node : graph.nodes()) {
    out << node << std::endl;
  }
  out << "Edges \n";
  if (Oriented) {
    for (auto edge : graph.edges()) {
      out << edge.first << " -> " << edge.second << std::endl;
    }
  } else {
    for (auto edge : graph.edges()) {
      out << edge.first << " <-> " << edge.second << std::endl;
    }
  }
  return out;
}

#endif // ! GRAPH_HPP

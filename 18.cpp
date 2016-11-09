

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

const int values[] = {
  75,
  95, 64,
  17, 47, 82,
  18, 35, 87, 10,
  20,  4, 82, 47, 65,
  19,  1, 23, 75,  3, 34,
  88,  2, 77, 73,  7, 63, 67,
  99, 65,  4, 28,  6, 16, 70, 92,
  41, 41, 26, 56, 83, 40, 80, 70, 33,
  41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
  53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
  70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
  91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
  63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
  04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23,
};

#define VALUE_COUNT static_cast<int>(sizeof(values) / sizeof(*values))

struct Vertex {
  const int value;
  int acc;
  bool known;
};

std::ostream &operator <<(std::ostream &o, Vertex const &v) {
  o << '[' << v.value << ']';
  return o;
}

class Graph {

public:
  using edge_map_t = std::unordered_multimap<int, int>;
  using edge_cit_t = edge_map_t::const_iterator;
private:

  std::vector<Vertex> _vertices;
  std::unordered_multimap<int, int> _edges;

public:

  void push_back_vertex(Vertex v) {
    _vertices.push_back(v);
  }

  void add_edge(int src, int dst) {
    _edges.emplace(src, dst);
  }

  Vertex &get_vertex(int i) {
    return _vertices[i];
  }

  std::pair<edge_cit_t, edge_cit_t> get_edges(int vid) const {
    return _edges.equal_range(vid);
  }

};

Graph make_graph() {
  Graph g;
  int i, width;

  i = 0;
  width = 1;
  while (i < VALUE_COUNT) {
    for (int j = 0; j < width; j++) {
      g.push_back_vertex({values[i], 0, false});
      if (j != width - 1) {
        // std::cout << "topright link: "
        //           << i - width + 1 << " " << g.get_vertex(i - width + 1)
        //           << " -> "
        //           << i << " " << g.get_vertex(i)
        //           << std::endl;
        g.add_edge(i - width + 1, i);
      }
      if (j != 0)
        g.add_edge(i - width, i);
      i++;
    }
    width++;
  }
  width--;
  g.push_back_vertex({0, 0, true});
  for (int j = 0; j < width; j++) {
    g.add_edge(VALUE_COUNT - j - 1, VALUE_COUNT);
  }
  return g;
}

int heaviest_path(Graph &g, int src) {
  Graph::edge_cit_t it, end;
  int max, tmp;
  Vertex &self = g.get_vertex(src);

  std::cout << "heaviest_path from " << src << " " << self << std::endl;
  if (self.known)
    return self.acc;
  std::tie(it, end) = g.get_edges(src);
  max = 0;
  while (it != end) {
    std::cout << "  " << src << " -> " << it->second << std::endl;
    tmp = heaviest_path(g, it->second);
    if (tmp > max)
      max = tmp;
    ++it;
  }
  self.known = true;
  self.acc = self.value + max;
  return self.acc;
}

int main() {

  Graph g = make_graph();

  std::cout << heaviest_path(g, 0) << std::endl;
}

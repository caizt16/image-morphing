#pragma once
#include "Vertex.h"

#include <vector>
#include <iostream>

class Edge {
  public:
    std::vector<Vertex> v;
    bool bad;
    Edge() { bad = 0; }
    Edge(Vertex a, Vertex b) { v.push_back(a); v.push_back(b); bad = 0; }
    ~Edge() {}
    bool isSame(Edge that) {
      for (int i = 0; i < 2; ++i)
        if (!(this->v[i].isSame(that.v[i])))
          return false;
      return true;
    }
};

std::ostream& operator<<(std::ostream &os, const Edge &e){
  return os << e.v[0] << " " << e.v[1];
}

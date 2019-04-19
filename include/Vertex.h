#pragma once
#include <iostream>
#include <cmath>

bool same(double x, double y) {
  return fabs(x-y) < std::numeric_limits<double>::min();
  return fabs(x-y) <= std::numeric_limits<double>::epsilon() * fabs(x+y) * 2
  || fabs(x-y) < std::numeric_limits<double>::min();
}

class Vertex {
  public:
    double x, y;
    int index;
    Vertex() { x = 0.0; y = 0.0; index = 0; }
    Vertex(double _x, double _y, int _index=-1): x(_x), y(_y), index(_index) {}
    Vertex operator-(Vertex that) const { return Vertex((*this).x - that.x, (*this).y - that.y); }
    Vertex operator+(Vertex that) const { return Vertex((*this).x + that.x, (*this).y + that.y); }
    Vertex operator/(double c) const { return Vertex((*this).x / c, (*this).y / c); }
    Vertex operator*(double c) const { return Vertex((*this).x * c, (*this).y * c); }
    bool operator!=(const Vertex &that) const { return (*this).index != that.index; }
    bool operator<(const Vertex &that) const { return (*this).index < that.index; }
    bool isSame(Vertex that) {
      return same((*this).x, that.x) && same((*this).y, that.y);
    }
    ~Vertex() {}
};

std::ostream& operator<<(std::ostream &os, const Vertex &v){
  return os << v.x << " " << v.y;
}

double dot(Vertex &a, Vertex &b) {
  return a.x * b.x + a.y * b.y;
}

Vertex max(Vertex &a, Vertex &b) {
  return Vertex(std::max(a.x, b.x), std::max(a.y, b.y));
}

Vertex min(Vertex &a, Vertex &b) {
  return Vertex(std::min(a.x, b.x), std::min(a.y, b.y));
}

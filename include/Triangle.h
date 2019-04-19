#pragma once
#include "Edge.h"
#include "Vertex.h"

#include <vector>
#include <cmath>
#include <algorithm>

class Triangle {
  public:
    std::vector<Vertex> v;
    std::vector<Edge> e;
    bool bad;
    Triangle() { bad = 0; }
    Triangle(Vertex a, Vertex b, Vertex c) {
      Triangle();
      v.push_back(a);
      v.push_back(b);
      v.push_back(c);
      sort(v.begin(), v.end());
      e.push_back(Edge(a, b));
      e.push_back(Edge(b, c));
      e.push_back(Edge(a, c));
      bad = 0;
    }
    ~Triangle() {}
    bool operator<(const Triangle &that) const {
      for (int i = 0; i < 3; ++i) {
        if (this->v[i] != that.v[i])
          return this->v[i] < that.v[i];
      }
      return false;
    }
    bool hasInvalidCircle(Vertex x) {
      double Radius_2;  // 半径的平方
      double Cntrx, Cntry; //圆心坐标

      // 求圆心和半径
      double a1 = (v[1].x - v[0].x), b1 = (v[1].y - v[0].y);
      double c1 = (a1*a1 + b1*b1) / 2.0;
      double a2 = (v[2].x - v[0].x), b2 = (v[2].y - v[0].y);
      double c2 = (a2*a2 + b2*b2) / 2.0;
      double d = (a1*b2 - a2*b1);
      Cntrx = v[0].x + (c1 * b2 - c2 * b1) / d;
      Cntry = v[0].y + (a1 * c2 - a2 * c1) / d;
      Radius_2 = pow(v[0].x - Cntrx , 2.0) + pow(v[0].y - Cntry, 2.0);

      // 判断 Vrtx0 是否在外接圆内或其上，若是，返回 true,否则，返回 false
      double Rad_V0Cntr;
      Rad_V0Cntr = pow(x.x - Cntrx , 2.0) + pow(x.y - Cntry, 2.0);
      return Rad_V0Cntr <= Radius_2;
    }
    bool hasVertex(Vertex x) {
      for (int i = 0; i < 3; ++i)
        if (v[i].isSame(x))
          return true;
      return false;
    }
    bool contains(Vertex x) {
      Vertex v0 = v[2] - v[0] ;
      Vertex v1 = v[1] - v[0] ;
      Vertex v2 = x - v[0] ;

      float dot00 = dot(v0, v0) ;
      float dot01 = dot(v0, v1) ;
      float dot02 = dot(v0, v2) ;
      float dot11 = dot(v1, v1) ;
      float dot12 = dot(v1, v2) ;

      float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;

      float u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
      if (u < 0 || u > 1) // if u out of range, return directly
      {
        return false ;
      }

      float v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
      if (v < 0 || v > 1) // if v out of range, return directly
      {
        return false ;
      }

      return u + v <= 1 ;
    }

};

std::vector<double> gaussian(Triangle t, Vertex v) {
  double A[3][3];
  for (int i = 0; i < 3; ++i) {
    A[0][i] = t.v[i].x;
    A[1][i] = t.v[i].y;
    A[2][i] = 1;
  }
  // for (int i = 0; i < 3; ++i) {
  //   for (int j = 0; j < 3; ++j) {
  //     std::cout << A[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;
  // double A[3][3] = {
  //   {10, -7, 0},
  //   {-3, 2, 6},
  //   {5, -1, 5}
  // };
  int p[3] = {0, 1, 2};
  for (int i = 0; i < 3; ++i) {
    int max = i;
    for (int j = i+1; j < 3; ++j)
      if (std::abs(A[j][i]) > std::abs(A[max][i]))
        max = j;
    if (max != i) {
      std::swap(p[i], p[max]);
      for (int j = 0; j < 3; ++j)
        std::swap(A[i][j], A[max][j]);
    }

    for (int j = i+1; j < 3; ++j) {
      A[j][i] = A[j][i] / A[i][i];
      for (int k = i+1; k < 3; ++k) {
        A[j][k] = A[j][k] - A[j][i]*A[i][k];
      }
    }
  // for (int i = 0; i < 3; ++i) {
  //   for (int j = 0; j < 3; ++j) {
  //     std::cout << A[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;
  }

  double b[3] = {v.x, v.y, 1};
  // double b[3] = {7, 4, 6};
  double tb[3] = {v.x, v.y, 1};
  for (int i = 0; i < 3; ++i) {
    b[i] = tb[p[i]];
  }
  // std::cout << "b ";
  // for (int i = 0; i < 3; ++i)
  // std::cout << b[i] << " ";
  // std::cout << std::endl;
  //
  // for (int i = 0; i < 3; ++i) {
  //   for (int j = 0; j < 3; ++j) {
  //     std::cout << A[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  double y[3];
  y[0] = b[0];
  y[1] = b[1] - A[1][0] * y[0];
  y[2] = b[2] - A[2][0] * y[0] - A[2][1] * y[1];

  double x[3];
  x[2] = y[2] / A[2][2];
  x[1] = (y[1] - A[1][2] * x[2]) / A[1][1];
  x[0] = (y[0] - A[0][2] * x[2] - A[0][1] * x[1]) / A[0][0];

  // std::cout << "x ";
  // for (int i = 0; i < 3; ++i)
  //   std::cout << x[i] << " ";
  // std::cout << std::endl;

  std::vector<double> res;
  res.push_back(x[0]);
  res.push_back(x[1]);
  res.push_back(x[2]);

  return res;
}

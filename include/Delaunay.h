#pragma once
#include "Triangle.h"
#include "Edge.h"
#include "Vertex.h"

#include <array>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;

class Delaunay {
  public:
    Delaunay() { _tv = vector<Triangle>(); _ev = vector<Edge>(); _vv = vector<Vertex>(); }
    Delaunay(string name) {
      Delaunay();
      ifstream fin;
      fin.open("./data/" + name + ".txt", ios::in);
      double x, y;
      int cnt = 0;
      while (fin >> x >> y) {
        _vv.push_back(Vertex(x, y, cnt ++));
      }
      img.loadFromFile("./img/" + name + ".png");
    }
    void solve() {
      Vertex maxv(0, 0);
      Vertex minv(numeric_limits<double>::max(), numeric_limits<double>::max());
      for (auto v: _vv) {
        maxv = max(maxv, v);
        minv = min(minv, v);
      }
      Vertex midv = (maxv + minv) / 2;
      Vertex deltav = maxv - midv;
      Vertex p1 = Vertex(minv.x - deltav.x * 2, minv.y - deltav.y * 0.1);
      Vertex p2 = Vertex(maxv.x + deltav.x * 2, minv.y - deltav.y * 0.1);
      Vertex p3 = Vertex(midv.x, maxv.y + deltav.y * 2);
      _tv.push_back(Triangle(p1, p2, p3));

      int cnt = 0;
      for (auto v: _vv) {
        vector<Edge> tmp_e;
        for (auto &t: _tv)
          if (t.hasInvalidCircle(v)) {
            t.bad = true;
            for (auto e: t.e) tmp_e.push_back(e);
          }

        // cout << "t" << endl;
        // cout << _tv.size();
        _tv.erase(remove_if(begin(_tv), end(_tv), [](Triangle &t){
          return t.bad;
        }), end(_tv));

        for (auto e1 = begin(tmp_e); e1 != end(tmp_e); ++e1)
          for (auto e2 = e1+1; e2 != end(tmp_e); ++e2)
            if (e1->isSame(*e2)) {
              // cout << *e1 << "aaa" << *e2 << endl;
              e1->bad = true;
              e2->bad = true;
            }


        tmp_e.erase(remove_if(begin(tmp_e), end(tmp_e), [](Edge &e){
          return e.bad;
        }), end(tmp_e));

        // cout << 2 << endl;
        // for (auto e: _ev) cout << e << endl;
        for (auto e: tmp_e)
          _tv.push_back(Triangle(e.v[0], e.v[1], v));
      }

      _tv.erase(remove_if(begin(_tv), end(_tv), [p1, p2, p3](Triangle &t) {
        return t.hasVertex(p1) || t.hasVertex(p2) || t.hasVertex(p3);
      }), end(_tv));

      sort(_tv.begin(), _tv.end());

      for (auto t: _tv) {
        // cnt ++;
        for (auto e: t.e)
          _ev.push_back(e);
        // if (cnt > 15) break;
        }
    }
    void draw() {
      sf::RenderWindow window(sf::VideoMode(800, 600), "Delaunay triangulation");

      // Transform each points of each vector as a rectangle
      std::vector<sf::RectangleShape*> squares;

      for(const auto p : _vv) {
        sf::RectangleShape *c1 = new sf::RectangleShape(sf::Vector2f(4, 4));
        c1->setPosition(p.x, p.y);
        squares.push_back(c1);
      }

      // Make the lines
      std::vector<std::array<sf::Vertex, 2> > lines;
      for(const auto &e : _ev) {
        lines.push_back({{
          sf::Vertex(sf::Vector2f(e.v[0].x + 2, e.v[0].y + 2)),
          sf::Vertex(sf::Vector2f(e.v[1].x + 2, e.v[1].y + 2))
        }});
      }

      while (window.isOpen())
      {
        sf::Event event;
        while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Closed)
          window.close();
        }

        window.clear();

        // Draw the squares
        for(const auto &s : squares) {
          window.draw(*s);
        }

        // Draw the lines
        for(const auto &l : lines) {
          window.draw(l.data(), 2, sf::Lines);
        }

        window.display();
      }
    }
    Triangle findTriangle(Triangle t) {
      /*
      for (auto tt: _tv) {
        bool find = 1;
        for (int i = 0; i < 3; ++i)
          if (tt.v[i].index != t.v[i].index)
            find = 0;
        if (find) return tt;
      }
      for (int i = 0; i < 3; ++i)
        cout << t.v[i].index << " ";
        cout << endl;
      return _tv[0];
      */
      vector<Vertex> vv;
      for (int i = 0; i< 3; ++i)
        vv.push_back(_vv[t.v[i].index]);
      return Triangle(vv[0], vv[1], vv[2]);
    }

    void setVertexs(vector<Vertex> vv) { _vv = vv; }
    vector<Triangle> getTriangles() { return _tv; }
    vector<Edge> getEdges() { return _ev; }
    vector<Vertex> getVertexs() { return _vv; }

    vector<Triangle> _tv;
    vector<Edge> _ev;
    vector<Vertex> _vv;
    sf::Image img;
};

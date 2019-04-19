#pragma once
#include "Delaunay.h"

// Delaunay* morph(Delaunay *source, Delaunay *target,int times) {
void morph(Delaunay *source, Delaunay *target,int times) {
  double alpha = times * 0.05;
  Delaunay *res = new Delaunay();
  vector<Vertex> vv;
  vector<Vertex> svv = source->getVertexs();
  vector<Vertex> tvv = target->getVertexs();
  int size = svv.size();
  for (int i = 0; i < size; ++i)
    vv.push_back(svv[i] * alpha + tvv[i] * (1 - alpha));
  for (int i = 0; i < size; ++i)
    vv[i].index = i;
  res->setVertexs(vv);
  res->solve();

  int img_x = source->img.getSize().x, img_y = source->img.getSize().y;
  res->img.create(img_x, img_y);
  for (int i = 0; i < img_x; ++i) {
    for (int j = 0; j < img_y; ++j) {
      // for (int k = 0; k < res->_tv.size(); ++k) {
      //   if (res->_tv[k].contains(Vertex(i, j))) {
      //     cout << k << " " << i << " " << j << endl;
      //   }
      // }

      Vertex pixel(i, j);
      for (auto t: res->_tv) {
        if (t.contains(pixel)) {
          sf::Color res_color(0, 0, 0);
          Triangle st = source->findTriangle(t);
          vector<double> bary = gaussian(t, pixel);
          Vertex s_pixel = st.v[0] * bary[0] + st.v[1] * bary[1] + st.v[2] * bary[2];
          sf::Color src_color = source->img.getPixel(int(s_pixel.x), int(s_pixel.y));

          st = target->findTriangle(t);
          bary = gaussian(t, pixel);
          Vertex t_pixel = st.v[0] * bary[0] + st.v[1] * bary[1] + st.v[2] * bary[2];
          sf::Color tar_color = target->img.getPixel(int(t_pixel.x), int(t_pixel.y));

          res_color = sf::Color(int(src_color.r * alpha), int(src_color.g * alpha), int(src_color.b * alpha))
                    + sf::Color(int(tar_color.r * (1 - alpha)), int(tar_color.g * (1 - alpha)), int(tar_color.b * (1 - alpha)));
          res->img.setPixel(i, j, res_color);
          break;
        }
      }
    }
    // break;
  // res->img.saveToFile("./res/result2.png");
  }
  res->img.saveToFile("./res/result2_" + to_string(times) + ".png");
  // return res;
}

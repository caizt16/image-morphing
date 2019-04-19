#include "Delaunay.h"
#include "Morph.h"

#include <math.h>
#include <limits>
#include <iostream>

#define _USE_MATH_DEFINES
using namespace std;

int main() {
  Delaunay *source = new Delaunay("source2");
  source->solve();
  // source->draw();
  Delaunay *target = new Delaunay("target2");
  target->solve();
  // target->draw();
  // Delaunay *morphed;
  for (int i = 0; i < 20; ++i) {
    morph(source, target, i);
    // delete morphed;
  }
  // morphed->draw();
  delete source;
  delete target;
}

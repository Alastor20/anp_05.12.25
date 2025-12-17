#include "canvas.hpp"
#include <iostream>

char *topIT::canvas(f_t fr, char fill)
{
  char *canv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i) {
    canv[i] = fill;
  }
  return canv;
}

void topIT::paint(char *cnv, f_t fr, p_t p, char fill)
{
  size_t dy = fr.bb.y - p.y;
  size_t dx = p.x - fr.aa.x;
  cnv[dy * cols(fr) + dx] = fill;
}

void topIT::flush(std::ostream &os, const char *cnv, f_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i) {
    for (size_t j = 0; j < cols(fr); ++j) {
      os << cnv[i * cols(fr) + j];
    }
    os << '\n';
  }
}

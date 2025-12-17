#include "geom.hpp"
#include <algorithm>
#include <stdexcept>

bool topIT::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}
bool topIT::operator!=(p_t a, p_t b)
{
  return !(a == b);
}
size_t topIT::cols(f_t fr)
{
  return fr.bb.x - fr.aa.x + 1;
}
size_t topIT::rows(f_t fr)
{
  return fr.bb.y - fr.aa.y + 1;
}

topIT::f_t topIT::frame(const p_t *pts, size_t s)
{
  if (!s) {
    throw std::logic_error("No points");
  }
  int minx = pts[0].x, maxx = minx;
  int miny = pts[0].x, maxy = miny;
  for (size_t i = 1; i < s; ++i) {
    minx = std::min(minx, pts[i].x);
    miny = std::min(miny, pts[i].y);
    maxx = std::max(maxx, pts[i].x);
    maxy = std::max(maxy, pts[i].y);
  }
  p_t aa = {minx, miny};
  p_t bb = {maxx, maxy};
  return {aa, bb};
}

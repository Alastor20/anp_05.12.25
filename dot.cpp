#include "dot.hpp"
#include <stdexcept>

topIT::Dot::Dot(int x, int y) : IDraw(), d{x, y}
{}
topIT::Dot::Dot(p_t dd) : IDraw(), d{dd}
{}

topIT::p_t topIT::Dot::begin() const
{
  return d;
}
topIT::p_t topIT::Dot::next(p_t prev) const
{
  if (prev != begin()) {
    throw std::logic_error("bad input");
  }
  return d;
}

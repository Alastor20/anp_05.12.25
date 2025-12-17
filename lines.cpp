#include "lines.hpp"
#include "geom.hpp"
#include <stdexcept>

topIT::VerticalLine::VerticalLine(p_t start, p_t end) : IDraw(), start_(start), end_(end)
{}

topIT::p_t topIT::VerticalLine::begin() const
{
  return start_;
}

topIT::p_t topIT::VerticalLine::next(p_t prev) const
{
  if (prev.y > end_.y || prev.x != start_.x || prev.y < start_.y) {
    throw std::logic_error("bad input");
  }
  if (prev == end_) {
    return begin();
  }
  return p_t{prev.x, prev.y + 1};
}

topIT::HorizontalLine::HorizontalLine(p_t start, p_t end) : IDraw(), start_(start), end_(end)
{}

topIT::p_t topIT::HorizontalLine::begin() const
{
  return start_;
}

topIT::p_t topIT::HorizontalLine::next(p_t prev) const
{
  if (prev.x > end_.x || prev.y != start_.y || prev.x < start_.x) {
    throw std::logic_error("bad input");
  }
  if (prev == end_) {
    return begin();
  }
  return p_t{prev.x + 1, prev.y};
}

topIT::DiagLine::DiagLine(p_t start, p_t end) : IDraw(), start_(start), end_(end)
{}

topIT::p_t topIT::DiagLine::begin() const
{
  return start_;
}

topIT::p_t topIT::DiagLine::next(p_t prev) const
{
  if (prev == end_) {
    return begin();
  }
  int factorx = (end_.x - prev.x) / abs(end_.x - prev.x);
  int factory = (end_.y - prev.y) / abs(end_.y - prev.y);
  return p_t{prev.x + factorx, prev.y + factory};
}

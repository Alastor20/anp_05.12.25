#ifndef LINES_HPP
#define LINES_HPP
#include "idraw.hpp"
namespace topIT
{
  struct VerticalLine : IDraw
  {
    VerticalLine(p_t start, p_t end);
    p_t start, end;
    p_t begin() const override;
    p_t next(p_t) const override;
  };
  struct HorizontalLine : IDraw
  {
    HorizontalLine(p_t start, p_t end);
    p_t start, end;
    p_t begin() const override;
    p_t next(p_t) const override;
  };
  struct DiagLine : IDraw
  {
  };
}
#endif

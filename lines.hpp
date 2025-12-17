#ifndef LINES_HPP
#define LINES_HPP
#include "idraw.hpp"
namespace topIT
{
  struct VerticalLine : IDraw
  {
    VerticalLine(p_t start, p_t end);
    p_t begin() const override;
    p_t next(p_t) const override;

  private:
    p_t start_, end_;
  };
  struct HorizontalLine : IDraw
  {
    HorizontalLine(p_t start, p_t end);
    p_t begin() const override;
    p_t next(p_t) const override;

  private:
    p_t start_, end_;
  };
  struct DiagLine : IDraw
  {
    DiagLine(p_t start, p_t end);
    p_t begin() const override;
    p_t next(p_t) const override;

  private:
    p_t start_, end_;
  };
}
#endif

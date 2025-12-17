#include "lines.hpp"
#include <stdexcept>

topIT::VerticalLine::VerticalLine(p_t start, p_t end)
    : IDraw(), start(start), end(end) {}

topIT::p_t topIT::VerticalLine::begin() const { return start; }

topIT::p_t topIT::VerticalLine::next(p_t prev) const
{
    if (prev.y > end.y || prev.x != start.x || prev.y < start.y)
    {
        throw std::logic_error("bad input");
    }
    if (prev == end)
    {
        return begin();
    }
    return p_t{prev.x, prev.y + 1};
}

topIT::HorizontalLine::HorizontalLine(p_t start, p_t end)
    : IDraw(), start(start), end(end) {}

topIT::p_t topIT::HorizontalLine::begin() const { return start; }

topIT::p_t topIT::HorizontalLine::next(p_t prev) const
{
    if (prev.x > end.x || prev.y != start.y || prev.x < start.x)
    {
        throw std::logic_error("bad input");
    }
    if (prev == end)
    {
        return begin();
    }
    return p_t{prev.x + 1, prev.y};
}
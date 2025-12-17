#ifndef IDROW_HPP
#define IDROW_HPP
#include "geom.hpp"
namespace topIT
{
    struct IDraw
    {
        virtual p_t begin() const = 0;
        virtual p_t next(p_t) const = 0;
        virtual ~IDraw() = default;
    };
    size_t points(const IDraw &d, p_t **pts, size_t s);
}

#endif
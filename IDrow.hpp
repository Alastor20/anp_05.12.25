#ifndef IDEOW_HPP
#define IDROW_HPP
#include"geom.hpp"
namespace topIT
{
     struct IDraw
    {
        virtual p_t begin() const = 0;
        virtual p_t next(p_t) const = 0;
        virtual ~IDraw() = default;
    };
}

#endif
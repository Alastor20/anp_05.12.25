#include <iostream>
#include "ascii_draw.hpp"

int main()
{
    using namespace topIT;
    IDraw *shapes[3] = {};
    p_t *pts = nullptr;
    int err = 0;
    size_t s = 0;
    try
    {
        shapes[0] = new Dot(0, 0);
        shapes[1] = new VerticalLine({1, 1}, {1, 13});
        shapes[2] = new HorizontalLine({5, 5}, {17, 5});
        for (size_t i = 0; i < 3; ++i)
        {
            s += points(*(shapes[i]), std::addressof(pts), s);
        }
        f_t fr = frame(pts, s);
        char *cnv = canvas(fr, '.');
        for (size_t i = 0; i < s; ++i)
        {
            paint(cnv, fr, pts[i], '#');
        }
        flush(std::cout, cnv, fr);
        delete[] cnv;
    }
    catch (...)
    {
        err = 2;
        std::cerr << "Bad drowing\n";
    }
    delete[] pts;
    for (size_t i = 0; i < 3; ++i)
    {
        delete shapes[i];
    }
    return err;
}

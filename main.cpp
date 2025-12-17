#include <iostream>
#include"geom.hpp"

namespace topIT
{
    struct IDraw
    {
        virtual p_t begin() const = 0;
        virtual p_t next(p_t) const = 0;
        virtual ~IDraw() = default;
    };
    struct Dot : IDraw
    {
        Dot(int x, int y);
        explicit Dot(p_t dd);
        p_t begin() const override;
        p_t next(p_t) const override;
        p_t d;
    };

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
    void extend(p_t **pts, size_t s, p_t p);
    size_t points(const IDraw &d, p_t **pts, size_t s);

    f_t frame(const p_t *pts, size_t s);
    char *canvas(f_t fr, char fill);

    void paint(char *cnv, f_t fr, p_t p, char fill);

    void flush(std::ostream &os, const char *cnv, f_t fr);
}
int main()
{
    using namespace topIT;
    topIT::IDraw *shapes[3] = {};
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
topIT::Dot::Dot(int x, int y) : IDraw(), d{x, y} {}
topIT::Dot::Dot(p_t dd) : IDraw(), d{dd} {}

topIT::p_t topIT::Dot::begin() const { return d; }
topIT::p_t topIT::Dot::next(p_t prev) const
{
    if (prev != begin())
    {
        throw std::logic_error("bad input");
    }
    return d;
}

void topIT::extend(p_t **pts, size_t s, p_t p)
{
    p_t *e = new p_t[s + 1];
    for (size_t i = 0; i < s; ++i)
    {
        e[i] = (*pts)[i];
    }
    e[s] = p;
    delete[] *pts;
    *pts = e;
}

size_t topIT::points(const IDraw &d, p_t **pts, size_t s)
{
    size_t r = 1;
    p_t p = d.begin();
    extend(pts, s, p);
    while (d.next(p) != d.begin())
    {
        p = d.next(p);
        extend(pts, s + r, p);
        ++r;
    }
    return r;
}

topIT::f_t topIT::frame(const p_t *pts, size_t s)
{
    if (!s)
    {
        throw std::logic_error("No points");
    }
    int minx = pts[0].x, maxx = minx;
    int miny = pts[0].x, maxy = miny;
    for (size_t i = 1; i < s; ++i)
    {
        minx = std::min(minx, pts[i].x);
        miny = std::min(miny, pts[i].y);
        maxx = std::max(maxx, pts[i].x);
        maxy = std::max(maxy, pts[i].y);
    }
    p_t aa = {minx, miny};
    p_t bb = {maxx, maxy};
    return {aa, bb};
}

char *topIT::canvas(f_t fr, char fill)
{
    char *canv = new char[rows(fr) * cols(fr)];
    for (size_t i = 0; i < rows(fr) * cols(fr); ++i)
    {
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
    for (size_t i = 0; i < rows(fr); ++i)
    {
        for (size_t j = 0; j < cols(fr); ++j)
        {
            os << cnv[i * cols(fr) + j];
        }
        os << '\n';
    }
}

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
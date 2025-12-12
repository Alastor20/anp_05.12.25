#include <iostream>

namespace top
{
    struct p_t
    {
        int x, y;
    };
    bool operator==(p_t, p_t);
    bool operator!=(p_t, p_t);
    struct f_t
    {
        p_t aa, bb;
    };

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
    /*
    TODO: Домашнее задание:
      //- Добавить еще 2-3 фигуры
      //- Вертикальный отрезок
      //- Горизонтальный отрезок
      - Диагональ под 45 градусов заданной длины
      - Придумать свою фигуру
      */
    void extend(p_t **pts, size_t s, p_t p);
    size_t points(const IDraw &d, p_t **pts, size_t s);

    f_t frame(const p_t *pts, size_t s);

    size_t rows(f_t fr);
    size_t cols(f_t fr);

    char *canvas(f_t fr, char fill);

    void paint(char *cnv, f_t fr, p_t p, char fill);

    void flush(std::ostream &os, const char *cnv, f_t fr);
} // namespace top
int main()
{
    using namespace top;
    top::IDraw *shapes[3] = {};
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
    catch (std::exception &e)
    {
        std::cerr << e.what() << '\n';
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
top::Dot::Dot(int x, int y) : IDraw(), d{x, y} {}
top::Dot::Dot(p_t dd) : IDraw(), d{dd} {}
bool top::operator==(p_t a, p_t b) { return a.x == b.x && a.y == b.y; }
bool top::operator!=(p_t a, p_t b) { return !(a == b); }
top::p_t top::Dot::begin() const { return d; }
top::p_t top::Dot::next(p_t prev) const
{
    if (prev != begin())
    {
        throw std::logic_error("bad input");
    }
    return d;
}

void top::extend(p_t **pts, size_t s, p_t p)
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

size_t top::points(const IDraw &d, p_t **pts, size_t s)
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

top::f_t top::frame(const p_t *pts, size_t s)
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

size_t top::cols(f_t fr) { return fr.bb.x - fr.aa.x + 1; }
size_t top::rows(f_t fr) { return fr.bb.y - fr.aa.y + 1; }

char *top::canvas(f_t fr, char fill)
{
    char *canv = new char[rows(fr) * cols(fr)];
    for (size_t i = 0; i < rows(fr) * cols(fr); ++i)
    {
        canv[i] = fill;
    }
    return canv;
}

void top::paint(char *cnv, f_t fr, p_t p, char fill)
{
    size_t dy = fr.bb.y - p.y;
    size_t dx = p.x - fr.aa.x;
    cnv[dy * cols(fr) + dx] = fill;
}

void top::flush(std::ostream &os, const char *cnv, f_t fr)
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

top::VerticalLine::VerticalLine(p_t start, p_t end)
    : IDraw(), start(start), end(end) {}

top::p_t top::VerticalLine::begin() const { return start; }

top::p_t top::VerticalLine::next(p_t prev) const
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

top::HorizontalLine::HorizontalLine(p_t start, p_t end)
    : IDraw(), start(start), end(end) {}

top::p_t top::HorizontalLine::begin() const { return start; }

top::p_t top::HorizontalLine::next(p_t prev) const
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
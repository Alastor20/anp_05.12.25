#include <iostream>

namespace topit
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
      - Добавить еще 2-3 фигуры
      - Вертикальный отрезок
      - Горизонтальный отрезок
      - Диагональ под 45 градусов заданной длины
      - Придумать свою фигуру
      */
    // TODO: расширять заданный массив точками из очередной фигуры
    //  - extend...
    size_t points(const IDraw &d, p_t **pts, size_t s);

    // TODO: найти минимум и максимум по каждой координате среди точек и сформировать фрейм
    f_t frame(const p_t *pts, size_t s);

    char *canvas(f_t fr, char fill);

    // TODO: координаты точки перевести в координаты в двумерном массиве
    void paint(char *cnv, f_t fr, p_t p, char fill);

    // TODO: вывод двумерного массива на основе размеров, определяемых фреймом
    void flush(std::ostream &os, const char *cnv, f_t fr);
}
int main()
{
    using namespace topit;
    topit::IDraw *shapes[3] = {};
    p_t *pts = nullptr;
    int err = 0;
    size_t s = 0;
    try
    {
        shapes[0] = new Dot(0, 0);
        shapes[1] = new Dot(5, 7);
        shapes[2] = new Dot(-5, -2);
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
        // TODO: больше catch
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
topit::Dot::Dot(int x, int y) : IDraw(), d{x, y} {}
topit::Dot::Dot(p_t dd) : IDraw(), d{dd} {}
bool topit::operator==(p_t a, p_t b)
{
    return a.x == b.x && a.y == b.y;
}
bool topit::operator!=(p_t a, p_t b)
{
    return !(a == b);
}
topit::p_t topit::Dot::begin() const
{
    return d;
}
topit::p_t topit::Dot::next(p_t prev) const
{
    if (prev != begin())
    {
        throw std::logic_error("bad input");
    }
    return d;
}
char *topit::canvas(f_t fr, char fill)
{
    size_t width = abs(fr.aa.x) + abs(fr.bb.x);
    size_t height = abs(fr.aa.y) + abs(fr.bb.y);
    char *canv = new char[height * width];
    for (size_t i = 0; i < height * width; ++i)
    {
        canv[i] = fill;
    }
    return canv;
}

topit::VerticalLine::VerticalLine(p_t start, p_t end) : IDraw(), start(start), end(end)
{
}

topit::p_t topit::VerticalLine::begin() const
{
    return start;
}

topit::p_t topit::VerticalLine::next(p_t prev) const
{
    if (prev.y >= end.y || prev.x != start.x || prev.y < start.y)
    {
        throw std::logic_error("bad input");
    }
    return p_t{prev.x, prev.y + 1};
}

topit::HorizontalLine::HorizontalLine(p_t start, p_t end) : IDraw(), start(start), end(end)
{
}

topit::p_t topit::HorizontalLine::begin() const
{
    return start;
}

topit::p_t topit::HorizontalLine::next(p_t prev) const
{
    if (prev.x >= end.x || prev.y != start.y || prev.x < start.x)
    {
        throw std::logic_error("bad input");
    }
    return p_t{prev.x + 1, prev.y};
}
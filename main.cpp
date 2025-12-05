#include <iostream>

namespace topIT
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
}
int main()
{
    using topIT::Dot;
    topIT::IDraw *shapes[3] = {};
    int err = 0;
    try
    {
        shapes[0] = new Dot(0, 0);
        shapes[1] = new Dot(5, 7);
        shapes[2] = new Dot(-5, -2);
    }
    catch (...)
    {
        err = 2;
        std::cerr << "Bad drowing\n";
    }
    for (size_t i = 0; i < 3; ++i)
    {
        delete shapes[i];
    }
    return err;
}

topIT::Dot::Dot(int x, int y) : IDraw(), d{x, y} {}

topIT::Dot::Dot(p_t dd) : IDraw(), d{dd} {}

bool topIT::operator==(p_t a, p_t b)
{
    return a.x == b.x && a.y == b.y;
}

bool topIT::operator!=(p_t a, p_t b)
{
    return !(a == b);
}

topIT::p_t topIT::Dot::begin() const
{
    return d;
}

topIT::p_t topIT::Dot::next(p_t prev) const
{
    if (prev != begin())
    {
        throw std::logic_error("bad input");
    }

    return d;
}
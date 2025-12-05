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
        virtual ~IDraw();
    };
}
int main()
{
    using topIT::p_t;
    p_t a{1, 0}, b{1, 0};
    std::cout << (a == b) << '\n';
}

bool topIT::operator==(p_t a, p_t b)
{
    return a.x == b.x && a.y == b.y;
}

bool topIT::operator!=(p_t a, p_t b)
{
    return !(a == b);
}
#include"geom.hpp"

bool topIT::operator==(p_t a, p_t b) { return a.x == b.x && a.y == b.y; }
bool topIT::operator!=(p_t a, p_t b) { return !(a == b); }
size_t topIT::cols(f_t fr) { return fr.bb.x - fr.aa.x + 1; }
size_t topIT::rows(f_t fr) { return fr.bb.y - fr.aa.y + 1; }
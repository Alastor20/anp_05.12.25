#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>

void skipline(std::istream &is)
{

  using lim_t = std::numeric_limits< std::streamsize >;
  is.ignore(lim_t::max(), '\n');
}

void next(std::ostream &os, std::istream &is, size_t &context)
{
  size_t i = 0;
  if (!(is >> i)) {
    throw std::runtime_error("hi expects unsigned int in param");
  }
  skipline(is);
  os << "< OK >\n";
  context = i;
}

void last(std::ostream &os, std::istream &, size_t &context)
{
  os << "< " << context << " >\n";
}

std::istream &getWord(std::istream &is, char *word, size_t k, size_t &size, bool (*c)(char))
{
  is >> std::noskipws;
  size_t i = 0;
  for (char next = 0; is && !c(next) && (i < k - 1); ++i) {
    assert(k > 0 && "k must be greater than 0");
    if (!k || !word) {
      throw std::logic_error("bad buffer");
    }
    is >> next;
    word[i] = next;
  }
  if (i == k) {
    is.clear(is.rdstate() | std::ios::failbit);
  }
  word[i] = 0;
  size = i;
  return is >> std::skipws;
}

size_t match(const char *word, const char *const *words, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    bool matching = std::strlen(word) == std::strlen(words[i]);
    matching = matching && !std::strcmp(word, words[i]);
    if (matching) {
      assert(i < k && "i must be less then k");
      return i;
    }
  }
  return k;
}

bool is_space(char c)
{
  return std::isspace(c);
}

int main()
{
  constexpr size_t cmds_count = 3;
  using cmd_t = void (*)(std::ostream &, std::istream &, size_t &);
  cmd_t cmds[cmds_count] = {next, last};
  const char *const cmd_text[] = {"next", "last"};

  size_t context = 0;

  constexpr size_t bcapasity = 255;
  char word[bcapasity + 2] = {};
  size_t size;
  while (!getWord(std::cin, word, bcapasity, size, is_space).eof()) {
    if (std::cin.fail()) {
      std::cerr << "< INVALID >\n";
      return 1;
    } else {
      word[size - 1] = '\0';
      if (size_t i = match(word, cmd_text, cmds_count); i < cmds_count) {
        try {
          cmds[i](std::cout, std::cin, context);
        } catch (const std::exception &e) {
          std::cerr << "< INVALID: " << e.what() << " >\n";
          if (std::cin.fail()) {
            std::cin.clear(std::cin.rdstate() ^ std::ios::failbit);
          }
          skipline(std::cin);
        }
      } else {
        std::cerr << "< UNKNOWN >\n";
      }
    }
  }
}

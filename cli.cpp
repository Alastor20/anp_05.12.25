#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <istream>
#include <stdexcept>

void hi(std::istream &)
{
  std::cout << "< HI! >\n";
}

void hello(std::istream &)
{
  std::cout << "< HELLO! >\n";
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
  using cmd_t = void (*)(std::istream &);
  cmd_t cmds[cmds_count] = {hi, hello};
  const char *const cmd_text[] = {"hi", "hello"};
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
        cmds[i](std::cin);
      } else {
        std::cerr << "< UNKNOWN >\n";
      }
    }
  }
}

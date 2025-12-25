#include <cctype>
#include <cstddef>
#include <iostream>

void hi()
{
  std::cout << "< HI! >\n";
}

std::istream &getWord(std::istream &is, char *word, size_t k, bool (*c)(char))
{}

size_t match(const char *word, const char *const *words, size_t k)
{}

bool is_space(char c)
{
  return std::isspace(c);
}

int main()
{
  constexpr size_t cmds_count = 1;
  void (*cmds[cmds_count])() = {hi};
  const char *const cmd_text[] = {"hi"};
  constexpr size_t bsize = 255;
  char word[bsize + 1] = {};
  while (!getWord(std::cin, word, bsize, is_space).eof()) {
    if (std::cin.fail()) {
      std::cerr << "< INVALID >\n";
      return 1;
    } else if (size_t i = match(word, cmd_text, cmds_count); i < cmds_count) {
      cmds[i]();
    } else {
      std::cerr << "< UNKNOWN >\n";
    }
  }
}

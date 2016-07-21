
#include <iostream>
#include <limits>

using uchar = unsigned char;

int main()
{
  const auto min = std::numeric_limits<char>::min();
  const auto max = std::numeric_limits<char>::max();

  for (int i = min; i < max; ++i)
  {
    const auto c = (char)i;
    if (c == ' ') { std::cout << "< hoge >" << std::endl; }
    std::cout << "c = " << c << std::endl;
  }
}

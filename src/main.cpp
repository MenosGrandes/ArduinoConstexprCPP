#include "constexprMapArduino.cpp"

int main()
{
constexpr size_t size = 2;
    using IntPair = Pair<int, int>;
 constexpr Array<size, IntPair> pair_array = {make_pair(1, 2),
                                              make_pair(3, 4)};

}

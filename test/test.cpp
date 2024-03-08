#include "ut.hpp"
#include "../source.h"
#include <vector>
#include <array>
#include <string>

int main() {
    using namespace boost::ut;

#if defined (WIN32)
    cfg<override> ={.colors={.none="", .pass="", .fail=""}};
#endif

    "the only one"_test = [] {

        std::vector<int> const v ({0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
        expect(getLastZeroPos(v) == 5);

        std::vector<int> const v2 ({0, 0, 0, 0, 0, 1, 1, 1});
        expect(getLastZeroPos(v2) == 5);

        std::vector<int> const v3 ({0, 0, 1, 1, 1});
        expect(getLastZeroPos(v3) == 2);

        std::vector<int> const v4 ({1});
        expect(getLastZeroPos(v4) == 0);

        std::array<int,6> a {{0, 0, 0, 0, 1, 1}};
        expect(getLastZeroPos(a) == 4);

        std::string s {"00111"};
        expect(getLastZeroPos(s) == 2);

        char unshaped_array[] = {"000000000000000000000111111111111111111111111111111"};
        expect(getLastZeroPos(unshaped_array) == 21);

    };

}

#include <iterator>
#include <cassert>
#include <iostream>
#include "../../Algorithms/numeric.h"
using namespace std;
void testAdjacentDifference() {
    int arr[] = {1, 2, 4, 7, 11};
    int result[5];
    adjacent_difference(std::begin(arr), std::end(arr),
                         std::begin(result), static_cast<int*>(nullptr));
    int expected[] = {1, 1, 2, 3, 4};
    for (int i = 0; i < 5; ++i) {
        cout << "Expected: " << expected[i] << ", Actual: " << result[i] << endl;
        assert(result[i] == expected[i]);
    }
}

int main() {
    testAdjacentDifference();
    return 0;
}
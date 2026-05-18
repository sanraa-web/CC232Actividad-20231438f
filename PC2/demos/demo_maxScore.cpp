#include <iostream>
#include <vector>
#include "maxScore.h"

int main() {
    std::vector<int> nums = {1, -1, -2, 4, -7, 3};
    int k = 2;
    int result = algorithm::maxScore(nums, k);
    std::cout << "Maximum score: " << result << std::endl;
    return 0;
}
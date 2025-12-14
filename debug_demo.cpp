#include <iostream>

int main() {
    int sum = 0;
    
    // 我们要在这里观察 sum 是怎么一点点变大的
    for (int i = 1; i <= 5; ++i) {
        int temp = i * 10;
        sum = sum + temp;
        std::cout << "Step " << i << ": sum = " << sum << std::endl;
    }
    
    std::cout << "Final Result: " << sum << std::endl;
    return 0;
}   
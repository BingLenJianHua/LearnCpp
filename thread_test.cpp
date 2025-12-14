#include <iostream>
#include <thread>
#include <mutex>

// 创建一个全局锁 mtx
std::mutex mtx;
int count = 0;

void add() {
    for (int i = 0; i < 10000; ++i) {
        // 在 count++ 操作前后加锁
        std::lock_guard<std::mutex> lock(mtx);  // lock_guard 会自动加锁和解锁，防止忘记解锁造成死锁
        count++;
        // lock_guard 会在作用域结束时自动解锁（RAII机制）
    }
}

int main() {
    std::thread t1(add);
    std::thread t2(add);

    t1.join();
    t2.join();

    std::cout << "count = " << count << std::endl;

    // lock_guard 比手动 lock/unlock 更好，因为 lock_guard 使用了 RAII 机制，
    // 可确保加锁和解锁成对出现，即使发生异常也能安全解锁，避免死锁风险，代码更加安全和简洁。

    return 0;
}

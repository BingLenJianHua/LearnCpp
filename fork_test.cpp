#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // fork() 会创建一个几乎完全一样的新进程（子进程），父进程继续执行，子进程也继续执行。
    // fork() 在父进程中返回子进程的PID，在子进程中返回0，如果创建失败返回-1。
    pid_t pid = fork();
    // fork() 为什么会返回两次？
    // 解释：调用fork()后，操作系统会创建一个子进程。父进程和子进程从fork()调用处各自继续往下执行。
    // 在父进程中，fork() 返回新创建的子进程的PID；
    // 在新创建的子进程中，fork() 返回0；
    // 这样父子进程可以通过返回值判断自己的身份，执行不同的代码。
    if (pid < 0) {
        // fork 出错，打印错误信息
        std::cerr << "fork 创建子进程失败！" << std::endl;
        return 1;
    } else if (pid == 0) {
        // 这里是子进程执行的分支
        std::cout << "我是子进程，我的PID是: " << getpid()
                  << "，我爸爸的PID是: " << getppid() << std::endl;
    } else {
        // 这里是父进程执行的分支
        std::cout << "我是父进程，我的PID是: " << getpid()
                  << "，我刚才生出的子进程PID是: " << pid << std::endl;
    }
    sleep(100);
    return 0;
    
}

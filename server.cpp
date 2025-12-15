
#include <iostream>

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 1. 创建 socket，AF_INET 表示 IPv4，SOCK_STREAM 表示 TCP
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "创建 socket 失败" << std::endl;
        return -1;
    }
    std::cout << "Server started..." << std::endl;
    // 2. 绑定地址和端口到 socket 上
    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // 监听所有网卡
    server_addr.sin_port = htons(12345); // 设置端口号为12345

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "绑定端口失败" << std::endl;
        close(server_fd);
        return -1;
    }

    // 3. 让 socket 进入监听状态，等待客户端连接
    if (listen(server_fd, 5) == -1) {
        std::cerr << "监听失败" << std::endl;
        close(server_fd);
        return -1;
    }
    std::cout << "服务器已启动，等待客户端连接..." << std::endl;

    // 4. 接受客户端连接
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == -1) {
        std::cerr << "接受客户端连接失败" << std::endl;
        close(server_fd);
        return -1;
    }
    std::cout << "客户端已连接" << std::endl;

    // 5. Echo 循环，接收消息后发送回去
    char buffer[1024];
    while (true) {
        std::memset(buffer, 0, sizeof(buffer));
        ssize_t recv_len = recv(client_fd, buffer, sizeof(buffer), 0);
        if (recv_len <= 0) {
            std::cout << "客户端断开连接或发生错误" << std::endl;
            break;
        }
        // 将收到的数据原样发回去
        send(client_fd, buffer, recv_len, 0);
    }

    // 6. 关闭 socket
    close(client_fd);
    close(server_fd);

    return 0;
}

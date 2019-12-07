# Agent

> LongSight 控制器

在执行本 README 之前务必有 go 1.10 或更高版本的 go，最好是 go 1.13

下面是安装 Go 的指南

| Linux                                                        | Windows      | Mac          |
| ------------------------------------------------------------ | ------------ | ------------ |
| [How To Install Go 1.13 on Ubuntu 18.04 & 16.04 LTS](https://tecadmin.net/install-go-on-ubuntu/) | To be filled | To be filled |

注意 Go 语言需要手动配置项目位置，请遵从指南将位置设为 LongSight Project 文件夹。

## Build and Setup

以下命令均在 Agent 文件夹的环境下执行。

### 环境依赖

Go 语言会帮助我们解决依赖问题，go.mod 里已经准备好了我们将要依赖的库的地址

```bash
# 初始化开发环境
go mod init # 务必要 go 1.10 版本以上才能使用 mod command，最好是 go 1.13 以上
```

### 客户端

```bash
# 编译拍摄程序，可执行程序名称必须为 capture 。
g++ capture.cpp -o ./bin/capture

# 编译客户端。
go build ./client

# 显示客户端程序的使用说明。
./client --help

# 运行客户端，须确保 capture 和 client 在同一目录。
# id：客户端（单片机）ID。
# capture：拍摄程序名称。
# nsqdAddr：nsqd TCP 地址。
# fsAddr：文件系统地址。
./client -id=1 -capture="./capture" -nsqdAddr="119.23.106.13:4150" -fsAddr="http://119.23.106.13:8080/group1/upload"
```

### 服务端

```bash
# 编译服务端。
go build ./server

# 显示服务端程序的使用说明。
./server --help

# 运行服务端。
./server -nsqdAddr="119.23.106.13:4150" # server 二进制需要和 public 文件夹在一个目录下，你可以手动移动
```

### 控制台

在成功运行**客户端**和**服务端**后，我们可以通过 [http://localhost:4000](http://localhost:4000) 访问**控制台**。

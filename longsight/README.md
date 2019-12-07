# LongSight

## Docker Compose

我们使用 [Docker Compose](https://docs.docker.com/compose/) 安装各种基础设施，具体安装命令如下。

```bash
# 具体安装文档：https://docs.docker.com/compose/install/

# 下载文件
sudo curl -L "https://github.com/docker/compose/releases/download/1.24.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
# 设置权限
sudo chmod +x /usr/local/bin/docker-compose
# 查看版本
dokcer-compose version
```





## ISO

We may need to pack ISO or burn ISO to the tf disk to implement fast Rasperry distributed system clonization. Here are some references.

| Linux                                                        | Windows                                                      | Mac                                                          |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [How to Create an ISO File in Linux](https://www.wikihow.com/Create-an-ISO-File-in-Linux) | [How to Create an ISO File](https://www.wikihow.com/Create-an-ISO-File) | [How to Create an ISO File](https://www.wikihow.com/Create-an-ISO-File) |



## Cross-Compile

Cross-Compile is an optional choice when the ISO burning doesn't work. And Wenyin will be in charge of the cross-compiling procedure from PC Linux/Ubuntu to ARM Rasperry system. 
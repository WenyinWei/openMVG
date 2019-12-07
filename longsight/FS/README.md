# FS

> LongSight 文件系统

## 安装与说明

我们使用 Docker Compose 部署 [go-fastdfs](https://github.com/sjqzhang/go-fastdfs) 文件系统服务。

```bash
# 部署 go-fastdfs 文件系统服务。
docker-compose up -d
```

**我们得确保防火墙能够放行 8080 端口的流量**。

在部署完成后，我们可访问本地的 8080 端口访问文件系统上传页面（[http://119.23.106.13:8080/](http://119.23.106.13:8080/)）。

## 停止运行

通过执行以下命令，我们即可停止 go-fastdfs 服务。

```
# 停止文件系统服务。
docker-compose down
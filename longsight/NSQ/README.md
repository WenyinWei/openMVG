# NSQ

> LongSight NSQ 消息队列服务

## 说明

- 我们部署的 NSQ 服务是单 `nsqd` 实例的（**足以完成任务**）。

## 安装和运行

我们使用 Docker Compose 部署 NSQ 服务。

```bash
# 部署 NSQ 服务。
docker-compose up -d
```

在部署完毕后，我们需要参看当前的**端口映射**状况。

```bash
# 查看所有容器的运行状况。
docker ps -a
```

以下是上述命令的执行结果（已移除无关信息），我们需要关注的是 `PORTS` 信息。注意：**以 0 结尾的端口代表 TCP 访问端口，以 1 结尾的端口代表 HTTP 访问端口**。

```
PORTS                                                                                        NAMES
4150-4151/tcp, 4160-4161/tcp, 4170/tcp, 0.0.0.0:4171->4171/tcp                               nsq_nsqadmin_1
4160-4161/tcp, 0.0.0.0:4150-4151->4150-4151/tcp, 4170-4171/tcp                               nsq_nsqd_1
4150-4151/tcp, 4170-4171/tcp, 0.0.0.0:4160-4161->4160-4161/tcp                               nsq_nsqlookupd_1
```

根据执行结果，我们知道：

- `nsqadmin` 管理页面的访问地址：127.0.0.1:4171
- `nsqlookupd` TCP 访问地址：127.0.0.1:4160
- `nsqlookupd` HTTP 访问地址：127.0.0.1:4161
- `nsqd` TCP 访问地址：127.0.0.1:4150
- `nsqd` HTTP 访问地址：127.0.0.1:4151

注意，**我们得确保防火墙能够放行上述流量**。

## 停止服务

通过执行以下命令，我们即可停止 NSQ 服务。

```bash
# 停止 NSQ 服务。
docker-compose down
```

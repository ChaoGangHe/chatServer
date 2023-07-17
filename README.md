# chatServer
可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端源码 (基于muduo redis mysql)

### 1 Install required packages and softwares

#### 1.1 install mysql

```shell
sudo apt install mysql-server  # ubuntu20 
sudo apt install libmysqlclient-dev
mysql --version
# mysql  Ver 8.0.33-0ubuntu0.22.04.2 for Linux on x86_64 ((Ubuntu))
```

```shell
sudo systemctl status mysql
sudo cat /etc/mysql/debian.cnf 
mysql -u debian-sys-maint -p
```

only local login
```sql
USE mysql;
SELECT User,Host,plugin FROM mysql.user WHERE user='root';
ALTER USER 'root'@'localhost' IDENTIFIED WITH caching_sha2_password BY '123456'; 
flush privileges;
exit;
```

set remote login
```shell
mysql -u root -p   # 123456
```

```sql
UPDATE mysql.user SET Host='%' WHERE User='root' AND Host='localhost';
flush privileges;
ALTER USER root IDENTIFIED WITH caching_sha2_password BY '123456';
flush privileges;
```

see also:
http://blog.chinaunix.net/uid-192452-id-5862571.html



#### 1.2 install redis 


ubuntu 命令安装 redis 服务
```shell
sudo apt-get install redis-server
ps -ef | grep redis
```

```shell
git clone https://github.com/redis/hiredis
cd hiredis
make
sudo make install
sudo ldconfig /usr/local/lib
```

运行redis客户端
```shell
redis-cli
```

redis相关命令
```redis
keys *   # 查看所有键
```


#### 1.3 nginx


```shell
# 官网下载源码
http://nginx.org/en/download.html    
# nginx-1.24.0.tar.gz

# linux内核版本至少为2.6
# 安装相关依赖
sudo apt-get install gcc g++ 
sudo apt-get install libpcre3-dev
sudo apt-get install libssl-dev
sudo apt-get install libz-dev

sudo apt-get install libpcre3-dev libssl-dev libz-dev

# 安装nginx
tar -xzvf nginx-1.24.0.tar.gz
cd nginx-1.24.0/
```

```shell
./configure --with-stream
sudo make && sudo make install
cd /usr/local/nginx
sudo vim ./conf/nginx.conf   # 修改配置文件为 */chatserver/nginx/nginx.conf 文件内容
sudo ./sbin/nginx
netstat -tanop
```

```shell
sudo ./sbin/nginx -s reload
sudo ./sbin/nginx -s stop
```


#### 1.4 build chatserver

```shell
sh autobuild.sh
```


### 2 run chatserver


#### 2.1 确保mysql启动，其端口默认为3306

然后运行sql语句

```sql
create database chat;
use chat;
source /home/zhengmao22/work/chatserver/sql/chat.sql;
show tables;  
DELETE FROM 表名;   # 删除表中所有数据
```

运行上面sql语句后chat数据库会生成如下名称5张表
allgroup/friend/groupuser/offlinemessage/user


#### 2.2 确保redis启动，其端口默认为6379
#### 2.3 确保启动nginx负载均衡器，其端口为8000
#### 2.4 启动多台chatserver服务器和多台客户端用于测试


```shell
./bin/ChatServer 127.0.0.1 6000
./bin/ChatServer 127.0.0.1 6001
./bin/ChatServer 127.0.0.1 6002
```

```shell
./bin/ChatClient 127.0.0.1 8000
./bin/ChatClient 127.0.0.1 8000
./bin/ChatClient 127.0.0.1 8000
./bin/ChatClient 127.0.0.1 8000
```

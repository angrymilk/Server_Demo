# test
## 测试过的功能介绍
### 1.服务器链接多个客户端，可以保证任意一个客户端失去链接情况下不影响服务器的运行
### 2.一次性发送三个合并的消息，消息可以一个个正确的解析
### 3.一次发送半个消息，第二次再发送剩下半个消息，消息可以在第二次被正确的解析
### 4.广播和单播基本功能测试都正常
### 5.在确定消息长度不会超过buffer总长度的情况下，但是多个消息会超过buffer指定长度的情况下，可以保证消息在从buffer尾到头移动正确

## 使用方式介绍
### 在test主目录下直接运行bash build_all.sh，会编译对应的可执行文件
### 客户端的使用方式在主目录下./server ${服务端的ip} ${服务端的端口} 
### 客户端的使用方式在主目录下./client ${客户端的ip} ${客户端的端口} ${服务端的ip} ${服务端的端口} 
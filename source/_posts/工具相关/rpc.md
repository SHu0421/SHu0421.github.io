---
title: RPC related
categories:
  - 工具相关
date: 2021-12-03 10:01:07
tags: rpc
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---

gRPC 可以保证不同语言之间的通讯
编写.proto文件，生成指定语言源代码。
编写服务端代码
编写客户端代码
https://www.liwenzhou.com/posts/Go/gRPC/  一个python客户端和go服务端的例子


pytorch的官网框架
rpc常见方法
rpc_sync同步远程调用、rpc_async异步远程调用、remote异步远程调用。

rpc.init_rpc 初始化rpc，需要在master和worker都进行初始化，方便之后的通讯
rpc.rpc_sync  worker端调用在master上进行执行的方法
rpc.rpc_async  
rpc.remote




dist_autograd.get_gradient(cid) 目前猜测在rpc场景进行前向传播，的梯度反向传播需要使用dist_grad

TrainNet是worker调用的假的网络，实际的网络是在Net里面调用，每次worker里面数据的前向传播，实际上都是在master里面的调用net进行前向传播
### 分析rpc_parameter_server代码
master和worker都需要init_rpc

worker里面主要执行TrainNet：初始化的时候得到远程parameterServer的引用，然后包含二个函数 get_global_param_rref 以及forward函数(均要调用remote_method)
master里面执行parameterServer类，：初始的时候，得到真实训练的model, 同时实现三个函数, 对模型参数加上的引用rpc.RRef，使用dist_autograd得到模型参数，以及对输入数据进行前向传播

在master中加上

uni_sample_score_rref


### gRPC

route_guide_client文件主要是通过stub 和传入的参数调用server的函数

route_guide_server里面主要是编写得到输入服务器处理函数逻辑

route_guide_pb2_grpc，类似于头文件，定义Stub类和Servicer类，每个类只是定义函数，但不进行具体的实现； 以及一个add_RouteGuideServicer_to_server的函数

 
#### 使用go语言
- 前置安装要求
安装go，和protocol buffer编译器
https://grpc.io/docs/languages/go/quickstart/#prerequisites

go command not found
使用export， 重启一个控制台窗口就找不到这个命令了
需要使用vim ~/.bashrc写入文件 将这个命令写进去，然后使用source ~/.bashrc
(~/.bashrc:是用户相关的终端（shell）的环境设置，通常打开一个新终端时，默认会load里面的设置，在这里的设置不影响其它人。
/etc/profile会影响所有的用户)

go download超时解决：
export GOPROXY=https://goproxy.cn

go 软件的安装
1. 直接使用 tar -C /usr/local -xzf go1.4.7.linux-amd64.tar.gz 解压到 local 目录 设置PATH，export PATH=$PATH:/usr/local/go/bin

2. 假定你想要安装Go的目录为 $GO_INSTALL_DIR，后面替换为相应的目录路径。 解压缩tar.gz包到安装目录下：tar zxvf go1.14.7.linux-amd64.tar.gz -C $GO_INSTALL_DIR。
设置PATH，export PATH=$PATH:$GO_INSTALL_DIR/go/bin

如果修改用户环境变量：设置 vim ~/.bash_profile
如果修改系统环境变量：设置 vim /etc/profile

3. [go安装的三种方法](https://github.com/astaxie/build-web-application-with-golang/blob/master/zh/01.1.md)


4. go的插件在vscode命令行中显示失败 i/o time out
解决方法：GO111MODULE=on GOPROXY=https://goproxy.cn,direct go install 

5. vscode下载go 包的时候一个failed的解决方案（和第4个有点雷同）
https://www.cnblogs.com/marshhu/p/11848020.html


#### 使用python
一个python小例子：https://grpc.io/docs/languages/python/quickstart/
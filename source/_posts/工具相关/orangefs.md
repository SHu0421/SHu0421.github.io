---
title: orangefs
categories:
  - 工具相关
date: 2021-12-01 15:54:01
tags: orangefs
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---

### orangefs

1. genconfig是一个go语言文件，它有一个可选参数oranges-server.conf

2. init_start_all.sh相比start_all.sh 多了一个/local500G/orange_store/ 以及多了一条有-f命令的语句 应该是在服务器节点启动pvfs-server
orangefs默认的服务器的文件系统挂载的目录是在oranges-server.conf里面进行配置（/nfs/home/yfwang/orangefs/install/etc/oranges-server.conf）

加上f的原因： 第一次启动PVFS2服务要首先分配空间，添加参数-f：
root@ubuntu:~# pvfs2-server /etc/pvfs2-fs.conf -f
其后启动服务则不需加参数，或使用-d使得服务运行于前台（占用当前终端窗口，终端窗口关闭后服务终止）

```bash
for host in `cat /nfs/home/yfwang/orangefs/install/nodelist`
do
#       ssh -t -t -o StrictHostKeyChecking=no -o PasswordAuthentication=no $USER@$host sudo rm -rf /local500G/orange_store/*
        ssh -t -t -o StrictHostKeyChecking=no -o PasswordAuthentication=no $USER@$host sudo /nfs/home/yfwang/orangefs/install/sbin/pvfs2-server -f /nfs/home/yfwang/orangefs/install/etc/oranges-server.conf
        ssh -t -t -o StrictHostKeyChecking=no -o PasswordAuthentication=no $USER@$host sudo /nfs/home/yfwang/orangefs/install/sbin/pvfs2-server /nfs/home/yfwang/orangefs/install/etc/oranges-server.conf
done 
```
4. stop_all.sh 停止所有的pvfs-server
```bash 
for host in `cat /nfs/home/yfwang/orangefs/install/nodelist`
do
        ssh -t -t -o StrictHostKeyChecking=no -o PasswordAuthentication=no $USER@$host sudo killall pvfs2-server
done
```

5. start_client.sh 启动客户端orangefs-client， 同时将服务器任意一个节点的位置暴露为客户端，例子是hec09

```bash 
sudo /nfs/home/yfwang/orangefs/install/sbin/pvfs2-client -f -p /nfs/home/yfwang/orangefs/install/sbin/pvfs2-client-core
sudo mount -t pvfs2 tcp://hec09:3334/orangefs /mnt/orangefs
```

nodelist
里面直接写hec10 hec11

https://github.com/waltligon/orangefs/wiki/Distributions-and-Layouts 设置数据不同的放置策略,一个文件放在一个节点使用basic方式 distribution

https://github.com/waltligon/orangefs/wiki/Programming-Guide

setfattr -n "user.pvfs2.dist_name" -v "basic_dist" /mnt/pvfs2/directory
./bin/pvfs2-xattr -s -k "user.pvfs2.dist_name" -v "basic-dist" /mnt/shu-orangefs/dataset

orangefs里面有一个PINT_dist函数
https://www.mcs.anl.gov/~robl/pvfs2/pvfs2-dox/html/pint-distribution_8c.html#a2

##### 现在找到将文件保存在一个服务器的方案：
https://stackoverflow.com/questions/64923445/how-to-configure-orangefs-save-the-file-into-the-same-server-not-split-it
使用命令：setfattr -n "user.pvfs2.num_dfiles" -v "1" /mnt/orangefs
如果按照这种方式设置会报错：setfattr -n "user.pvfs2.dist_name" -v "basic_dist" /mnt/pvfs2/directory 传输数据会报错




### 配置教程
安装server
拷贝已经编译好的程序
cp -r /nfs/home/yfwang/orangefs/install /nfs/home/weijian/orangefs_install/
配置server
./bin/pvfs2-genconfig /nfs/home/weijian/orangefs_install/install/orangefs-server.conf
具体的配置项，自己可以先记录下来
tcp
3336
/local500G/wj-fast/storage/data
/local500G/wj-fast/storage/meta
/var/log/orangefs-server.log
hec08,hec09
配置完成时可以cat /nfs/home/weijian/orangefs_install/install/orangefs-server.conf查看配置项是否符合需求
到各个server上，各自初始化存储目录
sudo ./sbin/pvfs2-server -f orangefs-server.conf -a <server alias>
到各个server上，启动服务
sudo ./sbin/pvfs2-server  orangefs-server.conf

安装client
拷贝已经编译好的程序（如果已经可以访问就不需要拷贝了）
scp -r weijian@hec08:/nfs/home/yfwang/orangefs/install/ /nfs/home/weijian/orangefs_install/
向内核加载orangefs模块
sudo modprobe orangefs
创建挂载点
sudo mkdir /mnt/wj-fast-orangefs
写配置文件
sudo sh -c “echo ‘tcp://hec08:3336/orangefs /mnt/wj-fast-orangefs pvfs2’ >> /etc/pvfs2tab”
测试与server是否连通
./bin/pvfs2-ping -m /mnt/wj-fast-orangefs
启动client客户端
sudo ./sbin/pvfs2-client -p ./sbin/pvfs2-client-core
挂载
sudo mount -t pvfs2 tcp://hec08:3336/orangefs /mnt/wj-fast-orangefs
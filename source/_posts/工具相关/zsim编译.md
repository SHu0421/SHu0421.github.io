---
title: Zsim编译
categories:
  - 工具相关
date: 2022-04-26 21:05:06
tags:
---


#### 服务器环境
ubuntu18.04下gcc7.5.0

#### 主要参考文档
步骤文档：
https://blog.csdn.net/yy1348046572/article/details/118194214
注意使用sudo make && sudo make install

安装zsim版本：https://github.com/SteveY4ng/zsim

除此之外，自己加了一个env.sh文件来添加环境变量

```bash
BASEDIR=$(pwd)
PINPATH=$BASEDIR/pin-2.14
ZSIMPATH=$BASEDIR/zsim
LIBCONFIGPATH=/nfs/home/siling/zsim/zsim-ubuntu18_04/libconfig-1.7.3
HDF5PATH=/nfs/home/siling/zsim/zsim-ubuntu18_04/hdf5-1.12.0
export CPATH="/usr/include/hdf5/serial/"
export ZSIMPATH PINPATH LIBCONFIGPATH POLARSSLPATH
export CXX=g++ CC=gcc
```


#### 遇到的问题及解决
在安装hdf5使用源文件，出错，因此使用的命令安装 sudo apt-get install libhdf5-dev
https://blog.csdn.net/tianminggenie/article/details/110921264


遇到的问题1：
can't find file #include<hdf5.h>
解决方案：
在env.sh中加上
export CPATH="/usr/include/hdf5/serial/"


遇到的问题2：
Cannot find -lhdf5_hl and -lhdf5
解决方案：
cd /usr/lib/x86_64-linux-gnu
\\然后根据情况执行下面两句：
sudo ln -s libhdf5_serial.so.10.1.0 libhdf5.so
sudo ln -s libhdf5_serial_hl.so.10.0.2 libhdf5_hl.so

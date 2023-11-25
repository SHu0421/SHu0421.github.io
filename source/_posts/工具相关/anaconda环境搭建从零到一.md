---
title: Anaconda环境搭建
tags: conda environment
categories:
  - 工具相关
date: 2021-12-15 14:48:24
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---

### 问题描述
一个服务器上已经搭建好的环境，但是需要换另一台机器，或者另外的用户需要访问这个环境， 如果另一台服务器上没有anaconda环境就需要从0开始进行搭建，然后再进行环境的迁移

### 解决方案

1. 安装anaconda3
```
 wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-5.3.1-Linux-x86_64.sh
 bash Anaconda3-5.3.1-Linux-x86_64.sh
```

一般情况下安装是默认设置，在安装vscode的时候可以根据需要选择no或者yes
注意在安装installer的时候需要选择yes, 如果选择了no
那么可以自行添加环境:
https://zhuanlan.zhihu.com/p/64930395（也就是激活环境中的方法二）


2. 激活环境
```
# 方法一失效
输入命令打开配置文件：vim ~/.bashrc
在最后添加语句：export PATH=/root/xxx/anaconda3/bin:$PATH （/root/xxx 为安装路径）
最后输入如下命令，更新配置文件即可：source ~/.bashrc

#方法二有效：
如果conda的初始化时选择了no，则需要自行配置环境变量。

打开profile文件：

vi /etc/profile
在文件最后加入如下语句（路径需要根据自己的安装位置更改）：

PATH=$PATH:/opt/anaconda3/bin
export PATH
保存文件并退出。最后使用如下命令刷新环境变量即可：

source /etc/profile
echo $PATH
```

PS: 如果conda名称弹出问题，使用```sudo vi ~/.bashrc```查看conda路径是否正确

3. conda相关命令
```
conda list 查看安装包
conda info --envs 查看环境
conda activate XXX 激活环境 （XXX 为环境名称）
python -V 检查Python版本

如果需要卸载anaconda的话，只需要删除anaconda目录即可:
rm -rf /root/xxx/anaconda3
```
4. 使用conda-pack迁移环境

在源机器：
```
conda pack -n env-name --ignore-editable-packages（如果没有后面这个会报错）
得到一个env_name.tar.gz压缩文件
```

在目标机器：
```
cd ~/anaconda3/envs;
mkdir env_name
tar -xzvf env_name.tar.gz -C /home/root_name/anaconda3/envs/env_name
```


5. 使用环境
```source activate attnGAN```

注意使用conda activate会报错
目前找到一个解决方案：
https://blog.csdn.net/qq_43828332/article/details/114235922


总共耗时 1个半小时左右~


#### 参考链接：
1. https://blog.csdn.net/lwgkzl/article/details/89329383
2. https://www.jianshu.com/p/1fddd11bcd25
3. https://blog.csdn.net/ds1302__/article/details/120027173



注意之江实验室hec anaconda3的安装路径是：/nfs/home 


#### 相关问题
在终端输入conda info --envs检验anaconda是否安装成功，发现报错：conda: command not found

原因是因为~/.bashrc文件没有配置好

解决方案：
sudo vim ~/.bashrc
在最后一行加上
export PATH=$PATH:/home/vincent/anaconda3/bin


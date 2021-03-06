---
title: rclone
categories:
  - 工具相关
date: 2021-11-08 21:39:25
tags:
---

### 从google drive中下载文件的两种方法

#### 1.让远程服务器使用rclone挂载google drive (谷歌云端硬盘)

简易步骤：
1. 下载rclone:
``` bash
wget https://www.moerats.com/usr/shell/rclone_debian.sh && bash rclone_debian.sh
```

2. rclone的配置

``` bash
rclone config
```

3.使用rclone进行google drive的挂载

``` bash 
#新建本地文件夹，路径自己定，即下面的LocalFolder
mkdir /root/GoogleDrive
#挂载为磁盘，下面的DriveName、Folder、LocalFolder参数根据说明自行替换
rclone mount DriveName:Folder LocalFolder --copy-links --no-gzip-encoding --no-check-certificate --allow-other --allow-non-empty --umask 000

#eg. DriveName:Folader ==> GoogleDrive:/   LoacalFolder ==> /data1/shu 

#rclone取消挂载
fusermount -qzu <本地路径>
```

参考链接： https://www.moerats.com/archives/481/


#### 2. 从google drive中使用wget下载单个文件 

1.下载小文件

``` bash
wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=FILEID' -O FILENAME

#有的评论说针对rar文件需要加上-r
wget --no-check-certificate -r 'https://docs.google.com/uc?export=download&id=FILEID' -O FILENAME
```

2.下载大文件

``` bash
wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=FILEID' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=FILEID" -O FILENAME && rm -rf /tmp/cookies.txt

```

PS:注意都是下载的文件，不是文件夹; folder目前找到的解决方案是使用循环


参考链接： https://gist.github.com/iamtekeste/3cdfd0366ebfd2c0d805





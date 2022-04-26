---
layout: blog
title: Linux命令
date: 2021-11-11 09:52:14
tags: Linux command
---

#### rename

批量修改后缀名
```bash

rename s/\后缀1/\后缀/' *

rename s/\后缀1/\后缀/' ** //递归所有的子目录

example: rename 's/\.tar.gz.1/\.tar.gz/' *
```

#### 手动清理缓存
```bash
释放缓存区内存的方法
1）清理pagecache（页面缓存）
[root@backup ~]# echo 1 > /proc/sys/vm/drop_caches     或者 # sysctl -w vm.drop_caches=1
 
2）清理dentries（目录缓存）和inodes
[root@backup ~]# echo 2 > /proc/sys/vm/drop_caches     或者 # sysctl -w vm.drop_caches=2
 
3）清理pagecache、dentries和inodes
[root@backup ~]# echo 3 > /proc/sys/vm/drop_caches     或者 # sysctl -w vm.drop_caches=3
　
上面三种方式都是临时释放缓存的方法，要想永久释放缓存，需要在/etc/sysctl.conf文件中配置：vm.drop_caches=1/2/3，然后sysctl -p生效即可！
 
另外，可以使用sync命令来清理文件系统缓存，还会清理僵尸(zombie)对象和它们占用的内存
[root@backup ~]# sync
```

#### 服务器之间使用scp进行文件传输和同步
rsync -r -P --rsh=ssh source_dir dest_dir(shu@10.5.26.19:/nfs/home/shu/hushuang-8a100)


Linux服务器上修改gcc版本
https://blog.csdn.net/qq_31175231/article/details/77774971



---
title: Linux Command
tags: linux
categories:
  - Tools
date: 2023-07-24 16:40:43
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---

#### 1. rename:

Modify the suffix in batches

```python

rename s/\suffix1/\suffix/' *

rename s/\suffix1/\suffix/' **  # recurse all subdirectories

example: rename 's/\.tar.gz.1/\.tar.gz/' *
```

#### 2. Manually clear the cache

```bash
methods to release buffer memory
1）clear pagecache
[root@backup ~]# echo 1 > /proc/sys/vm/drop_caches     or # sysctl -w vm.drop_caches=1
 
2）clear dentries和inodes
[root@backup ~]# echo 2 > /proc/sys/vm/drop_caches     or # sysctl -w vm.drop_caches=2
 
3）clear pagecache、dentries and inodes
[root@backup ~]# echo 3 > /proc/sys/vm/drop_caches     or # sysctl -w vm.drop_caches=3

```

The above three methods are all ways to temporarily release the cache. To permanently release the cache, you need to configure ```vm.drop_caches=1/2/3``` in the ```/etc/sysctl.conf   ```file, then, use ``` sysctl -p```  to activate it!

In addition, you can use the ```sync  ``` command to clean up the cache of file system. It can also clean up zombie objects and the memory they occupy

```bash
[root@backup ~]# sync
```

```
Use scp for file transfer and synchronization between servers
```

#### 3. Use scp to transfer files and synchronize between servers

`````bash
rsync -r -P --rsh=ssh source_dir dest_dir(shu@10.5.26.19:/nfs/home/shu/hushuang-8a100)
`````


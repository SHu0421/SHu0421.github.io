---
title: RClone Comand
tags: rclone
categories:
  - Tools
date: 2023-07-24 16:41:04
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---


### Download Files from Google Drive

#### METHOD ONE. Using rclone to mount google drive as a remote server

Simple Steps：
1. download clone:
``` bash
wget https://www.moerats.com/usr/shell/rclone_debian.sh && bash rclone_debian.sh
```

2. config rclone

``` bash
rclone config
```

3. mount google drive by rclone

``` bash 
#Create a new local folder, the path is determined by yourself, that is, the following LocalFolder
mkdir /root/GoogleDrive
#Mount as a disk, the following DriveName, Folder, LocalFolder parameters are replaced according to the instructions
rclone mount DriveName:Folder LocalFolder --copy-links --no-gzip-encoding --no-check-certificate --allow-other --allow-non-empty --umask 000

#eg. DriveName:Folader ==> GoogleDrive:/   LoacalFolder ==> /data1/shu 

#umount
fusermount -qzu <local path>
```

[Reference Materials]( https://www.moerats.com/archives/481/) 

#### METHOD TWO.  download single file from google drive by wget

##### 1. download small files

``` bash
wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=FILEID' -O FILENAME

#add -r towards rar files
wget --no-check-certificate -r 'https://docs.google.com/uc?export=download&id=FILEID' -O FILENAME
```

##### 2. download big files

``` bash
wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=FILEID' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=FILEID" -O FILENAME && rm -rf /tmp/cookies.txt

```

**Notice**: The methods mentioned above are all downloaded files, not folders; the solution currently found towards folder is to use a loop.

[Reference Materials](https://gist.github.com/iamtekeste/3cdfd0366ebfd2c0d805) 

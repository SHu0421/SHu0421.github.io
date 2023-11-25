---
title: 博客问题与改进
tags: hexo
hide: true
categories:
  - 其他
date: 2023-11-25 12:07:59
---


### 需要注意的地方
1. 使用git命令，如果回滚到上一次提交，但是本地记录不变的话，使用--mixed

### 目前博客的问题
1. 只能使用https deploy, 使用git ssh key上传会报错，但是ssh -T github.com是成功返回的
2. 如果自己使用git pull和git push上传会导致部署失败，而且会上传一些无关代码 .deploy_git .history等
3. 随机图片同一个时刻返回相同，导致主页index_img都相同


### 未来优化的方向
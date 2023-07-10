---
title: Git Related
categories:
  - 工具相关
date: 2022-10-17 20:13:18
tags:
---


1. git pull超时，访问缓慢的解决方案
参考链接：
https://jasonkayzk.github.io/2019/10/10/%E5%85%B3%E4%BA%8E%E4%BD%BF%E7%94%A8Git%E6%97%B6push-pull%E8%B6%85%E6%97%B6-%E4%BB%A5%E5%8F%8AGithub%E8%AE%BF%E9%97%AE%E6%85%A2%E7%9A%84%E8%A7%A3%E5%86%B3%E5%8A%9E%E6%B3%95/

git超时比较有用的命令：git config --global --add remote.origin.proxy "" 

git 现在不支持密码登陆，只支持token登陆：
git remote set-url origin https://<your_token>@github.com/<USERNAME>/<REPO>.git
比如：
git remote set-url origin https://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@github.com/SHu0421/DNN_Cplusplus.git

https://hexo.io/zh-cn/docs/github-pages.html#%E7%A7%81%E6%9C%89-Repository hexo+github私有仓库



2. github
```bash
Missing or invalid credentials.
Error: ENOSPC: no space left on device, write
    at Object.writeSync (node:fs:884:3)
    at Object.writeFileSync (node:fs:2163:26)
    at /nfs/home/shu/.vscode-server/bin/64bbfbf67ada9953918d72e1df2f4d8e537d340e/extensions/git/dist/askpass-main.js:1:9371

fatal: Authentication failed for 'https://github.com/SHu0421/Graduate_Thesis.git/'
```
1. 根目录满了
2. https://blog.csdn.net/weixin_41010198/article/details/119698015
当输入github的邮箱和密码的时候，使用git token作为密码，而不是github仓库的密码


3. 使用本地网络在服务器上下载东西
具体见：command-related的第一条


4. github clone一直卡住
https://blog.csdn.net/x763795151/article/details/114903758
一定要先设置代理后取消，直接取消没有效果


5. git pull 或者git push一直卡住
使用ssh key的方式连接远程仓库
查看remote-url:
'''git remote -v '''
删除remote-url:
’‘’git remote rm origin‘’‘
添加
’‘’git remote add origin git@xxxx '''

添加和删除可以合并为一个操作
‘’‘git remote set-url origin’‘’



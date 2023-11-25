---
title: Hexo 相关笔记
categories:
  - 工具相关
date: 2021-11-08 14:46:10
tags:
---


#### hexo 主题切换
```
git clone xxx.git themes/black-blue //注意在blog路径里面

vim _config.yml //修改theme为black-blue

npm install --save hexo-renderer-jade hexo-generator-feed hexo-generator-sitemap hexo-browsersync hexo-generator-archive

hexo clean

hexo g

hexo s

```
#### 常见命令

```bash
1.hexo建立某一个目录下的blog
hexo new blog -p leetcode/new_name.md

2.上传到github仓库 (一定注意在mac电脑上使用sudo)
sudo hexo d 

3. 生成静态页面
hexo generate

4.查看网页
hexo server

5.本地查看
hexo clean && hexo g && hexo s
```

上传git上面的一系列命令
hexo clean && hexo g && sudo hexo d

#### hexo source文件上传， source 分支和master分支
https://blog.csdn.net/itnerd/article/details/114274304 


#### hexo+github私有仓库
(参考链接)[https://hexo.io/zh-cn/docs/github-pages.html#%E7%A7%81%E6%9C%89-Repository]

#### 参考链接
[Mac OS上搭建Hexo博客流程](https://juejin.cn/post/6978377036645531662)
[配置指南](https://hexo.fluid-dev.com/docs/guide/#%E6%96%87%E7%AB%A0%E5%9C%A8%E9%A6%96%E9%A1%B5%E7%9A%84%E5%B0%81%E9%9D%A2%E5%9B%BE)

#### 常见问题
1. 文章中插入图片无法显示
解决方法：注意将图片放在/source/img 而不是/img路径，即使是首页图像也是如此

2. 文章加密或隐藏
- 设置某一个目录的文章加密
在_config.yml文件中设置目录名字和密码 - {name: tagName, password: 密码B}
在对应文章中设置tags 为 tagName （默认为private）即可完成文章的加密

- 设置某一文章为hidden
如果设置文章 hidden:true则网页上无法搜索到文章，上述方法可以在网页上看文章，但是需要密码
查看标签为hidden的文章 [github repo](https://github.com/prinsss/hexo-hide-posts)
  ```hexo hidden:list``` 

- 使用草稿箱隐藏
[使用方法参考链接](https://blog.holic-x.com/wv-blog/post/6aa34fdd.html#hexo-butterfly-%E6%96%87%E7%AB%A0%E9%9A%90%E8%97%8F)

3. 创建中英文博客
- 两个仓库 两个域名 推送/部署两次[参考链接]（https://youngforest.github.io/2021/09/07/Setup-English-blog/）
- 一个仓库 一个域名 推送/部署一次[参考链接1](https://www.brando.dev/zh-hans/2021/01/03/%E8%AE%B0%E4%B8%80%E6%AC%A1-Hexo-%E5%8D%9A%E5%AE%A2%E8%BF%81%E7%A7%BB%E4%B8%8E%E5%A4%9A%E8%AF%AD%E8%A8%80%E7%AB%99%E7%82%B9%E6%94%B9%E9%80%A0/)
[参考链接2](https://zhuanlan.zhihu.com/p/358599353)
- 使用hexo具有中英文切换的主题 minos [参考链接](https://medium.com/learn-or-die/%E5%88%A9%E7%94%A8-hexo-%E4%BE%86%E5%BB%BA%E7%AB%8B%E4%B8%80%E5%80%8B-%E5%A4%9A%E8%AA%9E%E7%B3%BB-%E9%83%A8%E8%90%BD%E6%A0%BC-4545cc6cdb6)
icarus: 中英文文章会同时出现[github repo](https://github.com/ppoffice/hexo-theme-icarus/discussions/1046)
- [搭建好的博客例子](https://medium.com/learn-or-die/%E5%88%A9%E7%94%A8-hexo-%E4%BE%86%E5%BB%BA%E7%AB%8B%E4%B8%80%E5%80%8B-%E5%A4%9A%E8%AA%9E%E7%B3%BB-%E9%83%A8%E8%90%BD%E6%A0%BC-4545cc6cdb6)




### 注意

1. 只能使用https deploy, 使用git ssh key上传会报错，但是ssh -T github.com是成功返回的；

2. source分支可以删除；开发在dev上，和仓库同步后，merge到master分支（在master分支执行命令```git merge dev```），使用run_cmd_d.sh进行提交部署；

3. master分支提交的其实是blog/public里面的文件；hexo g是生成public文件，因此clean文件的时候没必要运行hexo g
[hexo cli 源码/ hexo d 内部逻辑](https://blog.eson.org/pub/70d0eddc/)

4. 每次push的时候一定要指定upstream， ```git push origin dev/master/source```




### 未来优化的方向

1. 随机图片同一个时刻返回相同，导致主页index_img都相同

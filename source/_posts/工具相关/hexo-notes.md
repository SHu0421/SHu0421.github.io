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

#### 参考链接
https://juejin.cn/post/6978377036645531662
配置指南
https://hexo.fluid-dev.com/docs/guide/#%E6%96%87%E7%AB%A0%E5%9C%A8%E9%A6%96%E9%A1%B5%E7%9A%84%E5%B0%81%E9%9D%A2%E5%9B%BE

#### 常见问题
1. 文章中插入图片无法显示
解决方法：注意将图片放在/source/img 而不是/img路径，即使是首页图像也是如此
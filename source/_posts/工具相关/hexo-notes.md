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
```

#### 参考链接
https://juejin.cn/post/6978377036645531662
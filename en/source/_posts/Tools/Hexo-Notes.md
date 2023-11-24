---
title: Hexo Notes
tags: Tools
categories:
  - Tools
date: 2023-07-24 16:34:08
---

Welcome to [Hexo](https://hexo.io/)! This is your very first post. Check [documentation](https://hexo.io/docs/) for more info. If you get any problems when using Hexo, you can find the answer in [troubleshooting](https://hexo.io/docs/troubleshooting.html) or you can ask me on [GitHub](https://github.com/hexojs/hexo/issues).

#### 1. Quick Start

##### Create a new post

``` bash
$ hexo new "My New Post"
```

More info: [Writing](https://hexo.io/docs/writing.html)

##### Run server

``` bash
$ hexo server
```

More info: [Server](https://hexo.io/docs/server.html)

##### Generate static files

``` bash
$ hexo generate
```

More info: [Generating](https://hexo.io/docs/generating.html)

##### Deploy to remote sites

``` bash
$ hexo deploy
```

More info: [Deployment](https://hexo.io/docs/one-command-deployment.html)


#### 2. Hexo Theme Change
```
git clone xxx.git themes/black-blue 

vim _config.yml //change theme to black-blue

npm install --save hexo-renderer-jade hexo-generator-feed hexo-generator-sitemap hexo-browsersync hexo-generator-archive

hexo clean

hexo g

hexo s

```
#### 3. Common Hexo Command

```bash
# 1. set up a blog in a special directory
hexo new blog -p leetcode/new_name.md

# 2. upload it to the github repo and deploy
sudo hexo d 

# 3. generate static pages
hexo generate

# 4. run the server for webpages
hexo server

# 5. see in localhost
hexo clean && hexo g && hexo s
```

#### 4. Reference Materials
[Build Hexo Blog in Mac](https://juejin.cn/post/6978377036645531662)
[Hexo Reference Webpage](https://hexo.fluid-dev.com/docs/guide/#%E6%96%87%E7%AB%A0%E5%9C%A8%E9%A6%96%E9%A1%B5%E7%9A%84%E5%B0%81%E9%9D%A2%E5%9B%BE)

#### 5. Common Questions
1. Q: The images can't show in the articles or the main page

​				 S: put the images in the path ```/source/img ``` rather than ```/img```, the main pages' images too.

2. Q: How to encrypt the articles

   S: There are three methods

   **Method 1**: Set the encryption to a certain directory of articles.
   	First, set the encrypted tag name and password in the _config.yml file - {name: tagName B, password: password B}
   	Second, In the corresponding article, set tags to tagName (the default is private) 

   ​	Finally, after deployment, you can only access these articles with tagName B with passward B

   By this method, you can read the article on the webpage, but a password is required.

   **Method 2**: Set an article as hidden

    If you set ``` hidden: true``` at the top of the article, then, the article cannot be searched on the webpage. 
    View articles tagged hidden: ```hexo hidden: list```

    [Refer github repo](https://github.com/prinsss/hexo-hide-posts)

   **Method 3** : Hide articles using draftbox, to see the articles by publishing
   [How to realize draftbox](https://blog.holic-x.com/wv-blog/post/6aa34fdd.html#hexo-butterfly-%E6%96%87%E7%AB%A0%E9%9A%90%E8%97%8F)

   

3. Q: Create double lauguage blog (Chinese and English)

   A: Three methods:

   - Double Repo, Deploy Twice [Reference](https://youngforest.github.io/2021/09/07/Setup-English-blog/)

   - One Repo, Deploy Once [Reference 1](https://www.brando.dev/zh-hans/2021/01/03/%E8%AE%B0%E4%B8%80%E6%AC%A1-Hexo-%E5%8D%9A%E5%AE%A2%E8%BF%81%E7%A7%BB%E4%B8%8E%E5%A4%9A%E8%AF%AD%E8%A8%80%E7%AB%99%E7%82%B9%E6%94%B9%E9%80%A0/)
   [Reference 2](https://zhuanlan.zhihu.com/p/358599353)

   - Using a special hexo theme which supports double lauguage. For example,  minos [Minos Reference](https://medium.com/learn-or-die/%E5%88%A9%E7%94%A8-hexo-%E4%BE%86%E5%BB%BA%E7%AB%8B%E4%B8%80%E5%80%8B-%E5%A4%9A%E8%AA%9E%E7%B3%BB-%E9%83%A8%E8%90%BD%E6%A0%BC-4545cc6cdb6)
   icarus:  [github repo](https://github.com/ppoffice/hexo-theme-icarus/discussions/1046)

   - [Blog Example with Double Language](https://medium.com/learn-or-die/%E5%88%A9%E7%94%A8-hexo-%E4%BE%86%E5%BB%BA%E7%AB%8B%E4%B8%80%E5%80%8B-%E5%A4%9A%E8%AA%9E%E7%B3%BB-%E9%83%A8%E8%90%BD%E6%A0%BC-4545cc6cdb6)
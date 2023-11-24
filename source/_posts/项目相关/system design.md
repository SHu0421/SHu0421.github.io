---
title: System Design
categories:
  - 项目相关
date: 2021-11-24 20:40:15
tags:
hide: true
---

lintcode

一致性hash 算法
分布式场景下

Grokking system design 和数据密集型应用系统设计这两份资料。
时间不够的话优先看 Grokking system design。重点是掌握系统设计题目的回答套路，如何一步一步地展开自己的系统设计思路以及和面试官提哪些问题来确定设计细节。一定要多和面试官沟通，多提问。

真想入门的话去买个aws solutions architect certificate的课程都比这个要靠谱...书籍的话DDIA(design data intensive application)也只是科普，真想稍微深入点的话先推荐两本书：microservices patterns、guide to reliable distributed systems

需要注意的一些点：
  Ask before design. 问清楚再动手设计，不要一上来就冲着一个巨牛的方案去设计；
  No more no less. 不要总想着设计最牛的系统，要设计够用的系统；
  Work solution first. 先设计一个基本能工作的系统，然后再逐步优化；
  Analysis is important than solution. 系统设计没有标准答案，记住答案是没用的，通过分析过程展示知识储备，权衡各种设计方式的利弊。

https://www.pramp.com/#/ 系统设计模拟面试的网站

https://www.1point3acres.com/bbs/thread-827136-1-1.html 视频

问问题的顺序：
1. 需要设计哪些功能（也可以自己想），需要承受多大的访问量？
2. 将核心功能拆分为细小的服务，并写出接口
3. 每个服务选择合适的存储结构
4. 权衡和扩展
  1）系统的优化，新功能的拓展
  2）系统的鲁棒性，如果系统奔溃了怎么办，服务请求量暴增怎么办

#### 例题
  分布式id生成器
  雪花算法：41时间戳+10为工作id+12为序列号
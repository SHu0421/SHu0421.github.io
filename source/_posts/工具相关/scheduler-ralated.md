---
layout: blog
title: scheduler_related
date: 2021-11-12 10:04:52
tags: scheduler
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---

调度需要关注的问题/或者目标：提高资源利用率，负载均衡，用户的优先级和公平性

可能是针对深度学习场景的调度，也可能是平常的请求任务

ParSync:调度器需要进行及时的同步，如果不及时进行同步那么就可能造成大量冲突；但是在同步的时候，如果一个调度器固定同步固定几个机器的话。就无法充分利用机器空闲资源；
所以这篇论文提出利用分片同步的策略，就是一个调度器通过轮训的方式，分时段和多个机器进行同步；同时给最后同步的机器更高的优先级，因为它的状态最新，最可信，因此发生冲突的可能性会更小


Gavel: 针对深度学习的异构感知的集群调度策略； 将调度转为一个优化问题



### 阿里项目

资源池化的理解：
CPU、内存、磁盘、I/O等硬件变成可以动态管理的“资源池”，从而提高资源的利用率，简化系统管理，实现服务器整合。核心思想：能够通过区分资源优先次序并随时随地能够将服务器资源分配给最需要它们的工作负载来简化管理和提高效率，从而减少为单个工作负载峰值而存储的资源。

>池化简单来讲就是使用远程访问的形式使用GPU资源，任务使用本机的CPU和另一台机器的GPU，两者通过网络进行通信。

ref:https://bbs.cvmart.net/articles/3696

深度学习场景下异构池化资源管理和任务调度研究

池化和异构集群下的资源调度有什么区别？

相关研究工作：

Demand Based Hierarchical QoS Using Storage Resource Pools

化零为整:将多台服务器上的GPU集合起来提供给一个容器或者一个虚拟机使用
隔空取物：将虚拟机或者容器运行在一台没有物理 GPU 的服务器上，通过计算机网络，透明地使用另一台服务器上的 GPU 资源。
小模型场景的典型应用：从算力和显存两个角度，对GPU资源进行切分

问题：
这个池化是GPU还是包括CPU， 存储所有资源的池化
这个GPU的池化和云服务器有什么区别
GPU池化之后，拉远，数据传输的开销如何弥补
如果做到多个应用之间互不影响的，因为虽然充分应用了GPU的显存和算力资源，但是数据传输的带宽，不会因为任务量多，而相互竞争，从而影响效率吗

通过算力和显存从切分， 不在一个GPU上算力和显存如何协作起来，完成一件事情
与k8S的区别在哪里

为什么需要劫持调用才能实现资源的隔离

这里的调度是分配好了，就固定直到任务结束，还是像gandivia一样需要动态调整
主要是针对deep learning 的训练 推理还是普遍多任务背景下的任务调度，与资源池化


之后的安排：
看一下legoos 以及一些相关论文
看一下k8s的官方文档
看一下ppt里面的一些链接
讨论一下任务



相关论文总结：
### Multi-Job：
Gandiva: 主要是针对multi-job 超参数搜索的场景下的可预测性，在训练过程中，自适应的调整job, 最大化GPU资源的利用率

### 训练推理混合调度：
AntMan : Dynamic Scaling on GPU Clusters for Deep Learning
PipeSwitch: Fast Pipelined Context Switching for Deep Learning Applications

将推理任务插入训练的时间片中，充分利用GPU的资源

### 池化相关
LegoOS: A Disseminated, Distributed OS for Hardware Resource Disaggregation
推翻常规的整体server模式，使process memory和storage通过网络来进行通讯，而不是总线，使用一个全局manager进行粗粒度的分配，然后使用一个local manager进行细粒度资源管理

rCUDA remote CUDA
rCUDA: Going Further in Remote GPU Virtualization
VMware-vSphere-Bitfusion
驱动科技的GPU拉远策略

### 异构/集群资源调度
Scaling Large Production Clusters with Partitioned Synchronization
主要是多个调度器对集群支援进行调度，同时为了保证调度维持较好的实时性，减低可能发生的资源竞争，使用时间片轮训的方式，让一个调度器对多个机器组成的组进行调度

HiveD : Sharing a GPU Cluster for Deep Learning with Guarantees
Heterogeneity-Aware Cluster Scheduling Policies for Deep Learning Workloads
Topology-aware GPU scheduling for learning workloads in cloud environments
Tiresias: A GPU cluster manager for distributed deep learning
Gandiva: Introspective cluster scheduling for deep learning


### 针对深度学习的GPU共享survey
https://bbs.cvmart.net/articles/3696

https://cloud.tencent.com/developer/article/1766184   Improving GPU Utilization in Kubernetes


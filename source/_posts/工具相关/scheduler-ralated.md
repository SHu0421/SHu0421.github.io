---
layout: 阿里调度项目相关
title: scheduler_ralated
date: 2021-11-12 10:04:52
tags: scheduler
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




### k8s学习资源
https://github.com/0voice/k8s_awesome_document
minikube和microk8s




### k8s调度器修改
自定义k8s调度器
调度器其实也是运行在node上面的一个pod
调度框架现在更加适用



感觉扩展程序和调度框架的区别在于：扩展程序修改的extend字段，而框架修改的是plugin字段

- 扩展程序：主要实现/filter 和 /prioritize 两个端点的处理程序
- 调度框架：实现自己的插件，必须向调度框架注册插件并完成配置，另外还必须实现扩展点接口，对应的扩展点接口我们可以在源码 pkg/scheduler/framework/v1alpha1/interface.go 文件中找到；
  在最新的 Kubernetes v1.17 版本中，Scheduler Framework 内置的预选和优选函数已经全部插件化，所以要扩展调度器我们应该掌握并理解调度框架这种方式。


### 在配置中可以参考的资料
如何构建自己的k8s Framework插件
- https://kubernetes.io/zh/docs/reference/scheduling/config/#multiple-profiles 官网上的配置
- Kubernetes 负责 Kube-scheduler 的小组 sig-scheduling 为了更好的管理调度相关的 Plugin，新建了项目
scheduler-plugins 来方便用户管理不同的插件，用户可以直接基于这个项目来定义自己的插件。
https://github.com/kubernetes-sigs/scheduler-plugins

- 进击的 Kubernetes 调度系统系列文章
(一) Scheduling Framework
https://www.infoq.cn/article/lYUw79lJH9bZv7HrgGH5
(二) 支持批任务的 Coscheduling/Gang scheduling
https://www.infoq.cn/article/Q1l845yOl2GAF8WIVtCW

- https://www.cncf.io/wp-content/uploads/2020/08/%E9%98%BF%E9%87%8C%E5%B7%B4%E5%B7%B4%E5%A6%82%E4%BD%95%E6%89%A9%E5%B1%95Kubernetes-%E8%B0%83%E5%BA%A6%E5%99%A8%E6%94%AF%E6%8C%81-AI-%E5%92%8C%E5%A4%A7%E6%95%B0%E6%8D%AE%E4%BD%9C%E4%B8%9A%EF%BC%9F1-xi-jiang.pdf

https://www.servicemesher.com/blog/202003-k8s-scheduling-framework/ 插件里面每个需要实现的函数包括哪些，主要还是go语言实现




### microk8s安装
遇到的问题 
1. enable网络连不上：https://blog.51cto.com/u_10272167/2711146
将脚本拷贝出来，然后修改为国内网站，然后再下载

2.helm command not found
sudo snap install helm --classic

3. adaptive dl下载的时候可能会出现问题
重试一次就好了
https://githublab.com/repository/issues/petuum/adaptdl/106

4. docker连接的时候出现permission denied：
sudo groupadd docker
sudo gpasswd -a $USER docker //添加当前用户到docker组中
sudo gpasswd -a $shu //查看是否添加成功
newgrp docker

方法二：
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker

方法三：
sudo chmod 666 /var/run/docker.sock （ok）

5. Dockerfile运行的时候 pip install 非常缓慢
加上国内源： -i https://pypi.tuna.tsinghua.edu.cn/simple

6. 
sudo usermod -aG microk8s $USER 创建microk8s用户组
sudo groupadd microk8s
sudo gpasswd -a $USER microk8s
newgrp microk8s


7. 
私有registry的创建方法：理解为让自己的服务器作为k8s docker镜像的仓库

需要先创建一个docker 私有仓库，然后使用insecure-registries:
https://yeasy.gitbook.io/docker_practice/repository/registry (私有创建方法)
然后修改
sudo vim /etc/docker/daemon.json
{ 
 
"registry-mirrors": ["https://registry.docker-cn.com"], 
 
"insecure-registries":["127.0.0.1:5000"] 
 
} 
# 重载修改过的配置文件 
sudo systemctl daemon-reload 
# 重启docker service 
sudo systemctl restart docker.service 
# 查看docker service 状态 
systemctl status docker.service 


共有registry的创建方法：理解为让dockerhub作为k8s docker镜像的仓库
https://kubernetes.io/docs/tasks/configure-pod-container/pull-image-private-registry/#create-a-secret-by-providing-credentials-on-the-command-line


8. 上传不成功，需要修改为 用户名/镜像名 的样子
export ADAPTDL_SUBMIT_REPO=index.docker.io/cindybrain/adaptdl-submit
export ADAPTDL_SUBMIT_REPO_CREDS=regcred

9.现在问题：
sudo microk8s.kubectl version 测试是否有权限
sudo microk8s.kubectl create --dry-run=client -f hello_world/adaptdljob.yaml -o json
提交语句
 adaptdl submit hello_world

 接下来遇到的问题：
 Failure (InternalError): Internal error occurred: failed calling webhook "adaptdl-validator.adaptdl.svc.cluster.local": Post https://adaptdl-validator.adaptdl.svc:443/validate?timeout=10s: dial tcp 10.152.183.186:443: connect: connection refused

https://www.qikqiak.com/post/k8s-admission-webhook/

# microk8s
官方安装教程
https://kubernetes.io/zh/blog/2019/11/26/%E4%BD%BF%E7%94%A8-microk8s-%E5%9C%A8-linux-%E4%B8%8A%E6%9C%AC%E5%9C%B0%E8%BF%90%E8%A1%8C-kubernetes/
sudo snap alias microk8s.kubectl kubectl //这样给kubectl改别名



### 学习打算
先学习k8s, 在hec06 hec07, hec08上面搞，然后再学习microk8s minik8s, minikube的方式进行kubenetes的学习



### 原生k8s平台的搭建

#### 自己在hec集群上搭建过程

1. 安装kubelet kubeadm kubectl
```bash
#!/bin/bash

sudo apt-get update && sudo apt-get install -y apt-transport-https curl
# curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add - 
# 上面那个命令要翻墙，因此先将apt-get.gpg下载下来，然后使用如下命令替换
sudo apt-key add apt-key.gpg
sudo sh -c 'echo "deb https://mirrors.aliyun.com/kubernetes/apt kubernetes-xenial main">/etc/apt/sources.list'

sudo add-apt-repository --remove  ppa:pascallj/docker.io-clone3 删除ppa
或者cd /etc/apt/sources.list.d, 然后进行删除

# E: Package 'socat'/'conntrack' has no installation candidate
# 在 https://launchpad.net/+search?field.text=conntrack+ppa&field.actions.search=Search 
# 网站上搜索 conntrack/ socat的 ppa源，然后使用命令, 添加ppa源： 
sudo add-apt-repository ppa:ionel-mc/socat
sudo add-apt-repository ppa:brightbox/experimental 

sudo apt-get update

sudo apt-get install conntrack
sudo apt-get install socat
sudo apt-get update && sudo apt-get install docker.io

# 最后再运行下面的命令就不会报错了:
sudo apt-get install -y kubelet=1.15.1-00 kubeadm=1.15.1-00 kubectl=1.15.1-00

```

2. 运行docker
docker需要在每个节点都运行起来：
sudo systemctl start docker
<!-- 没有权限的解决方案 -->
sudo chmod a+rw /var/run/docker.sock

3. 用 kubeadm 创建 Cluster
在master节点上运行：
sudo kubeadm reset
sudo kubeadm init --apiserver-advertise-address=10.5.26.67 --pod-network-cidr=10.244.0.0/16 --image-repository=registry.aliyuncs.com/google_containers --ignore-preflight-errors=all


<!-- 其他人的一个例子 -->

 <!-- sudo kubeadm reset -->
<!-- sudo kubeadm init \
--apiserver-advertise-address=10.5.26.67 \
--image-repository registry.aliyuncs.com/google_containers \
--kubernetes-version v1.13.3 \
--service-cidr=10.1.0.0/16 \
--pod-network-cidr=10.244.0.0/16 \
--ignore-preflight-errors=all
-->
如果卡住的解决方法：[kubelet-check] Initial timeout of 40s passed.

查看原因：sudo journalctl -u kubelet
tail -100f /var/log/messages|grep kub

解决方法：
修改docker cgroup:
sudo vi /etc/docker/daemon.json
{
  "exec-opts": [
        "native.cgroupdriver=systemd"
  ],
  "log-driver": "json-file",
  "log-opts": {
        "max-size": "100m"
  },
  "storage-driver": "overlay2",
  "storage-opts": [
        "overlay2.override_kernel_check=true"
  ],
  "registry-mirrors" : [
        "https://ot2k4d59.mirror.aliyuncs.com/"
  ],
  "graph": "/data/docker"
}
sudo systemctl daemon-reload
sudo systemctl restart docker //重启docker
sudo iptables -F && sudo iptables -t nat -F && sudo iptables -t mangle -F && sudo iptables -X
sudo swapoff -a
sudo systemctl restart kubelet

参考链接：
https://stackoverflow.com/questions/67606941/kubeadm-init-failing-while-initializing-a-kubernetes-cluster





4. 为master配置 kubectl
  sudo mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config
  //运行完这三句之后，sudo kubectl version就正常了


5. 其他节点加入master节点

<!-- 注意一定要保证服务器和客户端之间的kubectl版本一致
sudo apt-get install -y kubelet=1.23.6-00 kubeadm=1.23.6-00 kubectl=1.23.6-00 -->

先初始化网络：
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml

最后得到的token:
sudo kubeadm join 10.5.26.67:6443 --token 9am4ce.fnycv1gi9gx7mbch \
    --discovery-token-ca-cert-hash sha256:3368a9667447c72ab00404ce0ff9b4975e9402b1f86c9afce511d992ecfcd29e --ignore-preflight-errors=all


问题：
一直join不了的解决方法和k8s master kubeadm init不了的解决方案相同，见”修改docker cgroup“


一些误区：
节点之间不需要免密登录，也能进行kubectl的通信（kubeadm join）


6. 建立镜像的时候出现docker build pip超时，使用国内源仍然无法解决
解决方案：在docker build命令后面加上 --network="host"


7.安装kubeflow
https://zhuanlan.zhihu.com/p/368720477
安装kubeflow遇到的问题：
https://stackoverflow.com/questions/69054622/unable-to-install-crds-in-kubernetes-kind

降级kubeadm的版本：sudo apt-get install kubeadm=1.20.4-00 kubectl=1.20.4-00 kubelet=1.20.4-00 -y --allow-downgrades 允许降低版本
在降低版本之后，需要重新进行kubeadm的init和join， 否则会导致kubectl 客户端和服务器版本不一致的问题

8. coredns 一直处在containerWaiting的状态

https://58jb.com/html/k8s_v1.20_coredns_error.html
注意worker节点上面的10-canal.conflist和calico-kubeconfig删 也要删除！！！1

// 这个链接没有尝试：https://bbs.huaweicloud.com/forum/thread-60243-1-1.html


service/pytorch-operator created
deployment.apps/pytorch-operator created

查看一个运行pod的镜像: kubectl edit pod pytorch-operator-7756f57455-6xj9g -n kubeflow

9.在安装pytorch operator的时候出现镜像找不到
参考的安装目录： https://zhuanlan.zhihu.com/p/368720477
"${MANIFESTS_DIR}/pytorch-job/pytorch-operator/base/" 里面deployment.yaml的镜像为
"registry.cn-shenzhen.aliyuncs.com/shikanon/kubeflow-images-public.pytorch-operator:v1.0.0-rc.0"

主要参考的替换方法：https://developer.aliyun.com/article/741640


10. 现在创建了pytorch job但是运行不起来，create 之后找不到

https://github.com/kubeflow/pytorch-operator（明天照着这个看看）

- 执行以下命令，通过 kubectl 提交该 PyTorch Job：
kubectl create -f ./pytorch_job_mnist_nccl.yaml
- 执行以下命令，查看该 PyTorch Job：
kubectl get -o yaml pytorchjobs pytorch-dist-mnist-nccl
- 执行以下命令，查看 PyTorch 任务创建的相关 Pod：
kubectl get pods -l pytorch_job_name=pytorch-dist-mnist-nccl  



11. 现在创建local-path-storage的时候遇到错误

换了一个节点hec05,然后在每个节点按照https://bbs.huaweicloud.com/forum/thread-60243-1-1.html 运行命令就可以了
然后使用设置为default的local-path
kubectl patch storageclass local-path -p '{"metadata": {"annotations":{"storageclass.kubernetes.io/is-default-class":"true"}}}'

正确的解决的方法应该是每个节点都删除cth0, 主要命令见服务器上的run_update.sh脚本


12. 下载kubeflow的时候cert-manager出现错误
<!-- //下面这个解决方法是错误的，因为for flannel  you must pass 10.244.0.0/16!!!!1
kubectl edit cm -n kube-system kube-flannel-cfg
将10.244.0.0/16 改为 最开始kubeadm init的值--pod-network-cidr=192.168.0.0/16
也可以通过下面命令查看 kubectl get nodes -o jsonpath='{.items[*].spec.podCIDR}' to get pod CIDR -->

正确的解决的方法应该是每个节点都删除cth0, 主要命令见服务器上的run_update.sh脚本， 同时设置--pod-network-cidr=10.244.0.0/16


13. 在执行命令kfctl apply -f kfctl_k8s_istio.v1.2.0.yaml 因为需要下载许多的镜像，所以可能会导致ImageBackOff
因此至少需要100G的存储空间，同时需要借助阿里云的镜像来进行所有镜像的下载，然后再执行这个命令，主要参考下面两个链接
https://blog.csdn.net/koukouwuwu/article/details/117016360
https://blog.csdn.net/qq_46595591/article/details/107765833

https://github.com/shikanon/kubeflow-manifests#%E5%AE%89%E8%A3%85kubeflow 国内环境一键安装kubeflow1.3试试


kubectl -n kubeflow get all 查看是否安装好



14. https://www.jianshu.com/p/f4e35abe0462 通过这个安装grafana和 prometheus
(主要安装命令见服务器 install_tools.sh)

遇到的问题无法将localhost:9090添加到grafana的仪表盘
主要原因： prometheus开启的时候自环网络，curl localhost:9090成功；但是curl 10.5.26.66:9090 失败；所以用
ssh -L 9090:127.0.0.1:9090 shu@10.5.26.66 -o ProxyCommand="ssh shu@10.5.26.19 -W %h:%p" 建立隧道也失败
解决方案：
1. 需要在你的prometheus.yml 文件 中监控的localhost 改为你的IP
2. grafana改用brower模式，填入htpp://localhost:30090 （也就是prometheus的浏览器地址）


#### 参考链接
[其他人搭建的过程，可借鉴](https://github.com/wenbin8/doc/blob/master/%E5%88%86%E5%B8%83%E5%BC%8F/CloudNative/Kubernetes/01-Kubernetes%E9%9B%86%E7%BE%A4%E6%90%AD%E5%BB%BA.md)





### 一些辅助功能
#### 查看日志
看系统日志

cat /var/log/messages


用kubectl 查看日志
<!-- 注意：使用Kubelet describe 查看日志，一定要带上 命名空间，否则会报如下错误[root@node2 ~]# kubectl describe pod coredns-6c65fc5cbb-8ntpvError from server (NotFound): pods "coredns-6c65fc5cbb-8ntpv" not found -->

kubectl describe pod kubernetes-dashboard-849cd79b75-s2snt --namespace kube-system

kubectl logs -f pods/monitoring-influxdb-fc8f8d5cd-dbs7d -n kube-system

kubectl logs --tail 200 -f kube-apiserver -n kube-system |more

kubectl logs --tail 200 -f podname -n jenkins



用journalctl查看日志非常管用

journalctl -u kube-scheduler

journalctl -xefu kubelet  -n 10（主要是这个）

journalctl -u kube-apiserver


journalctl -u kubelet |tail

journalctl -xe


用docker查看日志

docker logs c36c56e4cfa3  (容器id)





### 现有的调度算法总结
1. 使用类似gpu-share的方法，将任务按照memory-request进行gpu-memory的分配，使用最少适配方法
2. 建立规则进行调度。将workload特征 进行感知分类后进行资源的调度，比如延迟敏感性感知（决定任务优先级）、CPU敏感性感知（CPU处理更多还是GPU处理更多）、拓扑逻辑敏感性感知
3. 建立模型自动进行资源调度。


### github资源汇总

目标找到：主要针对推理任务+ 提高 GPU资源利用率（最好是使用GPU资源共享的）相关的论文
问题: 池化和GPU共享(使用GPU共享的调度 gpushare)最主要的区别在哪？在于能够将一个任务分配到不同GPU上么


1. gpushare-scheduler-extender
[code](https://github.com/AliyunContainerService/gpushare-scheduler-extender)
基于的假设:cuda核的数量和GPU内存是成正比的，因此在进行调度的时候查看一个任务需要的GPU内存需求，使用最佳适配原则（选择大于任务需求内存中同时最小的一个设备）来进行任务的调度。主要针对推理场景，而且不会保证任务共享资源的隔离


2.  针对资源的负载均衡的调度算法
[code](https://github.com/adolphlwq/liang)
提出两种算法：针对NetWork资源均衡 （BN算法）+ CPU, Memory, disk IO and network IO均衡的（CMDN算法），使用k8s extender实现代码
[论文解析博客](https://developpaper.com/how-to-customize-kubernetes-scheduling-algorithm/)（可能是毕设论文或者个人实现项目，因为没有相关文献找到）


3.  微软的针对深度学习的调度器
[论文解析博客](https://anonymity1.github.io/2021/04/06/osdi2020-HiveD/)
[code](https://github.com/microsoft/hivedscheduler)
[论文](https://www.usenix.org/conference/osdi20/presentation/zhao-hanyu)
[论文作者概述](https://cs.fudan.edu.cn/1b/d5/c24259a269269/page.htm)
主要是针对深度学习训练场景 对 1. 拓扑逻辑感知的资源保障 和 2. gang-scheduling 3. 任务的优先级 三方面 进行了优化，
idea 1. 将资源进行分层，实现细粒度资源调度：5GPU（最小cell是一个GPU，第一层） -> PCIe switch -> CPU socket -> node -> Rack（第5层）
使用伙伴算法，如果没有找到第k层可用资源，就将第k+1层拆分为第k层。尽可能保持粗粒度的资源没有被占用。
idea 2. 使用低优先级任务充分利用GPU资源，如果高优先级任务未找到可用资源的时候，可以抢占低优先级任务的资源

异同：
这篇论文拆分最小粒度还是1GPU，并没有考虑到拆分GPU情况（GPU-share），虽然减少了资源碎片问题，但是单个GPU的碎片并没有解决
池化场景应该GPU粒度可以更细的拆分，同时还要考虑到异构，以及提高单个GPU资源利用率（GPU-share场景）,以及可能存在的隔离问题

现在推理的时候会考虑分布式吗？还是主要关注资源的共享和隔离 方面的调度
总结一下算法！！！！


4. Firmament Fast, centralized cluster scheduling at scale
OSDI16 - 在k8s上进行修改的调度器， 使用图的最小流算法来确定调度的方案（Min-cost flow scheduler / min-cost max-flow (MCMF) optimization.）主要解决的是 高质量的放置策略通常会带来较高的放置延迟 问题
背景是一个任务被调度到不同的机器，会导致不同的cost（调度时延等）, 如何求一个最好的调度方案能够使得最后的cost最小
[code](https://github.com/coreos/ksched)
没有非常仔细的看

5.  一个根据GPU指标来进行调度的调度器
[code](https://github.com/Mr-Linus/Yoda-Scheduler)
就是找到GPU mem/clock/数量 符合条件的设备（过滤）， 然后根据每个设备的带宽，时钟，核， 空闲的内存，总内存等值来求三个分数（打分）
CalculateBasicScore(data.Value, s, pod) + CalculateAllocateScore(info, s) + CalculateActualScore(s) 最后得到candidate 设备的总分数，为什么这么计算，没有说

6. 现有的k8s 框架提供的一系列有关调度规则的插件
[code](https://github.com/kubernetes-sigs/scheduler-plugins)
- Capacity scheduling： 弹性的资源分配策略。定义每个任务的时候定义min, max资源，max该任务可以利用的最大资源 min表示为了保证整个任务运行的最少资源，在分配的时候只需要保证每个任务的min 加起来不超过节点GPU要求，
但是在实际运行的时候，每个任务可以暂时借用其他任务没用的资源，错时能够达到任务的最大资源，相比最开始就分配给每个任务最大资源提高了资源的利用率
- Coscheduling：多个任务要么同时启动要么都不启动的这种情况，现有的k8s可能会导致部分这样任务得到调度，部分没有，从而得到调度的任务一直等待状态，造成资源的浪费。这个插件就能通过将这些任务定义为同一个PodGroup使这样的任务具有相同优先级，在队列中排在一起，同时使用延迟绑定的方法，如果再出现上述情况，此时与Default Scheduler不同的是，并不是直接将3个Pod调度并创建。而是通过Framework的Permit机制进行等待。
- NodeResourcesLeastAllocatable： 就是在调度的时候选择满足要求，剩余资源最少/最接近的资源进行调度，这样更多的资源就被保留给需求更大的任务调度
（NodeResourcesLeastAllocated：选择满足要求，已分配资源最少的节点）
- Topology Aware Scheduling：在进行资源选择的时候会将NUMA拓扑逻辑结构作为输入信息考虑
- Preemption Toleration: 通过定义PriorityClass使得任务之间可以实现抢占，相比于默认的k8s提供的抢占功能，多了条件抢占/low-non-preempted priority class等功能
- Trimaran: Load-aware scheduling plugins： 设定资源利用率为x%,那么在进行选择的时候就选择调度方案使得集群每个节点利用率都接近x%。
包括下面两个插件
      - TargetLoadPacking 插件：它是 bin pack 算法的最佳变体，它根据节点的实际资源利用率对节点进行评分，所有使用的节点都有大约 x% 的利用率。一旦所有节点达到 x% 利用率，它就会移动到最不适合的变体。
      - LoadVariationRiskBalancing Plugin：它是一个节点排序插件，根据节点资源利用率的均值和标准差对节点进行排序。它的目的不仅在于平衡平均负载，还在于平衡负载变化引起的风险。


7. 现在k8s拥有的高级调度策略
针对不同QoS的任务，执行不同的调度策略。在进行share的时候，尽可能选择best-effort的任务进行抢占和共享， 针对Garantee任务，尽可能分配空闲的机器，而不是共享的机器
[链接](https://www.alibabacloud.com/blog/getting-started-with-kubernetes-%7C-scheduling-and-resource-management_596298) （没看完，继续看）
针对单个用户/命名空间 分配的资源量不能超过一个阈值
the total submission amount of a business or a user must be limited so that all the resources of the entire cluster cannot be occupied by one business or user.
现有share的是 不同QoS任务 时间片的共享，我们是否可以利用这个规则+CPU敏感/GPU敏感任务/共享敏感  指定GPU内存共享的规则 （任务分类处理思想好像比较老）

8. 一个batch的同步变为了众多小数据（minibatch）上的异步，计算完一个minibatch就立刻反向，一个minibatch的反向结束之后就更新对应worker的梯度
没有代码，但是是建立了一个模型来进行GPU利用率的预测

9. 也是有关于GPU共享的-应该是腾讯的vCuda项目
[调度器code](https://github.com/tkestack/gpu-admission)
[manager_code](https://github.com/tkestack/gpu-manager)
（also supports the payload with fraction resource of GPU device such as 0.1 card or 100MiB gpu device memory.）
[相关论文](https://ieeexplore.ieee.org/abstract/document/8672318) 
[部署/使用文档](https://blog.csdn.net/o0haidee0o/article/details/119407372) 

调度器实现的两个目标:
provides quota limitation according to GPU device type
avoids fragment allocation of node by working with gpu-manager
(感觉类似gpu-share找到满足条件且提供最小资源的node， 同时gpu-manager能够实现将多个任务放在一个节点上，感觉是从算力角度
对GPU资源进行划分，因为可以将GPU分成几分之几的GPU)


### 总结
使用微软（训练） gpu-share gpu-admission antman(无代码) 进行对比

[论文及代码仓库汇总](https://github.com/HuaizhengZhang/Awesome-System-for-Machine-Learning/blob/master/training.md)

[阿里云针对k8s现有算法的介绍](https://www.alibabacloud.com/blog/getting-started-with-kubernetes-%7C-scheduling-and-resource-management_596298)


### 问题
CPU资源是和GPU资源绑定分配还是一起分配
池化和GPU共享(使用GPU共享的调度 gpushare)最主要的区别在哪？在于能够将一个任务分配到不同GPU上么

论文的话一般是从策略角度，如果要具体算法的话，可能需要看repo 源码，但是现有的开源论文并不多






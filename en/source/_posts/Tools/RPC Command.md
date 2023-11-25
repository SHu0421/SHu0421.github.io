---
title: RPC Command
tags: rpc
categories:
  - Tools
date: 2023-07-24 16:40:54
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---



### 1. Compare of gRPC and Default RPC in Pytorch

###### gRPC can guarantee communication between different languages

Simple Steps to use gRPC:

1. Write a .proto file to generate the source code of the specified language.
2. Write server code
3. write client code
   [An example of python client and go server](https://www.liwenzhou.com/posts/Go/gRPC/)



###### RPC in pytorch

Methods provided in RPC in pytorch:
	- rpc_sync synchronous remote call: ```rpc.rpc_sync```
	- rpc_async asynchronous remote call: ``rpc.rpc_async``
	- remote asynchronous remote call: ```rpc.remote```

Simple Steps to use default RPC in Pytorch:

1. initializes rpc by ```rpc.init_rpc ```, which needs to be initialized on both master and worker to facilitate subsequent communication
2. The worker side invokes ```rpc.rpc_sync```  executed on the master


### 2. use gRPC 

[Examples of using gRPC in python or go](https://grpc.io/docs/languages/python/quickstart/)




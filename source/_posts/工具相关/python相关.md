---
layout: python相关
title: python相关
date: 2021-11-11 19:06:48
tags: python
index_img: https://img.xjh.me/random_img.php?type=bg&ctype=nature&return=302
---


#### Python语言部分
1. python 开启debug模式，使用logger.setLevel 以及在logger的时候设置不同的logger.info  logger.error  logger.warning等

``` python
import logging
import requests
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='myapp.log',
                    filemode='w')
 
logging.debug(session.get('http://www.qq.com'))
logging.debug(session.get('http://www.qq.com'))

```


tuple和list的区别

tuple和list都可以通过下标访问元素，但是list是可以修改列表中的元素， 但是tuple一旦初始化就不能修改，不能append和insert


#### PyTorch 部分

1. 在如果在模型训练的时候，一部分卷积使用的是dataparallel一部分使用的是直接cuda (比如alexnet) 这种情况在模型参数的加载的时候，需要修改keys中包含 module.的部分（dataparallel 部分）

方法一:
修改保存或者加载时的字典
```
from collections import OrderedDict
new_state_dict = OrderedDict()
for k, v in state_dict.items():
    namekey = k[7:] if k.startswith('module.') else k
    new_state_dict[namekey] = v
```

方法二：
```
uni_model.load_state_dict({k.replace('module.','') :v for k,v in model_queue.get(block=False).items() })
```


2. DatasetFolder类的解读
数据类别，是通过遍历目标文件夹，得到每个文件夹的名字，以及名字对应的下标
make_data返回的是 数据的路径+类别下标 序列元组 List of (sample path, class_index) tuples 得到self.samples
然后再在get_item函数中使用path = self.samples[index] self.loader(path) 获得图片实例


那么我自定义的缓存，既可以在MyDataSet里面的DataSet_ImageNet里面修改，判断是应该从缓存中取还是从文件系统；
也可以修改ImageFolder, 里面加一个缓存， 在self.loader那里加上if-else判断语句

但是多进程会初始化多个dataset, 这样每个进程都会有一个cache， 我的目的应该是只有一个cache, 然后多进程从里面都可以从这个cache中取数据；而且多进程如果每一轮的dataset的实例被销毁的话会导致
cache也会被销毁


3. DatasetLoader类的解读
问题：
worker_init_fn， prefetch_factor 和persistent_workers（保持被实例化的Dataset在下一轮仍然保持alive） 的作用是什么
warning中表示如果spwarn start method被使用， 那么worker_init_fn 不能是一个unpicklable object

_MultiProcessingDataLoaderIter 可以学习一下多进程的退出
使用了三个队列 index_queue worker_result_queue data_queue

workers_done_event 检测一个迭代器是否shut down, 如果一个迭代器进行shutdown，那么那个进程的input_queue里面的数据只需要为None就好了， 就不用一直等待那个queue里面的数据

为什么要使用 cancel_join_thread()  index_queue.cancel_join_thread()

记录：
多进程每个进程都可以创建多个dataset实例(这个好像是错的), 是否在主函数中初始化一个cacheout类，然后作为dataset的参数传过去，这样多进程也是使用的一个cache
主要的逻辑

```python
for i in range(self._num_workers):
            # No certainty which module multiprocessing_context is
            index_queue = multiprocessing_context.Queue()  # type: ignore
            # Need to `cancel_join_thread` here!
            # See sections (2) and (3b) above.
            index_queue.cancel_join_thread()
            w = multiprocessing_context.Process(
                target=_utils.worker._worker_loop,
                args=(self._dataset_kind, self._dataset, index_queue,
                      self._worker_result_queue, self._workers_done_event,
                      self._auto_collation, self._collate_fn, self._drop_last,
                      self._base_seed + i, self._worker_init_fn, i, self._num_workers,
                      self._persistent_workers))
```
只有一个worker_result_queue, 以及多个result_queue; 如果pin_memory=True, 那么会将worker_result_queue里面的数据，全部放在另外一个_data_queue中

#### pyTorch取数据过程详解（面试版本）
1. 初始化的时候，每个进程都会拥有自己的index_queue,里面最多存储两个batch 的index
2. 每个worker会不断判断自己的index_queue里面有没有数据，如果有，那么就取读一个batch, 读取的时候调用collate_fn函数，读取之后放入多进程共享的data_queue / worker_result_queue 里面
3. data_queue里面的数据会先放入reorder字典中进行重新排序，如果需要的下一个batch在reorder_dict里面，那么就从reorder_dict中弹出这个数据，否则就等待
4. 某个worker读取的数据被消耗之后，dataloader就会将新的index放到对应worker的index_queue里面，这个worker就继续从queue里面读下标和取数据
参考：
https://www.dazhuanlan.com/yiliabi/topics/1111356


4. 代码常见标记
TODO：英语翻译为待办事项，备忘录。如果代码中有该标识，说明在标识处有功能代码待编写，待实现的功能在说明中会简略说明。

FIXME：可以拆成短语，fix me ，意为修理我。如果代码中有该标识，说明标识处代码需要修正，甚至代码是错误的，不能工作，需要修复，如何修正会在说明中简略说明。

XXX：如果代码中有该标识，说明标识处代码虽然实现了功能，但是实现的方法有待商榷，希望将来能改进，要改进的地方会在说明中简略说明。

HACK：英语翻译为砍。如果代码中有该标识，说明标识处代码我们需要根据自己的需求去调整程序代码。


5. pytorch安装各种版本链接：
https://pytorch.org/get-started/previous-versions/

6. pytorch 多进程数据加载流程


7. iterator和next函数的关系
生成器都是iterator对象
可以被next函数调用的都是一个iterator对象，Iterator的计算是惰性的，只有在需要返回下一个数据时它才会计算。直到没有数据时抛出StopIteration错误。
list/dict/str这些是iterable但是不是iterator

Python的for循环本质上就是通过不断调用next()函数实现的，首先需要将list作为参数，传入iter函数中，获得一个iterator对象，然后才能调用next函数

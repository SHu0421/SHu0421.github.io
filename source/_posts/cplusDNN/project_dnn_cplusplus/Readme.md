---
categories:
  - cplusDNN
  - project_dnn_cplusplus
---
## Repo 主要是用c++实现的CNN的小项目

### 1. 已经完成的功能
- 用C++实现了CNN的卷积， BN, ReLU层，实现了BN和ReLU的反向传播（还没有调试）
- 实现了conv-bn-relu的融合
- 运行方式：在main文件的路径下执行:
```bash
make clean && make && ./main
```


### 2. TODO List:
- conv类的反向传播，以及BN, Relu类反向传播的测试
- 实现全连接层和损失函数
- 用一个实际的train/inference 例子判断计算出来的结果是否相同
- 使用 OpenMP, TBB 来进行多线程的加速运算
- 分析计算效率（真实计算FLOPS/理论FLOPS）


backward函数的实现：
// https://zhuanlan.zhihu.com/p/61898234
// loss关于y的导数（上一层的x的导数）：原图的delta误差，等于卷积结果的delta误差经过零填充后，与卷积核旋转180度后的卷积
// 卷积中w的导数，二维卷积核的导数等于原图对应通道与卷积结果对应通道的delta误差直接进行卷积。
// b的导数(列向量)：在反向传播时，它的导数等于卷积结果的delta误差在每一个通道上将所有delta误差进行求和的结果。

### 3. 文件功能介绍：
- base_layer.cpp base_layer.h: 主要包含matrix以及base_layer的定义
    其中matrix 封装一个4维矩阵（4维vector实现），可以传入[batch_size, channel_size, m_size, m_size], 返回用0，或者随机0-1的元素初始化(rand_flag=true)的4维矩阵； base_layer作为其他具体某层的父类，每个具体的类都应该实现类的前传和反传函数
- conv_layer.cpp conv_layer.h: 主要实现了Convolution类
- bn_layer.cpp bn_layer.h: 主要实现了BatchNormalization类
- relu_layer.cpp relu_layer.h: 主要实现了ReLU类


### 4. 有时间再优化
目前版本使用C++进行卷积的实现，用的4维vector, 为了加速内存的读取效率，可以转化为二维矩阵的运算，使用img2col 以及gemm来进行实现
可以参考的文献：
- https://zhuanlan.zhihu.com/p/90301095

- http://giantpandacv.com/academic/%E7%9B%AE%E6%A0%87%E6%A3%80%E6%B5%8B%E5%8F%8A%E8%B7%9F%E8%B8%AA/Darknet/%E5%9F%BA%E4%BA%8ECS231N%E5%92%8CDarknet%E8%A7%A3%E6%9E%90BatchNorm%E5%B1%82%E7%9A%84%E5%89%8D%E5%90%91%E5%92%8C%E5%8F%8D%E5%90%91%E4%BC%A0%E6%92%AD/

其他参考文献：
- https://sc18.supercomputing.org/proceedings/tech_poster/poster_files/post155s2-file2.pdf
- https://computing.llnl.gov/tutorials/openMP/
- Darknet的C实现: https://github.com/pjreddie/darknet.git




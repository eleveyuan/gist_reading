## word2vec

word2vec源码，使用c语言实现，不同于那些pytorch/tensorflow实现一个神经网络的出发点。
* word2vec更加注重的是实现，尽可能<优化>，使用求导完的推导公式进行计算
* 使用框架实现神经网络，更加注重的是<架构>，更加上层

**详细注释见文件word2vec.c**

### 核心函数

* void InitNet(): 初始化网络，也即权重矩阵
* void InitUnigramTable(): 初始化负采样表
* void CreateBinaryTree(): 构建霍夫曼树，实际使用的类似堆排序的方式，生成了三个辅助数组
* void *TrainModelThread(void *id): 训练


构建霍夫曼树：

使用一个循环构建，可以看看堆排序
``` c
  for (a = 0; a < vocab_size - 1; a++) {
    // First, find two smallest nodes 'min1, min2'
    if (pos1 >= 0) {
      if (count[pos1] < count[pos2]) {
        min1i = pos1;
        pos1--;
      } else {
        min1i = pos2;
        pos2++;
      }
    } else {
      min1i = pos2;
      pos2++;
    }
    if (pos1 >= 0) {
      if (count[pos1] < count[pos2]) {
        min2i = pos1;
        pos1--;
      } else {
        min2i = pos2;
        pos2++;
      }
    } else {
      min2i = pos2;
      pos2++;
    }
    count[vocab_size + a] = count[min1i] + count[min2i];
    parent_node[min1i] = vocab_size + a;
    parent_node[min2i] = vocab_size + a;
    binary[min2i] = 1;  //右边节点为1，左节点为0
  }
```

对窗口的单词，进行summation：
1. a < window * 2 + 1 - b
2. c = sentence_position - window + a;
这两个trick，来获取中心词旁边的上下文词。
``` c
for (a = b; a < window * 2 + 1 - b; a++) if (a != window) {
    // 把一个窗口中的单词全部上下文，计算出隐藏向量
    c = sentence_position - window + a;
    if (c < 0) continue;
    if (c >= sentence_length) continue;
    last_word = sen[c];
    if (last_word == -1) continue;
    for (c = 0; c < layer1_size; c++) neu1[c] += syn0[c + last_word * layer1_size]; // 把last_word索引的行数据加到neu1
    cw++; // cw: context word统计上下文单词数量
}
```

### 全局参数
阅读word2vec首先得把全局参数搞清楚:

\<\s\>: 表示句首 <br />
vocab_word: 一个单词包含的信息的结构体， 主要包括：单词，词频，霍夫曼编码 <br />
alpha: 学习率 <br />
train_words: 语料中训练用到的所有词 <br />
vocab: 单词表 <br />
vocab_hahs: 单词hash表，用于快速查找单词在vocab中的索引 <br />
expTable: 预计算的激活函数值表，即sigmoid在定义域(-6,6)的函数值 <br />
sample: 用于下采样 <br />
table_size: 负采样单词索引表大小 <br />

neu1：input vector <br />
neu1e：反向更新时，预测与实际值(cbow为中心词，skip-gram为上下文词)的error <br />
syn0：输入到隐藏层权重矩阵 <br />
syn1：隐藏层到输出层权重矩阵 <br />
syn1neg： <br />

### 助手函数

#### 词典表相关
* void LearnVocabFromTrainFile(): 构建词典表
* void SaveVocab(): 保存词典表
* void ReadVocab(): 读取词典表
* int AddWordToVocab(char *word): 往单词表添加单词


## 一些c函数

### 内存分配
[动态内存分配：malloc与calloc](https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/)

malloc：
1. 返回的是void*指针(void*可以被转换为任意类型的指针)
2. 接受一个参数，用于分配一块需要大小的内存

``` c
// 分配一个长度为5的int数组
ptr = (int*)malloc(5 * sizeof(int));
```

calloc:
1. 是分配连续内存
2. 接受两个参数, (元素个数，元素大小)
3. 会将分配的内存初始化为0值

``` c
// 在内存中为25个元素分配连续空间，每个元素的大小为浮点数。
ptr = (float*) calloc(25, sizeof(float));
```

### 多线程
c语言标准本身不支持多线程，可以通过引入pthread.h获得支持POSIX Threads

使用pthread.h
1. 声明一个pthread_t类型(实际为一个整型)变量，用于标识线程，相当于线程的id
2. pthread_create()函数用于创建线程，接受四个参数 <br />
    a) 第一个参数指向*线程的id*  <br /> 
    b) 表明属性, 使用NULL，则默认属性 <br />
    c) 指明创建的线程运行那个函数 <br />
    d) 传递给运行函数的参数 <br />
3. 在编译代码是需要带上-lpthread 来链接pthreads库

``` c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}
   
int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}
```
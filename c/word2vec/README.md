## word2vec

### 核心函数
* void InitNet(): 初始化网络
* void InitUnigramTable(): 初始化负采样表
* void CreateBinaryTree(): 构建霍夫曼树，实际使用的类似堆排序的方式，生成了三个辅助数组

### 全局参数
阅读word2vec首先得把全局参数搞清楚

\<\s\>: 表示句首
vocab_word: 一个单词包含的信息的结构体， 主要包括：单词，词频，霍夫曼编码
alpha: 学习率
train_words: 语料中训练用到的所有词
vocab: 单词表
vocab_hahs: 单词hash表，用于快速查找单词在vocab中的索引
expTable: 预计算的激活函数值表，即sigmoid在定义域(-6,6)的函数值
sample: 用于下采样
table_size: 负采样单词索引表大小

syn0: 
syn1: 
syn1neg: 

### 助手函数

#### 词典表相关
* void LearnVocabFromTrainFile(): 构建词典表
* void SaveVocab(): 保存词典表
* void ReadVocab(): 读取词典表
* int AddWordToVocab(char *word): 往单词表


## 头文件以及全局变量


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
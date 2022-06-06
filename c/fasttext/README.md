## fasttext
主要阅读的是v0.1.0版本

fasttext主要的有点是，运行速度快，且解决了word2vec中的oov问题。原理方面就读论文而言，创新在于对character-level ngrams进行summation来的得到最终的word embedding。其余都是继承自word2vec。
此外fasttext还可以通过**有监督任务**来获取word embedding。

对于这份代码主要学习的是：

监督模型：
1. 因为fasttext还可以进行分类任务的运行，主要想学习如何对一个句子进行分类出多个标签
2. fasttext中有一个参数wordNgrams，也是在分类中使用

非监督模型：
1. 对于word2vec中的hash算法是进行线性探测解决hash冲突，fasttext则不同于

其他(todo):
1. 模型压缩

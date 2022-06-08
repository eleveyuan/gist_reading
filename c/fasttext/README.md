## fasttext

### 有监督模型

原始语料：i like here

输入参数：

minn = 3,
maxn = 6,
wordNgrams = 2

标签：label1, label2, label3

```
train_x: <i>, <li, <lik, <like, <like>, lik, like, like>, ike, ike>, ke>, <he, <her, <here, <here>, her, here, here>, ere, ere>, re>, i like, like here
train_y: a random label
```

fasttext对一个句子打多个标签，在训练时只进行一次多分类，简单一点就是最后一层softmax获得最大概率。在验证时，通过**堆排序**获取最大的K个标签作为结果。

此外需要注意character ngrams(这里有预先切割的)和wordNgrams(这是在训练时切割)会hash到同一个值，没有解决hash冲突。

### 无监督模型

无监督模型则和word2vec训练是一样的，只是加入了ngrams，但是没有用到wordNgrams。

1. 获取word embedding，切割word进行summation然后除以ngrams长度。
2. 获取sentence/text embedding, 获取word embedding，加和每个归一化(这里归一化就是除以向量的长度)的word embedding最后在除以文本长度。
3. 获取word的nn邻居，预先计算出一个包含字典中所有word的矩阵，然后与去最相似(计算方式：a*b/|a|)的k个词
4. 词的推理任务(a-b + c)
5. ngrams再推理中的作用：https://fasttext.cc/docs/en/unsupervised-tutorial.html#importance-of-character-n-grams


## simple skip-gram

url links: https://www.geeksforgeeks.org/implement-your-own-word2vecskip-gram-model-in-python/

Rong X. word2vec parameter learning explained[J]. arXiv preprint arXiv:1411.2738, 2014.

现有的很多代码都是在优化基础上，没有最简单的架构的代码，个人疑惑的点也是在Rong X. 的论文中，对于隐藏层到输出层这里skip-gram模型是共享权重矩阵的，如果共享又如何输出预测词呢？


skip-gram是通过中心词预测上下文词的一个模型。就是一个CBOW模型的反转，具体如何反转的形式？

隐藏层到输出层是共享权重矩阵的，skip-gram又要预测多个词，这怎么做到共享矩阵呢？可以看到在构建数据集的时候，x为one-hot向量，y为ones-hot向量(个人造的词，如有雷同，纯属趣味相投)。也即隐藏层到输出层，得到的向量做softmax损失，相应的更新y对应为1的索引。

``` python 
for sentence in sentences:
    for i in range(len(sentence)):  # 构建训练数据
        center_word = [0 for x in range(V)]  # 中心词
        center_word[vocab[sentence[i]]] = 1
        context = [0 for x in range(V)]  # 上下文词
        
        for j in range(i-w2v.window_size,i+w2v.window_size):
            # 对窗口内单词中构建ones-hot vector，也即向量中存在多个索引位置为1
            # 对于当前代码会输出类似向量[1, 1, 0, 1, 0, 0]
            # 这也即对应一个单词预测多个上下文单词的情况，也就可以做到共享权重矩阵
            if i!=j and j>=0 and j<len(sentence):
                context[vocab[sentence[j]]] += 1
        w2v.X_train.append(center_word)
        w2v.y_train.append(context)
```
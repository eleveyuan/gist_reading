## fasttext
主要阅读的是v0.1.0版本

fasttext主要的有点是，运行速度快，且解决了word2vec中的oov问题。原理方面就读论文而言，创新在于对character-level ngrams进行summation来的得到最终的word embedding。其余都是继承自word2vec。
此外fasttext还可以通过**有监督任务**来获取word embedding。
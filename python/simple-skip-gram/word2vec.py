import numpy as np
import string
from nltk.corpus import stopwords

def softmax(x):
    """Compute softmax values for each sets of scores in x."""
    # 在应用 softmax 的时候，常见的问题是数值稳定性问题，也就是说，由于可能出现的指数和溢出误差，
    # ∑j e^(z_j) 可能会变得非常大。这个溢出误差可以通过用数组的每个值减去其最大值来解决。
    # https://stackoverflow.com/questions/34968722/how-to-implement-the-softmax-function-in-python
    e_x = np.exp(x - np.max(x))
    return e_x / e_x.sum()

class word2vec(object):
    def __init__(self):
        self.N = 10  # 词嵌入维度
        self.X_train = []
        self.y_train = []
        self.window_size = 2  # 圈词的窗口
        self.alpha = 0.001  # 学习率
        self.words = []
        self.word_index = {}

    def initialize(self,V,data):
        self.V = V
        self.W = np.random.uniform(-0.8, 0.8, (self.V, self.N))  # 输入-隐藏层权重矩阵
        self.W1 = np.random.uniform(-0.8, 0.8, (self.N, self.V))  # 隐藏-输出层权重矩阵
        
        self.words = data
        for i in range(len(data)):
            self.word_index[data[i]] = i

    
    def feed_forward(self,X):
        self.h = np.dot(self.W.T,X).reshape(self.N,1)
        self.u = np.dot(self.W1.T,self.h)
        #print(self.u)
        self.y = softmax(self.u)
        return self.y
        
    def backpropagate(self,x,t):
        e = self.y - np.asarray(t).reshape(self.V,1)
        # e.shape is V x 1
        dLdW1 = np.dot(self.h,e.T)
        X = np.array(x).reshape(self.V,1)
        dLdW = np.dot(X, np.dot(self.W1,e).T)
        self.W1 = self.W1 - self.alpha*dLdW1
        self.W = self.W - self.alpha*dLdW
        
    def train(self,epochs):
        for x in range(1,epochs):	
            self.loss = 0
            for j in range(len(self.X_train)):
                self.feed_forward(self.X_train[j])
                self.backpropagate(self.X_train[j],self.y_train[j])
                C = 0
                for m in range(self.V):
                    if(self.y_train[j][m]):
                        self.loss += -1*self.u[m][0]
                        C += 1
                self.loss += C*np.log(np.sum(np.exp(self.u)))
            print("epoch ",x, " loss = ",self.loss)
            self.alpha *= 1/( (1+self.alpha*x) )
            
    def predict(self,word,number_of_predictions):
        # 预测上下文词
        if word in self.words:
            index = self.word_index[word]
            X = [0 for i in range(self.V)]
            X[index] = 1
            prediction = self.feed_forward(X)
            output = {}
            for i in range(self.V):
                output[prediction[i][0]] = i
            
            top_context_words = []
            for k in sorted(output,reverse=True):
                top_context_words.append(self.words[output[k]])
                if(len(top_context_words)>=number_of_predictions):
                    break
    
            return top_context_words
        else:
            print("Word not found in dictionary")


def preprocessing(corpus):
    stop_words = set(stopwords.words('english')) 
    training_data = []
    sentences = corpus.split(".")  # 划分句子
    for i in range(len(sentences)):
        sentences[i] = sentences[i].strip()
        sentence = sentences[i].split()
        x = [word.strip(string.punctuation) for word in sentence
                                    if word not in stop_words]  # 去停词
        x = [word.lower() for word in x]
        training_data.append(x)
    return training_data
    

def prepare_data_for_training(sentences,w2v):
    # 处理数据
    data = {}
    for sentence in sentences:  # 统计数据出现频率
        for word in sentence:
            if word not in data:
                data[word] = 1
            else:
                data[word] += 1
    V = len(data)
    data = sorted(list(data.keys()))
    vocab = {}
    for i in range(len(data)):
        vocab[data[i]] = i  # 构建词典索引，个人认为可以使用enumerate构建更加pythonic
    
    #for i in range(len(words)):
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
    w2v.initialize(V,data)

    return w2v.X_train,w2v.y_train


corpus = ""
corpus += "The earth revolves around the sun. The moon revolves around the earth"
epochs = 1000

training_data = preprocessing(corpus)
w2v = word2vec()

prepare_data_for_training(training_data,w2v)
w2v.train(epochs)

print(w2v.predict("around",3))

## pipdeptree

url: https://github.com/naiquevin/pipdeptree

install: pip install pipdeptree

几百行的代码，即可帮你展示pip下载的包以及依赖，形成一个tree结构

可以dump出以下内容：
1. json
2. graphviz


## 本地运行代码

直接copy包的pipdeptree.py文件，即可运行

``` python3
python pipdeptree.py [参数]
```

## 阅读

### 抽象类：
1. 抽象类Package(DistPackage，ReqPackage继承)

### 基础信息类：
1. 安装的包会被封装到DistPackage类
2. 安装的包会被封装到ReqPackage类中：多一个required_version属性，即依赖包需要的版本

### 有向无环图类：
1. PackageDAG(继承自collections.abc.Mapping)：可以看做是邻接链表
2. ReversedPackageDAG(继承PackageDAG)：可以看做是逆邻接链表

个人用python实现过邻接链表、逆邻接链表：直接使用collection.defaultdit(list)存储即可，逆邻接表直接对邻接表取出key值，循环list即可获得。


## 助手函数
用来dump依赖信息


## 遇到的写法

``` python 
# 调用PackageDAG的classmethod，返回其实例(第一眼想到了单例模式，只有一个实例)
# 有人喜欢__init__函数初始化属性时(也即实例化对象)，调用一个函数，把实例化对象引入进来
# 相关讨论: https://stackoverflow.com/questions/2714573/instance-variables-vs-class-variables-in-python
# 谈到单例模式的实现，使用classmethod不是线程安全的(没有验证：https://www.cnblogs.com/huchong/p/8244279.html)
tree = PackageDAG.from_pkgs(pkgs)
```
这里实例化PackageDAG对象，用的classmethod方法进行实例化。有点类似单例模式，具体总结可以看上面的注释


``` python 
# https://stackoverflow.com/questions/20599375/what-is-the-purpose-of-checking-self-class
# https://stackoverflow.com/questions/1060499/difference-between-typeobj-and-obj-class/10633356#10633356
# type与__class__区别：https://stackoverflow.com/questions/1060499/difference-between-typeobj-and-obj-class/10633356#10633356
# 需要注意__class__可以被override，也即他是类的属性，有被修改的风险
# 注意以下连接，使用super调用静态方法需要：super(type1, type2).func()
# https://stackoverflow.com/questions/45498675/why-doesnt-super-work-with-static-methods-other-than-new
return self.__class__.frozen_repr(self._obj)


# https://stackoverflow.com/questions/20623925/class-vs-self-class-when-creating-object
# self.__class__()可以更好的应用于继承的状态下，让python自己选择类进行实例化
return self.__class__(self._obj, req)
```
代码有两处__class__的使用：
1. 调用父类静态方法
2. 实例化对象
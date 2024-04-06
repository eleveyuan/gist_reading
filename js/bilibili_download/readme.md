# bibili download

阅读这个js脚本的原因主要有两个：
1. 熟悉 js 脚本在 chrome 拓展中的使用。
2. 熟悉 bilibili 一些api接口的用途。

## 相关资源

1. ~~原脚本来自油猴~~：[脚本链接](https://greasyfork.org/zh-CN/scripts/413228-bilibili%E8%A7%86%E9%A2%91%E4%B8%8B%E8%BD%BD) 油猴这个脚本可读性有点太差了
2. [git仓库代码](https://github.com/injahow/user.js/tree/main/bilibili-parse-download)
3. 首先对于web的操作都是基于api的，但是对于此脚本不知道使用的哪里的api，我这里只找到github上的一个bilibili野生api仓库：[哔哩哔哩-API收集整理](https://github.com/SocialSisterYi/bilibili-API-collect)


## 阅读顺序

对于存在有界面操作或者web项目的代码，个人都是操作一遍流程根据这个流程去读代码，也即这个流程来确认黑盒整体的input -> output这条路径，然后在去看这路径上涉及到的助手函数。

对于 javascript 代码，有三个特点：
1. 链式调用很多
2. 匿名对象很多
3. 字典或者说map结构很多

由于不太熟悉这门语言的缘故，读着还是吃力的。

## 函数


## 补充知识
1 [廖雪峰：Promise](https://www.liaoxuefeng.com/wiki/1022910821149312/1023024413276544)
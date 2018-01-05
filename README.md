# TattyUI

![screenshot](https://raw.githubusercontent.com/BentleyBlanks/TattyUI/master/screenshots/1.png)

对比Chrome(本质上是TattyUI做的近似CSS实现)
![screenshot](https://raw.githubusercontent.com/BentleyBlanks/TattyUI/master/screenshots/2.png)

本UI框架底层渲染框架采用[nanovg](https://github.com/memononen/nanovg),采用类似浏览器WebKit的做法，将UI的样式与业务逻辑分离。本质上是一个简易的浏览器内核实现。

TattyUI第一个较为成熟的production级的产品将会是为 [WIP2D](https://github.com/wubugui/WIP) 2D游戏引擎制作```编辑器```，尽请期待。

底层[CSS解析器](https://github.com/BentleyBlanks/t2CSSPareser)为使用Flex+Bison，借鉴[Webkit](https://www.webkit.org/)与[W3C](http://www.w3.org/)中CSS2.0实现，详见[t2CSSParser](https://github.com/BentleyBlanks/t2CSSPareser)介绍。

# 依赖项说明
1.[GLFW](http://www.glfw.org/) ver 3.11

2.[GLEW](http://glew.sourceforge.net/) ver 1.13.0

3.[Gumbo](https://github.com/google/gumbo-parser) 

4.[t3DataStructures](https://github.com/BentleyBlanks/t3DataStructures) ver 1.0

5.[nanovg](https://github.com/memononen/nanovg)

> 依赖项已全部附带至Git，也可以根据需要自行更换
> 目前依赖项静态库为直接给出，可以根据平台需要以及Debug/Release模式的不同自行更换

# 构建说明
1.TattyUI采用CMake做跨平台搭建工作,支持Windows,OSX(OSX下的静态库配置仍需手动完成)等

2.假设您构建在新文件夹build中，那么仅需在IDE中设置包含```../TattyUI```即可

3.可自行构建```resources```文件夹用于放置资源

4.给出的文件夹```bin/graph```中包含了[Graphviz](www.graphviz.org/)生成的脚本与渲染出的可视AST，也可根据需要自行更换生成。

# 使用说明
1.CSS目前支持的属性已在```t2Style.cpp```声明，可自行查阅。

2.C++通过和t2DivController交互即可获取想要的```<div>```列表，所有C++代码都会直接或者间接的与全局表```divTable```进行交互。
> 例如

```cpp
// 两种方式获取指定名称的div作用都是相同的
t2Div *div1 = divController->find("div1");
t2Div *div2 = divController["div2"];
```
> 详情可见example

3.TattyUI较大的采用C++11标准，在回调函数的选择上使用```std::fucntion```从而支持成员函数，函数指针，Lambda表达式等，以最大的可能模拟浏览器的样式但采用本地矢量渲染。
> 例如

```cpp
// 以下回调函数都使用C++11支持的标准Lambda表达式
    root.mouseMovedIn = [](int x, int y, int px, int py)
    {
        t2Log("Root MovedIn\n");
    };

    root.mouseMovedOut = [](int x, int y, int px, int py)
    {
        t2Log("Root MovedOut\n");
    };

    div1.mouseMovedIn = [](int x, int y, int px, int py)
    {
        t2Log("Div1 MovedIn\n");
    };

    div1.mouseMovedOut = [](int x, int y, int px, int py)
    {
        t2Log("Div1 MovedOut\n");
    };
```

4.CSS解析部分支持大部分CSS2.0语法，部分未支持的语法规则已在[t2CSSParser](https://github.com/BentleyBlanks/t2CSSPareser)简介中给出

# 已知BUG
1.html中不给出```class```标签直接崩溃的错误

2.新解析器不支持类似```function```写法的错误，如下

``` css 
/* unsupported */
color: rgba();
/* supported */
color: #ffffff;
/* supported */
color: red;
```

3.#fff这样的位数不足六位写法解析出粗错，如下
```css
/* 解析器直接崩溃的错误 */
color: #fff;
/* 位数严格需要是六位 */
color: #ffffff;
```

4.```text-align```无法使用，TattyUI区别于普通浏览器的新增关键字目前并不支持，因此模拟```<h><p>```等标签就需要手工运算距离较麻烦

5.margin负数时未考虑，会直接忽略这种情况而重置为0。

6.目前请尽量使用稳定的```t2WindowBase```来创建窗口,t2Window尚有未解决的布局BUG。

# 版本说明
```
TattyUI ver 0.0.7 中感谢[ccss](https://github.com/jdeng/ccss)给我提供了非常好的使用正则表达式解析CSS的案例。

TattyUI ver 0.0.3 之前采用XML+Json+Lua的脚本配合

TattyUI ver 0.0.4 之后直接采用HTML+CSS+Lua的脚本
```
## 关于作者
```cpp
int 官某某 = "Bingo";

char[] 个人博客 = "http://bentleyblanks.github.io";
```





# DuHa-engine
**这是本人第一次写引擎**
**需要安装easyx图形库,链接:https://easyx.cn**需要支持c++的编译器

接下来就开始教程

首先先包含"DuHa3D.h"头文件

没有命名空间

在`int main`或`int WinMain`主函数中

创建一个`Game*`对象，并填好构造函数

参数:1.Near 2.Far 3.Aspect 4.Size 5.Fov

其中有两个构造函数 不填第五个参数将决定你使用的投影（透视或正交）

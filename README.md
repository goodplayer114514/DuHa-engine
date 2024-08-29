# DuHa-engine
**这是本人第一次写引擎**
**需要安装easyx图形库,链接:https://easyx.cn**
需要支持c++的编译器

接下来就开始教程(2dgame是测试程序，请勿拿来使用)

首先先包含"DuHa3D.h"头文件

没有命名空间


在`int main`或`int WinMain`主函数中

创建一个`Game* game`对象，并填好构造函数

参数:1.Near 2.Far 3.Aspect 4.Size 5.Fov

其中有两个构造函数 填不填第五个参数将决定你使用的投影矩阵（透视或正交）

其中Game类包含两个私立函数
你需要将其补充
```c++
void Game::update(){
// Write Something
}
void Game::input(){
//Write Something
}
```
其中update()是更新游戏状态
input()是处理玩家输入的

随后进行摄像头方位处理
```c++
game->MainCam.Cam_pos.x=0;//世界空间
game->MainCam.Cam_pos.y=0;
game->MainCam.Cam_pos.z=0;
game->MainCam.Cam_ro.x=0;//旋转
game->MainCam.Cam_ro.y=0;
game->MainCam.Cam_ro.z=0;
```

同时需要写顶点坐标
``Pos pos(x,y,z,w)``

函数接受3个参数

x:世界坐标x

y:世界坐标y

z:世界坐标z

w:齐次坐标,默认为1

还有``RoWorldNormal()``和``MoveWorldNormal()``

它们是决定旋转和移动

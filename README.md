# AIChatProject - By Wild_Pointer

<p align="center">
  <img src ="README_IMG\logo.png"/>
</p>

<p align="center">
    <img src ="https://img.shields.io/badge/version-1.0.0.1-purple"/>
    <img src ="https://img.shields.io/badge/platform-windows%7Clinux-yellow"/>
    <img src ="https://img.shields.io/badge/C%2B%2B-11-blue" />
    <img src ="https://img.shields.io/badge/framework-Qt6-orange"/>
    <img src ="https://img.shields.io/badge/build-Wild_Pointer-orange"/>
</p>

AIChatProject是一套基于Qt框架的开源智能即时聊天室系统，在经过多次反复优化迭代下成长为多功能的交友应用。

**源码可自由下载使用，更多信息参考[个人博客](wild-pointer.top)**：


在使用AiChatProject进行二次开发（策略、模块等）的过程中有任何疑问，可通过[**QQ邮箱**](3020922258@qq.com)或者[**谷歌邮箱**](wildpointer794@gmail.com)，也欢迎在分享你的使用心得或者使用中产生的bug，方便作者后续更新迭代！


## AIChatProject介绍

 智能即时聊天室系统（AIChatProject）是一个高效、灵活的即时通讯解决方案。它融合了百度的开源大型语言模型——文心一言，通过API接口实现深度集成。系统专为聊天和文件传输等核心功能设计，以便快速搭建定制化的即时通讯应用。采用客户端/服务器（C/S）架构，确保了应用的稳定性和扩展性。数据存储依托于MySQL数据库，保障了数据的安全性和高效管理。客户端之间的信息交换通过JSON格式实现，简洁而高效。此外，系统利用TCP协议进行数据传输，确保了通信的可靠性和稳定性。

1. 项目技术栈：

    * 数据库

        * MySQL

    * 技术栈
        * C++11

        * Qt6

        * 线程池

        * TCP协议

        * POST方法

        * JSON格式
2. 模块设计概述：
    * 数据传输：
        * 通过QTcpSocket使用TCP协议对客户端与服务端之间的数据进行传输，并且使用JSON格式对传递的数据进行格式化操作。服务端返回的JSON格式自带错误码，方便客户端对响应的请求反馈给用户
    * 线程模块：
        * 针对AIChatProject项目，作者采用QThreadPool模块，在客户端与服务端都定义了多线程模块。针对服务端共有两个线程，一个是数据库链接线程，一个是处理服务端数据线程。针对客户端定义了两个线程，分别用于处理与服务端数据传输以及对智能聊天数据的传输
    * AI智能模块：
        * 通过QNetWork模块，对其鉴权元素进行处理，对特定的地址进行POST请求，获取Token。后续使用Token对发出的询问进行加密，返回智能机器人的响应信息
    * 列表模块：
        * 针对列表模块使用了模型/视图架构，针对好友，群聊以及智能聊天机器人分别对其映射，将数据与视图隔离，规范了代码，降低耦合
    * 检测模块：
        * 针对用户作输入操作时，该项目采用正则表达式检测用户异常输出，防止恶意的SQL注入攻击及不规范的输入，减少服务端的恶意请求，降低成本
    * 加密模块：
        * 针对用户登录时，项目使用MD5加密算法对其密码等数据进行加密，减少用户被恶意攻击，数据泄漏的几率

## 环境准备

* 推荐使用Qt6版本进行部署
* 支持的数据库版本：MySQL 8.0
* 支持的系统版本：Windows 10以上
* 支持的C++版本：C++ 11/64位（**推荐使用C++ 11**）

## Qt模块准备

下载源码后，需要在Pro文件导入以下模块：

```
sql
```
```
network
```

```
websockets
```

**注意：源码中的Pro文件以及列举了Qt6所需的所有模块，其中Qt6不支持MySQL数据库驱动，需要手动配置**

## 代码示例

AIChatProject采用了统一的命名和注释格式，具体可参考以下代码：

```C++
/*  处理保存加密请求返回的信息
 *  jsonObject：服务端返回的用户数据
*/
int TcpThread::handle_EncryptResult(const QJsonObject &jsonObject)
{
    QString returnData = jsonObject["return"].toString();

    //返回服务器处理加密信息结果给主线程处理
    if(returnData == "True"){
        emit return_SaveEncryptResult(true,"");
        return 1;
    }else if(returnData == "False"){
        emit return_SaveEncryptResult(false,"");
        return 0;
    }
}
```
其中函数命名使用驼峰法，并且注释中带有函数参数以及默认返回值int，方便后续对异常的捕获进行诊断


## 运行示例
<p align="center">
    <img src ="README_IMG\1.gif"/>
</p>


## 作者留言
个人博客：wild-pointer.top

通过QQ邮箱联系我：3020922258@qq.com 

通过谷歌邮箱联系我：wildpointer794@gmail.com
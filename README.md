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


## 功能特点

1. 智能即时聊天室系统（AIChatProject）是一个高效、灵活的即时通讯解决方案。它融合了百度的开源大型语言模型——文心一言，通过API接口实现深度集成。系统专为聊天和文件传输等核心功能设计，以便快速搭建定制化的即时通讯应用。采用客户端/服务器（C/S）架构，确保了应用的稳定性和扩展性。数据存储依托于MySQL数据库，保障了数据的安全性和高效管理。客户端之间的信息交换通过JSON格式实现，简洁而高效。此外，系统利用TCP协议进行数据传输，确保了通信的可靠性和稳定性。

2. 应用实现：

    * 数据库

        * MySQL

    * 技术栈
        * C++11

        * Qt6

        * 线程池

        * TCP协议

        * POST方法

        * JSON格式

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

AIChatProject采用了统一的命名格式，具体可参考以下代码：

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

## 客户端运行示例
<p align="center">
    <img src ="README_IMG\1.png"/>
    <img src ="README_IMG\2.png"/>
    <img src ="README_IMG\3.png"/>
    <img src ="README_IMG\4.png"/>
</p>

## 服务端运行示例
<p align="center">
    <img src ="README_IMG\5.png"/>
</p>
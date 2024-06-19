QT += core gui sql network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    modelFile/AiList_Model.cpp \
    modelFile/FriendList_Model.cpp \
    modelFile/GroupList_Model.cpp \
    srcFile/AiSrc/AI.cpp \
    srcFile/AiSrc/AiThread.cpp \
    srcFile/NetWork.cpp \
    srcFile/TcpThread.cpp \
    srcFile/USER.cpp \
    uiFile/AiModel/AiChat.cpp \
    uiFile/AiModel/AiInfo.cpp \
    uiFile/Chatbubble/ChatBox.cpp \
    uiFile/Chatbubble/recvFilebox.cpp \
    uiFile/Emotion/Emotion.cpp \
    uiFile/FriendModel/FriendChat.cpp \
    uiFile/FriendModel/FriendInfo.cpp \
    uiFile/GroupModel/GroupChat.cpp \
    uiFile/GroupModel/GroupInfo.cpp \
    uiFile/Login.cpp \
    uiFile/addinfo/AddFriend.cpp \
    uiFile/addinfo/AddGroup.cpp \
    uiFile/addinfo/AddInfo.cpp \
    uiFile/addinfo/AddVerify.cpp \
    uiFile/Chatbubble/Recvbox.cpp \
    uiFile/Chatbubble/Sendbox.cpp \
    uiFile/Chatbubble/sendFilebox.cpp \
    uiFile/HeadImg.cpp \
    uiFile/Register.cpp \
    uiFile/SetUp/AiSetup.cpp \
    uiFile/SetUp/FileSetup.cpp \
    uiFile/SetUp/SetUp.cpp \
    uiFile/SetUp/UserSetup.cpp \
    uiFile/UserInfo.cpp

HEADERS += \
    modelFile/AiList_Model.h \
    modelFile/FriendList_Model.h \
    modelFile/GroupList_Model.h \
    srcFile/AiSrc/AI.h \
    srcFile/AiSrc/AiThread.h \
    srcFile/NetWork.h \
    srcFile/TcpThread.h \
    srcFile/USER.h \
    uiFile/AiModel/AiChat.h \
    uiFile/AiModel/AiInfo.h \
    uiFile/Chatbubble/ChatBox.h \
    uiFile/Chatbubble/recvFilebox.h \
    uiFile/Emotion/Emotion.h \
    uiFile/FriendModel/FriendChat.h \
    uiFile/FriendModel/FriendInfo.h \
    uiFile/GroupModel/GroupChat.h \
    uiFile/GroupModel/GroupInfo.h \
    uiFile/Login.h \
    uiFile/addinfo/AddFriend.h \
    uiFile/addinfo/AddGroup.h \
    uiFile/addinfo/AddInfo.h \
    uiFile/addinfo/AddVerify.h \
    uiFile/Chatbubble/Recvbox.h \
    uiFile/Chatbubble/Sendbox.h \
    uiFile/Chatbubble/sendFilebox.h \
    uiFile/HeadImg.h \
    uiFile/Register.h \
    uiFile/SetUp/AiSetup.h \
    uiFile/SetUp/FileSetup.h \
    uiFile/SetUp/SetUp.h \
    uiFile/SetUp/UserSetup.h \
    uiFile/UserInfo.h

FORMS += \
    uiFile/AiModel/AiChat.ui \
    uiFile/AiModel/AiInfo.ui \
    uiFile/Chatbubble/recvFilebox.ui \
    uiFile/Emotion/Emotion.ui \
    uiFile/FriendModel/FriendChat.ui \
    uiFile/FriendModel/FriendInfo.ui \
    uiFile/GroupModel/GroupChat.ui \
    uiFile/GroupModel/GroupInfo.ui \
    uiFile/Login.ui \
    uiFile/addinfo/AddFriend.ui \
    uiFile/addinfo/AddGroup.ui \
    uiFile/addinfo/AddInfo.ui \
    uiFile/addinfo/AddVerify.ui \
    uiFile/Chatbubble/Recvbox.ui \
    uiFile/Chatbubble/Sendbox.ui \
    uiFile/Chatbubble/sendFilebox.ui \
    uiFile/HeadImg.ui \
    uiFile/Register.ui \
    uiFile/SetUp/AiSetup.ui \
    uiFile/SetUp/FileSetup.ui \
    uiFile/SetUp/SetUp.ui \
    uiFile/SetUp/UserSetup.ui \
    uiFile/UserInfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/Image.qrc

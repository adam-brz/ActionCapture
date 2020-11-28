QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/ActionTable.cpp \
    input/Action.cpp \
    input/DeviceFactory.cpp \
    input/GlobalKeyboard.cpp \
    input/GlobalMouse.cpp \
    input/KeyboardAction.cpp \
    input/MouseAction.cpp \
    input/win/GlobalWinKeyboard.cpp \
    input/win/GlobalWinMouse.cpp \
    main.cpp \
    editorwindow.cpp \
    toolbox/Savable.cpp \
    toolbox/SavableData.cpp

HEADERS += \
    editorwindow.h \
    gui/ActionTable.h \
    input/Action.h \
    input/DeviceFactory.h \
    input/GlobalKeyboard.h \
    input/GlobalMouse.h \
    input/Key.h \
    input/KeyboardAction.h \
    input/KeyboardEvent.h \
    input/MouseAction.h \
    input/MouseEvent.h \
    input/Point.h \
    input/win/GlobalWinKeyboard.h \
    input/win/GlobalWinMouse.h \
    toolbox/Savable.h \
    toolbox/SavableData.h

FORMS += \
    editorwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TCategoryModel.cpp \
    TMainWnd.cpp \
    TProductDelegate.cpp \
    TProductModel.cpp \
    TSettings.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    TCategoryModel.h \
    TMainWnd.h \
    TProductDelegate.h \
    TProductModel.h \
    TSettings.h \
    mainwindow.h

FORMS += \
    TMainWnd.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Store.pro

RESOURCES += \
    res/store.qrc \
    res/store.qrc

DISTFILES += \
    res/minus.png \
    res/plus.png \
    res/search.png \
    res/store.ico \
    translations/store_ru.qm \
    translations/store_ru.ts

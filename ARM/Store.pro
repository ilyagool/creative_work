TEMPLATE = app
TARGET = Store

QT += core \
      gui \
	  	widgets \
			sql \
			xml
    
FORMS += ui/TMainWnd.ui
HEADERS += src/TMainWnd.h \
           src/TCategoryModel.h \
           src/TProductDelegate.h \
           src/TProductModel.h \
           src/TSettings.h
SOURCES += src/main.cpp \
           src/TCategoryModel.cpp \
           src/TMainWnd.cpp \
           src/TProductDelegate.cpp \
           src/TProductModel.cpp \
					 src/TSettings.cpp

RC_ICONS = res/store.ico

UI_DIR = ui_src
DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj

RESOURCES += res/store.qrc
OTHER_FILES += 

TRANSLATIONS = translations/store_ru.ts

QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare# -Wno-attributes

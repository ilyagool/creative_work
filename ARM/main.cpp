#include <QApplication>
#include <QStyleFactory>
#include <QTranslator>

#include "TMainWnd.h"

int main(int argc, char *argv[])
 {
 QApplication App(argc, argv);
 App.setStyle(QStyleFactory::create("Windows"));

 QTranslator mainTranslator;
 if (mainTranslator.load(qApp->applicationDirPath()+"/translations/store_"+QLocale::system().name()))
   App.installTranslator(&mainTranslator);
 QTranslator qtTranslator;
 if (qtTranslator.load(qApp->applicationDirPath()+"/translations/qt_"+QLocale::system().name()))
  App.installTranslator(&qtTranslator);

 TMainWnd MainWnd;
 MainWnd.show();
 return App.exec();
 }

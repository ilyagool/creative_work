#ifndef TMAINWND_H
#define TMAINWND_H

#include "ui_TMainWnd.h"

#include <QSqlDatabase>

class TCategoryModel;
class TProductModel;
class TProductDelegate;

class TMainWnd : public QMainWindow, private Ui::TMainWnd
  {
    Q_OBJECT
  public:
    TMainWnd(QWidget *parent = 0);

  protected:
    bool openDatabase(const QString &databaseName);
    void writeSettings();
    void readSettings();

    void closeEvent(QCloseEvent *event);

  protected slots:
    void aboutToQuit();
    void categoryChanged(const QModelIndex &current,const QModelIndex &previous);

    void appendProduct();
    void removeProduct();
    void searchProduct();

  private:
    QSqlDatabase m_dataBase;
    TCategoryModel *m_categoryModel;
    TProductModel *m_productModel;
    TProductDelegate *m_productDelegate;
  };

#endif // TMAINWND_H

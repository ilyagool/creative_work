#ifndef TCATEGORYMODEL_H
#define TCATEGORYMODEL_H

#include <QSqlTableModel>

class TCategoryModel : public QSqlTableModel
  {
    Q_OBJECT
  public:
    TCategoryModel(QObject *parent=nullptr,QSqlDatabase dataBase=QSqlDatabase());
    void setHeaders();

  protected:
    virtual QString selectStatement() const override;
  };

#endif // TCATEGORYMODEL_H

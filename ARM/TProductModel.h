#ifndef TPRODUCTMODEL_H
#define TPRODUCTMODEL_H

#include <QSqlTableModel>

class TProductModel : public QSqlTableModel
  {
    Q_OBJECT
  public:
    explicit TProductModel(QObject *parent = nullptr, QSqlDatabase dataBase=QSqlDatabase());
    void setHeaaders();

  protected:
    virtual QString selectStatement() const override;
  };

#endif // TPRODUCTMODEL_H

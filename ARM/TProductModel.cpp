#include "TProductModel.h"

#include <QDebug>

TProductModel::TProductModel(QObject *parent, QSqlDatabase dataBase) : QSqlTableModel{parent, dataBase}
  {
  setTable("products");
  setEditStrategy(QSqlTableModel::OnFieldChange);
  }

void TProductModel::setHeaaders()
  {
  setHeaderData(fieldIndex("id"),Qt::Horizontal,tr("ID"),Qt::DisplayRole);
  setHeaderData(fieldIndex("category_id"),Qt::Horizontal,tr("Category ID"),Qt::DisplayRole);
  setHeaderData(fieldIndex("name"),Qt::Horizontal,tr("Name"),Qt::DisplayRole);
  setHeaderData(fieldIndex("article"),Qt::Horizontal,tr("Article"),Qt::DisplayRole);
  setHeaderData(fieldIndex("amount"),Qt::Horizontal,tr("Amount"),Qt::DisplayRole);
  setHeaderData(fieldIndex("entrance_date"),Qt::Horizontal,tr("Entrance Date"),Qt::DisplayRole);
  }
//
QString TProductModel::selectStatement() const
  {
  QString statement=QStringLiteral("select products.id, products.category_id, products.name, products.article, products.amount, products.entrance_date "
                                   "from products");
  if (filter().isEmpty()==false)
    statement.append(" where "+filter());

  statement.append(" order by products.name");
  return statement;
  }

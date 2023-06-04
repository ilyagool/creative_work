#include "TCategoryModel.h"

TCategoryModel::TCategoryModel(QObject *parent, QSqlDatabase dataBase) : QSqlTableModel(parent,dataBase)
  {
  setTable("categories");
  setEditStrategy(QSqlTableModel::OnFieldChange);
  }

void TCategoryModel::setHeaders()
  {
  setHeaderData(fieldIndex("id"),Qt::Horizontal,tr("ID"),Qt::DisplayRole);
  setHeaderData(fieldIndex("category"),Qt::Horizontal,tr("Category"),Qt::DisplayRole);
  }

QString TCategoryModel::selectStatement() const
  {
  return QStringLiteral("select categories.id, categories.category from categories order by categories.category");
  }

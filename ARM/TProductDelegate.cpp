#include "TProductDelegate.h"
#include "TProductModel.h"

#include <QSqlRecord>
#include <QDate>
#include <QApplication>
#include <QDateEdit>
#include <QSpinBox>

TProductDelegate::TProductDelegate(QObject *parent) : QStyledItemDelegate{parent}
  {

  }

void TProductDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
  {
  const TProductModel *model=qobject_cast<const TProductModel*>(index.model());
  if (model==nullptr)
    return;
  QSqlRecord record=model->record();

  QStyleOptionViewItem newOption(option);
  if (index.column()==record.indexOf("amount"))
    {
    newOption.text=QString::number(index.data().toUInt());
    newOption.displayAlignment=Qt::AlignRight | Qt::AlignVCenter;
    qApp->style()->drawControl(QStyle::CE_ItemViewItem,&newOption,painter);
    return;
    }

  if (index.column()==record.indexOf("entrance_date"))
    {
    newOption.text=QDate::fromString(index.data().toString(),"yyyy-MM-dd").toString("dd.MM.yyyy");
    newOption.displayAlignment=Qt::AlignRight | Qt::AlignVCenter;
    qApp->style()->drawControl(QStyle::CE_ItemViewItem,&newOption,painter);
    return;
    }

  newOption.text=index.data().toString();
  qApp->style()->drawControl(QStyle::CE_ItemViewItem,&newOption,painter);
  }

QWidget *TProductDelegate::createEditor(QWidget *owner, const QStyleOptionViewItem &option, const QModelIndex &index) const
  {
  const TProductModel *model=qobject_cast<const TProductModel*>(index.model());
  if (model==nullptr)
    return nullptr;
  QSqlRecord record=model->record();

  if (index.column()==record.indexOf("amount"))
    {
    QSpinBox *spinBox=new QSpinBox(owner);
    spinBox->setRange(0,65535);
    return spinBox;
    }

  if (index.column()==record.indexOf("entrance_date"))
    {
    QDateEdit *dateEdit=new QDateEdit(owner);
    dateEdit->setCalendarPopup(true);
    return dateEdit;
    }

  return QStyledItemDelegate::createEditor(owner,option,index);
  }

void TProductDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
  {
  const TProductModel *model=qobject_cast<const TProductModel*>(index.model());
  if (model==nullptr)
    return;
  QSqlRecord record=model->record();

  if (index.column()==record.indexOf("amount"))
    {
    QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);
    if (spinBox==nullptr)
      return;

    spinBox->setValue(index.data().toUInt());
    return;
    }

  if (index.column()==record.indexOf("entrance_date"))
    {
    QDateEdit *dateEdit=qobject_cast<QDateEdit*>(editor);
    if (dateEdit==nullptr)
      return;

    dateEdit->setDate(QDate::fromString(index.data().toString(),"dd.MM.yyyy"));
    return;
    }

  QStyledItemDelegate::setEditorData(editor,index);
  }

void TProductDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
  {
  const TProductModel *productModel=qobject_cast<const TProductModel*>(model);
  if (productModel==nullptr)
    return;
  QSqlRecord record=productModel->record();

  if (index.column()==record.indexOf("amount"))
    {
    QSpinBox *spinBox=qobject_cast<QSpinBox*>(editor);
    if (spinBox==nullptr)
      return;

    model->setData(productModel->index(index.row(),record.indexOf("amount")),spinBox->value());
    return;
    }

  if (index.column()==record.indexOf("entrance_date"))
    {
    QDateEdit *dateEdit=qobject_cast<QDateEdit*>(editor);
    if (dateEdit==nullptr)
      return;

    model->setData(productModel->index(index.row(),record.indexOf("entrance_date")),dateEdit->date().toString("yyyy-MM-dd"));
    return;
    }

  QStyledItemDelegate::setModelData(editor,model,index);
  }

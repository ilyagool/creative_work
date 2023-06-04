#ifndef TPRODUCTDELEGATE_H
#define TPRODUCTDELEGATE_H

#include <QStyledItemDelegate>

class TProductDelegate : public QStyledItemDelegate
  {
    Q_OBJECT
  public:
    explicit TProductDelegate(QObject *parent = nullptr);

  protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
    QWidget *createEditor(QWidget *owner, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  };

#endif // TPRODUCTDELEGATE_H

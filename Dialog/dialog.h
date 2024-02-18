#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QItemSelection>

namespace Ui {
class Dialog;
}

class TextListModel;
class QSortFilterProxyModel;

class Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();

private slots:
  void on_mButAddText_clicked();
  void on_mButRemoveItem_clicked();
  void on_mButRemoveSortItem_clicked();
  void on_mButSortOrderAsc_clicked();
  void on_mButSortOrderDesc_clicked();

  void updateSortListSelection(const QItemSelection &selected, const QItemSelection &deselected);
  void updateListSelection(const QItemSelection &selected, const QItemSelection &deselected);

  void updateSortList();

private:
  Ui::Dialog *ui;

  TextListModel *mListModel;
  QSortFilterProxyModel *mSortListModel;

  Qt::SortOrder mSortOrder;
};

#endif // DIALOG_H

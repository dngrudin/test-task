#include "dialog.h"
#include "text_list_model.h"
#include "ui_dialog.h"

#include <QItemSelectionModel>
#include <QSortFilterProxyModel>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog), mSortOrder(Qt::AscendingOrder) {
  ui->setupUi(this);

  mListModel = new TextListModel(this);

  mSortListModel = new QSortFilterProxyModel(this);
  mSortListModel->setSourceModel(mListModel);

  ui->mList->setModel(mListModel);
  ui->mSortList->setModel(mSortListModel);

  connect(ui->mList->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
          this, SLOT(updateSortListSelection(QItemSelection, QItemSelection)));
  connect(ui->mSortList->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
          this, SLOT(updateListSelection(QItemSelection, QItemSelection)));
}

Dialog::~Dialog() { delete ui; }

void Dialog::updateSortListSelection(const QItemSelection &selected,
                                     const QItemSelection &deselected) {
  ui->mSortList->selectionModel()->select(mSortListModel->mapSelectionFromSource(deselected),
                                          QItemSelectionModel::Deselect);
  ui->mSortList->selectionModel()->select(mSortListModel->mapSelectionFromSource(selected),
                                          QItemSelectionModel::Select);
}

void Dialog::updateListSelection(const QItemSelection &selected, const QItemSelection &deselected) {
  ui->mList->selectionModel()->select(mSortListModel->mapSelectionToSource(deselected),
                                      QItemSelectionModel::Deselect);
  ui->mList->selectionModel()->select(mSortListModel->mapSelectionToSource(selected),
                                      QItemSelectionModel::Select);
}

void Dialog::updateSortList() { mSortListModel->sort(0, mSortOrder); }

void Dialog::on_mButAddText_clicked() {
  mListModel->addTextItm(ui->mText->text());
  updateSortList();
}

void Dialog::on_mButRemoveItem_clicked() {
  QModelIndexList selectIndexList = ui->mList->selectionModel()->selectedIndexes();
  if (selectIndexList.size())
    mListModel->delTextItm(selectIndexList.at(0).row());
}

void Dialog::on_mButRemoveSortItem_clicked() {
  QModelIndexList selectIndexList = ui->mSortList->selectionModel()->selectedIndexes();
  if (selectIndexList.size())
    mListModel->delTextItm(mSortListModel->mapToSource(selectIndexList.at(0)).row());
}

void Dialog::on_mButSortOrderAsc_clicked() {
  if (mSortListModel->sortOrder() == Qt::AscendingOrder)
    return;

  mSortOrder = Qt::AscendingOrder;
  updateSortList();
}

void Dialog::on_mButSortOrderDesc_clicked() {
  if (mSortListModel->sortOrder() == Qt::DescendingOrder)
    return;

  mSortOrder = Qt::DescendingOrder;
  updateSortList();
}

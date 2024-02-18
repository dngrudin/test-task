#include "text_list_model.h"

TextListModel::TextListModel(QObject *parent) : QAbstractListModel(parent) {}

QVariant TextListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if ((role == Qt::DisplayRole || role == Qt::EditRole) && index.row() < mTextList.size())
    return mTextList.at(index.row());

  return QVariant();
}

void TextListModel::addTextItm(const QString &text) {
  beginInsertRows(QModelIndex(), mTextList.size(), mTextList.size());
  mTextList.push_back(text);
  endInsertRows();
}

void TextListModel::delTextItm(int index) {
  if (index < 0 || index >= mTextList.size())
    return;

  beginRemoveRows(QModelIndex(), index, index);
  mTextList.removeAt(index);
  endRemoveRows();
}

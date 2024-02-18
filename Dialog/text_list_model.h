#ifndef TEXT_LIST_MODEL_H
#define TEXT_LIST_MODEL_H

#include <QAbstractListModel>
#include <QStringList>

class TextListModel : public QAbstractListModel {
  Q_OBJECT
public:
  explicit TextListModel(QObject *parent = nullptr);

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  int rowCount(const QModelIndex &parent = QModelIndex()) const {
    Q_UNUSED(parent);
    return mTextList.size();
  }

public slots:
  void addTextItm(const QString &text);
  void delTextItm(int index);

private:
  QStringList mTextList;
};

#endif // TEXT_LIST_MODEL_H

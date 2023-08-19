#ifndef EDITABLEDELEGATE_H
#define EDITABLEDELEGATE_H

#include <QItemDelegate>

class EditableDelegate : public QItemDelegate {
public:
    explicit EditableDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (index.column() == 0) {  // Only make the 'a' column editable
            return QItemDelegate::createEditor(parent, option, index);
        } else {
            return nullptr;
        }
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        QItemDelegate::setEditorData(editor, index);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        QItemDelegate::setModelData(editor, model, index);
    }
};

#endif // EDITABLEDELEGATE_H

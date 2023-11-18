#pragma once

#include <QComboBox>
#include <QItemDelegate>

class CompVIPRDelegate : public QItemDelegate
{
public:
    explicit CompVIPRDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (index.column() == 5) { // Customize the column index where you want to show the ComboBox
            QComboBox *comboBox = new QComboBox(parent);
            comboBox->addItem("PI");
            comboBox->addItem("Darcy");
            comboBox->addItem("Vogel");
            comboBox->addItem("Fetkovitch");
            return comboBox;
        }
        return QItemDelegate::createEditor(parent, option, index);
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const override {
        if (QComboBox *comboBox = qobject_cast<QComboBox *>(editor)) {
            QString text = index.data(Qt::EditRole).toString();
            int idx = comboBox->findText(text);
            comboBox->setCurrentIndex(idx);
        } else {
            QItemDelegate::setEditorData(editor, index);
        }
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
        if (QComboBox *comboBox = qobject_cast<QComboBox *>(editor)) {
            model->setData(index, comboBox->currentText(), Qt::EditRole);
        } else {
            QItemDelegate::setModelData(editor, model, index);
        }
    }
};

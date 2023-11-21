#pragma once

#include <QTreeWidget>
#include <QObject>

class MTreeWidget final : public QTreeWidget {
Q_OBJECT

public:
    explicit MTreeWidget(QWidget* parent = nullptr);

    void clearItems();

    void initializeItems();

private:
    QTreeWidgetItem* _makeItem(const QString& name, const QString& iconPath);

    QVector<QTreeWidgetItem*> _items{};
    QFont _font{};
    bool _didInitialized{false};
};

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
    QTreeWidgetItem* wellItem{};
    QTreeWidgetItem* sourceItem{};
    QTreeWidgetItem* sinkItem{};
    QTreeWidgetItem* junctionItem{};
    QTreeWidgetItem* flowlineItem{};

    QIcon wellIcon;
    QIcon sourceIcon;
    QIcon sinkIcon;
    QIcon junctionIcon;
    QIcon flowlineIcon;
    QFont font;
};

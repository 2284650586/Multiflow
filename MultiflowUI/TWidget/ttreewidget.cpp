#include "ttreewidget.h"
#include <QIcon>
#include <QFont>
#include <QSize>

TTreeWidget::TTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    wellIcon = QIcon(":/resources/image/Well.png");
    sourceIcon = QIcon(":/resources/image/source.png");
    sinkIcon = QIcon(":/resources/image/sink.png");
    junctionIcon = QIcon(":/resources/image/junction.png");
    flowlineIcon = QIcon(":/resources/image/flowline.png");

    font = headerItem()->font(0);
    font.setPixelSize(20);

    headerItem()->setFont(0, font);
    headerItem()->setText(0, "输入组件");
}

void TTreeWidget::addItem()
{
    font.setPixelSize(15);
//    QIcon wellIcon = QIcon(":/resources/image/Well.png");
//    QIcon sourceIcon = QIcon(":/resources/image/source.png");
//    QIcon sinkIcon = QIcon(":/resources/image/sink.png");
//    QIcon flowlineIcon = QIcon(":/resources/image/flowline.png");

    wellItem = new QTreeWidgetItem(this);
    wellItem->setFont(0, font);
    wellItem->setText(0, "油井");
    wellItem->setIcon(0, wellIcon);
    wellItem->setExpanded(true);

    sourceItem = new QTreeWidgetItem(this);
    sourceItem->setFont(0, font);
    sourceItem->setText(0, "源");
    sourceItem->setIcon(0, sourceIcon);
    sourceItem->setExpanded(true);

    sinkItem = new QTreeWidgetItem(this);
    sinkItem->setFont(0, font);
    sinkItem->setText(0, "sink");
    sinkItem->setIcon(0, sinkIcon);
    sinkItem->setExpanded(true);

    junctionItem = new QTreeWidgetItem(this);
    junctionItem->setFont(0, font);
    junctionItem->setText(0, "接合点");
    junctionItem->setIcon(0, junctionIcon);
    junctionItem->setExpanded(true);

    flowlineItem = new QTreeWidgetItem(this);
    flowlineItem->setFont(0, font);
    flowlineItem->setText(0, "管道");
    flowlineItem->setIcon(0, flowlineIcon);
    flowlineItem->setExpanded(true);
}

void TTreeWidget::clearItem()
{
    clear();
}


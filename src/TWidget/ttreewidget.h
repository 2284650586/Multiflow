#ifndef TTREEWIDGET_H
#define TTREEWIDGET_H

#include <QTreeWidget>
#include <QObject>



class TTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    TTreeWidget(QWidget *parent = nullptr);

public:

    void addItem();
    void clearItem();

private:
//    QList<TWellItem*> wellList;
//    QList<TSourceItem*> sourceList;
//    QList<TSinkItem*> sinkList;

    QTreeWidgetItem *wellItem;
    QTreeWidgetItem *sourceItem;
    QTreeWidgetItem *sinkItem;
    QTreeWidgetItem *junctionItem;
    QTreeWidgetItem *flowlineItem;

//    int wellColNum = 0;
//    int sourceColNum = 0;
//    int sinkColNum = 0;

    QIcon wellIcon;
    QIcon sourceIcon;
    QIcon sinkIcon;
    QIcon junctionIcon;
    QIcon flowlineIcon;
    QFont font;
};

#endif // TTREEWIDGET_H

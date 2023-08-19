#ifndef TTABWIDGET_H
#define TTABWIDGET_H

#include <QTabWidget>
#include <QObject>

class TTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TTabWidget(QWidget *parent = nullptr);
};

#endif // TTABWIDGET_H

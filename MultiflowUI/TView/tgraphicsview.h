#ifndef TGRAPHICSVIEW_H
#define TGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>

#include "TView/mulitem.h"

class TGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    TGraphicsView(QWidget *parent = nullptr);

    QString getScale() const;
    void setScale(QString newScale);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;


private:
    QString m_scale;

};

#endif // TGRAPHICSVIEW_H

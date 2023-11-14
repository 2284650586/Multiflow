#ifndef TGRAPHICSVIEW_H
#define TGRAPHICSVIEW_H

#include "tgraphicsscene.h"

#include <QGraphicsView>
#include <QObject>

#include "TView/mulitem.h"

class TGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit TGraphicsView(QWidget* parent = nullptr);

    [[nodiscard]] QString getScale() const;

    void setScale(QString newScale);

    [[nodiscard]] TGraphicsScene* scene() const;

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QString m_scale;
};

#endif // TGRAPHICSVIEW_H

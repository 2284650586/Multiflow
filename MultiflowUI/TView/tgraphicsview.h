#pragma once

#include "MGraphicsScene.hpp"

#include <QGraphicsView>
#include <QObject>

class TGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit TGraphicsView(QWidget* parent = nullptr);

    [[nodiscard]] QString getScale() const;

    void setScale(QString newScale);

    [[nodiscard]] MGraphicsScene* scene() const;

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QString m_scale;
};

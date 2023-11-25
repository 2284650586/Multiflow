#pragma once

#include "MGraphicsScene.hpp"

#include <QGraphicsView>

class MGraphicsView final : public QGraphicsView {
    Q_OBJECT

public:
    explicit MGraphicsView(QWidget* parent = nullptr);

    [[nodiscard]] QString getScale() const;

    void setScale(const QString& newScale);

    [[nodiscard]] MGraphicsScene* scene() const;

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QString _scale;
};

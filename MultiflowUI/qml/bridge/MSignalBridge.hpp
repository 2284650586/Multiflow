#pragma once

#include <QObject>
#include <QVariant>

class MSignalBridge final : public QObject {
    Q_OBJECT

public:
    explicit MSignalBridge(QObject* parent = nullptr);

signals:
    void onDataChanged(QVariant data);
};

Q_DECLARE_METATYPE(MSignalBridge)

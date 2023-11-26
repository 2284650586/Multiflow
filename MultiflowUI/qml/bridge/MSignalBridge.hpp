#pragma once

#include <QObject>
#include <QVariant>

class MSignalBridge final : public QObject {
    Q_OBJECT

public:
    explicit MSignalBridge(QObject* parent = nullptr);

    bool isConnected(const QMetaMethod &signal) const;

signals:
    void onDataChanged(QVariant data);
    void onOpenBlackOilManager();
};

Q_DECLARE_METATYPE(MSignalBridge)

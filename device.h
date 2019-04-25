#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

class Device : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString address READ address NOTIFY deviceInfoChanged)
public:
    explicit Device();
    explicit Device(const QBluetoothDeviceInfo &deviceInfo);
    virtual ~Device() override;

    QBluetoothDeviceInfo *deviceInfo() const;
    void setDeviceInfo(const QBluetoothDeviceInfo &deviceInfo);

    QString name() const;
    QString address() const;

signals:
    void deviceInfoChanged();

private:
    QScopedPointer<QBluetoothDeviceInfo> m_deviceInfo;
};

#endif // DEVICE_H

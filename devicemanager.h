#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include <QVector>
#include <QBluetoothDeviceDiscoveryAgent>

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

QT_FORWARD_DECLARE_CLASS(Device)
typedef QSharedPointer<Device> DevicePointer;

class DeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)
    Q_PROPERTY(int deviceCount READ deviceCount NOTIFY devicesUpdated)

public:
    explicit DeviceManager(QObject *parent = nullptr);
    virtual ~DeviceManager() override;

    QString info() const;
    int deviceCount() const;

    Q_INVOKABLE QVariant device(int index) const;

    Q_INVOKABLE void startScanning();

public slots:
    void setInfo(QString info);

private slots:
    void addDevice(const QBluetoothDeviceInfo &deviceInfo);
    void scanningFinished();
    void scanningError(QBluetoothDeviceDiscoveryAgent::Error error);

signals:
    void infoChanged(QString info);
    void devicesUpdated();

private:
    QScopedPointer<QBluetoothDeviceDiscoveryAgent> m_discoveryAgent;
    QVector<DevicePointer> m_devices;
    QString m_info;
};

#endif // DEVICEMANAGER_H

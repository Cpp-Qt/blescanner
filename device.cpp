#include "device.h"

#include <QBluetoothDeviceInfo>
#include <QBluetoothAddress>
#include <QBluetoothUuid>

Device::Device() : QObject()
{
}

Device::Device(const QBluetoothDeviceInfo &deviceInfo) :
    QObject(),
    m_deviceInfo(new QBluetoothDeviceInfo(deviceInfo))
{
}

Device::~Device()
{
}

QBluetoothDeviceInfo *Device::deviceInfo() const
{
    return m_deviceInfo.data();
}

void Device::setDeviceInfo(const QBluetoothDeviceInfo &deviceInfo)
{
    m_deviceInfo.reset(new QBluetoothDeviceInfo(deviceInfo));
    emit deviceInfoChanged();
}

QString Device::name() const
{
    return m_deviceInfo ? m_deviceInfo->name() : "";
}

QString Device::address() const
{
#ifdef Q_OS_DARWIN
    return m_deviceInfo ? m_deviceInfo->deviceUuid().toString() : "";
#else
    return m_deviceInfo ? m_deviceInfo->address().toString() : "";
#endif // Q_OS_MACOS
}

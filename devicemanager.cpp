#include "devicemanager.h"

#include <QBluetoothDeviceInfo>
#include <QMetaEnum>

#include <device.h>

DeviceManager::DeviceManager(QObject *parent) :
    QObject(parent),
    m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent())
{
    m_discoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    connect(m_discoveryAgent.data(), &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &DeviceManager::addDevice);
    connect(m_discoveryAgent.data(), &QBluetoothDeviceDiscoveryAgent::finished,
            this, &DeviceManager::scanningFinished);
    connect(m_discoveryAgent.data(), QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &DeviceManager::scanningError);
}

DeviceManager::~DeviceManager()
{
}

QString DeviceManager::info() const
{
    return m_info;
}

void DeviceManager::setInfo(QString info)
{
    if (m_info == info)
        return;

    m_info = info;
    emit infoChanged(m_info);
}

void DeviceManager::addDevice(const QBluetoothDeviceInfo &deviceInfo)
{
    if (deviceInfo.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        auto device = DevicePointer::create(deviceInfo);
        m_devices.append(device);
        setInfo(tr("Last device updated: %1").arg(device->name()));
    }
}

void DeviceManager::scanningFinished()
{
    emit devicesUpdated();
    if (m_devices.isEmpty()) {
        setInfo(tr("No BLE devices found!"));
    } else {
        setInfo(tr("Scanning finished!"));
    }
}

void DeviceManager::scanningError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    switch (error) {
    case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
        setInfo(tr("BT adapter powered off. Cannot discover devices."));
        break;
    case QBluetoothDeviceDiscoveryAgent::InputOutputError:
        setInfo(tr("Read/write device error."));
        break;
    default: {
        auto metaObject = m_discoveryAgent->metaObject();
        auto metaEnum = metaObject->enumerator(metaObject->indexOfEnumerator("Error"));
        setInfo(tr("Error: %1").arg(QString::fromLatin1(metaEnum.valueToKey(error))));
        break;
    }
    }
}

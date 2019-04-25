import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
    width: 600
    height: 400

    title: qsTr("Device list")

    property int deviceCount: -1
    onDeviceCountChanged: {
        console.log("Devices found:", deviceCount)
        defaultModel.clear()
        if (deviceCount > 0) {
            for (var i = 0; i < deviceCount; ++i) {
                var device = deviceManager.device(i)
                console.log("Device:", device)
                defaultModel.append(device)
            }
        }
    }

    ListModel {
        id: defaultModel
    }

    ListView {
        id: list
        anchors.fill: parent
        model: defaultModel
        spacing: 15
        delegate: ItemDelegate {
            width: parent.width
            height: 80
            ColumnLayout {
                anchors.fill: parent
                Label {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    text: model.name
                    font.pixelSize: 35
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Label {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 25
                    text: model.address
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}

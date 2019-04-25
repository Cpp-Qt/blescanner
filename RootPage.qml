import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
    width: 600
    height: 400

    title: qsTr("Devices list")

    /*Label {
        text: qsTr("You are on the home page.")
        anchors.centerIn: parent
    }*/

    ListModel {
        id: defaultModel
        ListElement {
            deviceId: 1
            name: "Device 1"
            deviceAddress: "00:00:00:00:00"
            description: "Description 1"
        }
        ListElement {
            deviceId: 2
            name: "Device 2"
            deviceAddress: "00:00:00:00:00"
            description: "Description 2"
        }
        ListElement {
            deviceId: 3
            name: "Device 3"
            deviceAddress: "00:00:00:00:00"
            description: "Description 3"
        }
        ListElement {
            deviceId: 4
            name: "Device 4"
            deviceAddress: "00:00:00:00:00"
            description: "Description 4"
        }
        ListElement {
            deviceId: 5
            name: "Device 5"
            deviceAddress: "00:00:00:00:00"
            description: "Description 5"
        }
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
                    Layout.preferredHeight: 15
                    text: model.description
                    font.pixelSize: 10
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Label {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 25
                    text: deviceAddress
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}

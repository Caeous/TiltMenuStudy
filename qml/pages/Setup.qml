import QtQuick 2.10
import QtQuick.Controls 2.0

Item {
    id : root

    signal beginStudy()
    property alias participantId: participantIdEdit.text

    Column {
        anchors.centerIn: parent
        spacing: 20

        Row {
            id: rowId

            Text {
                id: participantIdLabel
                text: "Id: "
                font.family: "Helvetica"
                font.pointSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                width: 240
                height: 40
                color: "transparent"
                border.color: "gray"
                border.width: 1
                anchors.verticalCenter: parent.verticalCenter

                Item {
                    anchors.fill: parent
                    anchors.margins: 5

                    TextInput {
                        id: participantIdEdit
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 5
                        font.family: "Helvetica"
                        font.pointSize: 20
                        color: "blue"
                        focus: true
                    }
                }
            }
        }

        Button {
            width: rowId.width
            height: 40
            text: "Begin study"
            onClicked: {
                root.beginStudy()
            }
        }
    }
}

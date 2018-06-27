import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    id: root

    property string textA: "A"
    property string textB: "B"

    property int borderWidth: 20

    Circle {
        id: borderCircle

        width: root.width
        height: root.width

        color: Qt.rgba(160/255, 217/255, 255/255, 1.0)

        Circle {
            id: fillCircle

            x: root.borderWidth
            y: root.borderWidth

            width: parent.width - root.borderWidth*2
            height: parent.width - root.borderWidth*2

            color: Qt.rgba(214/255, 238/255, 1.0, 1.0)
        }

        Rectangle {
            id: divider

            x: 0
            y: parent.height/2
            width: parent.width
            height: 2

            color: "gray"
        }

        ColumnLayout {
            anchors.fill: parent

            ZoneText {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: root.textA
            }

            ZoneText {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: root.textB
            }
        }
    }
}

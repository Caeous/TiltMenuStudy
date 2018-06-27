import QtQuick 2.0

Item {
    id: root

    property alias text: zoneText.text
    property color color: "black"

    Text {
        id: zoneText

        color: root.color
        minimumPointSize: 10
        font.pointSize: 20
        fontSizeMode: Text.Fit
        anchors.alignWhenCentered: true
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: parent.width < parent.height ? parent.width : parent.height
        height: width
        wrapMode: Text.WordWrap
    }
}

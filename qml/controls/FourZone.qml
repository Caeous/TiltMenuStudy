import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    id: root

    property string textA: "A"
    property string textB: "B"
    property string textC: "C"
    property string textD: "D"

    property real centreX: width / 2;
    property real centreY: height / 2;

    property int borderWidth: 20

    Rectangle {
        id: borderRect

        color: Qt.rgba(160/255, 217/255, 255/255, 1.0)

        anchors.fill: parent

        Rectangle {
            id: fillRect

            x: root.borderWidth
            y: root.borderWidth

            width: parent.width - root.borderWidth*2
            height: parent.height - root.borderWidth*2

            color: Qt.rgba(214/255, 238/255, 1.0, 1.0)

            Item {
                x: parent.width/4
                y: 0
                width: parent.width/2
                height: parent.height/4

                ZoneText {
                    anchors.fill: parent
                    text: root.textA
                }
            }

            Item {
                x: parent.width*3/4
                y: parent.height/4
                width: parent.width/4
                height: parent.height/2

                ZoneText {
                    anchors.fill: parent
                    text: root.textB
                }
            }

            Item {
                x: parent.width/4
                y: parent.height*3/4
                width: parent.width/2
                height: parent.height/4

                ZoneText {
                    anchors.fill: parent
                    text: root.textC
                }
            }

            Item {
                x: 0
                y: parent.height/4
                width: parent.width/4
                height: parent.height/2

                ZoneText {
                    anchors.fill: parent
                    text: root.textD
                }
            }
        }

        Canvas {
            id: canvas

            anchors.fill: parent

            property string dividerStrokeStyle: "gray"

            onPaint: {
                var ctx = canvas.getContext('2d');

                ctx.reset();

                // Divider line
                ctx.lineWidth = 2;
                ctx.strokeStyle = dividerStrokeStyle
                ctx.beginPath()
                ctx.moveTo(0, 0);
                ctx.lineTo(width, height)
                ctx.closePath()
                ctx.stroke()

                // Divider line
                ctx.lineWidth = 2;
                ctx.strokeStyle = dividerStrokeStyle
                ctx.beginPath()
                ctx.moveTo(0, height);
                ctx.lineTo(width, 0)
                ctx.closePath()
                ctx.stroke()
            }
        }

    }
}

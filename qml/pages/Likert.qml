import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id : root

    signal endStudy()
    property alias value: slider.value

    Column {
        anchors.centerIn: parent
        spacing: 20

        Column {
            id: columnId

            Text {
                id: participantIdLabel
                text: "Please rate the overall ease of use\nof the design on a Likert 7-point scale."
                font.family: "Helvetica"
                font.pointSize: 20
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Slider {
                id: slider
                width: participantIdLabel.width
                value: 4
                to: 7
                from: 1
                snapMode: Slider.SnapAlways
                stepSize: 1
            }
        }

        Button {
            width: participantIdLabel.width
            height: 40
            text: "Accept"
            onClicked: {
                root.endStudy()
                slider.value = 4
            }
        }
    }
}

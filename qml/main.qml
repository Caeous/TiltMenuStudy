import QtQuick 2.10
import QtQuick.Controls 1.4
import QtQuick.Window 2.10
import "qrc:/qml/controls/"
import "qrc:/qml/pages/"
import com.thalmic.TiltMenuModel 1.0
import com.thalmic.TiltMenuOptionsModel 1.0
import QtSensors 5.0

Window {
    id: root
    visible: true
    title: qsTr("Tilt Menu Study")

    property int trialCount: 0

    TiltMenuOptionsModel {
        id: tiltMenuOptionsModel
    }

    TiltMenuModel {
        id: tiltMenuModel
        participantId: ""
        width: root.width/2
        x: root.width/2
        y: root.height/2
        isTwoZone: false
        tiltMenuOptionsModel: tiltMenuOptionsModel
    }

    TiltSensor {
        id: tiltSensor
        active: true
    }

    // Timer to read out the x and y rotation of the TiltSensor
    Timer {
        id: tiltTimer
        interval: tiltMenuModel.intervalMs
        running: area.pressed
        repeat: true

        onTriggered: {
            tiltMenuModel.setXRotation(tiltSensor.reading.xRotation * 0.3);
            tiltMenuModel.setYRotation(tiltSensor.reading.yRotation * 0.3);
        }
    }

    Item {
        visible: tiltMenuModel.participantId != "" && tiltMenuModel.targetsRemaining > 0
        anchors.fill: parent

        Text {
            id: targetMenuOption
            text: tiltMenuModel.targetMenuOption
            font.pointSize: 30
            font.bold: true
            color: "gray"
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item {
            id: zoneArea
            width: tiltMenuModel.width
            height: width
            anchors.centerIn: parent

            TwoZone {
                id: twoZone
                anchors.fill: parent
                visible: tiltMenuModel.isTwoZone
                textA: tiltMenuOptionsModel.textA
                textB: tiltMenuOptionsModel.textB
                borderWidth: tiltMenuModel.borderWidth
            }

            FourZone {
                id: fourZone
                anchors.fill: parent
                visible: !tiltMenuModel.isTwoZone
                textA: tiltMenuOptionsModel.textA
                textB: tiltMenuOptionsModel.textB
                textC: tiltMenuOptionsModel.textC
                textD: tiltMenuOptionsModel.textD
                borderWidth: tiltMenuModel.borderWidth
            }
        }

        Circle {
            x: tiltMenuModel.x - width/2
            y: tiltMenuModel.y - height/2
            width: tiltMenuModel.borderWidth
            height: tiltMenuModel.borderWidth
        }

        Text {
            id: participantId
            color: "gray"
            text: tiltMenuModel.participantId
            font.pointSize: 30
            font.bold: true
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }

        Text {
            id: targetsRemaining
            color: "gray"
            text: (8 - tiltMenuModel.targetsRemaining) + "/8"
            font.pointSize: 30
            font.bold: true
            anchors.bottom: parent.bottom
            anchors.right: parent.right
        }

        MouseArea {
            id: area
            anchors.fill: parent

            onReleased: {
                tiltMenuModel.resetNavigation()
            }
        }
    }

    Setup {
        id: setup
        anchors.fill: parent
        visible: tiltMenuModel.participantId === ""
        onBeginStudy: {
            tiltMenuModel.setId(setup.participantId)
            tiltMenuModel.startNewTrial()
        }
    }

    Likert {
        id: likert
        anchors.fill: parent
        visible: tiltMenuModel.participantId != "" && tiltMenuModel.targetsRemaining === 0
        onEndStudy: {
            tiltMenuModel.setLikert(likert.value)
            tiltMenuModel.endTrial()

            root.trialCount++

            if (root.trialCount > 1) {
                // Do not switch the model variants to counterbalance and avoid order bias
                root.trialCount = 0
                tiltMenuModel.setId("")
            } else {
                tiltMenuModel.setIsTwoZone(!tiltMenuModel.isTwoZone)
            }

            tiltMenuModel.startNewTrial()
        }
    }
}

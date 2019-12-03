 import QtQuick 2.9
//import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QmlVTK 1.0

ApplicationWindow {
    id: root
    visible: true
    minimumWidth: 1024
    minimumHeight: 768
    title: qsTr("QmlVTKInteractor")

    Material.primary: Material.Indigo
    Material.accent: Material.LightBlue

    Rectangle {
        id: vtkViewer
        width: 200
        height: 200
        anchors.right: parent.right
        color: "red"

        Interactor {
            id: interactor
            objectName: "interactor"
            Text{
                text: "interactor is here"
            }

            anchors.fill: parent
            MouseArea{
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                anchors.fill: parent
                onPressed:{
                    mainWindow.mousePressHandler(pressedButtons, mouseX, mouseY);
                    mouse.accepted = false
                }
            }

        }



    }


    TextField {
        id: textField
        text: "Edit me"
        anchors {
            top: parent.top
            left: parent.left
        }
    }

    Label {
        text: {
            var x = textField.text
            return "(" + x + ")"
        }
        anchors {
            top: textField.bottom
            topMargin: 20
            left: parent.left
        }
    }
}

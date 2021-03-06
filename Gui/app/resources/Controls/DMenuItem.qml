import QtQuick 2.9
import QtQuick.Controls 2.3

import DNAI 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0
import Dnai.Theme 1.0

import "../Style"

MenuItem {
    id: control

    signal buttonPressed()

    property alias iconItem: _icon

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 6



    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onPressed: {
            if (control.enabled) {
                control.buttonPressed()
                action.trigger()
            }
        }
    }

    contentItem: Item {

        Row {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 4
            LabelAwesomeSolid {
                id: _icon
                verticalAlignment: Text.AlignVCenter
                height: txt.implicitHeight
                width: txt.implicitHeight
                anchors.leftMargin: 4
                color: control.enabled ? AppSettings.theme["text"]["color"] : AppSettings.theme["text"]["disableColor"]
            }
            Label {
                id: txt
                leftPadding: control.checkable && !control.mirrored ? control.indicator.width + control.spacing : 0
                rightPadding: control.checkable && control.mirrored ? control.indicator.width + control.spacing : 0

                text: control.text
                color: control.enabled ? AppSettings.theme["text"]["lightColor"] : AppSettings.theme["text"]["disableColor"]
                elide: Text.ElideRight
                visible: control.text
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }
    }


    indicator: Image {
        x: control.mirrored ? control.width - width - control.rightPadding : control.leftPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        visible: control.checked
        source: control.checkable ? "qrc:/qt-project.org/imports/QtQuick/Controls.2/images/check.png" : ""
    }

    background: Item {
        implicitWidth: 200
        implicitHeight: txt.implicitHeight * 1.4
        Rectangle {
            id: backgroundId
            x: 1
            y: 1
            width: parent.width - 2
            height: parent.height - 2
            color: control.pressed ? AppSettings.theme["colors"]["background"]["dark"] : control.hovered ? AppSettings.theme["colors"]["background"]["light"] : "transparent"

        }
    }
}

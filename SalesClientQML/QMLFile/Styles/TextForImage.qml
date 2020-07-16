import QtQuick 2.12

import QtGraphicalEffects 1.0
Text {
    property int size: 15

    anchors{
        fill: parent
        margins: mainView.dp(5)
    }

    horizontalAlignment: Text.AlignHCenter

    font.bold: true
    style: Text.Outline

    fontSizeMode: Text.HorizontalFit
    minimumPointSize: 8
    font.pointSize: size
}

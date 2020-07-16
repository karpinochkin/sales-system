import QtQuick 2.12

Rectangle {
    property string buttonText

    width: mainView.dp(140)
    height: mainView.dp(40)

    opacity: 1
    color: "#518dbb"
    border.width: mainView.dp(1)
    border.color: "#518dbb"
    radius: mainView.dp(2)
    // Сглаживание включено
    smooth: true

    Text {
        text: buttonText
        color: "white"
        anchors.centerIn: parent
        font.pointSize: 12
    }

}

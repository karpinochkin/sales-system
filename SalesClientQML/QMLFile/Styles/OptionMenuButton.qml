import QtQuick 2.12

Rectangle {
    property string textForButton

    width: layoutForOptions.width/3.3
    height: layoutForPointSaleId.height * 1.5

    opacity: 1
    color: "#518dbb"
    border.width: mainView.dp(1)
    border.color: "#518dbb"
    radius: mainView.dp(2)
    // Сглаживание включено
    smooth: true

    TextForButton {
        text: textForButton
        height: parent.height
        size: 15
    }

}


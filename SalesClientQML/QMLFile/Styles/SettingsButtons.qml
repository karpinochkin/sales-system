import QtQuick 2.12

Rectangle {
property string textForButton
    width: layoutForOptions.width/3.5
    height: layoutForPointSaleId.height

    TextForButton {
        text: textForButton
        height: parent.height
        size: 15
    }
}


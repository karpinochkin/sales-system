import QtQuick 2.12
import "qrc:/QMLFile/Styles"

Component {
    Rectangle {
        width: orderListView.width
        height: mainView.dp(90)
        color: "transparent"

        MouseArea {
            id: mouseItemOrderDelegateChange
            anchors.fill: parent

            onClicked: {
                mainView.prepareToOpenSelectionView(index, idProduct, idCategory, true)
            }
        }

        Rectangle {
            anchors{
                fill: parent
                margins: mainView.dp(2)
            }

            color: "#518dbb"
            opacity: 0.95

            border.width: mainView.dp(2)
            border.color: colorCode
            radius: mainView.dp(3)

            Rectangle {
                id: colorCategoryLay
                anchors{
                    left: parent.left
                    leftMargin: mainView.dp(5)
                    verticalCenter: parent.verticalCenter
                }
                height: parent.height/4
                width: height

                radius: height/2

                color: colorCategory
                border.width: mainView.dp(1)
                border.color: Qt.lighter(color)
            }

            Image {
               id:image
               anchors{
                   verticalCenter: parent.verticalCenter
                   right:parent.right
                   rightMargin: mainView.dp(2)
               }

               width: parent.height/1.3
               height: parent.height/1.3

               source: "qrc:/Image/cross-for-del.png"
               fillMode: Image.PreserveAspectFit
               smooth: true

               visible: true
               scale: mouseItemOrderDelegateDelete.pressed ? 0.9 : 1

               MouseArea {
                   id: mouseItemOrderDelegateDelete
                   anchors.fill: parent

                   onClicked: {
                       orderListModel.remove(index)
                       mainView.totalSumOrder()
                   }
               }
            }

            Rectangle {
                anchors{
                    top: parent.top
                    bottom: parent.bottom
                    left: colorCategoryLay.right
                    right: image.left
                    leftMargin: mainView.dp(5)
                }

                color: "transparent"

                TextForButton {
                    anchors.top: parent.top
                    anchors.topMargin: mainView.dp(2)
                    height: mainView.dp(25)
                    id: nameCoffe
                    text: name
                }

                TextForButton {
                    anchors.top: nameCoffe.bottom
                    anchors.topMargin: mainView.dp(6)
                    height: mainView.dp(25)

                    id: textVolume

                    text: stringSize
                    size: 15
                }

                TextForButton {
                    anchors.top: textVolume.bottom
                    id: textPrice

                    text: stringCost
                    size: 15
                }
            }
        }
    }
}

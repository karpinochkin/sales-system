import QtQuick 2.12
import "qrc:/QMLFile/Delegates"
import "qrc:/QMLFile/Styles"

Rectangle {
    id: reportView
    anchors.fill: parent    

    Connections {
        target: middlewareQML

        onSignalReceiptsCreate: {
             listReceiptModel.append({countReceipt:      qmlProperty.countReceipt,
                                      countProductsString: qmlProperty.countProductsString,
                                      sumReceiptString:  qmlProperty.sumReceiptString,
                                      dateReceiptString: qmlProperty.dateReceiptString,
                                      idReceipt:         qmlProperty.idReceipt})
        }

        onSignalFillSomePropertyInReportView:{
            currentUser.text = "открыта "+qmlProperty.openData
            cashSum.text =    qmlProperty.cashString
            nonCashSum.text = qmlProperty.nonCashString
            freeSum.text =   qmlProperty.freeString
        }

        onSignalSoldPositionsCreate:{
                listSoldPositionModel.append({nameProductString: qmlProperty.nameProductString,
                                              priceString:     qmlProperty.priceString,
                                              volumeString:    qmlProperty.volumeString,
                                              categoryString:  qmlProperty.categoryString,
                                              idProduct:         qmlProperty.idProduct,
                                              colorCode:       qmlProperty.colorCode})
        }
    }


    Image {
        anchors.fill: parent
        source: "qrc:/Image/backgroundForLogin.jpg"
        fillMode: Image.PreserveAspectCrop
        smooth: true
    }

    MouseArea {
        anchors.fill: parent
    }

    Rectangle {
        anchors{
            fill: parent
            margins: mainView.dp(10)
        }

        color: "transparent"

        Text {
            id: reportTitle
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            z: 1
            height: mainView.dp(30)

            horizontalAlignment: Text.AlignHCenter

            text:qsTr("Отчет по текущей смене")
            color: "white"
            style: Text.Outline
            font.bold: true
            styleColor: Qt.lighter("black")
            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 10
            font.pointSize: 26
        }

        Text {
            id: currentUser
            anchors{
                top: reportTitle.bottom
                topMargin: mainView.dp(10)
                left: parent.left
                right: parent.right
            }
            z: 1
            height: mainView.dp(20)

            horizontalAlignment: Text.AlignHCenter

            color: "white"
            style: Text.Outline
            font.bold: true
            styleColor: Qt.lighter("black")
            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 10
            font.pointSize: 18
        }

        Rectangle {
            id:layForTitleReport
            anchors{
                top: parent.top
                horizontalCenter: reportTitle.horizontalCenter
            }
            width: (reportTitle.contentWidth > currentUser.contentWidth ? reportTitle.contentWidth : currentUser.contentWidth) + mainView.dp(15)
            height: reportTitle.contentHeight + currentUser.contentHeight + mainView.dp(15)

            radius: mainView.dp(3)
            color: Qt.rgba(0,0,0,0.5)
        }

        Rectangle {
            id: layoutForReceiptListView
            anchors{
                left: parent.left
                right: parent.horizontalCenter
                top: layForTitleReport.bottom
                bottom: layoutForTotalSum.top
                margins: mainView.dp(7)
            }

            radius: mainView.dp(3)
            color: "#293a4c"
            border.width: mainView.dp(1)
            border.color: "#518dbb"

            Text {
                id: listReceiptTitle
                anchors{
                    top: parent.top
                    topMargin: mainView.dp(5)
                    horizontalCenter: parent.horizontalCenter
                }
                text: qsTr("Чеки")
                font.pointSize: 20
                color: "white"
            }

              GridView {
                  id: receiptGridView
                  anchors{
                      fill: parent
                      margins: mainView.dp(5)
                      topMargin: listReceiptTitle.contentHeight + mainView.dp(5)
                  }

                  snapMode: GridView.SnapOneRow

                  cellWidth: getCellSizeForGridView()
                  cellHeight: cellWidth

                  clip: true

                  delegate: MyItemForReceiptList{}

                  model: ListModel { id: listReceiptModel }
              }
          }

        Rectangle {
            id: layoutForSoldPositonListView
            anchors{
                left: parent.horizontalCenter
                right: parent.right
                top: layForTitleReport.bottom
                bottom: layoutForTotalSum.top
                margins: mainView.dp(7)
            }

            radius: mainView.dp(3)
            color: "#293a4c"
            border.width: mainView.dp(1)
            border.color: "#518dbb"

            Text {
                id: soldPositionTitle
                anchors{
                    top: parent.top
                    topMargin: mainView.dp(5)
                    horizontalCenter: parent.horizontalCenter
                }

                horizontalAlignment: Text.AlignHCenter

                color: "white"
                text: qsTr("Проданные товары")
                width: parent.width
                fontSizeMode: Text.HorizontalFit
                minimumPointSize: 8
                font.pointSize: 20
            }

            GridView {
                id: soldPositionGridView
                anchors{
                    fill: parent
                    margins: mainView.dp(5)
                    topMargin: listReceiptTitle.contentHeight + mainView.dp(5)
                }

                snapMode: GridView.SnapOneRow

                cellWidth: getCellSizeForSoldPosition()
                cellHeight: cellWidth*0.9

                clip: true

                delegate: MyItemForSoldPositionList{}

                model: ListModel { id: listSoldPositionModel }
            }
        }

        Rectangle {
            id: layoutForTotalSum
            anchors{
                left: parent.left
                bottom: parent.bottom
                leftMargin: mainView.dp(7)
            }

            width: layoutForReceiptListView.width
            height: mainView.dp(75)
            color: Qt.rgba(0,0,0,0.5)
            radius: mainView.dp(3)

            Text {
                id: cashSum
                anchors{
                    top: parent.top
                    left: parent.left
                    leftMargin: mainView.dp(10)
                    topMargin: mainView.dp(1)
                }
                width: layoutForTotalSum.width

                color: "white"
                style: Text.Outline
                font.bold: true
                styleColor: Qt.lighter("black")
                fontSizeMode: Text.HorizontalFit
                minimumPointSize: 8
                font.pointSize: 15
            }

            Text {
                id: nonCashSum
                anchors{
                    top: cashSum.bottom
                    left: parent.left
                    leftMargin: mainView.dp(10)
                    topMargin: mainView.dp(1)
                }
                width: layoutForTotalSum.width

                color: "white"
                style: Text.Outline
                font.bold: true
                styleColor: Qt.lighter("black")
                fontSizeMode: Text.HorizontalFit
                minimumPointSize: 8
                font.pointSize: 15
            }

            Text {
                id: freeSum
                anchors{
                    top: nonCashSum.bottom
                    left: parent.left
                    leftMargin: mainView.dp(10)
                    topMargin: mainView.dp(1)
                }
                width: layoutForTotalSum.width/2

                color: "white"
                style: Text.Outline
                font.bold: true
                styleColor: Qt.lighter("black")
                fontSizeMode: Text.HorizontalFit
                minimumPointSize: 8
                font.pointSize: 15
            }

        }

        Rectangle {
            id: layoutForOkButton
            anchors{
                right: parent.right
                bottom: parent.bottom
                rightMargin: mainView.dp(7)
            }
            width: acceptText.width + mainView.dp(10)
            height: layoutForTotalSum.height

            color: "#518dbb"
            border.width: mainView.dp(1)
            border.color: "#518dbb"
            radius: mainView.dp(3)

            Text {
                id: acceptText
                anchors.centerIn: parent
                text: qsTr("Принять")
                color: "white"
                font.pointSize: 24
            }

            MouseArea {
                id: okOnReportViewMouseArea
                anchors.fill: parent

                onClicked:{
                    loaderReportView.state = "State1"
                    listSoldPositionModel.clear()
                    listReceiptModel.clear()
                    soldPositionTitle.text = qsTr("Проданные товары")
                }
            }
            scale: okOnReportViewMouseArea.pressed ? 0.9 : 1.0
        }
    }

    function openSoldPosition(numberReceipt, idReceipt)
    {
        soldPositionTitle.text = qsTr("Проданные товары по чеку № ") + numberReceipt

        listSoldPositionModel.clear()
        middlewareQML.fillSoldPositions(idReceipt)
    }

    property int countCellGridForOneRow: receiptGridView.width/mainView.dp(140)

    function getCellSizeForGridView()
    {
        return countCellGridForOneRow!=0 ? receiptGridView.width/countCellGridForOneRow : receiptGridView.width
    }

    property int countCellGridForSoldPosition: soldPositionGridView.width/mainView.dp(165)

    function getCellSizeForSoldPosition()
    {
        return countCellGridForSoldPosition!=0 ? soldPositionGridView.width/countCellGridForSoldPosition : soldPositionGridView.width
    }
}

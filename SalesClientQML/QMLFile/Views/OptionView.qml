import QtQuick 2.12
import QtQuick.Dialogs 1.3
import "qrc:/QMLFile/Delegates"
import "qrc:/QMLFile/Delegates/Highlighters"
import "qrc:/QMLFile/Styles"


Rectangle {
    id: optrionView
    anchors.fill: parent

    property bool portHaveError: false
    property int currentIdPoinSale

    Connections {
        target: middlewareQML


        onSignalHostPortCreate: {
            hostAndPortListModel.append({ host: qmlProperty.address,
                                            port: qmlProperty.port })
        }

        onSignalPortInvalid: {
            portHaveError = true
        }
    }


    Image {
        anchors.fill: parent
        source: "qrc:/Image/backgroundForLogin.jpg"
        fillMode: Image.PreserveAspectCrop
        smooth: true
    }

    Rectangle {
        id: mainLayForOptions
        anchors{
            fill: parent
            margins: mainView.dp(15)
        }

        color: "transparent"

        Row {
            id: rowTitle
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: mainView.dp(10)
                bottomMargin: mainView.dp(10)
            }

            spacing: mainView.dp(50)

            Text {
                id: optionTitle

                height: optionTitle.contentHeight

                horizontalAlignment: Text.AlignHCenter

                text:qsTr("Настройки")
                color: "white"
                style: Text.Outline
                font.bold: true
                styleColor: Qt.lighter("black")
                fontSizeMode: Text.HorizontalFit
                minimumPointSize: 10
                font.pointSize: 26
            }

            Rectangle {
                id: layoutForPointSaleId
                width: pointSale.width + (idPoinSaleName.width / 2)
                height: optionTitle.height

                color: "#293a4c"
                opacity: 0.6

                radius: mainView.dp(2)
                border.width: mainView.dp(1)
                border.color: "#518dbb"

                Text {
                    id: pointSale
                    anchors.horizontalCenter: layoutForPointSaleId.horizontalCenter
                    anchors.verticalCenter: layoutForPointSaleId.verticalCenter

                    text:qsTr("ID точки продаж: ")
                    color: "white"
                    style: Text.Outline
                    font.bold: true
                    styleColor: Qt.lighter("black")
                    fontSizeMode: Text.HorizontalFit
                    minimumPointSize: 10
                    font.pointSize: 15
                }

                TextInput {
                    id: idPoinSaleName
                    width: pointSale.width
                    wrapMode: Text.WrapAnywhere
                    color: "white"
                    font.bold: true
                    font.pointSize: 15
                    anchors.verticalCenter: layoutForPointSaleId.verticalCenter
                    anchors.left: pointSale.right
                    anchors.leftMargin:  mainView.dp(5)


                    property bool enterPress

                    onAccepted: {
                        enterPress = true
                    }

                    onTextEdited: {
                        if ( idPoinSaleName.text.length !== 0 )
                            if(enterPress)
                            {
                                if ((idPoinSaleName.text.length-1 === port.length) || (idPoinSaleName.text.length+1 === port.length))
                                {
                                    currentIdPoinSale = idPoinSaleName.text
                                    enterPress = false
                                }
                            }
                            else
                            {
                                currentIdPoinSale = idPoinSaleName.text
                            }
                    }
                }
            }
        }



        Rectangle {
            id: layoutForOptions
            y: optionTitle.contentHeight+mainView.dp(20)
            width: parent.width
            height: mainView.height - y - layoutForOptionsButton.height - mainView.dp(40)
            opacity: 0.96
            color: "#293a4c"
            radius: mainView.dp(3)
            border.color: "#518dbb"
            border.width: mainView.dp(1)
            anchors.bottomMargin: 10

            ListView {
                id: hostAndPortListView
                anchors{
                    fill: parent
                    margins: mainView.dp(5)
                }

                boundsBehavior: Flickable.StopAtBounds
                clip: true

                delegate: MyItemForHostAndPortList { }

                model: ListModel{ id: hostAndPortListModel }
            }

            Component.onCompleted: {
                middlewareQML.fillHostPortFromSetings()
                middlewareQML.getIdPointSaleFromSettings()
                idPoinSaleName.text = qmlProperty.idPointSaleInOptions
            }
        }
        Rectangle {
            id: layoutForOptionsButton
            width: layoutForOptions.width
            height:layoutForPointSaleId.height
            color: Qt.rgba(0, 0, 0, 0)
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
            }

            OptionMenuButton {
                anchors.left: layoutForOptionsButton.left
                textForButton: qsTr("Добавить")

                MouseArea {
                    id: addButtonArea
                    anchors.fill: parent
                    onClicked: {
                        hostAndPortListModel.append({ host: "",
                                                        port: "" })
                    }
                }
                scale: addButtonArea.pressed ? 0.9 : 1.0
            }

            OptionMenuButton {
                anchors.horizontalCenter: layoutForOptionsButton.horizontalCenter
                textForButton: qsTr("Назад")

                MouseArea {
                    id: resetButtonArea
                    anchors.fill: parent
                    onClicked: {
                        middlewareQML.getLoginFromSettings()
                        loaderSelectionForOrder.setSource("LoginView.qml")
                    }
                }
                scale: resetButtonArea.pressed ? 0.9 : 1.0
            }
            OptionMenuButton {
                anchors.right: layoutForOptionsButton.right
                textForButton: qsTr("Сохранить")

                MouseArea {
                    id: exitButtonArea
                    anchors.fill: parent
                    onClicked: {
                        saveDataMessage.open()
                    }
                }
                scale: exitButtonArea.pressed ? 0.9 : 1.0
            }
        }
    }

    MessageDialog {
        id: errorMessage
        title: qsTr("Ошибка")
        text:  qsTr("В одном из соединений порт введен неправильно")
        standardButtons: StandardButton.Ok
    }

    MessageDialog {
        id: saveDataMessage
        title: qsTr("Сохранение данных")
        text:  qsTr("Вы уверены что хотите сохранить изменения?")
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            saveHostAndPortList()
            if(portHaveError)
            {
                errorMessage.open()
                portHaveError = false
            }
            else
            {
                qmlProperty.idPointSaleInOptions = currentIdPoinSale
                middlewareQML.saveIdPointSaleInSettings()
                middlewareQML.saveHostPortInSettings()
            }
        }
    }

    property int i

    function saveHostAndPortList(){
        for(i = 0;i<hostAndPortListModel.count;i++)
        {
            if(!portHaveError)
            {
                qmlProperty.address = hostAndPortListModel.get(i).host
                qmlProperty.port = hostAndPortListModel.get(i).port
                middlewareQML.saveHostPortInMiddleware()
            }
        }
    }
}

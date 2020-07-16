import QtQuick 2.12
import QtQuick.Dialogs 1.3
import "qrc:/QMLFile/Styles"

Rectangle {
    id: mainFormLogin
    anchors.fill: parent

    Connections {
        target: middlewareQML

        onSignalGoodAuthorized: {
            middlewareQML.saveLoginInSettings()
            formConectingToDB.state = "Hidden"
            loaderSelectionForOrder.state = "State1"
            loaderSelectionForOrder.setSource("ItemSelectionForOrderView.qml")

        }

        onSignalBadAuthorized: {
            formConectingToDB.state = "Hidden"
            errorMessage.setText(qmlProperty.errorString)
            errorMessage.open()
        }

        onSignalMessageSplashScreen: {
            statusConnectString.text = message
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
        id: formLoginUser
        anchors.centerIn: parent

        width: grdLogin.width + mainView.dp(70)
        height: grdLogin.height + formLoginBtn.height + (mainView.dp(35) * 2)

        color: "#293a4c"
        opacity: 0.96

        radius: mainView.dp(3)
        border.color: "#518dbb"
        border.width: mainView.dp(1)

        Grid {
            id: grdLogin
            anchors.top: formLoginUser.top
            anchors.horizontalCenter: formLoginUser.horizontalCenter
            anchors.topMargin: mainView.dp(30)

            rows: 3
            columns: 1

            rowSpacing: mainView.dp(15)
            columnSpacing: mainView.dp(5)

            Rectangle {
                width: formLoginBtn.width
                height: formLoginBtn.height

                color: Qt.rgba(0, 0, 0, 1)
                opacity: 0.6

                radius: mainView.dp(2)
                border.width: mainView.dp(1)
                border.color: "#518dbb"

                Image {
                    id: loginIcon
                    source: "qrc:/Image/login.png"
                    height: parent.height / 1.6
                    fillMode: Image.PreserveAspectFit

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left;
                    anchors.leftMargin: mainView.dp(5)
                }

                TextInput {
                    id: nameUser
                    anchors.fill: parent

                    verticalAlignment:TextInput.AlignVCenter
                    horizontalAlignment: TextInput.AlignHCenter
                    wrapMode: TextEdit.NoWrap
                    text: qmlProperty.login

                    font.pixelSize: mainView.dp(15)
                    color: "white"

                    property bool enterPress

                    onAccepted: {
                        enterPress = true
                    }

                    onTextEdited: {
                        if ( nameUser.text.length !== 0 )
                            if(enterPress)
                            {
                                enterPress = false
                            }
                            else
                            {
                                qmlProperty.login = nameUser.text
                            }
                    }
                }

                Component.onCompleted: {
                    middlewareQML.getLoginFromSettings()
                    if (qmlProperty.login !== null)
                        nameUser.text = qmlProperty.login
                }
            }

            Rectangle {
                width: formLoginBtn.width
                height: formLoginBtn.height

                color: Qt.rgba(0, 0, 0, 1)
                opacity: 0.6

                radius: mainView.dp(2)
                border.width: mainView.dp(1)
                border.color: "#518dbb"

                Image {
                    id: passwordIcon
                    source: "qrc:/Image/password.png"
                    height: parent.height / 1.6
                    fillMode: Image.PreserveAspectFit

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left;
                    anchors.leftMargin: mainView.dp(5)
                }

                TextInput {
                    id: password
                    anchors.fill: parent

                    verticalAlignment:TextInput.AlignVCenter
                    horizontalAlignment: TextInput.AlignHCenter

                    text: qmlProperty.password

                    font.pixelSize: mainView.dp(15)
                    color: "white"

                    echoMode: TextInput.Password

                    property bool enterPress

                    onAccepted: {
                        enterPress = true
                    }
                    onTextEdited: {
                        if ( nameUser.text.length !== 0 )
                            if(enterPress)
                            {
                                enterPress = false
                            }
                            else
                            {
                                qmlProperty.password = password.text
                            }
                    }
                    Component.onCompleted: {
                        qmlProperty.password = password.text
                    }
                }
            }
        }
        Row {
            id: formLoginBtn
            anchors{
                top: grdLogin.bottom
                horizontalCenter: grdLogin.horizontalCenter
                topMargin: mainView.dp(10)
            }
            spacing: mainView.dp(15)

            Rectangle {
                id: closeButton
                width: formLoginUser.width/3
                height: width/3
                opacity: 1
                color: "#518dbb"
                border.width: mainView.dp(1)
                border.color: "#518dbb"
                radius: mainView.dp(2)
                // Сглаживание включено
                smooth: true
                //                anchors.left: buttonsRectangle.left
                scale: formLoginExitArea.pressed ? 0.9 : 1.0

                Text {
                    anchors.fill: parent

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    text: qsTr("Закрыть")

                    color: "white"
                    font.bold: true

                    fontSizeMode: Text.HorizontalFit
                    minimumPixelSize: mainView.dp(8)
                    font.pixelSize: mainView.dp(15)
                }

                MouseArea {
                    id: formLoginExitArea
                    anchors.fill: parent

                    onClicked:{
                        if (formConectingToDB.state != "Visible")
                        {
                            exitMessage.open()
                        }
                    }
                }
            }
            Image {
                height: closeButton.height
                width: height

                smooth: true
                source: "qrc:/Image/settings.png"
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: optionArea
                    anchors.fill: parent

                    onPressAndHold: {
                        if (formConectingToDB.state != "Visible")
                        {
                            loaderSelectionForOrder.setSource("OptionView.qml")
                        }
                    }
                }
            }

            Rectangle {
                width: closeButton.width
                height: closeButton.height

                opacity: 1
                color: "#518dbb"
                border.width: mainView.dp(1)
                border.color: "#518dbb"
                radius: mainView.dp(2)
                // Сглаживание включено
                smooth: true
                //                anchors.right: buttonsRectangle.right
                scale: formLoginOkArea.pressed ? 0.9 : 1.0

                Text {
                    anchors.fill: parent

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    text: qsTr("Войти")

                    color: "white"
                    font.bold: true

                    fontSizeMode: Text.HorizontalFit
                    minimumPixelSize: mainView.dp(8)
                    font.pixelSize: mainView.dp(15)
                }

                MouseArea {
                    id: formLoginOkArea
                    anchors.fill: parent

                    onClicked: {
                        if (formConectingToDB.state != "Visible")
                        {
                            formConectingToDB.state = "Visible"
                            middlewareQML.connectToHost()
                        }
                    }
                }

            }
        }

    }

    Rectangle {
        id: formConectingToDB
        anchors.fill: parent
        z: 2
        Text {
            id: connectString
            anchors.centerIn: parent

            text: "Соединение..."
            font.pointSize: 40
            color: "white"
        }

        Text {
            id: statusConnectString
            anchors.top: connectString.bottom
            anchors.topMargin: mainView.dp(25)
            anchors.horizontalCenter: connectString.horizontalCenter
            font.pointSize: 20
            color: "white"
        }

        color: Qt.rgba(0,0,0,0.8)

        state: "Hidden"
        states: [
            State {
                //Обычное состояние меню
                name: "Hidden"
                PropertyChanges {
                    target: formConectingToDB
                    visible: false
                }
            },
            State {
                //Выбрано меню
                name: "Visible"
                PropertyChanges {
                    target: formConectingToDB
                    visible: true
                }
            }
        ]
    }

    MessageDialog {
        id: errorMessage
        title: qsTr("Ошибка")
        standardButtons: StandardButton.Ok
    }

    MessageDialog {
        id: exitMessage
        title: qsTr("Выход")
        text:  qsTr("Точно хотите выйти из приложения?")
        standardButtons: StandardButton.Yes | StandardButton.No
        icon: StandardIcon.Question
        onYes: {
            middlewareQML.exitApp()
            //  Qt.callLater(Qt.quit)
        }
    }
}


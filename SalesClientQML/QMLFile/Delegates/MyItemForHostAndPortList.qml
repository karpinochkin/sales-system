import QtQuick 2.12

Component{
    Rectangle {
        id: mainLayoutForItemHostAndPortList
        color:"transparent"
        width: parent.width
        height: (hostName.contentHeight > portName.contentHeight ? hostName.contentHeight : portName.contentHeight) + mainView.dp(60)

        Rectangle {
            id: itemRectangle
            anchors{
                margins: mainView.dp(5)
            }
            width: parent.width
            height: grdLogin.height
            color: "#2E516B"
            border.width: mainView.dp(1)
            border.color: "#518dbb"
            radius: mainView.dp(2)

            Grid {
                id: grdLogin
                anchors.left: itemRectangle.left
                anchors.leftMargin: mainView.dp(15)

                rows: 2
                columns: 3

                rowSpacing: mainView.dp(15)
                columnSpacing: mainView.dp(15)


                Text {
                    id: userText
                    text: qsTr("Хост:")
                    color: "white"
                    font.pixelSize: mainView.dp(30)
                    minimumPixelSize: mainView.dp(8)
                    wrapMode: Text.WrapAnywhere
                }

                Rectangle {
                    width: hostName.width
                    height: hostName.height
                    color: "#29272f"
                    border.width: mainView.dp(1)
                    border.color: "#518dbb"
                    radius: mainView.dp(2)

                    TextInput {
                        width: mainView.width*2/3 - mainView.dp(20)
                        id: hostName
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        text: host
                        color: "white"
                        font.pixelSize: mainView.dp(30)

                        property bool enterPress

                        onAccepted: {
                            enterPress = true
                        }

                        onTextChanged: {
                            if ( hostName.text.length !== 0 )
                                if(enterPress)
                                {
                                    if ((hostName.text.length-1 === host.length) || (hostName.text.length+1 === host.length))
                                    {
                                        host = hostName.text
                                        enterPress = false
                                    }
                                }
                                else
                                {
                                    host = hostName.text
                                }
                        }
                    }
                }
                Image {
                    height: userText.height
                    width: height

                    smooth: true
                    source: "qrc:/Image/cross-for-del.png"
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        id: optionArea
                        anchors.fill: parent

                        onClicked: {
                            hostAndPortListModel.remove(index)
                        }
                    }

                    scale: optionArea.pressed ? 0.9 : 1
                }

                Text {

                    text: qsTr("Порт:")
                    color: "white"
                    font.pixelSize: mainView.dp(30)
                    wrapMode: Text.WrapAnywhere
                }

                Rectangle {
                    width: portName.width
                    height: portName.height
                    color: "#29272f"
                    border.width: mainView.dp(1)
                    border.color: "#518dbb"
                    radius: mainView.dp(2)

                    TextInput {
                        width: mainView.width*2/3 - mainView.dp(20)
                        id: portName
//                        wrapMode: Text.WrapAnywhere
                        text: port
                        color: "white"
                        font.pixelSize: mainView.dp(30)
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                        property bool enterPress2

                        onAccepted: {
                            enterPress2 = true
                        }

                        onTextEdited: {
                            if ( portName.text.length !== 0 )
                                if(enterPress2)
                                {
                                    if ((portName.text.length-1 === port.length) || (portName.text.length+1 === port.length))
                                    {
                                        port = portName.text
                                        enterPress2 = false
                                    }
                                }
                                else
                                {
                                    port = portName.text
                                }
                        }

                    }
                }

            }
        }
    }
}

import QtQuick 2.12
import "qrc:/QMLFile/Styles"

Component {
      Rectangle {
          id: oneButtomFromMenu
          width: gridViewForItemFromMenu.cellWidth - mainView.dp(15)
          height: gridViewForItemFromMenu.cellHeight - mainView.dp(15)

          color: !buttonCoffieArea.pressed ? "#518dbb" : "lightblue"

          border.width: mainView.dp(3)
          border.color: colorCode
          radius: mainView.dp(3)

          opacity: 0.96

          Image {
              anchors.centerIn: parent

              width: gridViewForItemFromMenu.cellWidth - mainView.dp(15)
              height: gridViewForItemFromMenu.cellHeight - mainView.dp(15)
              source: "image://products/" + idProduct

              fillMode: Image.PreserveAspectFit

              TextForImage{
                  text: name
                  verticalAlignment: Text.AlignBottom
                  color: "white"
              }
          }

          MouseArea {
              id: buttonCoffieArea
              anchors.fill: parent

              onClicked: {
                  mainView.prepareToOpenSelectionView(index, idProduct, idCategory, false)
              }
          }
     }
}

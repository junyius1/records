import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import de.framework.QtMvvm.Core 1.1
import de.framework.QtMvvm.Quick 1.1
import com.cross.notes 1.1

Page {
    id: tabView
    property MainViewModel viewModel: null
    readonly property bool presentAsRoot: true

    Connections {
      target: Qt.application
      onStateChanged: {
          if(Qt.application.state === Qt.ApplicationActive)
          {
//              clipboard.showDialog(clipboard.text())
//              console.log(Qt.ApplicationActive," ",Qt.application.state )
          }
//          console.log("text=====", clipboard.text())
      }
    }

    header: ContrastToolBar {
        height: 56 + tabBar.height

        GridLayout {
            anchors.fill: parent
            rowSpacing: 0
            columnSpacing: 0
            columns: 2

            ActionButton {
                text: "≣"
                display: AbstractButton.TextOnly
                onClicked: QuickPresenter.toggleDrawer()
            }

            ToolBarLabel {
                text: qsTr("Note");
                Layout.fillWidth: true
                Layout.preferredHeight: 56
            }

            //swipe view's head tab bar
            TabBar {
                id: tabBar
                Layout.columnSpan: 2
                Layout.fillWidth: true
                Repeater {
                }
                currentIndex: swipe.currentIndex
                Material.background: Material.primary
            }
        }
    }

    PresenterProgress {}

    SwipeView {
        id: swipe
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
    }

    Component {
        id: _newTab
        TabButton {
            property MainTabItemViewModel viewModel: null

            text: viewModel.title
            width: Math.max(100, tabBar.width / 5)
        }
    }


    property var tabKeeper :[]//because of c++ created component will be gc by qml, so add this component's reference

    function presentTab(item) {
        tabBar.insertItem(tabBar.count - 1, _newTab.createObject(tabBar, {viewModel: item.viewModel}));
//        item.parent = swipe;
        swipe.addItem(item);
        tabKeeper.push(item);
//        tabBar.setCurrentIndex(tabBar.count - 2);
        return true;
    }

    function afterPop() {
        while(tabBar.count > 0)
            tabBar.takeItem(0).destroy();
        while(swipe.count > 0)
            swipe.takeItem(0).destroy();
    }
}

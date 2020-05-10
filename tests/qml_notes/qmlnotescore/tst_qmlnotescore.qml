import QtQuick 2.12
import QtQuick.Controls 2.12
import de.framework.QtMvvm.Core 1.1
import de.framework.QtMvvm.Quick 1.1
import QtTest 1.1

Item {
    id: _root
    width: 360
    height: 520
    PresentingStackView {
        id: _rootStack
        anchors.fill: parent
    }

    function presentItem(item) {
        return _rootStack.presentItem(item);
    }

    function presentDrawerContent(item) {
        if(!_drawerLoader.item)
            _drawerLoader.active = true;
        return _drawerLoader.item.presentDrawerContent(item);
    }

    //! @copybrief PresentingDrawer::toggle
    function toggleDrawer() {
        if(_drawerLoader.item)
            _drawerLoader.item.toggle();
        else
            console.warn("No drawer like view active. Cannot toggle drawer");
    }

    Connections {
      target: dirFileDelegate
      onDelFileOrDir: {
          for(var i=0; i < _rootStack.depth; i++)
          {
              var item = _rootStack.get(i, StackView.ForceLoad)
              if(item)
              {
                  item.closeTab(path);
              }
          }
      }
    }

    Loader {
        id: _drawerLoader
        active: false
        asynchronous: false
        sourceComponent: PresentingDrawer {
            id: _rootDrawer

            interactive: !_root.rootOnlyDrawer || _rootStack.depth === 1
        }
    }

	TestCase {
        name: "Present"
        when: windowShown

		function test_1_SingleInit() {
            var item = findChild(_rootStack, "addNewNote");
            verify(item, "not found addNewNote");
            mouseClick(item);
            var tabBar = findChild(_rootStack, "tabBar");
            var tabButton = tabBar.itemAt(0);
            verify(tabButton, "not found first tabButton");
            wait(1000)//wait new tab init and add to swipe ok
            var swipe = findChild(_rootStack, "swipe");
            verify(swipe, "not found swipe");
            var newTabButton = tabBar.itemAt(1);
            verify(newTabButton, "not found second tabButton");
            mouseClick(tabButton);
            wait(100)//wait for click ative tab take effect

            var fileListView = findChild(swipe.currentItem, "fileListView");
            verify(fileListView, "not found fileListView");
            var newFileItem;
            for(var i =0; i < fileListView.count; i++)
            {
                var fileNameItem = findChild(fileListView.itemAtIndex(i), "fileName");
                if(fileNameItem.text === newTabButton.fileName)
                {
                    newFileItem = fileListView.itemAtIndex(i);
                    break;
                }
            }
            verify(fileListView, "not found newFileItem named "+newTabButton.fileName);

            mousePress(newFileItem);

            mouseRelease(newFileItem, newFileItem.width / 2, newFileItem.height / 2, Qt.LeftButton, Qt.NoModifier, 2000)
            wait(100)//wait for pop up menu

            var oprFileMenu = findChild(fileListView, "oprFileMenu");
            verify(oprFileMenu, "no pop up menu");
            var deleteItem = findChild(oprFileMenu, "delete");
            mouseClick(deleteItem);

            wait(1000000)
		}
	}
    Component.onCompleted: {
        QuickPresenter.qmlPresenter = _root
    }
}

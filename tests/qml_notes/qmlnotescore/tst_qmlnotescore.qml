import QtQuick 2.12
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
            verify(item!==null, "not found addNewNote")
            mouseClick(item);
            wait(10000)
		}
	}
    Component.onCompleted: {
        QuickPresenter.qmlPresenter = _root
    }
}

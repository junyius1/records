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

    signal openTab(string fileName, string filePath, int tabIndex, bool fileIsDir);

    onOpenTab: {
//        console.log("emit parameter", fileIsDir, "==", filePath);
        if(fileIsDir){
            popAfterIndex(tabIndex);
            viewModel.show("MainTabItemViewModel*", {
                               "title": fileName,
                               "path": filePath
                           })
        } else{
            viewModel.show("NoteTabItemViewModel*", {
                               "title": fileName,
                               "filePath": filePath,
                               "keyword": fileName
                           })
        }
    }

    header: ContrastToolBar {
        height: 56 + tabBar.height

        GridLayout {
            anchors.fill: parent
            rowSpacing: 0
            columnSpacing: 0
            columns: 4

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

            ActionButton {
                id: addNewNote
                objectName:"addNewNote"
                text: "+"
                display: AbstractButton.TextOnly
                onClicked: addTab();
            }

            ActionButton {
                text: "x"
                display: AbstractButton.TextOnly
                onClicked: popCurTab();
            }

            //swipe view's head tab bar
            TabBar {
                id: tabBar
                objectName: "tabBar"
                Layout.columnSpan: 4
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
        objectName: "swipe"
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        onCurrentIndexChanged: {
            if(currentItem ){
                if(currentItem.viewModel.reset){
                    currentItem.viewModel.reset();
                }
                if(currentItem instanceof MainTabItemView)
                {
                    addNewNote.text = "+";
                    addNewNote.enabled = true;
                } else{
                    addNewNote.text = "";
                    addNewNote.enabled = false;
                }
            }
        }
    }

    Component {
        id: _newTab
        TabButton {
            property string title: ""
            property string fileName: ""

            text: title
            width: Math.max(100, tabBar.width / 5)

            TextEdit {
                //anchors.bottomMargin: 2
                id: editInfo
                visible: false;

                anchors.fill: parent
                text: title

                selectByMouse: true
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                onVisibleChanged: if(visible) editInfo.forceActiveFocus()
                onEditingFinished: {
                    parent.text = parent.title
                    editInfo.visible = false;
                    title = swipe.currentItem.viewModel.filePath;
                    console.log("sssssssss========",title)
                    dirFileDelegate.startRename(title, false);
                    var index = title.lastIndexOf('/');
                    var path = title.substring(0, index);
                    console.log("index=====",index, "====",path);
                    dirFileDelegate.endPaste(path + fileName);
                    console.log("currentindex===", tabBar.currentIndex)
                    setTitle();
                }
            }
            onPressAndHold: {
                editInfo.visible = true;
                editInfo.selectAll();
                editInfo.focus = true;
                text = ""
            }
            function setTitle()
            {
                var index = fileName.lastIndexOf('.');
                title = index===-1?fileName:fileName.substring(0, index);
            }

            Component.onCompleted: {
                setTitle();
            }
        }

    }



    function resetTabButtonRename()
    {
        for(var i in tabBar.currentItem.children)
        {
            var item = tabBar.currentItem.children[i];
            if(item instanceof TextEdit)
            {
                item.focus = false;
            }
        }
    }

    function getCurrentIndex()
    {
        return swipe.currentIndex;
    }

    property var tabKeeper :new Object//because of c++ created component will be gc by qml, so add this component's reference
    property string jsString: ""//only declare like this can be javascript string

    function presentTab(item) {
        tabBar.addItem(_newTab.createObject(tabBar, {fileName: item.viewModel.title}));//item.viewModel.title is fileName
        item.parentView = tabView;
        item.tabIndex = tabBar.count-1;
        swipe.addItem(item);
        tabKeeper[item.viewModel.filePath] = item;
        tabBar.setCurrentIndex(item.tabIndex)
        return true;
    }

    function closeTab(path)
    {
        for(var p in tabKeeper)
        {
            jsString = p;

//            console.log("str11-----===",tabKeeper[p],"==", jsString, "===", path, "===",jsString.indexOf(path));

            if(jsString.indexOf(path) != -1)
            {
                removeTab(tabKeeper[p].tabIndex);
            }
        }
    }
    function removeTab(index)
    {
        var item = swipe.takeItem(index);
        if(item)
        {
            delete tabKeeper[item.viewModel.filePath]
            item.destroy();
        }

        item = tabBar.takeItem(index);
        if(item)
        {
            item.destroy();
        }
    }

    function addTab()
    {
        viewModel.show("NoteTabItemViewModel*", {
                           "filePath": swipe.currentItem.viewModel.getCurDirectory(),
                           "isNew":true
                       })
    }

    function popCurTab()
    {
        var i = getCurrentIndex();
        if(!i)return;
        removeTab(i);
    }

    function popAfterIndex(tabIndex)
    {
        for(var i =swipe.count-1; i > tabIndex; i --)
        {
            removeTab(i)
        }
    }

    function afterPop() {
        while(tabBar.count > 0)
            tabBar.takeItem(0).destroy();
        while(swipe.count > 0)
            swipe.takeItem(0).destroy();
        tabKeeper = new Object;
    }
}

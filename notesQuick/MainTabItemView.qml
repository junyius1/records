import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import de.framework.QtMvvm.Core 1.1
import de.framework.QtMvvm.Quick 1.1
import com.cross.notes 1.1

Page {
	property MainTabItemViewModel viewModel: null
    property MainView parentView: null
    property int tabIndex: -1

    Component{
        id:dirFileOprMenu
        Menu {
            property string cachePath: ""
            property bool cacheIsDir: false
            Component {
                id: menuItem
                MenuItem {

                }
            }

            function createMenu(map)
            {
                if(map["copy"])
                {
                    var obj = menuItem.createObject(parent, { text: "copy"});
                    obj.triggered.connect(function(){
                            dirFileDelegate.startCopy(cachePath, cacheIsDir)
                        });
                    addItem(obj)
                }
                if(map["cut"])
                {
                    obj = menuItem.createObject(parent, { text: "cut"});
                    obj.triggered.connect(function(){
                            dirFileDelegate.startCut(cachePath, cacheIsDir)
                        });
                    addItem(obj)
                }
                if(map["paste"])
                {
                    obj = menuItem.createObject(parent, { text: "paste"});
                    obj.triggered.connect(function(){
                            dirFileDelegate.endPaste(cachePath)
                        });
                    addItem(obj)
                }
                if(map["delete"])
                {
                    obj = menuItem.createObject(parent, { text: "delete"});
                    obj.triggered.connect(function(){
                            dirFileDelegate.remove(cachePath, cacheIsDir)
                        });
                    addItem(obj)
                }
            }
        }
    }



    GridLayout {
        columns: 2
        anchors.fill: parent
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        ListView {
            id: fileListView
            x: 57
            y: 146
            Layout.fillWidth:true
            height: 652
            antialiasing: true
            clip: false
            orientation: ListView.Vertical
            highlightRangeMode: ListView.NoHighlightRange
            snapMode: ListView.NoSnap
            spacing: 0
            contentHeight: 450
            focus: true

            model: DelegateModel {
                id:delegateModel
                property var rootPathIndex
                model: viewModel.fileSystemModel
                rootIndex:{
                    rootPathIndex = viewModel.getRootPathIndex();
                    console.log("set rootIndex==", rootPathIndex)
                    return rootPathIndex
                }
                onRootIndexChanged:{
                    rootIndex = rootPathIndex
                }

                delegate: Rectangle {
                    id: wrapper
                    width: fileListView.width
                    height: img.height+4
                    color: ListView.isCurrentItem ? "gray" : (index %2 ?"transparent":"#f0f0f0")
                    Image{
                        id: img
                        source: {
                            fileIsDir ? "/images/FolderClosed.png" : "/images/File.png"
                        }
                        x: 0
                        y: 2
                        height: 15
                        width: 15
                    }
                    Text {
                        //anchors.bottomMargin: 2
                        id: contactInfo
                        x: 17
                        y: 4
                        text: {
                            if(!fileName) return "";
                            return wrapper.ListView.isCurrentItem ? "<b>" + fileName +"</b>" : fileName
                        }
                        color: wrapper.ListView.isCurrentItem ? "black" : "blue"
                        horizontalAlignment: Text.AlignHCenter
                    }
                    MouseArea{
                        anchors.fill: wrapper
//                        hoverEnabled: true
                        onPressed: {
                            fileListView.currentIndex = index
                        }

                        onPressAndHold: {
                            var menu = dirFileOprMenu.createObject(parent, {cachePath:filePath, cacheIsDir:fileIsDir});
                            menu.createMenu({"copy":true, "cut":true, "delete":true});
                            menu.popup();
                        }

                        onClicked: {
                            emit: parentView.openTab(fileName, filePath, tabIndex, fileIsDir);
                        }
//                        onDoubleClicked: {
//                            fileListView.currentIndex = index
//                            if (model.hasModelChildren){
//                                delegateModel.rootPathIndex = delegateModel.modelIndex(index)
//                                delegateModel.rootIndex = delegateModel.rootPathIndex
//                            }
//                        }
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                propagateComposedEvents: true
                onPressed:{
                    if(fileListView.itemAt(mouse.x, mouse.y))
                    {
                        mouse.accepted =false;
                    } else{
                        if(dirFileDelegate.canPaste()){
                            var menu = dirFileOprMenu.createObject(parent, {cachePath:viewModel.getCurDirectory()});
                            menu.createMenu({"paste":true});
                            menu.popup();
                        }
                    }
                }
            }
        }
    }

    footer:Rectangle {
                width: parent.width
                height: 20
                color:"#E0E0E0"
                clip: true
                Text {
                    id:footer_text
                    x:0

                    anchors.verticalCenter :parent.verticalCenter
                    text: viewModel.getCurDirectory();
                    SequentialAnimation on x {
                                    loops: Animation.Infinite
                                    PropertyAnimation {
                                        from:0
                                        to: 0
                                        duration: 2000
                                    }

                                    PropertyAnimation {
                                        from:0
                                        to: -footer_text.width
                                        duration: 5000
                                    }
                                }

                }
            }

}

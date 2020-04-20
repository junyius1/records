import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import de.framework.QtMvvm.Core 1.1
import de.framework.QtMvvm.Quick 1.1
import com.cross.notes 1.1

Pane {
    property NoteTabItemViewModel viewModel: null
    property MainView parentView: null
    property int tabIndex: -1

    GridLayout {
        columns: 2
        anchors.fill: parent

        ListView {
            id: lView
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            ScrollBar.vertical: ScrollBar {}

            model: viewModel.noteModel

            delegate: WordsDelegate {}
        }
    }

//    Clipboard {
//        id:clipboard
//        property string preText

//        function showDialog(text){
//            if(text !== preText){
//                preText = text;
//                // 弹出输入框
//                Message.getInput("New Note", "Content:", "QString", function(){
//                    var item = swipe.itemAt(swipe.count - 1)
//                    //界面触发添加text到MainTabItemViewModel到notesmodel
//                    item.viewModel.addData(text)
//                }, text)
//            }
//        }
//    }

}

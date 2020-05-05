import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import de.framework.QtMvvm.Core 1.1
import de.framework.QtMvvm.Quick 1.1
import com.cross.notes 1.1

Page {
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
            MouseArea{
                anchors.fill: parent
                propagateComposedEvents: true
                onPressed:{
                    mouse.accepted =false;
                    parentView.resetTabButtonRename()
                }
            }
        }
    }


    Menu {
        id: codecMenu

        MenuItem {
            text: "Big5"
            onTriggered: {viewModel.setCodec("Big5");}
        }

        MenuItem {
            text: "Big5-HKSCS"
            onTriggered: {viewModel.setCodec("Big5-HKSCS");}
        }

        MenuItem {
            text: "CP949"
            onTriggered: {viewModel.setCodec("CP949");}
        }

        MenuItem {
            text: "EUC-JP"
            onTriggered: {viewModel.setCodec("EUC-JP");}
        }

        MenuItem {
            text: "EUC-KR"
            onTriggered: {viewModel.setCodec("EUC-KR");}
        }

        MenuItem {
            text: "GB18030"
            onTriggered: {viewModel.setCodec("GB18030");}
        }

        MenuItem {
            text: "HP-ROMAN8"
            onTriggered: {viewModel.setCodec("HP-ROMAN8");}
        }

        MenuItem {
            text: "IBM 850"
            onTriggered: {viewModel.setCodec("IBM 850");}
        }

        MenuItem {
            text: "IBM 866"
            onTriggered: {viewModel.setCodec("IBM 866");}
        }

        MenuItem {
            text: "IBM 874"
            onTriggered: {viewModel.setCodec("IBM 874");}
        }

        MenuItem {
            text: "ISO 2022-JP"
            onTriggered: {viewModel.setCodec("ISO 2022-JP");}
        }

        MenuItem {
            text: "ISO 8859-1 to 10"
            onTriggered: {viewModel.setCodec("ISO 8859-1 to 10");}
        }

        MenuItem {
            text: "ISO 8859-13 to 16"
            onTriggered: {viewModel.setCodec("ISO 8859-13 to 16");}
        }

        MenuItem {
            text: "Iscii-Bng, Dev, Gjr, Knd, Mlm, Ori, Pnj, Tlg, and Tml"
            onTriggered: {viewModel.setCodec("Iscii-Bng, Dev, Gjr, Knd, Mlm, Ori, Pnj, Tlg, and Tml");}
        }

        MenuItem {
            text: "KOI8-R"
            onTriggered: {viewModel.setCodec("KOI8-R");}
        }

        MenuItem {
            text: "KOI8-U"
            onTriggered: {viewModel.setCodec("KOI8-U");}
        }

        MenuItem {
            text: "Macintosh"
            onTriggered: {viewModel.setCodec("Macintosh");}
        }

        MenuItem {
            text: "Shift-JIS"
            onTriggered: {viewModel.setCodec("Shift-JIS");}
        }

        MenuItem {
            text: "TIS-620"
            onTriggered: {viewModel.setCodec("TIS-620");}
        }

        MenuItem {
            text: "TSCII"
            onTriggered: {viewModel.setCodec("TSCII");}
        }

        MenuItem {
            text: "UTF-8"
            onTriggered: {viewModel.setCodec("UTF-8");}
        }

        MenuItem {
            text: "UTF-16"
            onTriggered: {viewModel.setCodec("UTF-16");}
        }

        MenuItem {
            text: "UTF-16BE"
            onTriggered: {viewModel.setCodec("UTF-16BE");}
        }

        MenuItem {
            text: "UTF-16LE"
            onTriggered: {viewModel.setCodec("UTF-16LE");}
        }

        MenuItem {
            text: "UTF-32"
            onTriggered: {viewModel.setCodec("UTF-32");}
        }

        MenuItem {
            text: "UTF-32BE"
            onTriggered: {viewModel.setCodec("UTF-32BE");}
        }

        MenuItem {
            text: "UTF-32LE"
            onTriggered: {viewModel.setCodec("UTF-32LE");}
        }

        MenuItem {
            text: "Windows-1250 to 1258"
            onTriggered: {viewModel.setCodec("Windows-1250 to 1258");}
        }

    }
    footer:Rectangle {
                id: rect
                width: parent.width
                height: 20
                color:"#E0E0E0"
                Text {
                    x:parent.width/3*2

                    anchors.verticalCenter :parent.verticalCenter
                    text: viewModel.getCodec()
                    MouseArea{
                        anchors.fill: parent;
                        onClicked: {

                            codecMenu.popup();
                        }
                    }
                }
            }
    Connections {
      target: Qt.application
      onStateChanged: {
          if(Qt.application.state === Qt.ApplicationActive)
          {
              if(tabIndex === parentView.getCurrentIndex())
              {
                clipboard.showDialog(clipboard.text())
//              console.log(Qt.ApplicationActive," ",Qt.application.state )
              }
          }
//          console.log("text=====", clipboard.text())
      }
    }

    Clipboard {
        id:clipboard
        property string preText

        function showDialog(text){
            if(text !== preText){
                preText = text;
                // show input box
                Message.getInput("New Note", "Content:", "QString", function(result){
                    if(result===undefined)return;
                    //add text to note model
                    viewModel.addData(result)
                }, text)
            }
        }
    }

}

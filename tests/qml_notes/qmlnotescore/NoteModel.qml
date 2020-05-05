import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import de.framework.QtMvvm.Core 1.1
import de.framework.QtMvvm.Quick 1.1
import com.cross.notes 1.1

Component {

    Connections {
      target: noteModel
      onEnterNoteName: {
          if(noteModel.getCurNodeName()===""){
              if(!noteModel.inputDialog){
                  noteModel.inputDialog = true;
                  // 弹出输入框
                  Message.getInput("Enter Note Name", "Name:", "QString", function(result){
                      noteModel.addNoteName(result);
                  }, "")
              }
          }
      }
    }
}

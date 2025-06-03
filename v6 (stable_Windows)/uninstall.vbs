Set oFSO = CreateObject("Scripting.FileSystemObject")
Set oWS = CreateObject("WScript.Shell")

buildPath = oFSO.GetParentFolderName(WScript.ScriptFullName) & "\build"
shortcutPath = oWS.SpecialFolders("Desktop") & "\ENcrypt-DEcrypt.lnk"

removedAnything = False

If oFSO.FileExists(shortcutPath) Then
    oFSO.DeleteFile shortcutPath, True
    removedAnything = True
Else
    MsgBox "Ярлык на рабочем столе не найден.", vbInformation, "Информация"
End If

If oFSO.FolderExists(buildPath) Then
    oFSO.DeleteFolder buildPath, True
    removedAnything = True
Else
    MsgBox "Папка build не найдена — возможно, проект не собирался.", vbInformation, "Информация"
End If

If removedAnything Then
    MsgBox "Удаление завершено успешно.", vbInformation, "Готово"
Else
    MsgBox "Нечего удалять: ярлык и папка build не найдены.", vbExclamation, "Нет действий"
End If

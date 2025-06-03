Set oFSO = CreateObject("Scripting.FileSystemObject")
Set oWS = CreateObject("WScript.Shell")

exePath = oFSO.GetParentFolderName(WScript.ScriptFullName) & "\build\encrypt_decrypt.exe"
If Not oFSO.FileExists(exePath) Then
    MsgBox "Файл encrypt_decrypt.exe не найден в папке build. Пожалуйста, сначала соберите проект.", vbExclamation, "Ошибка"
    WScript.Quit
End If

sLinkFile = oWS.SpecialFolders("Desktop") & "\ENcrypt-DEcrypt.lnk"

Set oLink = oWS.CreateShortcut(sLinkFile)
oLink.TargetPath = exePath
oLink.WorkingDirectory = oFSO.GetParentFolderName(WScript.ScriptFullName) & "\build"
oLink.WindowStyle = 1
oLink.Save

MsgBox "Ярлык ENcrypt-DEcrypt создан на рабочем столе", vbInformation, "Успех"

Set oFSO = CreateObject("Scripting.FileSystemObject")
Set oWS = CreateObject("WScript.Shell")

buildPath = oFSO.GetParentFolderName(WScript.ScriptFullName) & "\build"
shortcutPath = oWS.SpecialFolders("Desktop") & "\ENcrypt-DEcrypt.lnk"

removedAnything = False

If oFSO.FileExists(shortcutPath) Then
    oFSO.DeleteFile shortcutPath, True
    removedAnything = True
Else
    MsgBox "����� �� ������� ����� �� ������.", vbInformation, "����������"
End If

If oFSO.FolderExists(buildPath) Then
    oFSO.DeleteFolder buildPath, True
    removedAnything = True
Else
    MsgBox "����� build �� ������� � ��������, ������ �� ���������.", vbInformation, "����������"
End If

If removedAnything Then
    MsgBox "�������� ��������� �������.", vbInformation, "������"
Else
    MsgBox "������ �������: ����� � ����� build �� �������.", vbExclamation, "��� ��������"
End If

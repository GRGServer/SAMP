Enumeration
	#XML
	#Window
	#List
	#InfoList
	#Splitter
	#Menu
	#PopupMenu
	#Menu_Reload
	#Menu_Save
	#Menu_Quit
	#Menu_Add
	#Menu_Edit
	#Menu_Delete
	#Edit_Window
	#Edit_Text1
	#Edit_Text2
	#Edit_Text3
	#Edit_ID
	#Edit_English
	#Edit_German
	#Edit_OK
	#Edit_Cancel
EndEnumeration

#Title = "Language String Editor"

Global editItemID
Global fileChanged
Global xmlFile$

Procedure IsEqual(value1, value2)
	If value1 = value2
		ProcedureReturn #True
	EndIf
EndProcedure

Procedure.s TrimEx(string$)
	newString$ = Trim(string$, Chr(13))
	newString$ = Trim(newString$, Chr(10))
	newString$ = Trim(newString$)
	If newString$ <> string$
		newString$ = TrimEx(newString$)
	EndIf
	ProcedureReturn newString$
EndProcedure

Procedure UpdateWindowSize(window)
	Select window
		Case #Edit_Window
			ResizeGadget(#Edit_ID, #PB_Ignore, #PB_Ignore, WindowWidth(#Edit_Window) - 100, #PB_Ignore)
			ResizeGadget(#Edit_English, #PB_Ignore, #PB_Ignore, WindowWidth(#Edit_Window) - 100, #PB_Ignore)
			ResizeGadget(#Edit_German, #PB_Ignore, #PB_Ignore, WindowWidth(#Edit_Window) - 100, #PB_Ignore)
			ResizeGadget(#Edit_OK, WindowWidth(#Edit_Window) - 220, #PB_Ignore, #PB_Ignore, #PB_Ignore)
			ResizeGadget(#Edit_Cancel, WindowWidth(#Edit_Window) - 110, #PB_Ignore, #PB_Ignore, #PB_Ignore)
		Case #Window
			ResizeGadget(#Splitter, #PB_Ignore, #PB_Ignore, WindowWidth(#Window), WindowHeight(#Window) - MenuHeight())
	EndSelect
EndProcedure

Procedure EditItem(item)
	editItemID = item
	items = CountGadgetItems(#List)
	If item = -1
		title$ = "Add language string"
		stringID = -1
		Repeat
			stringID + 1
			useID = #True
			For currentItem = 0 To items - 1
				If Val(GetGadgetItemText(#List, currentItem, 0)) = stringID
					useID = #False
				EndIf
			Next
		Until useID
	Else
		title$ = "Edit language string"
		stringID = Val(GetGadgetItemText(#List, item, 0))
		englishString$ = GetGadgetItemText(#List, item, 1)
		germanString$ = GetGadgetItemText(#List, item, 2)
	EndIf
	If OpenWindow(#Edit_Window, 100, 100, 500, 140, title$, #PB_Window_MinimizeGadget | #PB_Window_MaximizeGadget | #PB_Window_SizeGadget | #PB_Window_WindowCentered, WindowID(#Window))
		TextGadget(#Edit_Text1, 10, 10, 70, 20, "ID:")
		TextGadget(#Edit_Text2, 10, 40, 70, 20, "English string:")
		TextGadget(#Edit_Text3, 10, 70, 70, 20, "German string:")
		StringGadget(#Edit_ID, 90, 10, 0, 20, Str(stringID), #PB_String_Numeric)
		StringGadget(#Edit_English, 90, 40, 0, 20, englishString$)
		StringGadget(#Edit_German, 90, 70, 0, 20, germanString$)
		ButtonGadget(#Edit_OK, 0, 100, 100, 30, "OK")
		ButtonGadget(#Edit_Cancel, 0, 100, 100, 30, "Cancel")
		DisableWindow(#Window, #True)
		WindowBounds(#Edit_Window, 230, WindowHeight(#Edit_Window), #PB_Ignore, WindowHeight(#Edit_Window))
		UpdateWindowSize(#Edit_Window)
	EndIf
EndProcedure

Procedure CloseEditWindow()
	DisableWindow(#Window, #False)
	CloseWindow(#Edit_Window)
EndProcedure

Procedure SetFileChangedState(state)
	fileChanged = state
	If fileChanged
		SetWindowTitle(#Window, #Title + " [Changed]")
	Else
		SetWindowTitle(#Window, #Title)
	EndIf
EndProcedure

Procedure IsDuplicateStringID(stringID, ignoreItemID)
	For item = 0 To CountGadgetItems(#List) - 1
		If item <> ignoreItemID And Val(GetGadgetItemText(#List, item, 0)) = stringID
			ProcedureReturn #True
		EndIf
	Next
EndProcedure

Procedure.s EscapeXMLCharacters(string$)
	string$ = ReplaceString(string$, "<", "&lt;")
	string$ = ReplaceString(string$, ">", "&gt;")
	ProcedureReturn string$
EndProcedure

Procedure LoadLanguageStrings()
	If LoadXML(#XML, xmlFile$)
		If XMLStatus(#XML) = #PB_XML_Success
			*mainNode = MainXMLNode(#XML)
			If *mainNode
				ClearGadgetItems(#List)
				*stringNode = ChildXMLNode(*mainNode)
				While *stringNode
					stringID = Val(GetXMLAttribute(*stringNode, "id"))
					If IsDuplicateStringID(stringID, -1)
						AddGadgetItem(#InfoList, -1, "Duplicate string ID " + Str(stringID))
					Else
						germanString$ = ""
						englishString$ = ""
						*languageNode = XMLNodeFromPath(*stringNode, "de")
						If *languageNode
							germanString$ = TrimEx(GetXMLNodeText(*languageNode))
						EndIf
						*languageNode = XMLNodeFromPath(*stringNode, "en")
						If *languageNode
							englishString$ = TrimEx(GetXMLNodeText(*languageNode))
						EndIf
						AddGadgetItem(#List, -1, Str(stringID) + Chr(10) + englishString$ + Chr(10) + germanString$)
						If Not englishString$
							AddGadgetItem(#InfoList, -1, "Missing English language string for string ID " + Str(stringID))
						EndIf
						If Not germanString$
							AddGadgetItem(#InfoList, -1, "Missing German language string for string ID " + Str(stringID))
						EndIf
					EndIf
					*stringNode = NextXMLNode(*stringNode)
				Wend
				SetFileChangedState(#False)
				result = #True
			Else
				MessageRequester("No main node", "No main node found in XML file!", #MB_ICONERROR)
			EndIf
		Else
			message$ = "Error in XML file!" + Chr(13)
			message$ + Chr(13)
			message$ + "Code: " + Str(XMLStatus(#XML)) + Chr(13)
			message$ + "Line: " + Str(XMLErrorLine(#XML)) + Chr(13)
			message$ + "Character: " + Str(XMLErrorPosition(#XML)) + Chr(13)
			message$ + Chr(13)
			message$ + XMLError(#XML)
			MessageRequester("XML error", message$, #MB_ICONERROR)
		EndIf
		FreeXML(#XML)
	Else
		MessageRequester("Error", "Can not load XML file!", #MB_ICONERROR)
	EndIf
	ProcedureReturn result
EndProcedure

Procedure SaveLanguageStrings()
	Structure TempList
		id.l
		englishString.s
		germanString.s
	EndStructure
	NewList TempList.TempList()
	For item = 0 To CountGadgetItems(#List) - 1
		AddElement(TempList())
		TempList()\id = Val(GetGadgetItemText(#List, item, 0))
		TempList()\englishString = GetGadgetItemText(#List, item, 1)
		TempList()\germanString = GetGadgetItemText(#List, item, 2)
	Next
	SortStructuredList(TempList(), #PB_Sort_Ascending, OffsetOf(TempList\id), #PB_Sort_Long)
	file = CreateFile(#PB_Any, xmlFile$)
	If IsFile(file)
		WriteStringN(file, "<?xml version=" + Chr(34) + "1.0" + Chr(34) + " encoding=" + Chr(34) + "ISO-8859-1" + Chr(34) + "?>")
		WriteStringN(file, "<languagestrings>")
		ForEach TempList()
			WriteStringN(file, Chr(9) + "<string id=" + Chr(34) + Str(TempList()\id) + Chr(34) + ">")
			WriteStringN(file, Chr(9) + Chr(9) +"<en>" + EscapeXMLCharacters(TempList()\englishString) + "</en>")
			WriteStringN(file, Chr(9) + Chr(9) +"<de>" + EscapeXMLCharacters(TempList()\germanString) + "</de>")
			WriteStringN(file, Chr(9) + "</string>")
		Next
		WriteString(file, "</languagestrings>")
		CloseFile(file)
		SetFileChangedState(#False)
		ProcedureReturn #True
	EndIf
EndProcedure

Procedure CheckQuit()
	If fileChanged
		Select MessageRequester("Unsaved changes", "There are unsaved changes!" + Chr(13) + Chr(13) + "Do you want to save before quit?", #MB_YESNOCANCEL | #MB_ICONQUESTION)
			Case #PB_MessageRequester_Yes
				If SaveLanguageStrings()
					End
				Else
					MessageRequester("Save language strings", "Can not write to file '" + xmlFile$ + "'!" + Chr(13) + Chr(13) + "Click OK to go back without exiting the application.", #MB_ICONERROR)
				EndIf
			Case #PB_MessageRequester_No
				End
		EndSelect
	Else
		End
	EndIf
EndProcedure

mainPath$ = GetPathPart(ProgramFilename())
mainPath$ = "X:\Projects\SAMP-Server\tools\"
serverRoot$ = GetPathPart(Left(mainPath$, Len(mainPath$) - 1))
xmlFile$ = serverRoot$ + "scriptfiles\languagestrings.xml"

If OpenWindow(#Window, 100, 100, 800, 500, #Title, #PB_Window_MinimizeGadget | #PB_Window_MaximizeGadget | #PB_Window_SizeGadget | #PB_Window_ScreenCentered)
	If CreateMenu(#Menu, WindowID(#Window))
		MenuTitle("File")
		MenuItem(#Menu_Reload, "Reload")
		MenuItem(#Menu_Save, "Save" + Chr(9) + "Ctrl+S")
		MenuBar()
		MenuItem(#Menu_Quit, "Quit" + Chr(9) + "Alt+F4")
		MenuTitle("Edit")
		MenuItem(#Menu_Add, "Add" + Chr(9) + "Ins")
		MenuItem(#Menu_Edit, "Edit")
		MenuBar()
		MenuItem(#Menu_Delete, "Delete" + Chr(9) + "Del")
		DisableMenuItem(#Menu, #Menu_Edit, #True)
		DisableMenuItem(#Menu, #Menu_Delete, #True)
	EndIf
	ListIconGadget(#List, 0, 0, 0, 0, "ID", 50, #PB_ListIcon_FullRowSelect)
	AddGadgetColumn(#List, 1, "English", 300)
	AddGadgetColumn(#List, 2, "German", 300)
	ListViewGadget(#InfoList, 0, 0, 0, 0)
	SplitterGadget(#Splitter, 0, 0, 0, 0, #List, #InfoList, #PB_Splitter_Separator)
	UpdateWindowSize(#Window)
	AddKeyboardShortcut(#Window, #PB_Shortcut_Control | #PB_Shortcut_S, #Menu_Save)
	AddKeyboardShortcut(#Window, #PB_Shortcut_Insert, #Menu_Add)
	AddKeyboardShortcut(#Window, #PB_Shortcut_Delete, #Menu_Delete)
	If Not LoadLanguageStrings()
		End
	EndIf
	Repeat
		Select WaitWindowEvent()
			Case #PB_Event_Gadget
				Select EventGadget()
					Case #List
						item = GetGadgetState(#List)
						DisableMenuItem(#Menu, #Menu_Edit, IsEqual(item, -1))
						DisableMenuItem(#Menu, #Menu_Delete, IsEqual(item, -1))
						Select EventType()
							Case #PB_EventType_LeftDoubleClick
								EditItem(item)
							Case #PB_EventType_RightClick
								If CreatePopupMenu(#PopupMenu)
									MenuItem(#Menu_Add, "Add" + Chr(9) + "Ins")
									If item <> -1
										MenuItem(#Menu_Edit, "Edit")
										MenuBar()
										MenuItem(#Menu_Delete, "Delete" + Chr(9) + "Del")
									EndIf
									DisplayPopupMenu(#PopupMenu, WindowID(#Window))
								EndIf
						EndSelect
					Case #Edit_OK
						stringID = Val(GetGadgetText(#Edit_ID))
						If stringID < 0
							MessageRequester("Invalid string ID", Str(stringID) + " is not a valid string ID!" + Chr(13) + Chr(13) + "Only use non-negative numbers!", #MB_ICONERROR)
						Else
							If IsDuplicateStringID(stringID, editItemID)
								MessageRequester("Duplicate string ID", "The string ID " + Str(stringID) + " already exists in the list!", #MB_ICONERROR)
							Else
								If editItemID = -1
									AddGadgetItem(#List, -1, Str(stringID) + Chr(10) + GetGadgetText(#Edit_English) + Chr(10) + GetGadgetText(#Edit_German))
								Else
									SetGadgetItemText(#List, editItemID, Str(stringID), 0)
									SetGadgetItemText(#List, editItemID, GetGadgetText(#Edit_English), 1)
									SetGadgetItemText(#List, editItemID, GetGadgetText(#Edit_German), 2)
								EndIf
								CloseEditWindow()
								SetFileChangedState(#True)
							EndIf
						EndIf
					Case #Edit_Cancel
						CloseEditWindow()
				EndSelect
			Case #PB_Event_Menu
				item = GetGadgetState(#List)
				Select EventMenu()
					Case #Menu_Reload
						If fileChanged
							If MessageRequester("Reload file", "Are you sure to reload all language strings from the XML file?" + Chr(13) + Chr(13) + "You will lose all unsaved changes!", #MB_YESNO | #MB_ICONQUESTION) = #PB_MessageRequester_Yes
								LoadLanguageStrings()
							EndIf
						Else
							LoadLanguageStrings()
						EndIf
					Case #Menu_Save
						If SaveLanguageStrings()
							MessageRequester("Save language strings", "Language strings saved", #MB_ICONINFORMATION)
						Else
							MessageRequester("Save language strings", "Can not write to file '" + xmlFile$ + "'!", #MB_ICONERROR)
						EndIf
					Case #Menu_Quit
						CheckQuit()
					Case #Menu_Add
						EditItem(-1)
					Case #Menu_Edit
						If item <> -1
							EditItem(item)
						EndIf
					Case #Menu_Delete
						If item <> -1
							If MessageRequester("Delete language string", "Delete the selected language string?" + Chr(13) + Chr(13) + "ID: " + GetGadgetItemText(#List, item, 0), #MB_YESNO | #MB_ICONQUESTION) = #PB_MessageRequester_Yes
								RemoveGadgetItem(#List, item)
								SetFileChangedState(#True)
							EndIf
						EndIf
				EndSelect
			Case #PB_Event_SizeWindow
				UpdateWindowSize(EventWindow())
			Case #PB_Event_CloseWindow
				Select EventWindow()
					Case #Window
						CheckQuit()
					Case #Edit_Window
						CloseEditWindow()
				EndSelect
		EndSelect
	ForEver
EndIf
; IDE Options = PureBasic 4.60 (Windows - x86)
; CursorPosition = 149
; FirstLine = 126
; Folding = --
; EnableXP
; UseIcon = Language String Editor.ico
; Executable = Language String Editor.exe
; EnableCompileCount = 101
; EnableBuildCount = 2
; EnableExeConstant
; IncludeVersionInfo
; VersionField0 = 1,0,0,0
; VersionField1 = 1,0,0,0
; VersionField2 = SelfCoders
; VersionField3 = Language String Editor
; VersionField4 = 1.0
; VersionField5 = 1.0
; VersionField6 = Language String Editor
; VersionField7 = Language String Editor
; VersionField8 = %EXECUTABLE
; VersionField13 = languagestringeditor@selfcoders.com
; VersionField14 = http://www.selfcoders.com
; VersionField15 = VOS_NT_WINDOWS32
; VersionField16 = VFT_APP
; VersionField17 = 0409 English (United States)
; VersionField18 = Build
; VersionField19 = Compile OS
; VersionField20 = Date
; VersionField21 = %BUILDCOUNT
; VersionField22 = %OS
; VersionField23 = %y-%m-%d %h:%i:%s
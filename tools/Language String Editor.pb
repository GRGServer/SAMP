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
	#Menu_Goto
	#Menu_Search
	#Menu_SearchNext
	#Edit_Window
	#Edit_Text1
	#Edit_Text2
	#Edit_Text3
	#Edit_ID
	#Edit_EnglishString
	#Edit_GermanString
	#Edit_IgnoreUnused
	#Edit_OK
	#Edit_Cancel
EndEnumeration

#Title = "Language String Editor"

Structure Options
	preserveCount.l
EndStructure

Structure Strings
	stringID.l
	englishString.s
	germanString.s
	ignoreUnused.b
EndStructure

Global editItemID
Global fileChanged
Global listColumn
Global serverRoot$
Global xmlFile$

Global Options.Options

Global NewList Strings.Strings()

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
			ResizeGadget(#Edit_EnglishString, #PB_Ignore, #PB_Ignore, WindowWidth(#Edit_Window) - 100, #PB_Ignore)
			ResizeGadget(#Edit_GermanString, #PB_Ignore, #PB_Ignore, WindowWidth(#Edit_Window) - 100, #PB_Ignore)
			ResizeGadget(#Edit_OK, WindowWidth(#Edit_Window) - 220, #PB_Ignore, #PB_Ignore, #PB_Ignore)
			ResizeGadget(#Edit_Cancel, WindowWidth(#Edit_Window) - 110, #PB_Ignore, #PB_Ignore, #PB_Ignore)
		Case #Window
			ResizeGadget(#Splitter, #PB_Ignore, #PB_Ignore, WindowWidth(#Window), WindowHeight(#Window) - MenuHeight())
	EndSelect
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

Procedure FindEmptySlot()
	stringID = -1
	Repeat
		stringID + 1
		useID = #True
		For currentItem = 0 To CountGadgetItems(#List) - 1
			If Val(GetGadgetItemText(#List, currentItem, 0)) = stringID
				useID = #False
			EndIf
		Next
	Until useID
	ProcedureReturn stringID
EndProcedure

Procedure EditItem(item)
	editItemID = item
	If item = -1
		title$ = "Add language string"
		stringID = FindEmptySlot()
		englishString$ = ""
		germanString$ = ""
		ignoreUnused = #False
	Else
		title$ = "Edit language string"
		stringID = Val(GetGadgetItemText(#List, item, 0))
		englishString$ = GetGadgetItemText(#List, item, 1)
		germanString$ = GetGadgetItemText(#List, item, 2)
		ignoreUnused = GetGadgetItemData(#List, item)
	EndIf
	If OpenWindow(#Edit_Window, 100, 100, 500, 200, title$, #PB_Window_MinimizeGadget | #PB_Window_MaximizeGadget | #PB_Window_SizeGadget | #PB_Window_WindowCentered, WindowID(#Window))
		TextGadget(#Edit_Text1, 10, 10, 70, 20, "ID:")
		TextGadget(#Edit_Text2, 10, 40, 70, 20, "English:")
		TextGadget(#Edit_Text3, 10, 70, 70, 20, "English:")
		StringGadget(#Edit_ID, 90, 10, 0, 20, Str(stringID), #PB_String_Numeric)
		StringGadget(#Edit_EnglishString, 90, 40, 0, 20, englishString$)
		StringGadget(#Edit_GermanString, 90, 70, 0, 20, germanString$)
		CheckBoxGadget(#Edit_IgnoreUnused, 90, 100, 100, 20, "Ignore unused")
		ButtonGadget(#Edit_OK, 0, 100, 100, 30, "OK")
		ButtonGadget(#Edit_Cancel, 0, 100, 100, 30, "Cancel")
		DisableWindow(#Window, #True)
		ResizeWindow(#Edit_Window, #PB_Ignore, #PB_Ignore, #PB_Ignore, 140)
		WindowBounds(#Edit_Window, 230, WindowHeight(#Edit_Window), #PB_Ignore, WindowHeight(#Edit_Window))
		UpdateWindowSize(#Edit_Window)
		AddKeyboardShortcut(#Edit_Window, #PB_Shortcut_Return, #Edit_OK)
		AddKeyboardShortcut(#Edit_Window, #PB_Shortcut_Escape, #Edit_Cancel)
		SetGadgetState(#Edit_IgnoreUnused, ignoreUnused)
	EndIf
EndProcedure

Procedure CloseEditWindow()
	DisableWindow(#Window, #False)
	CloseWindow(#Edit_Window)
EndProcedure

Procedure EditOK()
	stringID = Val(GetGadgetText(#Edit_ID))
	If stringID < 0
		MessageRequester("Invalid string ID", Str(stringID) + " is not a valid string ID!" + Chr(13) + Chr(13) + "Only use non-negative numbers!", #MB_ICONERROR)
	Else
		If IsDuplicateStringID(stringID, editItemID)
			MessageRequester("Duplicate string ID", "The string ID " + Str(stringID) + " already exists in the list!", #MB_ICONERROR)
		Else
			If editItemID = -1
				AddGadgetItem(#List, -1, Str(stringID))
				editItemID = CountGadgetItems(#List) - 1
			EndIf
			SetGadgetItemText(#List, editItemID, Str(stringID), 0)
			SetGadgetItemText(#List, editItemID, GetGadgetText(#Edit_EnglishString), 1)
			SetGadgetItemText(#List, editItemID, GetGadgetText(#Edit_GermanString), 2)
			SetGadgetItemData(#List, editItemID, GetGadgetState(#Edit_IgnoreUnused))
			If GetGadgetState(#Edit_IgnoreUnused)
				SetGadgetItemColor(#List, editItemID, #PB_Gadget_BackColor, RGB(255, 200, 200), -1)
			Else
				SetGadgetItemColor(#List, editItemID, #PB_Gadget_BackColor, -1, -1)
			EndIf
			CloseEditWindow()
			SetFileChangedState(#True)
		EndIf
	EndIf
EndProcedure

Procedure.s EscapeXMLCharacters(string$)
	string$ = ReplaceString(string$, "<", "&lt;")
	string$ = ReplaceString(string$, ">", "&gt;")
	ProcedureReturn string$
EndProcedure

Procedure FindListItem(gadget, item, column, searchString$) 
	ProcedureReturn FindString(LCase(GetGadgetItemText(gadget, item, column)), LCase(searchString$))
EndProcedure

Procedure AddString(stringID, englishString$, germanString$, addNotExisting, ignoreUnused)
	alreadyExisting = #False
	ForEach Strings()
		If Strings()\englishString = englishString$
			Strings()\ignoreUnused = ignoreUnused
			If germanString$
				Strings()\germanString = germanString$
			EndIf
			alreadyExisting = #True
			Break
		EndIf
	Next
	If Not alreadyExisting
		If addNotExisting
			If stringID = -1
				stringID = FindEmptySlot()
			EndIf
			AddElement(Strings())
			Strings()\stringID = stringID
			Strings()\englishString = englishString$
			Strings()\germanString = germanString$
			Strings()\ignoreUnused = ignoreUnused
		Else
			AddGadgetItem(#InfoList, -1, "String ID " + Str(stringID) + " is not used anymore: " + englishString$)
		EndIf
	EndIf
EndProcedure

Procedure ScanStringsInFile(fileName$)
	stringIDRegEx = CreateRegularExpression(#PB_Any, "StringID:([0-9\-]+)\(" + Chr(34) + "(.*?)" + Chr(34) + "\)")
	idRegEx = CreateRegularExpression(#PB_Any, "StringID:([0-9\-]+)")
	stringRegEx = CreateRegularExpression(#PB_Any, Chr(34) + "(.*?)" + Chr(34))
	file = ReadFile(#PB_Any, fileName$)
	If IsFile(file)
		Repeat
			lineIndex + 1
			line$ = ReadString(file)
			Dim matches$(0)
			count = ExtractRegularExpression(stringIDRegEx, line$, matches$())
			For match = 0 To count - 1
				Dim ids$(0)
				ExtractRegularExpression(idRegEx, matches$(match), ids$())
				stringID = Val(RemoveString(ids$(0), "StringID:"))
				Dim strings$(0)
				ExtractRegularExpression(stringRegEx, matches$(match), strings$())
				string$ = Trim(strings$(0), Chr(34))
				If string$
					AddString(stringID, string$, "", #True, #False)
				Else
					AddGadgetItem(#InfoList, -1, "Warning: Missing text for string ID " + Str(stringID) + " in " +fileName$ + ":" + Str(lineIndex))
				EndIf
			Next
		Until Eof(file)
		CloseFile(file)
	Else
		AddGadgetItem(#InfoList, -1, "Error: Unable to read file: " + fileName$)
	EndIf
EndProcedure

Procedure ScanStringsInDirectory(path$)
	dir = ExamineDirectory(#PB_Any, path$, "*.*")
	If IsDirectory(dir)
		While NextDirectoryEntry(dir)
			name$ = DirectoryEntryName(dir)
			If name$ <> "." And name$ <> ".."
				Select DirectoryEntryType(dir)
					Case #PB_DirectoryEntry_File
						If GetExtensionPart(name$) = "inc"
							ScanStringsInFile(path$ + "\" + name$)
						EndIf
					Case #PB_DirectoryEntry_Directory
						ScanStringsInDirectory(path$ + "\" + name$)
				EndSelect
			EndIf
		Wend
		FinishDirectory(dir)
	EndIf
EndProcedure

Procedure LoadLanguageStrings()
	ClearGadgetItems(#List)
	ScanStringsInDirectory(serverRoot$ + "includes\grgserver")
	If LoadXML(#XML, xmlFile$)
		If XMLStatus(#XML) = #PB_XML_Success
			*mainNode = MainXMLNode(#XML)
			If *mainNode
				*stringNode = XMLNodeFromPath(*mainNode, "string")
				While *stringNode
					stringID = Val(GetXMLAttribute(*stringNode, "id"))
					ignoreUnused = Val(GetXMLAttribute(*stringNode, "ignoreUnused"))
					englishString$ = ""
					*languageNode = XMLNodeFromPath(*stringNode, "en")
					If *languageNode
						englishString$ = TrimEx(GetXMLNodeText(*languageNode))
					EndIf
					germanString$ = ""
					*languageNode = XMLNodeFromPath(*stringNode, "de")
					If *languageNode
						germanString$ = TrimEx(GetXMLNodeText(*languageNode))
					EndIf
					AddString(stringID, englishString$, germanString$, ignoreUnused, ignoreUnused)
					*stringNode = NextXMLNode(*stringNode)
				Wend
				SetFileChangedState(#False)
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
	EndIf
	SortStructuredList(Strings(), #PB_Sort_Ascending, OffsetOf(Strings\stringID), #PB_Long)
	highestStringID = 0
	ForEach Strings()
		highestStringID = Strings()\stringID
		AddGadgetItem(#List, -1, Str(Strings()\stringID) + Chr(10) + Strings()\englishString + Chr(10) + Strings()\germanString)
		If Strings()\ignoreUnused
			item = CountGadgetItems(#List) - 1
			SetGadgetItemColor(#List, item, #PB_Gadget_BackColor, RGB(255, 200, 200), -1)
			SetGadgetItemData(#List, item, #True)
		EndIf
	Next
	AddGadgetItem(#InfoList, -1, "Note: MAX_LANGUAGE_STRINGS should be at least " + highestStringID + ".")
EndProcedure

; Procedure SaveLanguageStrings()
; 	file = CreateFile(#PB_Any, xmlFile$)
; 	If IsFile(file)
; 		WriteStringN(file, "<?xml version=" + Chr(34) + "1.0" + Chr(34) + " encoding=" + Chr(34) + "ISO-8859-1" + Chr(34) + "?>")
; 		WriteStringN(file, "<languagestrings>")
; 		For item = 0 To CountGadgetItems(#List) - 1
; 			WriteStringN(file, Chr(9) + "<string id=" + Chr(34) + GetGadgetItemText(#List, item, 0) + Chr(34) + ">")
; 			WriteStringN(file, Chr(9) + Chr(9) +"<en>" + EscapeXMLCharacters(GetGadgetItemText(#List, item, 1)) + "</en>")
; 			WriteStringN(file, Chr(9) + Chr(9) +"<de>" + EscapeXMLCharacters(GetGadgetItemText(#List, item, 2)) + "</de>")
; 			WriteStringN(file, Chr(9) + "</string>")
; 		Next
; 		WriteString(file, "</languagestrings>")
; 		CloseFile(file)
; 		SetFileChangedState(#False)
; 		ProcedureReturn #True
; 	EndIf
; EndProcedure

Procedure SaveLanguageStrings()
	xml = CreateXML(#PB_Any, #PB_Ascii)
	If IsXML(xml)
		*mainNode = CreateXMLNode(RootXMLNode(xml))
		SetXMLNodeName(*mainNode, "languagestrings")
		For item = 0 To CountGadgetItems(#List) - 1
			*stringNode = CreateXMLNode(*mainNode)
			SetXMLNodeName(*stringNode, "string")
			SetXMLAttribute(*stringNode, "id", GetGadgetItemText(#List, item, 0))
			If GetGadgetItemData(#List, item)
				SetXMLAttribute(*stringNode, "ignoreUnused", "1")
			EndIf
			*englishNode = CreateXMLNode(*stringNode)
			SetXMLNodeName(*englishNode, "en")
			SetXMLNodeText(*englishNode, GetGadgetItemText(#List, item, 1))
			*germanNode = CreateXMLNode(*stringNode)
			SetXMLNodeName(*germanNode, "de")
			SetXMLNodeText(*germanNode, GetGadgetItemText(#List, item, 2))
		Next
		FormatXML(xml, #PB_XML_LinuxNewline | #PB_XML_ReIndent | #PB_XML_ReFormat, 4)
		SaveXML(xml, xmlFile$)
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

Procedure SearchStringInList(string$)
	startingItem = GetGadgetState(#List) + 1
	If startingItem >= CountGadgetItems(#List)
		startingItem = 0
	EndIf
	foundItem = -1
	For item = startingItem To CountGadgetItems(#List) - 1
		For column = 1 To listColumn
			If FindListItem(#List, item, column, string$)
				foundItem = item
				Break
			EndIf
		Next
		If foundItem <> -1
			Break
		EndIf
	Next
	If foundItem = -1 And startingItem > 0
		For item = 0 To startingItem -1
			For column = 1 To listColumn
				If FindListItem(#List, item, column, string$)
					foundItem = item
					Break
				EndIf
			Next
			If foundItem <> -1
				Break
			EndIf
		Next
	EndIf
	If foundItem = -1
		MessageRequester("Search string", "The entered string '" + string$ + "' was not found!", #MB_ICONERROR)
	Else
		SetGadgetState(#List, foundItem)
	EndIf
EndProcedure

serverRoot$ = ProgramParameter()
If serverRoot$ = ""
	mainPath$ = GetPathPart(ProgramFilename())
	serverRoot$ = GetPathPart(Left(mainPath$, Len(mainPath$) - 1))
EndIf

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
		MenuBar()
		MenuItem(#Menu_Goto, "Goto ID" + Chr(9) + "Ctrl+G")
		MenuItem(#Menu_Search, "Search" + Chr(9) + "Ctrl+F")
		MenuItem(#Menu_SearchNext, "Search next" + Chr(9) + "F3")
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
	AddKeyboardShortcut(#Window, #PB_Shortcut_Control | #PB_Shortcut_G, #Menu_Goto)
	AddKeyboardShortcut(#Window, #PB_Shortcut_Control | #PB_Shortcut_F, #Menu_Search)
	AddKeyboardShortcut(#Window, #PB_Shortcut_F3, #Menu_SearchNext)
	SetGadgetState(#Splitter, 400)
	LoadLanguageStrings()
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
						EditOK()
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
					Case #Menu_Goto
						string$ = Trim(InputRequester("Goto string ID", "Enter the string ID you want to go to.", ""))
						If string$
							stringID = Val(string$)
							If Str(stringID) = string$
								startingItem = GetGadgetState(#List) + 1
								If startingItem >= CountGadgetItems(#List)
									startingItem = 0
								EndIf
								foundItem = -1
								For item = startingItem To CountGadgetItems(#List) - 1
									If FindListItem(#List, item, 0, string$)
										foundItem = item
										Break
									EndIf
								Next
								If foundItem = -1 And startingItem > 0
									For item = 0 To startingItem -1
										If FindListItem(#List, item, 0, string$)
											foundItem = item
											Break
										EndIf
									Next
								EndIf
								If foundItem = -1
									MessageRequester("Goto string ID", "The entered string ID '" + string$ + "' was not found!", #MB_ICONERROR)
								Else
									SetGadgetState(#List, foundItem)
								EndIf
							Else
								MessageRequester("Not a number", "The entered text is not a number!", #MB_ICONERROR)
							EndIf
						EndIf
					Case #Menu_Search
						string$ = Trim(InputRequester("Search string", "Enter the string you want to search for.", searchedString$))
						If string$
							searchedString$ = string$
							SearchStringInList(string$)
						EndIf
					Case #Menu_SearchNext
						If searchedString$
							SearchStringInList(searchedString$)
						Else
							string$ = Trim(InputRequester("Search string", "Enter the string you want to search for.", searchedString$))
							If string$
								searchedString$ = string$
								SearchStringInList(string$)
							EndIf
						EndIf
					Case #Edit_OK
						EditOK()
					Case #Edit_Cancel
						CloseEditWindow()
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
; IDE Options = PureBasic 5.11 (Windows - x86)
; CursorPosition = 340
; FirstLine = 331
; Folding = ----
; EnableXP
; UseIcon = Language String Editor.ico
; Executable = Language String Editor.exe
; CommandLine = X:\Projects\SAMP-Server\
; EnableCompileCount = 235
; EnableBuildCount = 10
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
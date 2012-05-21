Procedure OpenNetworkConnectionEx(url)
	url$ = PeekS(url)
	Select UCase(Trim(StringField(url$, 1, ":")))
		Case "TCP"
			type = #PB_Network_TCP
		Case "UDP"
			type = #PB_Network_UDP
		Default
			type = #PB_Network_TCP
	EndSelect
	serverName$ = Trim(StringField(url$, 2, ":"))
	connection = OpenNetworkConnection(Mid(serverName$, 3), Val(Trim(StringField(url$, 3, ":"))), type)
	If connection
		CloseNetworkConnection(connection)
	EndIf
EndProcedure

Procedure Knock(serverName$, port, type$, timeout)
	url$ = type$+"://" + serverName$ + ":" + Str(port)
	PrintN("Knocking port " + Str(port) +"/" + type$ + "...")
	threadID = CreateThread(@OpenNetworkConnectionEx(), @url$)
	For delay = 1 To timeout Step 10
		Delay(10)
		If Not IsThread(threadID)
			Break
		EndIf
	Next
	If IsThread(threadID)
		KillThread(threadID)
	EndIf
	ProcedureReturn delay
EndProcedure

mainPath$ = GetPathPart(ProgramFilename())
keyFile$ = "Tunnel.ppk"

timeout = Val(ProgramParameter())

If timeout < 100
	timeout = 1000
EndIf

InitNetwork()

SetCurrentDirectory(mainPath$)

If OpenConsole()
	ConsoleTitle("Tunnel Connector")
	keyFile = ReadFile(#PB_Any, keyFile$)
	If IsFile(keyFile)
		CloseFile(keyFile)
		Restore KnockPorts
		For byte = ?KnockPorts To ?EndPorts
			Read port
			Knock("selfcoders.com", port, "TCP", timeout)
			byte + 4
		Next
		RunProgram(mainPath$ + "plink.exe", "-ssh -v -N -L 3306:127.0.0.1:3306 -l tunnel -i " + keyFile$ + " selfcoders.com", mainPath$, #PB_Program_Wait)
		PrintN("")
		PrintN("Connection closed")
	Else
		PrintN("There is no " + GetFilePart(keyFile$) + " file!")
	EndIf
	Repeat
		Delay(100)
	ForEver
EndIf

DataSection
	KnockPorts:
		Data.l 17362, 13173, 18654, 19815
	EndPorts:
EndDataSection
; IDE Options = PureBasic 4.60 (Windows - x86)
; CursorPosition = 40
; FirstLine = 17
; Folding = -
; EnableXP
; UseIcon = Tunnel Connector.ico
; Executable = Tunnel Connector.exe
; EnableCompileCount = 6
; EnableBuildCount = 6
; EnableExeConstant
; IncludeVersionInfo
; VersionField0 = 1,0,0,0
; VersionField1 = 1,0,0,0
; VersionField2 = SelfCoders
; VersionField3 = Tunnel Connector
; VersionField4 = 1.0
; VersionField5 = 1.0
; VersionField6 = Tunnel Connector
; VersionField7 = Tunnel Connector
; VersionField8 = %EXECUTABLE
; VersionField13 = tools@selfcoders.com
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
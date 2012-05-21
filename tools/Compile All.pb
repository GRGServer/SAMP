Global mainPath$
Global serverRoot$

Procedure CompileEx(type$, file$)
	PrintN("Compiling " + type$ + "/" + file$ + "...")
	program = RunProgram(serverRoot$ + "tools\pawn\pawncc.exe", file$ + " " + Chr(34) + "-i" + serverRoot$ + "includes" + Chr(34) + " -; -(", serverRoot$ + type$, #PB_Program_Open | #PB_Program_Read)
	If program
		Repeat
			If AvailableProgramOutput(program)
				PrintN(ReadProgramString(program))
			EndIf
			stdErr$ = ReadProgramError(program)
			If stdErr$
				If errors$
					errors$ + Chr(13)
				EndIf
				errors$ + stdErr$
			EndIf
		Until Not ProgramRunning(program)
		If errors$
			PrintN(errors$)
		EndIf
		CloseProgram(program)
		ProcedureReturn #True
	Else
		PrintN("Unable to launch the pawn compiler!")
	EndIf
EndProcedure

Procedure Compile(type$)
	directory = ExamineDirectory(#PB_Any, serverRoot$ + type$, "*.pwn")
	If IsDirectory(directory)
		While NextDirectoryEntry(directory)
			file$ = DirectoryEntryName(directory)
			If DirectoryEntryType(directory) = #PB_DirectoryEntry_File And file$ <> "." And file$ <> ".."
				CompileEx(type$, file$)
				PrintN("")
			EndIf
		Wend
		FinishDirectory(directory)
	EndIf
EndProcedure

mainPath$ = GetPathPart(ProgramFilename())
serverRoot$ = GetPathPart(Left(mainPath$, Len(mainPath$) - 1))

If OpenConsole()
	ConsoleTitle("Compile All")
	PrintN("Server root: " + serverRoot$)
	PrintN("")
	Compile("filterscripts")
	Compile("gamemodes")
	Compile("npcmodes")
	PrintN("")
	PrintN("Done")
	Repeat
		Delay(100)
	ForEver
EndIf
; IDE Options = PureBasic 4.60 (Windows - x86)
; CursorPosition = 29
; Folding = -
; EnableXP
; UseIcon = Compile All.ico
; Executable = Compile All.exe
; EnableCompileCount = 9
; EnableBuildCount = 8
; EnableExeConstant
; IncludeVersionInfo
; VersionField0 = 1,0,0,0
; VersionField1 = 1,0,0,0
; VersionField2 = SelfCoders
; VersionField3 = Compile all GRG Scripts
; VersionField4 = 1.0
; VersionField5 = 1.0
; VersionField6 = Compile all GRG Scripts
; VersionField7 = Compile all GRG Scripts
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
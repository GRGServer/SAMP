Copy pawn.api to %PROGRAMFILES%\Notepad++\plugins\APIs

Copy insertExt.ini and userDefineLang.xml to %APPDATA%\Notepad++

Install NppExec plugin

Select Plugins > NppExec > Execute...

Paste the following code:

NPP_SAVE
cd $(CURRENT_DIRECTORY)
"<Path to SAMP-Root>\tools\pawn\pawncc.exe" "$(FILE_NAME)" "-i<Path to SAMP-Root>\includes" -; -(

Save
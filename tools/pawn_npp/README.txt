Copy pawn.api to %PROGRAMFILES%\Notepad++\plugins\APIs

Copy insertExt.ini and userDefineLang.xml to %APPDATA%\Notepad++

Install NppExec plugin

Select Plugins > NppExec > Execute...


Paste the following code:

NPP_SAVE
cd $(CURRENT_DIRECTORY)
"X:\Projects\SAMP-Server\pawno\pawncc.exe" "$(FILE_NAME)" -; -(

Save
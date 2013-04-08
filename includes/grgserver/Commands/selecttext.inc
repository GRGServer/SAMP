CMD:selecttext(playerID, params[], 629)
{
    SendClientMessageEx(playerID, 0xFFFFFFFF, 630);
	for(new i = 0; i < MAX_TEXT_DRAWS; i++) 	TextDrawSetSelectable(Text:i, 1); 
	printf("Ausgeführt PlayerTextDrawSetSelectable");
	return COMMAND_OK;
}
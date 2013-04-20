/**
 * <summary>
 *	This callback gets called once a player sent a command it got performed.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which sent the command.
 * </param>
 *
 * <param name="command">
 *	The name of the command without the slash.
 * </param>
 *
 * <param name="parameters">
 *	The parameters passed to the command.
 * </param>
 *
 * <param name="returnCode">
 *	The return code of the command.
 * </param>
 *
 * <param name="isAlias">
 *	<item>true if the command has been executed using an alias</item>
 *	<item>false if this command has been typed directly by the player</item>
 * </param>
 */

OnPlayerCommandPerformed(playerID, command[], parameters[], returnCode, isAlias)
{
	switch (returnCode)
	{
		case COMMAND_ERROR:
		{
			PlaySound(playerID, SOUND_COMMAND_ERROR);
			SendClientMessageEx(playerID, COLOR_ERROR, "143");
		}
		case COMMAND_NOT_FOUND:
		{
			if (isAlias)
			{
				PlaySound(playerID, SOUND_COMMAND_ERROR);
				SendClientMessageEx(playerID, COLOR_ERROR, "520", command);
				SendClientMessageEx(playerID, COLOR_ERROR, "82");
			}
			else
			{
				new aliasCommandText[MAX_FUNCTION_NAME];
				MySQLQuery("SELECT * FROM `cmdaliases` WHERE `name` = '%s'", MySQLEscapeString(command));
				mysql_store_result();
				if (mysql_num_rows())
				{
					strcat(aliasCommandText, GetMySQLField("command"));
				}
				mysql_free_result();
				if (strlen(aliasCommandText))
				{
					new aliasParameters[256];
					new aliasCommand[MAX_FUNCTION_NAME];
					if (!sscanf(aliasCommandText, "ss", aliasCommand, aliasParameters))
					{
						if (StrNotNull(parameters))
						{
							strcat(aliasParameters, " ");
							strcat(aliasParameters, parameters);
						}
					}
					else
					{
						strcat(aliasParameters, parameters);
					}
					ExecuteCommand(playerID, aliasCommand, aliasParameters, true);
				}
				else
				{
					PlaySound(playerID, SOUND_COMMAND_ERROR);
					SendClientMessageEx(playerID, COLOR_ERROR, "521");
					SendClientMessageEx(playerID, COLOR_ERROR, "82");
				}
			}
		}
		case COMMAND_NOT_IN_VEHICLE:
		{
			SendClientMessageEx(playerID, COLOR_ERROR, "146");
		}
		case COMMAND_NPC_ONLY:
		{
			SendClientMessageEx(playerID, COLOR_ERROR, "145");
		}
		case COMMAND_OK:
		{
			PlaySound(playerID, SOUND_COMMAND_OK);
		}
		case COMMAND_OK_NOSOUND:
		{
			// Command executed successfully -> Do nothing
		}
		case COMMAND_PERMISSION_DENIED:
		{
			PlaySound(playerID, SOUND_COMMAND_DENIED);
			SendClientMessageEx(playerID, COLOR_ERROR, "148");
			printf("%s tried to execute /%s but has not the required permission!", GetPlayerNameEx(playerID), command);
		}
		case COMMAND_PLAYER_NOT_FOUND:
		{
			SendClientMessageEx(playerID, COLOR_ERROR, "147");
		}
		case COMMAND_TELEPORTED:
		{
			SendClientMessageEx(playerID, COLOR_INFO, "144");
		}
		case COMMAND_USAGE:
		{
			// Command usage message displayed -> Nothing to do yet
		}
		default:
		{
			printf("Unknown command return code from /%s: %d", command, returnCode);
			return false;
		}
	}
	return true;
}
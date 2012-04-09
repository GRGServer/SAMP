#define GetStringArg(%0,%1); \
for(new i_%0 = 0; ; ++i_%0) \
{ \
	if((%1[i_%0] = getarg((%0), i_%0)) != EOS) \
		continue; \
	else \
		break; \
}


// Commands
#define CMD:%0(%1,%2,%3) COMMAND:%0(%1, %2)
#define NCMD:%0(%1,%2,%3) COMMAND:%0(%1, %2) if (!IsPlayerNPC(%1)) return COMMAND_NPC_ONLY; else
#define PCMD:%0[%1](%2,%3,%4) COMMAND:%0(%2, %3) if (!permissions[%2][PERMISSION_%1]) return COMMAND_PERMISSION_DENIED; else
#define RCMD:%0(%1,%2) forward rcmd_%0(%1); public rcmd_%0(%1)


// Functions
#define Count%0(%1,%2) for (new %1 = 0; %1 < %2; %1++)
#define Exec:%0(%1) %0(%1); print("Done"); return true
#define Format:%0(%1) format(%0, sizeof(%0), %1)
#define FormatNew:%0[%1](%2) new %0[%1]; Format:%0(%2)
#define FormatMoney(%0) FormatNumber(Float:%0, 2, '.', ',')
#define GetUserDBValue(%0,%1) GetMySQLValue("users", %1, "UserID", val2str(PVar:%0[USERID]))
#define IsKeyPressed(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define LoadPermission:%0(%1,%2) permissions[%1][PERMISSION_%0] = strval(GetMySQLField(%2))
#define MD5(%0) MD5_Hash(%0, true)
#define MySQLQuery(%0) Format:sqlQuery(%0); mysql_query(sqlQuery)
#define PlayerLoop(%0) Count(%0, maxPlayers)
#define PTextDraw:%0[%1] PVar:%0[TEXTDRAW_%1]
#define PVar:%0[%1] playerVariables[%0][PVAR_%1]
#define SetPVarStr:%0[%1][%2](%3) format(PVar:%0[%1], %2, %3)
#define SetUserDBValue(%0,%1,%3) SetMySQLValue("users", %1, %3, "UserID", val2str(PVar:%0[USERID]))
#define StartTimer:%0(%1,%2) SetTimer(%1, TIMER_%0, %2); printf("Timer %s (Interval: %d; Repeating: %d) started", %1, TIMER_%0, %2)
#define Timer:%0(%1) forward Timer_%0(%1); public Timer_%0(%1)
#define UpdateUserDB(%0,%1) Format:sqlQuery(%1); Format:sqlQuery("UPDATE `users` SET %s WHERE `UserID` = '%d'", sqlQuery, PVar:%0[USERID]); mysql_query(sqlQuery)
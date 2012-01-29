#define getStringArg(%0,%1); \
	for(new i_%0 = 0; ; ++i_%0) \
	{ \
		if((%1[i_%0] = getarg((%0), i_%0)) != EOS) \
			continue; \
		else \
			break; \
	}

#define md5(%0) MD5_Hash(%0, true)

#define getUserDBValue(%0,%1) getMySQLValue("users", %1, "UserID", val2str(GetPVarInt(%0, "UserID")))
#define setUserDBValue(%0,%1,%3) setMySQLValue("users", %1, %3, "UserID", val2str(GetPVarInt(%0, "UserID")))
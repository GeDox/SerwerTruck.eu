#define MAX_CRASHS 80

enum E_CRASH
{
	crashNick[MAX_PLAYER_NAME],
	Float:crashPos[3],
	crashTime
}

new pCrash[MAX_CRASHS][E_CRASH];
new Float:pTempPos[MAX_PLAYERS][3];

stock Crash_OnGameModeInit()
{
	SetTimer("TruncateCrashTable", 5 * 60 * 1000, true);
	return 1;
}

stock Crash_OnPlayerConnect(playerid)
{
	for(new i = 0; i < MAX_CRASHS; i++)
	{
		if(!IsValidCrash(i))
			continue;

		if(!strcmp(PlayerName(playerid), pCrash[i][crashNick]))
		{
			printf("Wczytano crash gracza %s.", PlayerName(playerid));
			if((gettime() - pCrash[i][crashTime]) <= 300) // ca�e 5 minut na powr�t
			{
				Msg(playerid, COLOR_INFO, "Twoje statystyki zosta�y przywr�cone. Mo�esz teleportowa� si� do pozycji przed crashem/timeoutem u�ywaj�c komendy {b}/lastpos{/b}.");
				pTempPos[playerid][0] = pCrash[i][crashPos][0];
				pTempPos[playerid][1] = pCrash[i][crashPos][1];
				pTempPos[playerid][2] = pCrash[i][crashPos][2];
			}

			pCrash[i][crashTime] = 0;
			pCrash[i][crashPos][0] = 0.0;
			pCrash[i][crashPos][1] = 0.0;
			pCrash[i][crashPos][2] = 0.0;
			pCrash[i][crashNick] = EOS;
			break;
		}
	}
	return 1;
}

stock Crash_OnPlayerDisconnect(playerid, reason)
{
	if((reason == 0 || reason == 2) && IsPlayerLogged(playerid) && IsPlayerSpawned(playerid))
	{
		for(new i = 0; i < MAX_CRASHS; i++)
		{
			if(IsFreeCrash(i))
			{
				strcat(pCrash[i][crashNick], PlayerName(playerid));
				GetPlayerPos(playerid, pCrash[i][crashPos][0], pCrash[i][crashPos][1], pCrash[i][crashPos][2]);
				pCrash[i][crashTime] = gettime();
				break;
			}
		}
	}
	if(pTempPos[playerid][0] != 0 && pTempPos[playerid][1] != 0 && pTempPos[playerid][2] != 0)
	{
		pTempPos[playerid][0] = 0.0;
		pTempPos[playerid][1] = 0.0;
		pTempPos[playerid][2] = 0.0;
	}
	return 1;
}

stock IsValidCrash(crashid)
{
	if(pCrash[crashid][crashTime] <= 0)
		return false;
	return true;
}

stock IsFreeCrash(crashid)
{
	if(pCrash[crashid][crashTime] <= 0)
		return true;
	return false;
}

forward TruncateCrashTable();
public TruncateCrashTable()
{
	for(new i = 0; i < MAX_CRASHS; i++)
	{
		if((gettime() - pCrash[i][crashTime]) > 300) // ca�e 5 minut na powr�t, teraz tesetujemy je�eli gracz nie wr�ci� ;P 
		{
			pCrash[i][crashTime] = 0;
			pCrash[i][crashPos][0] = 0.0;
			pCrash[i][crashPos][1] = 0.0;
			pCrash[i][crashPos][2] = 0.0;
			pCrash[i][crashNick] = EOS;
		}
	}
	return 1;
}

CMD:lastpos(playerid)
{
	if(pTempPos[playerid][0] == 0 && pTempPos[playerid][1] == 0 && pTempPos[playerid][2] == 0)
		return Msg(playerid, COLOR_ERROR, "Brak pozycji do wczytania.");
	Teleport(playerid, pTempPos[playerid][0], pTempPos[playerid][1], pTempPos[playerid][2], true);
	Msg(playerid, COLOR_INFO, "Pozycja {b}crashu / timeoutu{/b} zosta�a wczytana.");
	pTempPos[playerid][0] = 0.0;
	pTempPos[playerid][1] = 0.0;
	pTempPos[playerid][2] = 0.0;
	return 1;
}
forward Sytuacje_OneMinPlayerTimer(playerid);
public Sytuacje_OneMinPlayerTimer(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))
		return 0;

	switch(random(20))
	{
		case 0: 
		{
			if(GetDTime(playerid) < 7200)
				return 0;

			SetPlayerDrunkLevel(playerid, 5500);
			Msg(playerid, COLOR_INFO2, "Zm�czy�e� si�, zbyt d�ugo je�dzisz!");
		} // gdy za d�ugo je�dzi - b�dzie mia� ciemniejszy ekran + drunk

		case 1: 
		{

		} // gdy b�dzie za g�odny
		
		case 2: 
		{
			SetPVarInt(playerid, "zaslabl", 1);
			Msg(playerid, COLOR_ERROR, "Zas�ab�e� za kierownic�!");
			TogglePlayerControllable(playerid, false);
			SetTimerEx("Zaslabniecie", 15000, false, "d", playerid);
		} // po prostu zas�abni�cie

		default: {} // nic
	}
	return 1;
}

forward Zaslabniecie(playerid);
public Zaslabniecie(playerid)
{
	if(!IsPlayerConnected(playerid) || !GetPVarInt(playerid, "zaslabl"))
		return 0;

	TogglePlayerControllable(playerid, true);
	DeletPVar(playerid, "zaslabl");
	Msg(playerid, COLOR_INFO, "Odzyska�e� si�y, lepiej nie wsiadaj za k�ko.");
	return 1;
}

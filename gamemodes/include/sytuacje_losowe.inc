forward Sytuacje_OneMinPlayerTimer(playerid);
public Sytuacje_OneMinPlayerTimer(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))
		return 0;

	switch(random(20))
	{
		case 0: {} // gdy za d�ugo je�dzi - b�dzie mia� ciemniejszy ekran + drunk
		case 1: {} // gdy b�dzie za g�odny
		case 2: {} // po prostu zas�abni�cie
		default: {} // nic
	}
	return 1;
}
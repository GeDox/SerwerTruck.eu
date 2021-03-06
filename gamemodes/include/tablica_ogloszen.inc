enum eTablicaOgloszen
{
	UID,
	Float:PostionX,
	Float:PostionY,
	Float:PostionZ
};

new Float:TablicaOgloszen[][eTablicaOgloszen] = {
	{0, 1623.4889,-1045.8835,23.8984},
	{1, 1396.1667,1007.4241,10.9297},
	{2, -242.1355,-236.4762,2.4297},
	{3, -2137.5225,-135.9968,35.3203}
};

forward TablicaOgloszen_OnGameModeInit();
public TablicaOgloszen_OnGameModeInit()
{
	new szString[128];
	Loop(i, sizeof TablicaOgloszen)
	{
		format(szString, sizeof szString, "Tablica og�osze� w {b}%s{/b}.\nWpisz {b}/tablica{/b} aby u�y�.", GetPointZone(TablicaOgloszen[i][PostionX], TablicaOgloszen[i][PostionY]));
		CreateDynamicObject(2737, TablicaOgloszen[i][PostionX], TablicaOgloszen[i][PostionY], TablicaOgloszen[i][PostionZ], 0.0, 0.0, 0.0, -1, -1, -1, 100);
   		CreateDynamic3DTextLabel(clText(COLOR_INFO, szString), -1, TablicaOgloszen[i][PostionX], TablicaOgloszen[i][PostionY], TablicaOgloszen[i][PostionZ], 20.0);
	}
}

CMD:tablica(playerid, params[])
{
	new bool:find=false;

	Loop(i, sizeof TablicaOgloszen)
		if(GetDistanceFromMeToPoint(playerid, TablicaOgloszen[i][PostionX], TablicaOgloszen[i][PostionY], TablicaOgloszen[i][PostionZ]) <= 20)
		{
			new wiadomosc[600], zapytanie[70];

			mysql_query("SELECT `owner`, `text`, `time` FROM `st_tablica_ogloszen` ORDER BY `time` DESC LIMIT 0,10");
			mysql_store_result();

			if(mysql_num_rows()==0)
				strcat(wiadomosc, "Brak og�osze�.");
			else
			{
				format(wiadomosc, sizeof(wiadomosc), "Gracz\tWiadomo��\tData\n");
				while(mysql_fetch_row(zapytanie, "|")) 
				{
			    	mysql_fetch_field("owner", zapytanie);
			    	strcat(wiadomosc, zapytanie);
			    	strcat(wiadomosc, "\t");

			    	mysql_fetch_field("text", zapytanie);
			    	strcat(wiadomosc, zapytanie);
			    	strcat(wiadomosc, "\t");

			    	mysql_fetch_field("time", zapytanie);
			    	strcat(wiadomosc, zapytanie);
			    	strcat(wiadomosc, "\n");
				} 
			}

			find=true;
			Dialog_Show(playerid, DIALOG_ID_OGLOSZENIE, (mysql_num_rows() ? DIALOG_STYLE_TABLIST_HEADERS : DIALOG_STYLE_MSGBOX), "Og�oszenia", wiadomosc, "Dodaj", "Zamknij");
			break;
		}

	if(!find)
		ShowInfo(playerid, "Nie znajdujesz si� obok tablicy og�osze�.");

	return 1;
}

Dialog:DIALOG_ID_OGLOSZENIE(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	return Dialog_Show(playerid, DIALOG_ID_OGLOSZENIE_DODAJ, DIALOG_STYLE_INPUT, "Og�oszenia > Dodaj", "Dodanie og�oszenia kosztuje: $2000\nMaksymalna ilo�� znak�w: 60\n\nWpisz tre��:", "Dodaj", "Zamknij");
}

Dialog:DIALOG_ID_OGLOSZENIE_DODAJ(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	if(GetMoney(playerid) < 2000)
		return ShowInfo(playerid, "Masz zbyt ma�o pieni�dzy.");

	new Name[32], tekst[120], wiadomosc[60];

	format(wiadomosc, sizeof(wiadomosc), "%s", inputtext);
	GiveMoney(playerid, -2000);

	mysql_real_escape_string(PlayerName(playerid), Name);		
	mysql_real_escape_string(wiadomosc, wiadomosc);

	delstr(wiadomosc, "{");
	delstr(wiadomosc, "}");
	delstr(wiadomosc, "\t");
	delstr(wiadomosc, "\n");

	format(tekst, sizeof(tekst), "INSERT INTO `st_tablica_ogloszen` (`owner`, `text`) VALUES ('%s', '%s')", Name, wiadomosc);
	mysql_query(tekst);


	return cmd_tablica(playerid, "");
}
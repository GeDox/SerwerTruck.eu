//CMD:gps(playerid, params[])
	//return cmd_nawigacja(playerid, params);
CMD:gpsnawi(playerid, params[])
{
	if(GetPVarType(playerid, "GPS_OstatniRaz") == PLAYER_VARTYPE_INT)
		if( (GetTickCount() - GetPVarInt(playerid, "GPS_OstatniRaz"))/1000 < 1.0 )
			return ShowInfo(playerid, "Odczekaj sekund� przed nast�pn� aktualizacj� GPSa.");

	Dialog_Show(playerid, DIALOG_ID_GPS, DIALOG_STYLE_LIST, "GPS System", "Doki towarowe\nStacje\nBary\nSklepy ViaToll\nWy��cz", "Wybierz", "");
	
	return 1;
}

forward GPS_Function(playerid, listitem);
public GPS_Function(playerid, listitem)
{
	if( (GetTickCount() - KtosJuzAktualizujeGPSa)/1000 <= 2)
		return ShowInfo(playerid, "GPS przeci��ony, musisz chwil� odczeka�.");

	KtosJuzAktualizujeGPSa = GetTickCount();

	switch(listitem)
	{
		case 1: // Stacje
		{
			if(GPSGracz[playerid][GPSStacje] || GPSGracz[playerid][GPSDoki] || GPSGracz[playerid][GPSBary] || GPSGracz[playerid][GPSViatoll])
				return ShowInfo(playerid, "Ju� masz w��czonego GPSa, najpierw go wy��cz.");

			for(new i; i <= ID_STACJA; i++)
				if(IsValidDynamicMapIcon(StacjeMapIcon[i][playerid]))
				{
					Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, StacjeMapIcon[i][playerid], E_STREAMER_STREAM_DISTANCE, 6000.0);
					Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, StacjeMapIcon[i][playerid], E_STREAMER_STYLE, MAPICON_GLOBAL);
				}
			GPSGracz[playerid][GPSStacje]=true;
		}
		case 2: // Bary
		{
			if(GPSGracz[playerid][GPSStacje] || GPSGracz[playerid][GPSDoki] || GPSGracz[playerid][GPSBary] || GPSGracz[playerid][GPSViatoll])
				return ShowInfo(playerid, "Ju� masz w��czonego GPSa, najpierw go wy��cz.");

			ShowInfo(playerid, "Funkcja chwilowo wy��czona.");
		}
		case 3: // ViaToll
		{
			if(GPSGracz[playerid][GPSStacje] || GPSGracz[playerid][GPSDoki] || GPSGracz[playerid][GPSBary] || GPSGracz[playerid][GPSViatoll])
				return ShowInfo(playerid, "Ju� masz w��czonego GPSa, najpierw go wy��cz.");

			ShowInfo(playerid, "Funkcja chwilowo wy��czona.");
		}
		case 4: // wy��cz
		{
			if(GPSGracz[playerid][GPSDoki])
			{
				for(new i; i <= ID_DOKOW; i++)
					if(IsValidDynamicMapIcon(LoadingPoinstMapIcon[i][playerid]))
					{
						Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, LoadingPoinstMapIcon[i][playerid], E_STREAMER_STREAM_DISTANCE, 300.0);
						Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, LoadingPoinstMapIcon[i][playerid], E_STREAMER_STYLE, MAPICON_LOCAL);
						Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, LoadingPoinstMapIcon[i][playerid], E_STREAMER_TYPE, 51);
					}

				GPSGracz[playerid][GPSDoki]=false;
			}
			else if(GPSGracz[playerid][GPSStacje])
			{
				for(new i; i <= ID_STACJA; i++)
					if(IsValidDynamicMapIcon(StacjeMapIcon[i][playerid]))
					{
						Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, StacjeMapIcon[i][playerid], E_STREAMER_STREAM_DISTANCE, 300.0);
						Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, StacjeMapIcon[i][playerid], E_STREAMER_STYLE, MAPICON_LOCAL);
					}
				GPSGracz[playerid][GPSStacje]=false;
			}
		}

		case 10..16:
		{
			if(GPSGracz[playerid][GPSStacje] || GPSGracz[playerid][GPSDoki] || GPSGracz[playerid][GPSBary] || GPSGracz[playerid][GPSViatoll])
				return ShowInfo(playerid, "Ju� masz w��czonego GPSa, najpierw go wy��cz.");

			for(new i; i <= ID_DOKOW; i++)
				if(LoadingPoints[i][pType] == listitem-10)
					if(IsValidDynamicMapIcon(LoadingPoinstMapIcon[i][playerid]))
					{
						//Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, LoadingPoinstMapIcon[i][playerid], E_STREAMER_STREAM_DISTANCE, 6000.0);
						Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, LoadingPoinstMapIcon[i][playerid], E_STREAMER_STYLE, MAPICON_GLOBAL);
						Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, LoadingPoinstMapIcon[i][playerid], E_STREAMER_TYPE, 19);
					}

			GPSGracz[playerid][GPSDoki]=true;
		}
	}

	SetPVarInt(playerid, "GPS_OstatniRaz", GetTickCount());
	return 1;
}

Dialog:DIALOG_ID_GPS(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	if(listitem == 0)
		Dialog_Show(playerid, DIALOG_ID_GPS_TYPE, DIALOG_STYLE_LIST, "GPS System => Doki", "Budowlane\nElektroniczne\nArt. spo�ywcze\nArt. odzie�owe\nNiebezpieczne\nNielegalne", "Za�aduj", "Anuluj");
	else
	{
		SetTimerEx("GPS_Function", random(300)+200, false, "dd", playerid, listitem);
		ShowInfo(playerid, "Trwa aktualizacja nawigacji...");
	}

	return 1;
}

Dialog:DIALOG_ID_GPS_TYPE(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	SetTimerEx("GPS_Function", random(300)+200, false, "dd", playerid, listitem+10);
	return ShowInfo(playerid, "Trwa aktualizacja nawigacji...");
}
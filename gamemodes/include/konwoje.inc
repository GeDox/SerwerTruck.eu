#define MAX_CONVOYS 			25
#define MAX_CONVOY_MEMBERS 		20

new pConvoy[MAX_PLAYERS];
new pConvoyInvites[MAX_PLAYERS][MAX_CONVOYS];

enum E_CONVOY
{
	cId,
	cBoss,
	cMembers[MAX_CONVOY_MEMBERS],
	cPersons
}

new cInfo[MAX_CONVOYS][E_CONVOY];

forward Konwoje_OnPlayerConnect(playerid);
public Konwoje_OnPlayerConnect(playerid)
{
	for(new i = 1; i < MAX_CONVOYS; i++)
		pConvoyInvites[playerid][i] = 0;

	pConvoy[playerid] = -1;

	return 1;
}

forward Konwoje_OnPlayerDisconnect(playerid);
public Konwoje_OnPlayerDisconnect(playerid)
{
	if(!GetPVarInt(playerid, "CONVOY_Boss"))
		return 1;

	return DIALOG_CONVOY_MAIN_DEL(playerid, true, 0, "");
}

forward Konwoje_OnPlayerText(playerid, text[]);
public Konwoje_OnPlayerText(playerid, text[])
{
	if(strcmp(text, "!", true, 1) || pConvoy[playerid] < 0)
		return 0;

	new string[200];
	text[1] = toupper(text[1]);
	format(string, sizeof(string), "{FFFF00}!Konw�j >> %s(id:%d): %s", PlayerName(playerid), playerid, text[1]);
		
	Loop(playeri, MAX_PLAYERS)
		if(pConvoy[playerid] == pConvoy[playeri])
			SendClientMessage(playeri, 0x0, string);

	return 1;
}

CMD:konwoj(playerid)
{
	new szString[128], IsBoss = GetPVarInt(playerid, "CONVOY_Boss");
	if(pConvoy[playerid] > -1)
	{
		if(IsBoss)
			format(szString, sizeof szString, "Konw�j (ID: %d)\n \nUczestnicy konwoju\nZapro� graczy (%d/%d)\nWypro� gracza\nUsu� konw�j", pConvoy[playerid], cInfo[pConvoy[playerid]][cPersons], MAX_CONVOY_MEMBERS);
		else
			format(szString, sizeof szString, "Konw�j\n \nUczestnicy konwoju (%d/%d)\nOpu�� konw�j", cInfo[pConvoy[playerid]][cPersons], MAX_CONVOY_MEMBERS);
	
		Dialog_Show(playerid, DIALOG_CONVOY_MAIN, DIALOG_STYLE_LIST, " ", szString, "Wybierz", "Wyjd�");
	}
	else
	{
		Dialog_Show(playerid, DIALOG_CONVOY_CREATE, DIALOG_STYLE_MSGBOX, " ", "Tworzenie konwoju\nStworzenie konwoju jest darmowe. Konw�j mo�e maksymalnie pomie�ci� 20 os�b.\nCzy chcesz stworzy� konw�j?", "Tak", "Wyjd�");
	}
	return 1;
}

CMD:zaproszenia(playerid)
{
	if(pConvoy[playerid] > -1)
		return Msg(playerid, COLOR_ERROR, "Jeste� ju� w konwoju.");
	new szString[256], count;
	for(new i = 0; i < MAX_CONVOYS; i++)
	{
		if(pConvoyInvites[playerid][i] != 0)
		{
			new szTemp[64];
			format(szTemp, sizeof szTemp, "Konw�j gracza %s\n", PlayerName(cInfo[pConvoyInvites[playerid][i]][cBoss]));
			strcat(szString, szTemp);
			count++;
		}
	}
	if(count <= 0)
		format(szString, sizeof szString, "Brak zaprosze�.");

	Dialog_Show(playerid, DIALOG_CONVOY_INV_LIST, DIALOG_STYLE_LIST, " ", szString, "Akceptuj", "Wyjd�");
	return 1;
}

Dialog:DIALOG_CONVOY_INV_LIST(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	new count;
	for(new i = 0; i < MAX_CONVOYS; i++)
		if(pConvoyInvites[playerid][i] > 0)
			count++;

	if(count <= 0)
	{
		if(listitem == 1)
			return cmd_zaproszenia(playerid);
	}
	else
	{
		for(new c = 0; c < MAX_CONVOYS; c++)
		{
			if(listitem == c)
			{
				if(pConvoyInvites[playerid][c] < 0)
					return Msg(playerid, COLOR_ERROR, "Zaproszenie straci�o wa�no��.");
				
				new szTemp[64];
				pConvoy[playerid] = pConvoyInvites[playerid][c];
				format(szTemp, sizeof szTemp, "Pomy�lnie do��czono do konwoju gracza {b}%s{/b}.", PlayerName(cInfo[pConvoy[playerid]][cBoss]));
				Msg(playerid, COLOR_INFO, szTemp);

				format(szTemp, sizeof szTemp, "Gracz {b}%s{/b} do��czy� do twojego konwoju.", PlayerName(playerid));
				Msg(cInfo[pConvoy[playerid]][cBoss], COLOR_INFO, szTemp);

				cInfo[pConvoy[playerid]][cPersons]++;
				break;
			}
		}
	}
	return 1;
}

Dialog:DIALOG_CONVOY_CREATE(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	new free = -1;
	for(new i = 0; i < MAX_CONVOYS; i++)
	{	
		if(cInfo[i][cPersons] == 0)
		{
			free = i;
			break;
		}
	}
	if(free < 0)
		return Msg(playerid, COLOR_ERROR, "Brak wolnych miejsc na konw�j.");

	cInfo[free][cId] = free;
	cInfo[free][cBoss] = playerid;
	cInfo[free][cMembers][0] = playerid;
	cInfo[free][cPersons] = 1;
	SetPVarInt(playerid, "CONVOY_Boss", 1);
	pConvoy[playerid] = free;
	Msg(playerid, COLOR_INFO, "{b}Pomy�lnie{/b} utworzono konw�j. Aby kogo� zaprosi�, ponownie u�yj komendy {b}/konwoj{/b}.");
	return 1;
}

Dialog:DIALOG_CONVOY_MAIN(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	switch(listitem)
	{
		case 0 .. 1:
			return cmd_konwoj(playerid);
		case 2:
		{
			Dialog_Show(playerid, DIALOG_CONVOY_MAIN_LIST, DIALOG_STYLE_MSGBOX, " ", GetConvoyMembers(pConvoy[playerid]), "Wr��", #);
		}
		case 3:
		{
			if(GetPVarInt(playerid, "CONVOY_Boss"))
			{
				if(cInfo[pConvoy[playerid]][cPersons] == MAX_CONVOY_MEMBERS)
				{
					cmd_konwoj(playerid);
					return Msg(playerid, COLOR_ERROR, "Nie mo�esz doda� wi�cej os�b do konwoju.");
				}

				Dialog_Show(playerid, DIALOG_CONVOY_MAIN_INVIT, DIALOG_STYLE_INPUT, " ", "Wprowad� ID lub nick gracza kt�rego chcesz zaprosi�:", "Zapro�", "Wstecz");
			}
			else
			{
				cInfo[pConvoy[playerid]][cPersons]--;
				pConvoy[playerid] = -1;
				Msg(playerid, COLOR_INFO, "Opu�ci�e� konw�j.");
			}
		}
		case 4:
		{
			Dialog_Show(playerid, DIALOG_CONVOY_MAIN_KICK, DIALOG_STYLE_INPUT, " ", "Wprowad� ID lub nick gracza kt�rego chcesz wyprosi�:", "Wypro�", "Wstecz");
		}
		case 5:
		{
			Dialog_Show(playerid, DIALOG_CONVOY_MAIN_DEL, DIALOG_STYLE_MSGBOX, " ", "Czy aby na pewno chcesz usun�� konw�j?", "Tak", "Wstecz");
		}
	}
	return 1;
}

Dialog:DIALOG_CONVOY_MAIN_LIST(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;
	else
		return cmd_konwoj(playerid);
}

Dialog:DIALOG_CONVOY_MAIN_INVIT(playerid, response, listitem, inputtext[])
{
	if(!response)
		return cmd_konwoj(playerid);

	new targetid = GetIDByNick(inputtext);
	if(targetid < 0)
	{
		return Dialog_Show(playerid, DIALOG_CONVOY_MAIN_INVIT, DIALOG_STYLE_INPUT, " ", "Wprowad� ID lub nick gracza kt�rego chcesz zaprosi�:\nNie odnaleziono takiego gracza na serwerze...", "Zapro�", "Wstecz");
	}
	if(pConvoy[targetid] > 0)
		return Dialog_Show(playerid, DIALOG_CONVOY_MAIN_INVIT, DIALOG_STYLE_INPUT, " ", "Wprowad� ID lub nick gracza kt�rego chcesz zaprosi�:\nTen gracz uczestniczy w innym konwoju...", "Zapro�", "Wstecz");

	new szTemp[128];
	format(szTemp, sizeof szTemp, "Pomy�lnie zaproszono gracza {b}%s{/b}.", PlayerName(targetid));
	Msg(playerid, COLOR_INFO, szTemp);

	format(szTemp, sizeof szTemp, "Zosta�es zaproszony do konwoju gracza {b}%s{/b}. Aby odpowiedzie� na zg�oszenie wpisz /zaproszenia.", PlayerName(playerid));
	Msg(targetid, COLOR_INFO, szTemp);

	for(new i = 0; i < MAX_CONVOYS; i++)
	{
		if(pConvoyInvites[targetid][i] == 0)
		{
			pConvoyInvites[targetid][i] = pConvoy[playerid];
			break;
		}
	}
	return 1;
}

Dialog:DIALOG_CONVOY_MAIN_KICK(playerid, response, listitem, inputtext[])
{
	if(!response)
		return cmd_konwoj(playerid);

	new targetid = GetIDByNick(inputtext);
	if(targetid < 0)
	{
		return Dialog_Show(playerid, DIALOG_CONVOY_MAIN_KICK, DIALOG_STYLE_INPUT, " ", "Wprowad� ID lub nick gracza kt�rego chcesz wyprosi�:\nNie odnaleziono takiego gracza na serwerze", "Wypro�", "Wstecz");
	}
	if(pConvoy[targetid] != pConvoy[playerid])
		return Dialog_Show(playerid, DIALOG_CONVOY_MAIN_KICK, DIALOG_STYLE_INPUT, " ", "Wprowad� ID lub nick gracza kt�rego chcesz wyprosi�:\nTen gracz nie uczestniczy w twoim konwoju...", "Zapro�", "Wstecz");
	if(targetid == playerid)
		return Dialog_Show(playerid, DIALOG_CONVOY_MAIN_KICK, DIALOG_STYLE_INPUT, " ", "Wprowad� ID lub nick gracza kt�rego chcesz wyprosi�:\nNie mo�esz wyprosi� samego siebie...", "Zapro�", "Wstecz");

	new szTemp[128];
	format(szTemp, sizeof szTemp, "Gracz {b}%s{/b} zosta� pomy�lnie usuni�ty.", PlayerName(targetid));
	Msg(playerid, COLOR_INFO, szTemp);

	format(szTemp, sizeof szTemp, "Zosta�e� {b}usuni�ty{/b} z konwoju gracza {b}%s{/b}.", PlayerName(playerid));
	Msg(targetid, COLOR_INFO, szTemp);

	pConvoy[targetid] = -1;
	return 1;
}

Dialog:DIALOG_CONVOY_MAIN_DEL(playerid, response, listitem, inputtext[])
{
	if(!response)
		return cmd_konwoj(playerid);

	new konwojid = pConvoy[playerid];
	Msg(playerid, COLOR_ERROR, "Pomy�lnie usuni�to konw�j.");
	DeletePVar(playerid, "CONVOY_Boss");

	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(pConvoy[i] != konwojid)
			continue;

		if(i != playerid)
			Msg(cInfo[pConvoy[playerid]][cMembers][i], COLOR_ERROR, "Tw�j konw�j zosta� {b}usuni�ty{/b} przez za�o�yciela!");

		pConvoy[i] = -1;
		cInfo[pConvoy[playerid]][cMembers][i] = 0;

		for(new c = 0; c < MAX_CONVOYS; c++)
		{
			if(pConvoyInvites[i][c] == pConvoy[playerid])
			{
				pConvoyInvites[i][c] = 0;
				new szTemp[64];
				format(szTemp, sizeof szTemp, "Zaproszenie do konwoju gracza {b}%s{/b} zosta�o cofni�te.", PlayerName(playerid));
				Msg(i, COLOR_INFO, szTemp);
			}
		}
	}

	cInfo[pConvoy[playerid]][cId] = 0;
	cInfo[pConvoy[playerid]][cBoss] = 0;
	cInfo[pConvoy[playerid]][cPersons] = 0;
	return 1;
}

stock GetConvoyMembers(convoyId)
{
	new szString[540];
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && pConvoy[i] == convoyId)
		{
			strcat(szString, PlayerName(i));
			if(i == cInfo[convoyId][cBoss])
				strcat(szString, " (za�o�yciel)");
			strcat(szString, "\n");
		}
	}
	return szString;
}
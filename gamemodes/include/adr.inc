enum
{
	ADR_Level_0, // brak licencji
	ADR_Level_1, // paliwa
	ADR_Level_2, // gazy
	ADR_Level_3  // ca�a reszta
}

// Klasa licencji | Numer pytania | {Pytanie - Odpowied� 1 - Odpowied� 2 - Odpowied� 3} | Prawid�owa odpowied�

new ADR_ReqLvl[] = {
	1, 5, 10
};

new ADR_Cost[] = {
	6000, 4000, 3000
};

new ADR_QuestNumb[] = {
	5, 5, 3
};

new ADRQuestions[][][] = {
	{ADR_Level_1, 1, "{488CDB}1) W jakim miejscu nale�y zatrzymywa� si� z towarem �atwopalnym w celu zrobienia przerwy?{FFFFFF}\n \na) a poboczu drogi\nb) na specjalnym parkingu\nc) gdziekolwiek", 2},
	{ADR_Level_1, 2, "{488CDB}2) Czy mo�na zostawia� za�adowany pojazd bez nadzoru?{FFFFFF}\n \na) tak\nb) nie\nc) nie wiem", 2},
	{ADR_Level_1, 3, "{488CDB}3) Czym jest licencja ADR i na co pozwala?{FFFFFF}\n \na) s� to uprawnienia do przewo�enia towar�w �atwopalnych etc.\nb) s� to uprawnienia do przewo�enia warto�ci pieni�nych\nc) nie s� to �adne specjalne uprawnienia i nic one nie daj�", 1},
	{ADR_Level_1, 4, "{488CDB}4) Towar niebezpieczny wed�ug licencji ADR to:{FFFFFF}\n \na) ka�dy towar przewo�ony w cysternie\nb) ka�dy �adunek przewo�ony bez opakowania\nc) ka�da substancja zakwalifikowana do kt�rej� z klas niebezpiecze�stwa", 3},
	{ADR_Level_1, 5, "{488CDB}5) Kt�re z poni�szych zagro�e� stwarzanych przez towary �atwopalne uznaje si� za najgro�niejsze?{FFFFFF}\n \na) utlenianie\nb) palno��\nc) w�a�ciwo�ci �r�ce", 2},
	{ADR_Level_2, 1, "{488CDB}1) Przed wyruszeniem w drog� z nape�nion� cystern� kierowca musi:{FFFFFF}\n \na) odpocz�� przez pewien czas\nb) zatankowa� ci�gnik do pe�na\nc) sprawdzi� czy naczepa jest bezpieczna", 3},
	{ADR_Level_2, 2, "{488CDB}2) Co grozi pojazdom obok podczas wypadku z pe�n� cystern�?{FFFFFF}\n \na) potencjalne podpalenie\nb) wy��czenie silnika\nc) zgaszenie si� �wiate�", 1},
	{ADR_Level_2, 3, "{488CDB}3) Silne poruszanie si� substancji w zbiorniku cysterny powodowane jest:{FFFFFF}\n \na) przez du�� pr�dko��\nb) przez ostre hamowanie\nc) przez jazd� pod g�rk�", 2},
	{ADR_Level_2, 4, "{488CDB}4) Co nale�y zrobi� po odbyciu kolizji z innym pojazdem maj�c za�adowany towar?{FFFFFF}\n \na) wezwa� pomoc drogow�\nb) wezwa� pogotowie\nc) wezwa� policj�", 1},
	{ADR_Level_2, 5, "{488CDB}5) Dlaczego uderzenie lub tarcie jest niebezpieczne dla towar�w wybuchowych?{FFFFFF}\n \na) poniewa� naczepa jest zbyt s�aba\nb) poniewa� zawsze w ich wyniku ro�nie ci�nienie\nc) poniewa� mog� one zainicjowa� ich wybuch", 3},
	{ADR_Level_3, 1, "{488CDB}1) Towarami wybuchowymi inicjuj�cymi s�:{FFFFFF}\n \na) towary wybuchowe, kt�re s� stosowane do wytwarzania innych towar�w wybuchowych\nb) towary najbardziej wra�liwe\nc) towary zawieraj�ce czarny proch", 2},
	{ADR_Level_3, 2, "{488CDB}2) W celu ochrony przed kradzie�� pojazd przewo��cy towary wybuchowe mo�e by� zaparkowany:{FFFFFF}\n \na) jedynie w obszarze zabudowanym\nb) powinien by� konwojowany przez policj�\nc) powinien by� zamykany na klucz", 3},
	{ADR_Level_3, 3, "{488CDB}3) Jakimi drogami nie powinno si� porusza� z pe�n� cystern�?{FFFFFF}\n \na) drogami bez odpowiedniej nawierzchni\nb) autostradami\nc) drogami w mie�cie", 1}
};

CMD:adr(playerid)
{
	new class = 0, levelReq, szBuffer[256], szForm[5];
	switch(PlayerInfo[playerid][pADR])
	{
		case 0: class = 1;
		case 1: class = 2;
		case 2: class = 3;
		case 3: return Msg(playerid, COLOR_ERROR, "Posiadasz ju� wszystkie klasy licencji ADR.");
	}
	levelReq = ADR_ReqLvl[class - 1];
	if(GetPlayerLevel(pInfo[playerid][pExp]) < levelReq)
		return Msg(playerid, COLOR_ERROR, "Nie spe�niasz wymaga� aby m�c zdawa� testy na licencj� nast�pnej klasy.");
	if(GetPlayerMoney(playerid) < ADR_Cost[class -1])
	{
		format(szBuffer, sizeof szBuffer, "Nie posiadasz wystarczajaco du�o got�wki. Aby m�c zdawa� testy potrzebujesz $%d.", ADR_Cost[class -1]);
		return Msg(playerid, COLOR_ERROR, szBuffer);
	}

	szForm = (class == 1) ? ("szej") : ((class == 2) ? ("giej") : ("ciej"));

	format(szBuffer, sizeof szBuffer, "{488CDB}Licencja ADR\n \n{FFFFFF}Czy jeste� pewien, �e chcesz przyst�pi� do testu na licencj� ADR klasy %d-%s?\n \nW przypadku oblania test�w koszta ($%d) nie zostan� zwr�cone\nW zale�no�ci od klasy test sk�ada si� z od 3 do 5 pyta�.\nPowodzenia. :)", class, szForm, ADR_Cost[class - 1]);
	ShowPlayerDialog(playerid, DIALOG_ADR, DIALOG_STYLE_MSGBOX, " ", szBuffer, "Rozumiem", "Anuluj");
	return 1;
}

/*
switch(dialogid)
{
	case DIALOG_ADR:
	{
		if(response)
		{
			new questNumb = PlayerInfo[playerid][pADR] * 5;

			GivePlayerMoney(playerid, -ADR_Cost[PlayerInfo[playerid][pADR]]);
			ShowPlayerDialog(playerid, DIALOG_ADR2, DIALOG_STYLE_INPUT, " ", ADRQuestions[questNumb][2], "Dalej", #);
			SetPVarInt(playerid, "ADR_Step", 0);
			SetPVarInt(playerid, "ADR_Balance", 0);
		}
		else
			return 1;
	}
	case DIALOG_ADR2:
	{
		new step = GetPVarInt(playerid, "ADR_Step"), questNumb = (PlayerInfo[playerid][pADR] * 5) + step;
		if(response)
		{
			new answer, balance;
			
			if(!isnull(inputtext) && !strcmp(inputtext[0], "a", true) || !strcmp(inputtext[0], "b", true) || !strcmp(inputtext[0], "c", true))
			{
				switch(inputtext[0])
				{
					case 'a': answer = 1;
					case 'b': answer = 2;
					case 'c': answer = 3;

					case 'A': answer = 1;
					case 'B': answer = 2;
					case 'C': answer = 3;
				}
				balance = GetPVarInt(playerid, "ADR_Balance");
				if(ADRQuestions[questNumb][3][0] == answer)
					balance++;
				SetPVarInt(playerid, "ADR_Balance", balance);
				if(ADR_QuestNumb[PlayerInfo[playerid][pADR]] == step + 1)
				{
					new szBuffer[128], szForm[5];
					szForm = (PlayerInfo[playerid][pADR]+1 == 1) ? ("szej") : ((PlayerInfo[playerid][pADR]+1 == 2) ? ("giej") : ("ciej"));
					if(GetPVarInt(playerid, "ADR_Balance") >= (ADR_QuestNumb[PlayerInfo[playerid][pADR]]-1))
					{
						PlayerInfo[playerid][pADR] += 1;
						format(szBuffer, sizeof szBuffer, "Gracz {b}%s{/b} zdoby� licencj� ADR {b}%d{/b}-{b}%s{/b} klasy!", GetPlayerNick(playerid), PlayerInfo[playerid][pADR], szForm);
						MsgToAll(COLOR_INFO2, szBuffer);
						format(szBuffer, sizeof szBuffer, "{488CDB}Gratulacje!{FFFFFF}\n \nUda�o Ci si� zaliczy� testy na licencje ADR klasy {488CDB}%d-%s.", PlayerInfo[playerid][pADR], szForm);
					}
					else
					{
						format(szBuffer, sizeof szBuffer, "{488CDB}Niestety...{FFFFFF}\n \nNie uda�o Ci si� zaliczy� test�w na licencje ADR klasy {488CDB}%d-%s.\n", PlayerInfo[playerid][pADR]+1, szForm);
					}

					DeletePVar(playerid, "ADR_Step");
					DeletePVar(playerid, "ADR_Balance");
					ShowPlayerDialog(playerid, DIALOG_ADR3, DIALOG_STYLE_MSGBOX, " ", szBuffer, "Rozumiem", #);
					return 1;
				}
				else
					ShowPlayerDialog(playerid, DIALOG_ADR2, DIALOG_STYLE_INPUT, " ", ADRQuestions[questNumb + 1][2], "Dalej", #),
					step++,
					SetPVarInt(playerid, "ADR_Step", step);
			}
			else
				ShowPlayerDialog(playerid, DIALOG_ADR2, DIALOG_STYLE_INPUT, " ", ADRQuestions[questNumb][2], "Dalej", #);
		}
		else
			ShowPlayerDialog(playerid, DIALOG_ADR2, DIALOG_STYLE_INPUT, " ", ADRQuestions[questNumb][2], "Dalej", #);
	}
	case DIALOG_ADR3:
	{
		return 1;
	}
}*/
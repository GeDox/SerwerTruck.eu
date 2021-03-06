native IsValidVehicle(vehicle);

#undef MAX_PLAYERS

#define MAX_ACTUAL_FIRES	20
#define MAX_PLAYERS 		40
#define MAX_STACJE 			200
#define MAX_FOTORADAROW 	1000
#define MAX_VIASHOP 		200
#define MAX_VEHICLES_DB 	5000
#define MAX_FIRM 			50
#define MAX_SPIKESTRIPS 	25
#define MAX_BARY 			200
#define MAX_BARYIN 			200
#define MAX_LOADING_POINTS	200
#define MAX_RADIOS			100
#define MAX_RESTAURANTS		100
#define MAX_WORDS			100
#define MAX_STATIONS		100

// ---------------------------

#define INVALID_FOTO_ID 		0
#define INVALID_VIASHOP_ID 		0
#define INVALID_BARY_ID 		0
#define INVALID_BTOBJ_ID 		0
#define INVALID_REMONTBT3D_ID 	0
#define INVALID_DOK_ID 			0
#define INVALID_BARYIN_ID 		0

#define MOVE_SPEED              100.0
#define ACCEL_RATE              0.03

#define CAMERA_MODE_NONE    	0
#define CAMERA_MODE_FLY     	1

#define MOVE_FORWARD    		1
#define MOVE_BACK       		2
#define MOVE_LEFT       		3
#define MOVE_RIGHT      		4
#define MOVE_FORWARD_LEFT       5
#define MOVE_FORWARD_RIGHT      6
#define MOVE_BACK_LEFT          7
#define MOVE_BACK_RIGHT         8

// ---------------------------

enum 
{
	TEAM_TYPE_TRUCKER = 0,
	TEAM_TYPE_POLICE,
	TEAM_TYPE_MEDIC,
	TEAM_TYPE_POMOC,
	TEAM_TYPE_CARGO,
	TEAM_TYPE_PETROL,
	TEAM_TYPE_SMLOG,
	TEAM_TYPE_BUILD
}

// ---------------------------

#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#define Loop(%1,%2) for(new %1 = 0; %1 < %2; %1++)
#define ResetVariablesInEnum(%0,%1) 	for(new __rvine; %1:__rvine != %1; __rvine++) %0[%1:__rvine]=0
#define ShowInfo(%0,%1) Dialog_Show(%0, NEVER_DIALOG, DIALOG_STYLE_MSGBOX, "{FF0000}Informacja", %1, "Ok", "")
#define HOLDING(%0) ((newkeys & (%0)) == (%0))

#define LIGHTGREEN 			0xBCEE68FF
#define LIGHTBLUE 			0xA8C3E3FF
#define LIGHTRED 			0xEE5555FF
#define YELLOW 				0xEAAF00FF
#define ORANGE 				0xFFAB00FF
#define WHITE 				0xFFFFFFFF
#define GREY 				0xB2BBBFFF
#define ZIELONY99 			0x00FF00FF
#define ZIELONY5 			0x00FF00FF
#define ZIELONY6 			0x00FF00FF
#define ZIELONY4 			0x00FF00FF
#define LIGHTRED 			0xEE5555FF
#define ZIELONY 			0x00FF00FF
#define ZIELONY2 			0x00FF00FF
#define ZIELONY3 			0x00FF00FF
#define ZIELONY4 			0x00FF00FF
#define ZIELONY7 			0x004080FF

// ---------------------------

#define GCOLOR_GREEN 		"{BCEE68}"
#define GCOLOR_WHITE 		"{FFFFFF}"
#define GCOLOR_RED 			"{FF4040}"
#define GCOLOR_VIOLET 		"{BF3EFF}"
#define GCOLOR_GREY 		"{A9A9A9}"
#define GCOLOR_GUI 			"{a9c4e4}"
#define GCOLOR_YELLOW 		"{FFB90F}"
#define GCOLOR_CREAM 		"{FFD39B}"
#define COLOR_GUI 			"{a9c4e4}"

// ---------------------------

#define COLOR_INFO 			0
#define COLOR_INFO2			1
#define COLOR_INFO3			2
#define COLOR_ERROR			3

// ---------------------------

new const szCommands[][] = {
	" ",
	"/foto\n/mandat /aresztuj\n/wywal\n/wyrzuc\n/praca\n/dyzur\n/skuj\n/rozkuj\n/kontrola\n/alkomat\n/open\n/close\n/kolczatka\n/usunkolczatke\n/usunkolczatki\n/stop\n/unareszt\n/kartoteka",
	"/ulecz\n/wypadki\n/wywal\n/wyrzuc\n/praca\n/dyzur\n/o [1 - 8]\n/c [1 - 8]\n/open\n/close", // pogotowie
	"/open\n/close\n/vehcolor\n/zatankuj\n/praca\n/dyzur\n/open\n/close\n/setplate\n/przeglad",  // pomoc drogowa
	"/open\n/close\n/zaladuj\n/rozladuj", // cargo
	"/open\n/close\n/zaladuj\n/rozladuj", // petrol
	"/open\n/close\n/zaladuj\n/rozladuj", // smlog
	"/open\n/close\n/stworzobiekt\n/napis\n/kamera\n\n/obiektname\n/changepos\n/delone\n/delone" // build
};

new const szHookInclude[][] = {
	"Banki", // banki.inc
	"Konwoje", // konwoje.inc
	"Ladowanie", // ladowanie.inc
	"Pogoda", // pogoda.inc
	"Radio", // radio.inc
	"Reczny", // reczny.inc
	"Spectactor", // spectactor.inc
	"TablicaOgloszen", // tablicaogloszen.inc
	"ViaToll", // viatoll.inc
	"Vote", // vote.inc
	"Loadings", // zaladunki.inc
	"Fade", // lib/j_fader.inc
	"FadePlayer", // fade.inc
	"Logo", // logo.inc
	"Photo", // fotoradary.inc
	"GPS", // gps.inc
	"BT" // organizacje/buildtrans.inc
};

new const szRandomMessages[][] = {
	"Nie wiesz jak zacz��? Wpisz {b}/faq{/b} i zapoznaj si� z zasadami panuj�cymi na Project Truck.",
	"Zapraszamy do cz�stego odwiedzania naszego forum {b}www.projecttruck.pl{/b}!",
	"Kto� utrudnia Ci gr�? U�yj komendy {b}/report{/b} by powiadomi� o tym administracj�.",
	"Zapraszamy do korzystania z serwerowego {b}Team Speak 3{/b}.",
	"Zauwa�y�e� jaki� {b}b��d{/b} na serwerze? Zg�o� go nam na forum w dziale {b}b��dy / propozycje{/b}."
};

/*
	DOST�PNE FUNKCJE:
		_OnGameModeInit()
		_OnGameModeExit()
		_OnPlayerConnect(playerid)
		_OnPlayerDisconnect(playerid)
		_OnPlayerEnterJob(playerid, jobid) (called with /praca and OnPlayerSpawn)
		_OnPlayerSpawn(playerid)
		_OnPlayerDeath(playerid, killerid, reason)
		_OnVehicleSpawn(vehicleid)
		_OnVehicleDeath(vehicleid, killerid)
		_OnPlayerText(playerid, text[])
		_OnVehicleDamage(vehicleid, playerid) -- OnVehicleDamageStatusUpdate
		_OnPlayerExitVehicle(playerid, vehicleid)
		_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
		_OnPlayerStateChange(playerid, newstate, oldstate)
		_OnPlayerKey(playerid, newkeys, oldkeys)
		_OnPlayerClickTextdraw(playerid, clickedid)
		_OneSecTimer()
		_OneSecPlayerTimer(playerid)
		_OneMinuteTimer()
		_OneMinPlayerTimer(playerid)
		_OnTrailerUpdate(playerid, vehicleid)
		_OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
		_OnPlayerEditDynObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
		_OnPlayerCommand(playerid, cmdtext[], success)
*/
// ---------------------------

enum
{
	P_USER,
	P_SUPPORT,
	P_ADMIN,
	P_RCON
}

enum E_GAMEMODE
{
	gmCountdown,
	gmCountdownFreeze,
	bool:gmCountdownStarted,
	gmCountdownTimer,
	gmUsersConnected,
	adminPass[32],
	adminsOnline,
	gmLoadedVehicles,
	gmHour,
	gmMinute,
	gmDay,
	actFires[MAX_ACTUAL_FIRES],
	totalFires,
	lastFire,
	lastConnection,
	lastIP[17],
	lift[2]
}

enum E_PLAYER 
{
	pID,
	pMoney,
	pScore,
	Float:pHunger,
	pAdminAllowed,
	pOnlineTime,
	pBankomat,
	pFirm,
	pSkin,
	pTacho,
	pPhoto,
	pToll,
	pGTime,
	pWorkTime,
	pBuildmaster,
	pADR,
	pPursued,
	bool:pInvited[8],
	pAdmin,
	pChained,
	pChainedTimer,
	pLastPos,
	pSpawn,
	pSpawnInfo[32],
	pCBNick[32],
	pMagnesTime,
	bool:pMagnes,
	pCanister,
	pRepairKit,
	pDrivingLicense,
	pJailTime
}

enum E_CAMERA
{
	cCameramode,
	cFlyobject,
	cMode,
	cLrold,
	cUdold,
	cLastmove,
	Float:cAccelmul
}

enum E_STATION
{
	sID,
	Float:sPosX,
	Float:sPosY,
	Float:sPosZ,
	sGasAmount,
	sPetroleumAmount,
	sPetrolAmount,
	Float:sGasPrice,
	Float:sPetroleumPrice,
	Float:sPetrolPrice,
	sPetrolFirm,
	sOpenHour,
	sCloseHour,
	bool:sCreated
}

enum E_TEAM 
{
	tID,
	tName[32],
	tChef,
	tVcChef,
	tAccountant,
	tType,
	tBank,
	Float:tSpawnX,
	Float:tSpawnY,
	Float:tSpawnZ,
	tSkin1,
	tSkin2,
	tSkin3,
	tSkin4,
	tSkin5,
	tColor
}

enum E_GPS
{
	bool:gLoadings,
	bool:gStations,
	bool:gRestaurants,
	bool:gViatoll,
	bool:gCustom
}

enum E_VIATOLL 
{
	vtID,
	Float:vtPosX,
	Float:vtPosY,
	Float:vtPosZ
}

enum E_STRIPE
{
	sCreated,
	Float:sX,
	Float:sY,
	Float:sZ,
	sObject,
	Text3D:sText
}

enum E_VEHICLE
{
	vID,
	vModel,
	vOwnerID,
	vOwnerType,
	Float:vPosX,
	Float:vPosY,
	Float:vPosZ,
	Float:vPosA,
	Float:vHealth,
	Float:vFuel,
	vFuelType,
	Float:vPrzebieg,
	vColor1,
	vColor2,
	vLocked,
	vPanels,
	vDoors,
	vLights,
	vTires,
	vOwnerVC,
	vPlate[32],
	vPrzeglad[32],
	bool:vGasBootle,
	Float:vGasAmount,
	vSAMPID,
	bool:vGasStatus
};

enum E_TEMP_VEHICLE 
{
	Float:vFuel,
	vFuelType,
	Float:vPrzebieg,
	Color1,
	Color2
}

enum E_RADIO
{
	sID,
	sName[32],
	sURL[176]
};

enum E_REPORT
{
	bool:repUsed,
	repPReport,
	repPReported,
	repReason[76]
}

enum E_CALL
{
	bool:callUsed[MAX_PLAYERS*2],
	callPCalled[MAX_PLAYERS*2],
	callAssigned[MAX_PLAYERS*2]
}

enum E_RESTAURANT
{
	bool:resCreated,
	resId,
	resInt,
	Float:resPos[3]
}

enum E_MENU
{
	menName[24],
	menHunger,
	menPrice
}

new menuList[][E_MENU] = {
	{"Pizza", 20, 30},
	{"Hot-dog", 10, 15},
	{"�niadanie", 40, 60},
	{"Obiad", 50, 80},
	{"Kolacja", 20, 30}
};

new 
	banwords[MAX_WORDS],
	resInfo[MAX_RESTAURANTS][E_RESTAURANT],
	callInfo[3][E_CALL],
	repInfo[MAX_PLAYERS*2][E_REPORT],
	gmInfo[E_GAMEMODE],
	radioInfo[MAX_RADIOS][E_RADIO],
	camInfo[MAX_PLAYERS][E_CAMERA],
	spikeInfo[MAX_SPIKESTRIPS][E_STRIPE],
	gpsInfo[MAX_PLAYERS][E_GPS],
	viaInfo[MAX_VIASHOP][E_VIATOLL],
	firmInfo[MAX_FIRM][E_TEAM],
	playerInfo[MAX_PLAYERS][E_PLAYER],
	stationInfo[MAX_STACJE][E_STATION],
	vehInfo_Temp[MAX_VEHICLES][E_TEMP_VEHICLE],
	vehInfo[MAX_VEHICLES_DB][E_VEHICLE],
	cmdCars[][] = {
		{1, "Linerunner"},
		{10, "Tanker"},
		{20, "Roadtrain"},
		{1, "DFT-30"},
		{5, "Flatbed"},
		{5, "Boxville"},
		{10, "Benson"},
		{10, "Pony"},
		{15, "Rumpo"},
		{15, "Yankee"}
	};

// ---------------------------

new const Float:gSpawnvehicleplayer[][3] = {
	{1648.4308,-1053.9159,23.8984},
	{1398.5642,1009.4103,10.9297},
	{-240.4012,-231.1620,2.3985},
	{-2136.7207,-126.3667,36.5191}
};

new SECURITYON = 1;

#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

//new Text:Radarpolice[MAX_PLAYERS][4];

new brama[22];

new Float:savpos[1000][5];
new savedpos;
new Spray[9];

#define KEY_AIM 			132

#define MAX_ADMIN_VEHICLES 	50
new AdminsVehs[MAX_ADMIN_VEHICLES];
new SpawnedAdminVehicles;

new Text3D:Trucking[MAX_PLAYERS];
new podgladADMIN[MAX_PLAYERS] = 0;
new kogutPD[MAX_VEHICLES],
    bool:kpd[MAX_VEHICLES];
new kogutPOLI[MAX_VEHICLES],
    bool:kpoli[MAX_VEHICLES];

new Text:AlertTD,
	Text:TireTD;

new const DoswiadczeniePoziomy[] = 
{
	(-1),
	0,
	10,
	20,
	35,
	45,
	60,
	80,
	120,
	150,
	195,
	240,
	287,
	355,
	410,
	476,
	524,
	588,
	680,
	735,
	845,
	940,
	1120,
	1300,
	1510,
	1588,
	1630,
	1672,
	1742,
	2000,
	2450,
	2725,
	3010,
	3550,
	3900,
	4450
};

enum {
	FUEL_TYPE_GAS=0,
	FUEL_TYPE_BENZ,
	FUEL_TYPE_TDI
}

enum {
	OWNER_TYPE_PLAYER=0,
	OWNER_TYPE_TEAM,
	OWNER_TYPE_SPAWNED
}

new Float:vPos[MAX_VEHICLES][6];
new DBVehID[MAX_VEHICLES_DB];
new HighVehicleID=INVALID_VEHICLE_ID;
new VehicleDriver[MAX_VEHICLES]=INVALID_PLAYER_ID;

new timer[MAX_PLAYERS],
	timer7[MAX_PLAYERS],
	timer9[MAX_PLAYERS];

new bool:Spawned[MAX_VEHICLES];

new Text3D:StacjeText3D[MAX_STACJE];
new StacjeMapIcon[MAX_STACJE];
new StacjeMapIconForAll[MAX_STACJE];
new ID_STACJA=1;

new NaDyzurze[MAX_FIRM];

new colors[][] = {
	"niewidoczny", "bia�y", "pomara�czowy", "czerwony", "r�owy",
	"��ty", "br�zowy", "zielony", "jasnoniebieski", "niebieski"
};

new Text3D:viashop3D[MAX_VIASHOP];
new viashop3DForAll[MAX_VIASHOP];
new viashopIKON[MAX_VIASHOP];
new ID_VIATOLL=1;

enum {
	LOG_TYPE_CHAT=0,
	LOG_TYPE_COMMANDS,
	LOG_TYPE_PLAYER
}

new VehicleNames[212][] = {
{"Landstalker"},{"Bravura"},{"Buffalo"},{"Linerunner"},{"Perrenial"},{"Sentinel"},{"Dumper"},
{"Firetruck"},{"Trashmaster"},{"Stretch"},{"Manana"},{"Infernus"},{"Voodoo"},{"Pony"},{"Mule"},
{"Cheetah"},{"Ambulance"},{"Leviathan"},{"Moonbeam"},{"Esperanto"},{"Taxi"},{"Washington"},
{"Bobcat"},{"Mr Whoopee"},{"BF Injection"},{"Hunter"},{"Premier"},{"Enforcer"},{"Securicar"},
{"Banshee"},{"Predator"},{"Bus"},{"Rhino"},{"Barracks"},{"Hotknife"},{"Pe�na naczepa"},{"Previon"},
{"Coach"},{"Cabbie"},{"Stallion"},{"Rumpo"},{"RC Bandit"},{"Romero"},{"Packer"},{"Monster"},
{"Admiral"},{"Squalo"},{"Seasparrow"},{"Pizzaboy"},{"Tram"},{"Wywrotka"},{"Turismo"},
{"Speeder"},{"Reefer"},{"Tropic"},{"Flatbed"},{"Yankee"},{"Caddy"},{"Solair"},{"Berkley's RC Van"},
{"Skimmer"},{"PCJ-600"},{"Faggio"},{"Freeway"},{"RC Baron"},{"RC Raider"},{"Glendale"},{"Oceanic"},
{"Sanchez"},{"Sparrow"},{"Patriot"},{"Quad"},{"Coastguard"},{"Dinghy"},{"Hermes"},{"Sabre"},
{"Rustler"},{"ZR-350"},{"Walton"},{"Regina"},{"Comet"},{"BMX"},{"Burrito"},{"Camper"},{"Marquis"},
{"Baggage"},{"Dozer"},{"Maverick"},{"News Chopper"},{"Rancher"},{"FBI Rancher"},{"Virgo"},{"Greenwood"},
{"Jetmax"},{"Hotring"},{"Sandking"},{"Blista Compact"},{"Police Maverick"},{"Boxville"},{"Benson"},
{"Mesa"},{"RC Goblin"},{"Hotring Racer A"},{"Hotring Racer B"},{"Bloodring Banger"},{"Rancher"},
{"Super GT"},{"Elegant"},{"Journey"},{"Bike"},{"Mountain Bike"},{"Beagle"},{"Cropdust"},{"Stunt"},
{"Tanker"}, {"Roadtrain"},{"Nebula"},{"Majestic"},{"Buccaneer"},{"Shamal"},{"Hydra"},{"FCR-900"},
{"NRG-500"},{"HPV1000"},{"Cement Truck"},{"Tow Truck"},{"Fortune"},{"Cadrona"},{"FBI Truck"},
{"Willard"},{"Forklift"},{"Tractor"},{"Combine"},{"Feltzer"},{"Remington"},{"Slamvan"},
{"Blade"},{"Freight"},{"Streak"},{"Vortex"},{"Vincent"},{"Bullet"},{"Clover"},{"Sadler"},
{"Firetruck LA"},{"Hustler"},{"Intruder"},{"Primo"},{"Cargobob"},{"Tampa"},{"Sunrise"},{"Merit"},
{"Utility"},{"Nevada"},{"Yosemite"},{"Windsor"},{"Monster A"},{"Monster B"},{"Uranus"},{"Jester"},
{"Sultan"},{"Stratum"},{"Elegy"},{"Raindance"},{"RC Tiger"},{"Flash"},{"Tahoma"},{"Savanna"},
{"Bandito"},{"Freight Flat"},{"Streak Carriage"},{"Kart"},{"Mower"},{"Duneride"},{"Sweeper"},
{"Broadway"},{"Tornado"},{"AT-400"},{"DFT-30"},{"Huntley"},{"Stafford"},{"BF-400"},{"Newsvan"},
{"Tug"},{"Cysterna"},{"Emperor"},{"Wayfarer"},{"Euros"},{"Hotdog"},{"Club"},{"Freight Carriage"},
{"Skr�cona naczepa"},{"Andromada"},{"Dodo"},{"RC Cam"},{"Launch"},{"Police LSPD"},{"Police SFPD"},
{"Police LVPD"},{"Police Ranger"},{"Picador"},{"S.W.A.T. Van"},{"Alpha"},{"Phoenix"},{"Glendale"},
{"Sadler"},{"Luggage Trailer A"},{"Luggage Trailer B"},{"Stair Trailer"},{"Boxville"},{"Farm Plow"},
{"Utility Trailer"}};

new Float:viaPoints[][] =
{
    {2343.3713,834.1098,6.7344},
	{2342.8552,852.7947,6.7344},
	{2342.8552,852.7947,6.7344},
	{2709.0635,1727.1296,6.7344},
	{1880.1187,2523.7358,6.8112},
	{1887.0364,2506.6235,6.8095},
	{1497.9585,2473.4600,6.7421},
	{1497.2330,2454.0833,6.7344},
	{927.8715,2605.2581,10.4440},
	{918.6038,2589.4097,10.3475},
	{1208.7083,2032.0959,6.7344},
	{1226.3341,2029.1606,6.7344},
	{1207.9796,1339.0520,6.7344},
	{1226.3348,1337.4695,6.7344},
	{1806.9712,1078.4344,6.7344},
	{1786.8424,1080.1672,6.7420},
	{1805.8663,2027.7371,3.9063},
	{1788.1750,2028.1434,3.9063},
	{931.2241,742.9670,10.6972},
	{936.8785,724.9408,10.6991},
	{55.7237,668.2198,5.9933},
	{65.7794,650.0699,6.2311},
	{-1101.6611,1544.8802,27.2211},
	{-1127.2782,1538.1731,21.9345},
	{-1679.2386,2167.9458,20.5576},
	{-1701.1515,2148.0486,18.2075},
	{-2716.1616,2640.0427,88.3590},
	{-2671.3555,2577.1851,75.4093},
	{-1140.9016,1109.9440,38.2559},
	{-1131.0656,1098.9979,38.3143},
	{-1910.8617,-1082.6947,38.2344},
	{-1896.8868,-1082.9814,38.2344},
	{-2900.0620,-1709.4854,22.1113},
	{-2929.8584,-1715.5850,19.0224},
	{-2699.3176,-401.7303,7.9082},
	{-2707.4353,-390.6496,7.9113},
	{-2341.4968,-2580.8574,46.3502},
	{-2349.1631,-2615.9939,58.7623},
	{-1342.6294,-2875.8237,55.3919},
	{-1326.8586,-2919.8411,49.8097},
	{-0.1825,-2607.7610,39.8488},
	{-35.0069,-2613.9233,43.7653},
	{92.8385,-1284.4017,13.8588},
	{76.7223,-1263.8002,14.2713},
	{170.6697,-1602.8448,13.8510},
	{182.8681,-1593.4392,13.8707},
	{1038.4319,-1941.4056,13.2205},
	{1048.3969,-1945.4319,13.2205},
	{1063.6014,-1945.1613,13.2205},
	{1213.6760,-2433.0134,9.6150},
	{1210.0365,-2448.0322,9.5693},
	{2098.5908,-2662.0005,13.3821},
	{2348.7107,-2226.2048,13.3821},
	{2338.7896,-2215.2847,13.3750},
	{2843.0481,-1835.4346,10.8943},
	{2824.4434,-1831.3973,10.8904},
	{2896.9583,-649.9005,10.8359},
	{2877.1814,-647.2960,10.8359},
	{2766.5542,221.4342,20.2656},
	{2747.9395,216.6371,27.0347},
	{1968.9531,292.3683,33.4549},
	{1968.8036,312.4247,33.5116},
	{1746.1255,572.7900,24.7794},
	{1763.3621,568.7740,24.6825},
	{1347.0687,-2281.6086,13.3904},
	{1331.9624,-2279.8809,13.3828}
};

new 
	__FlashTime[MAX_VEHICLES],
	_Flash[MAX_VEHICLES],
	enabledFlashes,
	bool:vehicleExploded[MAX_VEHICLES],
	Float:PlayerCruiseSpeed[MAX_PLAYERS];

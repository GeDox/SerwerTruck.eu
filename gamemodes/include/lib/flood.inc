//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
/* ANTI-RECONNECT - � iPLEOMAX 2011 */
/* Do not remove the credits!       */
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

#if !defined _samp_included
    #tryinclude <a_samp>
    #if !defined _samp_included
        #error a_samp.inc must be included before using this.
    #endif
#endif

/*
native ARKick(playerid);
native ARConnect(playerid);
native ARDisconnect(playerid);
native ARIgnore(playerid);
*/

#define ARConnect(%0) AR_OnPlayerConnect(%0)
#define ARDisconnect(%0) AR_OnPlayerDisconnect(%0)
#define ARIgnore(%0) IPDATA[%0][Ignore] = true

#define MAX_R_ATTEMPTS 3
//Continously Disconnect and Connect, how many times should it happen before crashing him? Default: 3
#define STATUS_SECONDS 20
//Time before the Success/Fail Message is shown. Default: 20
#define RESET_CHECK 10
//Time after the IP which is saved in var gets reset. (If you set it 0, it will save forever until the slot gets a new player)

#define PUB:%1(%2) forward %1(%2); public %1(%2) //Thanks to "Mean" I got it from him.

enum IP_DATA
{
	IP_ADDRESS[16],
	bool:Crashing,
	bool:Ignore
};

new
	IPDATA[MAX_PLAYERS][IP_DATA],
	Text:CrashTD,
	JoinAttempts,
	JoinIP[16]
;

PUB:AR_OnPlayerConnect(playerid)
{
	new CurIP[16]; GetPlayerIp(playerid, CurIP, sizeof CurIP);
	for(new i=0; i<MAX_PLAYERS; i++)
    {
    	if(strlen(IPDATA[i][IP_ADDRESS]) > 2 && !strcmp(CurIP,IPDATA[i][IP_ADDRESS],false))
     	{
      		printf("[info] ID %i possibly reconnected after Kick.",playerid);
            CrashPlayer(playerid, CurIP);
            break;
        }
	}
    if (!strcmp(CurIP, JoinIP, false))
	{
	    JoinAttempts++;
	    if (JoinAttempts >= MAX_R_ATTEMPTS)
	    {
	        CrashPlayer(playerid, CurIP);
	    }
	} else JoinAttempts = 0;
    GetPlayerIp(playerid, JoinIP, sizeof(JoinIP));
	return true;
}

PUB:AR_OnPlayerDisconnect(playerid)
{
	TextDrawHideForPlayer(playerid, CrashTD);
	IPDATA[playerid][Crashing] = false;
	IPDATA[playerid][Ignore] = false;
	return true;
}

PUB:CrashPlayer(playerid, playerIP[])
{
	if(IPDATA[playerid][Crashing]) return true;
	IPDATA[playerid][Crashing] = true;
    printf("[info] Attempting to crash ID%i with IP:[%s] (ANTI-RECONNECT)",playerid,playerIP);
	GameTextForPlayer(playerid, "~HAX# 1337",1000,3); // 1337 K1dz l1k3 $p@mz!1!1
	GameTextForPlayer(playerid, "~DIE*** ~HAHA",1000,3);
	GameTextForPlayer(playerid, "SUCKER! ~xD",1000,3);
	SetPlayerSkin(playerid, -32);
	TextDrawDestroy(CrashTD);
	CrashTD = TextDrawCreate(320,240,"~WTF");
	TextDrawShowForPlayer(playerid, CrashTD);
	SetTimerEx("CrashStatus",STATUS_SECONDS*1000,false,"ds",playerid,playerIP);
	return true;
}

PUB:CrashStatus(playerid, playerIP[])
{
	new CurIP[16]; GetPlayerIp(playerid, CurIP, sizeof CurIP);
	if(IsPlayerConnected(playerid) && !strcmp(CurIP,playerIP,false))
	{ printf("[info] Unable to crash ID%i. [FAIL]",playerid); }
	else
	{ printf("[info] Crashed ID %i [%s]. [SUCCESS]",playerid,playerIP); }
	return true;
}

PUB:ARKick(playerid)
{
	if(!IPDATA[playerid][Ignore])
	{
		GetPlayerIp(playerid, IPDATA[playerid][IP_ADDRESS], 16);
		new rchck = RESET_CHECK;
		if(rchck != 0) SetTimerEx("ResetIPSlot", RESET_CHECK*1000, false, "d", playerid);
	}
	printf("[AR-iPLEOMAX]: ARKick has been used on ID %i",playerid);
	Kick(playerid);
	return true;
}

PUB:ResetIPSlot(ipslotid)
{
	printf("[info] Resetted saved IP Slot %i [%s]",ipslotid, IPDATA[ipslotid][IP_ADDRESS]);
	format(IPDATA[ipslotid][IP_ADDRESS],16,"_");
	return true;
}

/* Enjoy! */
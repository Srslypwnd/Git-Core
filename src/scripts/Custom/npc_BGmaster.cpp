#include "ScriptPCH.h"
#include "Chat.h"
 
void SendMessageToPlayer(Player* player, const char *str)
{
    if (!player->GetSession())
        return;
 
    WorldPacket data;
 
    // need copy to prevent corruption by strtok call in LineFromMessage original string
    char* buf = strdup(str);
    char* pos = buf;
 
    while (char* line = ChatHandler::LineFromMessage(pos))
    {
        ChatHandler::FillMessageData(&data, player->GetSession(), CHAT_MSG_SYSTEM, LANG_UNIVERSAL, NULL, 0, line, NULL);
        player->GetSession()->SendPacket(&data);
    }
 
    free(buf);
}

bool GossipHello_npc_BGjoiner(Player *player, Creature *_Creature)
{
	if (!player->isInCombat())
	{
            player->ADD_GOSSIP_ITEM(0, "Join the battle for Quel'thalas Keep!", GOSSIP_SENDER_MAIN, 1);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());  
		    return true;
	}
	player->GetSession()->SendNotification("Jsi v combate.");
	return false;

}

bool GossipSelect_npc_BGjoiner(Player *player, Creature *creature, uint32 sender, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();
	switch (action)
	{
           case 1: //Join to Quel'thalas Keep battle!
                if ( player->GetTeam() == ALLIANCE)
		    {
	           		if (sWorld.GetPlayersAllianceInZone(2037) < 1)
		    		{
                    player->TeleportTo(0, 3415.042969f, -2114.816895f, 131.407578f, 0.907265f);
					player->AddItem(999951, 1);
					SendMessageToPlayer(player, "Welcome to Quel Thalas Keep!");
					sLog.outString("QuelThalas Keep: New Player has joined the battle!");

     					char MSG[200];
              			sprintf(MSG, "Player '|cff0000f1 %s |r' has joined the battle!", player->GetName());
              			sWorld.SendZoneText(2037, MSG);
                        	}
	           		else 
		    		{
                       		SendMessageToPlayer(player, "Quel Thalas Keep is full!");
                  	}
	           		return true;
		    }
		    else if ( player->GetTeam() == HORDE)
		    {
	           		if (sWorld.GetPlayersHordeInZone(2037) < 1)
		    		{
                    player->TeleportTo(0, 3514.493896f, -1979.416016f, 131.407623f, 4.097552f);
					player->AddItem(999951, 1);
					SendMessageToPlayer(player, "Welcome to Quel Thalas Keep!");
					sLog.outString("QuelThalas Keep: New Player has joined the battle!");

     					char MSG[200];
              			sprintf(MSG, "Player '|cffde0909 %s |r' has joined the battle!", player->GetName());
              			sWorld.SendZoneText(2037, MSG);
                  	}
	           		else 
		    		{
                       		SendMessageToPlayer(player, "Quel Thalas Keep is full!");
                  	}
	           		return true;
		    }
		    return true;
            break;

    } // end of switch
} //end of function

void AddSC_npc_BGjoiner()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "BGjoiner";
	newscript->pGossipHello = &GossipHello_npc_BGjoiner;
	newscript->pGossipSelect = &GossipSelect_npc_BGjoiner;
	newscript->RegisterSelf();
}
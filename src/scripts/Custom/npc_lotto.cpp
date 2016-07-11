#include "ScriptPCH.h"

enum eEnums
{
	ITEM_LOTTO = 200800,

};

bool GossipHello_npc_lotto(Player *player, Creature *creature)
{
	if (player->HasItemCount(ITEM_LOTTO, 1, false))
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "The stars say i'll be looking, i fancy my chances in the lottery this week.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	}
	else
		creature->MonsterWhisper("You dont have enough Lottery Tickets", player->GetGUID());

	player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	return true;
};

bool GossipSelect_npc_lotto(Player *player, Creature *creature, uint32 sender, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();
	switch (action)
	{
	case GOSSIP_ACTION_INFO_DEF + 1:
		creature->MonsterWhisper("Greetings competitor! Thank you for purchasing your Lottery ticket, please be sure to check your numbers against our database, for your chance to win a stunning 200 gold coins!", player->GetGUID());
		WorldDatabase.PExecute("INSERT INTO game_lotto (entry, comment) values (%u,0)", player->GetGUIDLow());
		player->DestroyItemCount(ITEM_LOTTO, 1, true, false);
		break;
	}

	player->CLOSE_GOSSIP_MENU();
	return true;
}

void AddSC_npc_lotto()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "npc_lotto";
	newscript->pGossipHello = &GossipHello_npc_lotto;
	newscript->pGossipSelect = &GossipSelect_npc_lotto;
	newscript->RegisterSelf();
}
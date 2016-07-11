#include "ScriptPCH.h"

#define INTEL 33078
#define AGI 33077
#define ARMOR 33079
#define SPIRIT 33078
#define STAMINA 33081
#define STRENGTH 33082

bool GossipHello_npc_buffer(Player *pPlayer, Creature *pCreature)
{
	if (!pPlayer->isInCombat())
	{
		pPlayer->ADD_GOSSIP_ITEM(0, "Stamina", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		pPlayer->ADD_GOSSIP_ITEM(0, "Intelect", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(0, "Armor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(0, "Agility", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		pPlayer->ADD_GOSSIP_ITEM(0, "Strength", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		pPlayer->ADD_GOSSIP_ITEM(0, "Spirit", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		return true;
	}
	pPlayer->GetSession()->SendNotification("You are in combat.");
	return false;

}



bool GossipSelect_npc_buffer(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
	switch (action)
	{
		//Stamina
	case GOSSIP_ACTION_INFO_DEF + 1:
		pCreature->CastSpell(pPlayer, STAMINA, false);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
		//Mana
	case GOSSIP_ACTION_INFO_DEF + 2:
		//pCreature->CastSpell(pPlayer, INTEL, false);
		pPlayer->CastSpell(pPlayer, INTEL, false);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
		//BOK
	case GOSSIP_ACTION_INFO_DEF + 3:
		pCreature->CastSpell(pPlayer, ARMOR, false);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;

		//BOM
	case GOSSIP_ACTION_INFO_DEF + 4:
		pCreature->CastSpell(pPlayer, AGI, false);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;

		//BOW
	case GOSSIP_ACTION_INFO_DEF + 5:
		pCreature->CastSpell(pPlayer, STRENGTH, false);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;

		//spirit
	case GOSSIP_ACTION_INFO_DEF + 6:
		pCreature->CastSpell(pPlayer, SPIRIT, false);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;

	}
	return true;
}



void AddSC_npc_buffer()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name = "npc_buffer";
	newscript->pGossipHello = &GossipHello_npc_buffer;
	newscript->pGossipSelect = &GossipSelect_npc_buffer;
	newscript->RegisterSelf();
}
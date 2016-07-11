#include "ScriptPCH.h"

void ukaz_menu(Player * player, Creature * creature)
{
	player->ADD_GOSSIP_ITEM(1, "Co robit po vyexpeni?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	player->ADD_GOSSIP_ITEM(1, "Ako kontaktovat GM?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
	player->ADD_GOSSIP_ITEM(1, "Kde zozeniem goldy?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
	player->ADD_GOSSIP_ITEM(1, "Nasiel som bug, co mam urobit?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
	player->ADD_GOSSIP_ITEM(1, "Mam nejaky problem, co mam urobit?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
	player->ADD_GOSSIP_ITEM(1, "Kde najdem custom patch na fix spellov atd?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
	player->ADD_GOSSIP_ITEM(1, "Aka je nasa web stranka?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
	player->ADD_GOSSIP_ITEM(1, "Aka je nasa facebook stranka?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
	player->ADD_GOSSIP_ITEM(1, "Nemam zajem", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
}

bool GossipHello_npc_support(Player *player, Creature *creature)
{
	ukaz_menu(player, creature);
	return true;
}
bool GossipSelect_npc_support(Player *player, Creature *creature, uint32 sender, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();
	switch (action)
	{

	case GOSSIP_ACTION_INFO_DEF + 1:
		creature->MonsterWhisper("Po vyexpeni navstivte Fishing Zone, kde najdete Tier1 itemy. Odporucame si taktiez vyklikat vsetky talenty a vytrainova class spelly a zbrane.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 2:
		creature->MonsterWhisper("GM mozete kontaktovat prostrednictvom ticketu (cerveny otaznik dole v bare a nasledne TALK TO GM) alebo pomocou /whisper |meno GM]", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 3:
		creature->MonsterWhisper("Goldy ziskate prostrednictvom fishingu v nasej Fishing Zone alebo cez Daily questy.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 4:
		creature->MonsterWhisper("Bugy je potrebne nahlasit prislušnym GMkam. Ak GM nieje online, vytvorte topic na nasom fore v sekcii Bugy, chyby, problemy.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 5:
		creature->MonsterWhisper("Ak sa jedna o maly problem (napr. neviem, kde pada T2), spytajte sa na channele world (joinnete sa pomocou prikazu /join world. Ak mte nieco zlozitejsie, vytvorte si ticket (cerveny otaznik dole v bare a nasledne TALK TO GM)", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 6:
		creature->MonsterWhisper("Custom patch nasho serveru najdete na nasej stranke www.apokalipticwow.eu", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 7:
		creature->MonsterWhisper("Nasa web stranka je www.apokalipticwow.eu , na ktorej najdete informacie o serveri, novinky ale taktiez armory, account manager a podobne vymozenosti. ", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 8:
		creature->MonsterWhisper("Nasa facebookova stranka je www.facebook.com/apokalipticwow , kde najdete najnovsie, priebezne informacie o chode serveru a novinkach.", player->GetGUID());
		player->CLOSE_GOSSIP_MENU();
		break;
	case GOSSIP_ACTION_INFO_DEF + 9:
		player->CLOSE_GOSSIP_MENU();
		return true;
		break;
	}
	ukaz_menu(player, creature);
	return true;
}



void AddSC_npc_support()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "npc_support";
	newscript->pGossipHello = &GossipHello_npc_support;
	newscript->pGossipSelect = &GossipSelect_npc_support;
	newscript->RegisterSelf();
}
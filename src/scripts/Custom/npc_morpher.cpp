#include "ScriptPCH.h"

bool GossipHello_npc_morpher(Player *player, Creature *creature)
{
            player->ADD_GOSSIP_ITEM( 3, "Gnome",                     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( 3, "Human",                     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( 3, "Tauren",                    GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM( 3, "Goblin",                    GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM( 3, "Blood Elf",                 GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM( 3, "Broken",                    GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM( 3, "Other",                     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
			player->ADD_GOSSIP_ITEM( 3, "City Guard",                GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->ADD_GOSSIP_ITEM( 9, "Demorph",                   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
}
bool GossipSelect_npc_morpher(Player *player, Creature *creature, uint32 sender, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();
	switch (action)
	{
		case GOSSIP_ACTION_INFO_DEF://Demorph
			player->CLOSE_GOSSIP_MENU();
			player->DeMorph();
			break;
		case GOSSIP_ACTION_INFO_DEF + 1: //Gnome
			player->ADD_GOSSIP_ITEM(3, "Male",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
			player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;
		case GOSSIP_ACTION_INFO_DEF + 2: //Human
			player->ADD_GOSSIP_ITEM(3, "Male",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;
		case GOSSIP_ACTION_INFO_DEF + 3: //Tauren
			player->ADD_GOSSIP_ITEM(3, "Male",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
			player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;
		case GOSSIP_ACTION_INFO_DEF + 4: //Goblin
			player->ADD_GOSSIP_ITEM(3, "Male",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
			player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;
		case GOSSIP_ACTION_INFO_DEF + 5: //Blood Elf
			player->ADD_GOSSIP_ITEM(3, "Male",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
			player->ADD_GOSSIP_ITEM(3, "Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;
		case GOSSIP_ACTION_INFO_DEF + 6: //Broken
			player->ADD_GOSSIP_ITEM(3, "Male",   GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;
		case GOSSIP_ACTION_INFO_DEF + 7: //Other
			player->ADD_GOSSIP_ITEM(3, "Pirate",     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
			player->ADD_GOSSIP_ITEM(3, "Ghost",      GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
			player->ADD_GOSSIP_ITEM(3, "wolf",       GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
			player->ADD_GOSSIP_ITEM(3, "prophet velen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34);
			player->ADD_GOSSIP_ITEM(3, "cyclop take daco", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 37);
			player->ADD_GOSSIP_ITEM(3, "night elf", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 38);
			player->ADD_GOSSIP_ITEM(3, "morogrim", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 39);
			player->ADD_GOSSIP_ITEM(3, "monkey", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
			player->ADD_GOSSIP_ITEM(3, "Exodus Guard", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42);
			player->ADD_GOSSIP_ITEM(3, "diablik", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43);
			player->ADD_GOSSIP_ITEM(3, "Blood elf alee ta elitka zo swp", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 44);
			player->ADD_GOSSIP_ITEM(3, "--->", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;

		case GOSSIP_ACTION_INFO_DEF + 19: // Other page : 2
			player->ADD_GOSSIP_ITEM(3, "to iste len inac vyzera", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 45);
			player->ADD_GOSSIP_ITEM(3, "blood elf ale female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 46);
			player->ADD_GOSSIP_ITEM(3, "strom", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 47);
			player->ADD_GOSSIP_ITEM(3, "Dog", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41);
			player->ADD_GOSSIP_ITEM(3, "blood elf", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 48);
			player->ADD_GOSSIP_ITEM(3, "female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 49);
			player->ADD_GOSSIP_ITEM(3, "night elf female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
			player->ADD_GOSSIP_ITEM(3, "kalecgos human", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51);
			player->ADD_GOSSIP_ITEM(3, "draenei quartermaster", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52);
			player->ADD_GOSSIP_ITEM(3, "human conjurer", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53);
			player->ADD_GOSSIP_ITEM(3, "Draenei vindicator", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54);
			player->ADD_GOSSIP_ITEM(3, "Gri'lek", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			break;

		case GOSSIP_ACTION_INFO_DEF + 8: //City Guard
			player->ADD_GOSSIP_ITEM(3, "Darnassus",  GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
			player->ADD_GOSSIP_ITEM(3, "Ironforge",  GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
			player->ADD_GOSSIP_ITEM(3, "Orgrimmar",  GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
			player->ADD_GOSSIP_ITEM(3, "Silvermoon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
			player->ADD_GOSSIP_ITEM(3, "Stormwind",  GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
			player->ADD_GOSSIP_ITEM(3, "Exodar",     GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
			player->ADD_GOSSIP_ITEM(3, "Undercity",  GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
			player->ADD_GOSSIP_ITEM(3, "Thunder Bluff", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;

		case GOSSIP_ACTION_INFO_DEF + 21: //Pirate
			player->ADD_GOSSIP_ITEM(3, "Male",      GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35);
			player->ADD_GOSSIP_ITEM(3, "Female",    GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36);
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());       
			break;

		case GOSSIP_ACTION_INFO_DEF + 9: //Gnome male
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20580);
			break;

		case GOSSIP_ACTION_INFO_DEF + 10://Gnome - Female
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20581);
			break;

		case GOSSIP_ACTION_INFO_DEF + 11://Human - Male
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(19723);
			break;

		case GOSSIP_ACTION_INFO_DEF + 12://Tauren - Male
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20585);
			break;

		case GOSSIP_ACTION_INFO_DEF + 13://Tauren - Female
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20584);
			break;

		case GOSSIP_ACTION_INFO_DEF + 14://Goblin - Male
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(21855);
			break;

		case GOSSIP_ACTION_INFO_DEF + 15://Goblin - Female
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(21857);
			break;

		case GOSSIP_ACTION_INFO_DEF + 16://Blood Elf - Male
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20578);
			break;

		case GOSSIP_ACTION_INFO_DEF + 17://Blood Elf - Female
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20579);
			break;

		case GOSSIP_ACTION_INFO_DEF + 18://Broken - Male
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(21105);
			break;

		case GOSSIP_ACTION_INFO_DEF + 23://Ghost
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(14560);
			break;

		case GOSSIP_ACTION_INFO_DEF + 24://Wolf
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(741);
			break;

		case GOSSIP_ACTION_INFO_DEF + 35://Pirate - Male
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(4620);
			break;

		case GOSSIP_ACTION_INFO_DEF + 36://Pirate - Female
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(4619);
			break;
		
		case GOSSIP_ACTION_INFO_DEF + 25://Darnassus
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(14614);
			break;

		case GOSSIP_ACTION_INFO_DEF + 27://Ironforge
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(3526);
			break;

		case GOSSIP_ACTION_INFO_DEF + 28://Orgrimmar
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(4602);
			break;

		case GOSSIP_ACTION_INFO_DEF + 29://Silvermoon
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(15511);
			break;

		case GOSSIP_ACTION_INFO_DEF + 30://Stormwind
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(5567);
			break;

		case GOSSIP_ACTION_INFO_DEF + 31://Exodar
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(17373);
			break;

		case GOSSIP_ACTION_INFO_DEF + 32://Undercity
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(14452);
			break;

		case GOSSIP_ACTION_INFO_DEF + 33://Thunder Bluff
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(9391);
			break;

		case GOSSIP_ACTION_INFO_DEF + 34: //prophet velen
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(17822);
			break;

		case GOSSIP_ACTION_INFO_DEF + 37: //cyclop take daco
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(18649);
			break;

		case GOSSIP_ACTION_INFO_DEF + 38: //night elf
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(18718);
			break;

		case GOSSIP_ACTION_INFO_DEF + 39: //morogrim
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20739);
			break;

		case GOSSIP_ACTION_INFO_DEF + 40: //monkey
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(21362);
			break;

		case GOSSIP_ACTION_INFO_DEF + 41: //dog
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(7891);
			break;

		case GOSSIP_ACTION_INFO_DEF + 42: //Exodus guard
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(20558);
			break;

		case GOSSIP_ACTION_INFO_DEF + 43: //diablik
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(10992);
			break;

		case GOSSIP_ACTION_INFO_DEF + 44: //Blood elf alee ta elitka zo swp
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(23479);
			break;

		case GOSSIP_ACTION_INFO_DEF + 45: //to iste len inac vyzera
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(23477);
			break;

		case GOSSIP_ACTION_INFO_DEF + 46: //blood elf ale female
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(23473);
			break;

		case GOSSIP_ACTION_INFO_DEF + 47: //strom
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(21213);
			break;

		case GOSSIP_ACTION_INFO_DEF + 48: 
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(7874);
			break;

		case GOSSIP_ACTION_INFO_DEF + 49: 
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(7872);
			break;

		case GOSSIP_ACTION_INFO_DEF + 50: 
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(11657);
			break;

		case GOSSIP_ACTION_INFO_DEF + 51: 
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(23459);
			break;

		case GOSSIP_ACTION_INFO_DEF +52: //draenei quartermaster
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(16924);
			break;

		case GOSSIP_ACTION_INFO_DEF + 53: //human conjurer
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(16280);
			break;

		case GOSSIP_ACTION_INFO_DEF + 54: //Draenei vindicator
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(16602);
			break;

		case GOSSIP_ACTION_INFO_DEF + 55: //Gri'lek
			player->CLOSE_GOSSIP_MENU();
			player->SetDisplayId(7873);
			break;
	}
	return true;
}

void AddSC_npc_morpher()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_morpher";
    newscript->pGossipHello =  &GossipHello_npc_morpher;
    newscript->pGossipSelect = &GossipSelect_npc_morpher;
    newscript->RegisterSelf();
}
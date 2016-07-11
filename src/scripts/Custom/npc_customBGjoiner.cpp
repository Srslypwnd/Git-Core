#include "ScriptPCH.h"

void zobrazit_menu(Player * player, Creature * creature)
{
            player->ADD_GOSSIP_ITEM( 6, "Buy Honor Points", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM( 6, "Buy Arena Points", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM( 0, "Price List", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
			player->ADD_GOSSIP_ITEM( 1, "Nemam zajem", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
}

bool GossipHello_npc_BGreward(Player *player, Creature *creature)
{
	zobrazit_menu(player, creature);
	return true;
}

bool GossipSelect_npc_BGreward(Player *player, Creature *creature, uint32 sender, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();
	switch (action)
	{
	        case GOSSIP_ACTION_INFO_DEF + 1: //Buy Honor Points
			   if (player->HasItemCount(999950, 5))
			   {
				  player->DestroyItemCount(999950, 5, true);
				  player->ModifyHonorPoints(+250);
				  creature->MonsterWhisper("Tu su tvoje honor pointy", player->GetGUID());
			    }
			else
				creature->MonsterWhisper("Nemas dostatek BG marek!", player->GetGUID());
			break;

           case GOSSIP_ACTION_INFO_DEF + 2: //Buy Arena Points
			if (player->HasItemCount( 999950, 5))
			{
				player->DestroyItemCount(999950, 5, true);
				player->ModifyArenaPoints(+5);
				creature->MonsterWhisper("Tu su tvoje arena pointy", player->GetGUID());
			}
			else 
			
				creature->MonsterWhisper("Nemas dostatek BG marek!", player->GetGUID());
                break;

			case GOSSIP_ACTION_INFO_DEF + 3: //Price List
			creature->MonsterWhisper("[5x Keep Points] - 200 Honor Points, 5 Arena Points, 1xEmblem of Frost, 1xEmblem of Triumph", player->GetGUID());
            break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			player->CLOSE_GOSSIP_MENU();
			return true;
			break;
	}
	zobrazit_menu(player, creature);
	return true;
}
void AddSC_npc_BGreward()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_BGreward";
    newscript->pGossipHello = &GossipHello_npc_BGreward;
    newscript->pGossipSelect = &GossipSelect_npc_BGreward;
    newscript->RegisterSelf();
}
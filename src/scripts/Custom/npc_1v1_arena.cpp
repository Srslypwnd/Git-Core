#include "WorldPacket.h"
#include "WorldSession.h"
#include "ObjectMgr.h"
#include "ArenaTeam.h"
#include "ScriptPCH.h"
#include "BattleGroundMgr.h"
#include <cstring>

bool GossipHello_npc_arena_1v1(Player* pPlayer, Creature* pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM(9, "Vytvorit 1v1 Team", GOSSIP_SENDER_MAIN, 1000);
	pPlayer->ADD_GOSSIP_ITEM(9, "Vymazat 1v1 Team", GOSSIP_SENDER_MAIN, 2000);
	pPlayer->ADD_GOSSIP_ITEM(9, "Prihlasit 1v1 Arenu", GOSSIP_SENDER_MAIN, 3000);

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}

void SendDefaultMenu_npc_arena_1v1(Player* player, Creature* creature, uint32 action)
{
    // Not allowed if in combat.
    if (player->isInCombat())
    {
      player->CLOSE_GOSSIP_MENU();
      creature->MonsterWhisper("Si v combate.", player->GetGUID());
      return;
    }

	if (!sWorld.getConfig(CONFIG_ARENA_SINGLE))
	{
		player->CLOSE_GOSSIP_MENU();
		creature->MonsterWhisper("1v1 areny niesu povolene.", player->GetGUID());
		return;
	}

/*	if (player->GetInt32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS) > sWorld.getConfig(CONFIG_ARENA_SINGLE_MAX_BH))
	{
		player->CLOSE_GOSSIP_MENU();
		creature->MonsterWhisper("Si HEALER! Zmen svoj equip!", player->GetGUID());
		return;
	}

	if (sWorld.getConfig(CONFIG_ARENA_SINGLE_NOHEAL_SPELLS))
		if (player->HasSpell(31842) || 
			player->HasSpell(15355) || 
			player->HasSpell(15356)
			)
		{
			player->CLOSE_GOSSIP_MENU();
			creature->MonsterWhisper("Si HEALER! Zmen svoje talenty!", player->GetGUID());
			return;
		}
*/

	std::string teamname = player->GetName();
	uint32 type = 5;
	switch(action)
    {
	case 1000:
		{
			uint32 oldatid = player->GetArenaTeamId(2);
			ArenaTeam* oldat = objmgr.GetArenaTeamById(oldatid);
			if (oldat)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterWhisper("Uz mas 1v1 arena team.", player->GetGUID());
				return;
			}
			if (objmgr.GetArenaTeamByName(teamname))
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterWhisper("Arena tym s tvojim menom uz existuje. Mozes si vytvorit team pri Arena Organizerovi. Vytvor 5v5 team. Podpisy nepotrebujes!", player->GetGUID());
				return;
			}

			ArenaTeam* at = new ArenaTeam;
			if (!at->Create(player->GetGUID(), type, teamname))
			{
				sLog.outError("Npc_arena_1v1: arena team create failed.");
				delete at;
				return;
			}

			uint32 icon, iconcolor, border, bordercolor, backgroud;
			icon = 69;
			iconcolor = 4294705169;
			border = 4;
			bordercolor = 4294903296;
			backgroud = 4278190080;

			at->SetEmblem(backgroud, icon, iconcolor, border, bordercolor);

			// register team and add captain
			objmgr.AddArenaTeam(at);
			sLog.outDebug("Npc_arena_1v1: arena team added to objmrg");

			player->CLOSE_GOSSIP_MENU();
			creature->MonsterWhisper("Tvoj 1v1 arena team bol vytvoreny.", player->GetGUID());
		}
	break;
	case 2000:
		{
			uint32 atid = player->GetArenaTeamId(2);
			ArenaTeam* at = objmgr.GetArenaTeamById(atid);
			if (!atid || !at)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterWhisper("Nemas 1v1 arena team.", player->GetGUID());
				return;
			}
			player->CLOSE_GOSSIP_MENU();
			at->DelMember(player->GetGUID());
			at->Disband(player->GetSession());
			creature->MonsterWhisper("Tvoj 1v1 arena team bol vymazany.", player->GetGUID());
		}
	break;
	case 3000:
		{
			uint32 atid = player->GetArenaTeamId(2);
			ArenaTeam* at = objmgr.GetArenaTeamById(atid);
			if (!atid || !at)
			{
				player->CLOSE_GOSSIP_MENU();
				creature->MonsterWhisper("Nemas 1v1 arena team.", player->GetGUID());
				return;
			}
			uint8 arenaslot = 2;
			uint8 asGroup = 0;
			uint8 isRated = 1;

			uint8 arenatype = ARENA_TYPE_5v5;
			uint32 arenaRating = 0;

			BattleGround* bg = NULL;
			if (!(bg = sBattleGroundMgr.GetBattleGroundTemplate(BATTLEGROUND_AA)))
			{
				player->CLOSE_GOSSIP_MENU();
				sLog.outError("Npc_arena_1v1: template bg (all arenas) not found");
				return;
			}

			bg = sBattleGroundMgr.GetBattleGroundTemplate(BATTLEGROUND_AA);
		    uint8 bgTypeId = bg->GetTypeID();
			uint32 bgQueueTypeId = sBattleGroundMgr.BGQueueTypeId(bgTypeId, arenatype);

			if (player->GetBattleGroundQueueIndex(bgQueueTypeId) < PLAYER_MAX_BATTLEGROUND_QUEUES)
				return;
			if (!player->HasFreeBattleGroundQueueId())
				return;

			arenaRating = at->GetRating();

			uint32 queueSlot = player->AddBattleGroundQueueId(bgQueueTypeId);
			player->SetBattleGroundEntryPoint(player->GetMapId(),player->GetPositionX(),player->GetPositionY(),player->GetPositionZ(),player->GetOrientation());

			WorldPacket data;
            sBattleGroundMgr.BuildBattleGroundStatusPacket(&data, bg, player->GetTeam(), queueSlot, STATUS_WAIT_QUEUE, 0, 0, arenatype, isRated);
            player->GetSession()->SendPacket(&data);
            sBattleGroundMgr.BuildGroupJoinedBattlegroundPacket(&data, bgTypeId);
            player->GetSession()->SendPacket(&data);
			GroupQueueInfo * ginfo = sBattleGroundMgr.m_BattleGroundQueues[bgQueueTypeId].AddGroup(player, bgTypeId, arenatype, isRated, arenaRating);
            sBattleGroundMgr.m_BattleGroundQueues[bgQueueTypeId].AddPlayer(player, ginfo);
            sLog.outDebug("Npc_arena_1v1: player joined queue for arena as group bg queue type %u bg type %u: GUID %u, NAME %s",bgQueueTypeId,bgTypeId,player->GetGUIDLow(), player->GetName());

			sLog.outDebug("Npc_arena_1v1: arena join end");
			sBattleGroundMgr.m_BattleGroundQueues[bgQueueTypeId].Update(bgTypeId, player->GetBattleGroundQueueIdFromLevel(), arenatype, isRated, arenaRating);

			player->CLOSE_GOSSIP_MENU();
			creature->MonsterWhisper("Tvoja 1v1 arena je prihlasena.", player->GetGUID());
		}
	break;
	}
}

bool GossipSelect_npc_arena_1v1(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    // Show menu
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_npc_arena_1v1(pPlayer, pCreature, uiAction);
    return true;
}

void AddSC_npc_arena_1v1()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_arena_1v1";
    newscript->pGossipHello = &GossipHello_npc_arena_1v1;
    newscript->pGossipSelect = &GossipSelect_npc_arena_1v1;
    newscript->RegisterSelf();
}
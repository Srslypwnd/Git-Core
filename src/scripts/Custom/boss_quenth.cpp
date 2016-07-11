/*
* This file is part of the OregonCore Project. See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/* ScriptData
SDName: Boss_Sapphiron
SD%Complete: 0
SDComment: Place Holder
SDCategory: Naxxramas
EndScriptData */

#include "ScriptPCH.h"

// Elite Grounder AI Spells
#define SPELL_CLEAVE      46559
#define SPELL_LESSER_HEAL 44256

// Grounder AI Spells
#define SPELL_FEL_LIGHTING   46480
#define SPELL_FEL_FLAMES 40562

// Boss AI Spells
#define SPELL_RAIN_OF_FIRE      43440
#define SPELL_FEL_FIREBALL      46101
#define SPELL_FIRE_NOVA         46551
#define SPELL_DRAGONS_BREATH    35250

// Spawner walk pos
#define POS_SPAWNER_X 2262.291504f
#define POS_SPAWNER_Y 5400.280273f
#define POS_SPAWNER_Z 145.892075f

// Boss summon pos
#define POS_BOSS_X    2243.267578f
#define POS_BOSS_Y    5421.990234f
#define POS_BOSS_Z    144.225830f

// Creature IDs
#define NPC_GROUNDER          170180
#define NPC_GROUNDER_FLIGHT   170181
#define BOSS_QUENTH           741364

enum PhaseSpawner
{
	PHASE_SPAWNER_NULL = 0,
	PHASE_WALK_AND_SPAWN = 1,
	PHASE_TALK = 2
};

/*struct Locations
{
	float x, y, z;
};

static Locations spawnerWP[]=
{
{770.01f, 304.50f, 312.29f}
};*/

struct grounderAI : public ScriptedAI
{
	grounderAI(Creature* c) : ScriptedAI(c) {}
	uint32 Lighting_timer;
	uint32 Consuption_timer;

	void Reset()
	{
		Lighting_timer = 15000;
		Consuption_timer = 17000;
	}

	void EnterCombat(Unit * /*who*/)
	{
	}

	void UpdateAI(const uint32 diff)
	{
		if (!UpdateVictim())
			return;

		if (Lighting_timer <= diff)
		{
			DoCast(me->getVictim(), SPELL_FEL_LIGHTING);

			Lighting_timer = 10000;
		}
		else Lighting_timer -= diff;

		if (Consuption_timer <= diff)
		{
			Unit* pTarget;
			pTarget = SelectUnit(SELECT_TARGET_NEAREST, 0);

			if (pTarget)
				DoCast(me->getVictim() , SPELL_FEL_FLAMES);

			Consuption_timer = 17000;
		}
		else Consuption_timer -= diff;

		DoMeleeAttackIfReady();
	}
};

struct elite_grounderAI : public ScriptedAI
{
	elite_grounderAI(Creature* c) : ScriptedAI(c) {}
	uint32 Heal_timer;
	uint32 Cleave_timer;

	void Reset()
	{
		Heal_timer = rand() % 20000;
		Cleave_timer = 12000;
	}

	void EnterCombat(Unit * /*who*/)
	{
	}

	void UpdateAI(const uint32 diff)
	{
		if (!UpdateVictim())
			return;

		// Cleave every 12 sec.
		if (Cleave_timer <= diff)
		{
			DoCast(me->getVictim(), SPELL_CLEAVE);

			Cleave_timer = 12000;
		}
		else Cleave_timer -= diff;

		// Self-Heal randomly to 40 sec.
		if (Heal_timer <= diff)
		{
			DoCast(me, SPELL_LESSER_HEAL);
			Heal_timer = rand()%20000;
		}
		else Heal_timer -= diff;

		DoMeleeAttackIfReady();
	}
};

struct npc_spawnerAI : public ScriptedAI
{
	npc_spawnerAI(Creature* c) : ScriptedAI(c) {}

	bool Event;
	uint32 Timer;
	uint32 TalkCount;
	uint32 Phase;

	void Reset()
	{
		// Base flags
		me->SetUInt32Value(UNIT_NPC_FLAGS, 0); // Database sometimes has strange values..
		me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
		me->AddUnitMovementFlag(MOVEFLAG_WALK_MODE);

		Phase = PHASE_SPAWNER_NULL;
		Event = false;
		TalkCount = 0;
		me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
	}

	void EnterPhase(PhaseSpawner NextPhase)
	{
		switch (NextPhase)
		{
		case PHASE_SPAWNER_NULL:
			break;

		case PHASE_WALK_AND_SPAWN:
			Unit* Boss;
			me->GetMotionMaster()->MovePoint(0, POS_SPAWNER_X, POS_SPAWNER_Y, POS_SPAWNER_Z);
			Boss = me->SummonCreature(BOSS_QUENTH, POS_BOSS_X, POS_BOSS_Y, POS_BOSS_Z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);
			me->setActive(true);
			Timer = 0;
			me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
			break;

		case PHASE_TALK:
			me->MonsterYell("Outland are no longer afraid of your masteries Quenth !", LANG_UNIVERSAL, 0);
			me->setEmoteState(1);
			break;
		}
	}

	void EnterCombat(Unit * /*who*/) 
	{
	}

	void MoveInLineOfSight(Unit* /*who*/) {}

	void HandleTalkSequence()
	{
		switch (TalkCount)
		{
		case 0:
			break;

		case 1:
			break;

		case 2:
			break;
		}
		++TalkCount;
	}

	void UpdateAI(const uint32 diff)
	{
		if (!UpdateVictim())
			return;

			if (Timer <= diff)
			{
				me->MonsterYell("Timer works ?", LANG_UNIVERSAL, 0);
				Event = true;
			}
			else Timer -= diff;

		if (Event)
		{
			switch (Phase)
			{
			case PHASE_SPAWNER_NULL:
					break;

			case PHASE_WALK_AND_SPAWN:
				me->GetMotionMaster()->MovePoint(0, POS_SPAWNER_X, POS_SPAWNER_Y, POS_SPAWNER_Z);
					break;

			case PHASE_TALK:
				HandleTalkSequence();
				break;

			default:
				break;
			}
	    }
	}
};

struct boss_quenthAI : public ScriptedAI
{
	boss_quenthAI(Creature* c) : ScriptedAI(c) {}

	uint32 phase;
	uint32 PhaseSwitch_timer;
	uint32 PhaseSwitch_timer2;
	uint32 rain_of_fire_timer;
	uint32 fel_fireball_timer;
	uint32 dragons_breath_timer;
	uint32 fire_nova_timer;
	uint32 ground_summon_timer;
	uint32 flight_summon_timer;

	void Reset()
	{
		phase = 2; // must be 1. for talk state.
		PhaseSwitch_timer = 60000; // switch phase every minute.
		PhaseSwitch_timer2 = 120000; // Switch back to floor.

		// Start on ground , attackable and walking
		me->RemoveUnitMovementFlag(MOVEFLAG_ROOT);
		me->AddUnitMovementFlag(MOVEFLAG_WALK_MODE);
		me->RemoveUnitMovementFlag(MOVEFLAG_LEVITATING | MOVEFLAG_ONTRANSPORT);
		me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

		// Phase 1 (talk)


		// Phase 2
		rain_of_fire_timer = 20000; // 20sec.
		fel_fireball_timer = 10000; // 10sec.
		dragons_breath_timer = 25000; // 25sec.
		fire_nova_timer = 35000; // 35sec.
		ground_summon_timer = 20000; // 20sec.

		// Phase 3
		flight_summon_timer = 5000;
	}

	void EnterCombat(Unit* /*who*/)
	{
		/*me->AddUnitMovementFlag(MOVEFLAG_ROOT);
		me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
		me->AddUnitMovementFlag(MOVEFLAG_LEVITATING | MOVEFLAG_ONTRANSPORT);
		me->GetMotionMaster()->Clear(false);
		me->GetMotionMaster()->MoveIdle();
		me->SetHover(true);                      Uncomment when spawner is full scripted*/
	}

	void UpdateAI(const uint32 diff)
	{
		if (!UpdateVictim())
			return;

		//---------------Ground phase start--------------------------
		if (phase == 2) // Ground
		{
		if (PhaseSwitch_timer <= diff)
		{
			phase = 3; // to Air
			me->AddUnitMovementFlag(MOVEFLAG_ROOT);
			me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
			me->AddUnitMovementFlag(MOVEFLAG_LEVITATING | MOVEFLAG_ONTRANSPORT);
			me->GetMotionMaster()->Clear(false);
			me->GetMotionMaster()->MoveIdle();
			me->SetHover(true);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

			PhaseSwitch_timer = 120000;
			PhaseSwitch_timer2 = 60000;
		}
		else PhaseSwitch_timer -= diff;

		if (rain_of_fire_timer <= diff)
		{
			Unit* pTarget = NULL;
			pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);

			if (pTarget)
			{
				DoCast(pTarget, SPELL_RAIN_OF_FIRE);
			}

			rain_of_fire_timer = 20000;
		}
		else rain_of_fire_timer -= diff;

		if (fel_fireball_timer <= diff)
		{
			Unit* pTarget = NULL;
			pTarget = SelectUnit(SELECT_TARGET_TOPAGGRO, 0);

			if (pTarget)
				DoCast(pTarget, SPELL_FEL_FIREBALL);

			fel_fireball_timer = 10000;
		}
		else fel_fireball_timer -= diff;

		if (dragons_breath_timer <= diff)
		{
			DoCast(me->getVictim(), SPELL_DRAGONS_BREATH);
			dragons_breath_timer = 25000;
		}
		else dragons_breath_timer -= diff;

		if (fire_nova_timer <= diff)
		{
			DoCast(me, SPELL_FIRE_NOVA);
			fire_nova_timer = 35000;
		}
		else fire_nova_timer -= diff;

		if (ground_summon_timer <= diff)
		{
			Unit* pTarget = NULL;
			Unit* Creature;
			pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
			Creature = me->SummonCreature(NPC_GROUNDER, me->GetPositionX() + 5, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
			Creature = me->SummonCreature(NPC_GROUNDER, me->GetPositionX() - 5, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);

			if (pTarget)
				Creature->Attack(pTarget, false);

			ground_summon_timer = 19000;
		}
		else ground_summon_timer -= diff;
		
		}
		//----------------Ground phase end-----------------------


		//----------------Fly phase start---------------------
		if (phase == 3) // Air
		{
		if (PhaseSwitch_timer2 <= diff)
		{
		phase = 2; // Back to ground
		me->SetSpeed(MOVE_RUN, 1.0f);
		me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		me->RemoveUnitMovementFlag(MOVEFLAG_ROOT);
		me->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
		me->RemoveUnitMovementFlag(MOVEFLAG_LEVITATING | MOVEFLAG_ONTRANSPORT);
		me->GetMotionMaster()->Clear(false);
		me->GetMotionMaster()->MoveChase(me->getVictim());
		me->SetHover(true);

		PhaseSwitch_timer = 60000;
		PhaseSwitch_timer2 = 120000;
		}
		else PhaseSwitch_timer2 -= diff;

		if (rain_of_fire_timer <= diff)
		{
			for (int i = 0; i < 6; i++)
			{
				Unit* pTarget = NULL;
				pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);

				if (pTarget)
				{
					DoCast(pTarget, SPELL_RAIN_OF_FIRE);
				}
			}

			rain_of_fire_timer = 20000;
		}
		else rain_of_fire_timer -= diff;

		if (flight_summon_timer <= diff)
		{
			Unit* pTarget = NULL;
			Unit* Creature;
			pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
			Creature = me->SummonCreature(NPC_GROUNDER_FLIGHT, me->GetPositionX() + 5, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
			Creature = me->SummonCreature(NPC_GROUNDER_FLIGHT, me->GetPositionX() - 5, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);

			if (pTarget)
				Creature->Attack(pTarget, false);


			flight_summon_timer = 6000;
		}
		else flight_summon_timer -= diff;

		}
		//--------------Fly phase end-------------------------

		if (phase != 3 && phase != 1)
		DoMeleeAttackIfReady();
	}
};

bool GossipSelect_npc_spawner(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
	if (uiAction == GOSSIP_ACTION_INFO_DEF + 1) // Begin the Event
	{
		CAST_AI(npc_spawnerAI, pCreature->AI())->EnterPhase(PHASE_WALK_AND_SPAWN);
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	return true;
}

bool GossipHello_npc_spawner(Player* pPlayer, Creature* pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM(0, "Iam ready to beat Soul Burner", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

	return true;
}

CreatureAI* GetAI_grounder(Creature* pCreature)
{
	return new grounderAI(pCreature);
}

CreatureAI* GetAI_elite_grounder(Creature* pCreature)
{
	return new elite_grounderAI(pCreature);
}

CreatureAI* GetAI_npc_spawner(Creature* pCreature)
{
	return new npc_spawnerAI(pCreature);
}

CreatureAI* GetAI_boss_quenth(Creature* pCreature)
{
	return new boss_quenthAI(pCreature);
}

void AddSC_boss_quenth()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name = "boss_quenth";
	newscript->GetAI = &GetAI_boss_quenth;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "grounder";
	newscript->GetAI = &GetAI_grounder;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "elite_grounder";
	newscript->GetAI = &GetAI_elite_grounder;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "npc_spawner";
	newscript->GetAI = &GetAI_npc_spawner;
	newscript->pGossipHello = &GossipHello_npc_spawner;
	newscript->pGossipSelect = &GossipSelect_npc_spawner;
	newscript->RegisterSelf();
}


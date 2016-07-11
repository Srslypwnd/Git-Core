#include "ScriptPCH.h"

#define SPELL_WHIRLWIND 46271

struct npc_soldierAI : public ScriptedAI
{
    npc_soldierAI(Creature *c) : ScriptedAI(c) {}

	uint32 whirlwind_timer;

	void reset ()
	{
		whirlwind_timer = 15000;
	}

    void DamageTaken(Unit *done_by, uint32 &damage)
    {		
		damage = 0; // takes no damage
	}
	
	void UpdateAI(const uint32 diff) 
	{
		if (!UpdateVictim())
			return;

		if (whirlwind_timer <= diff)
		{
			DoCast(me->getVictim(), SPELL_WHIRLWIND);

			whirlwind_timer=15000;
		}else whirlwind_timer -= diff;

		DoMeleeAttackIfReady();
	}
};

CreatureAI* npc_soldier(Creature* pCreature)
{
    return new npc_soldierAI(pCreature);
}

void AddSC_npcs_war_zone()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_soldier";
    newscript->GetAI = &npc_soldier;
    newscript->RegisterSelf();
}
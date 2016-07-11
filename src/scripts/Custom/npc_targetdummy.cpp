/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName:  npc_targetdummy
SD%Complete: 100
SDComment: Test target dummy by Midna
SDCategory: -
EndScriptData */

#include "ScriptPCH.h"

struct npc_targetdummyAI : public ScriptedAI
{
    npc_targetdummyAI(Creature *c) : ScriptedAI(c) {}


    void DamageTaken(Unit *done_by, uint32 &damage)
    {		
		damage = 0; // target dummy takes no damage

		if(done_by->getPowerType() == POWER_RAGE)
			done_by->SetPower(POWER_RAGE, done_by->GetPower(POWER_RAGE) + 50);
		// as the rage user is not in comat, he loses 1 rage per sec.
		// we simply give him 5 rage for every damage he does(including bleed ticks etc...), dirty but effective >.>
	}
	
	void UpdateAI(const uint32 diff) 
	{
		me->SetStunned(true);
		for (std::list<HostileReference*>::iterator itr = me->getThreatManager().getThreatList().begin(); itr != me->getThreatManager().getThreatList().end(); ++itr)
		{
			Unit* plr = (*itr)->getTarget();
			if (plr->GetOwner())						// if its a pet
			{
				if (plr->GetOwner()->GetTypeId() == TYPEID_PLAYER)
					plr->GetOwner()->ToPlayer()->ClearInCombat(); // clear the pet owner from combat
			}
			else {
				if (plr->GetTypeId() == TYPEID_PLAYER)
					plr->ToPlayer()->ClearInCombat(); // clear the player from combat
			}
		}
		me->getThreatManager().getThreatList().empty(); // clear the threat list
	}
};

CreatureAI* npc_targetdummy(Creature* pCreature)
{
    return new npc_targetdummyAI(pCreature);
}

void AddSC_npc_targetdummy()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_targetdummy";
    newscript->GetAI = &npc_targetdummy;
    newscript->RegisterSelf();
}
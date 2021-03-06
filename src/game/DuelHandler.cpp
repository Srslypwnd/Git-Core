/*
 * Copyright (C) 2005-2008 MaNGOS <http://www.mangosproject.org/>
 *
 * Copyright (C) 2008 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 Oregon <http://www.oregoncore.com/>
 *
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

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "Log.h"
#include "Opcodes.h"
#include "UpdateData.h"
#include "MapManager.h"
#include "Player.h"

void WorldSession::HandleDuelAcceptedOpcode(WorldPacket& recvPacket)
{
    recvPacket >> Unused<uint64>();                         // guid

    if (!GetPlayer()->duel)                                  // ignore accept from duel-sender
        return;

    Player *pl       = GetPlayer();
    Player *plTarget = pl->duel->opponent;

    if (pl == pl->duel->initiator || !plTarget || pl == plTarget || pl->duel->startTime != 0 || plTarget->duel->startTime != 0)
        return;

    //sLog.outDebug("WORLD: received CMSG_DUEL_ACCEPTED");
    DEBUG_LOG("Player 1 is: %u (%s)", pl->GetGUIDLow(),pl->GetName());
    DEBUG_LOG("Player 2 is: %u (%s)", plTarget->GetGUIDLow(),plTarget->GetName());

    time_t now = time(NULL);
    pl->duel->startTimer = now;
    plTarget->duel->startTimer = now;

    if (sWorld.getConfig(CONFIG_DUEL_MOD))
    {
        pl->ResetAllPowers();
        plTarget->ResetAllPowers();

        if (sWorld.getConfig(CONFIG_DUEL_CD_RESET) && !pl->GetMap()->IsDungeon())
            pl->RemoveArenaSpellCooldowns();

        if (sWorld.getConfig(CONFIG_DUEL_CD_RESET) && !plTarget->GetMap()->IsDungeon())
            plTarget->RemoveArenaSpellCooldowns();
    }

    WorldPacket data(SMSG_DUEL_COUNTDOWN, 4);
    data << (uint32)3000;                                   // 3 seconds
    pl->GetSession()->SendPacket(&data);
    plTarget->GetSession()->SendPacket(&data);
}

void WorldSession::HandleDuelCancelledOpcode(WorldPacket& recvPacket)
{
    //sLog.outDebug("WORLD: received CMSG_DUEL_CANCELLED");

    recvPacket >> Unused<uint64>();                         // guid

    // no duel requested
    if (!GetPlayer()->duel)
        return;

    // player surrendered in a duel using /forfeit
    if (GetPlayer()->duel->startTime != 0)
    {
		if (sWorld.getConfig(CONFIG_DUEL_CD_RESET))
        {
			GetPlayer()->ResetAllPowers();
			GetPlayer()->duel->opponent->ResetAllPowers();

			if (sWorld.getConfig(CONFIG_DUEL_CD_RESET) && !GetPlayer()->GetMap()->IsDungeon())
				GetPlayer()->RemoveArenaSpellCooldowns();

			if (sWorld.getConfig(CONFIG_DUEL_CD_RESET) && !GetPlayer()->duel->opponent->GetMap()->IsDungeon())
				GetPlayer()->duel->opponent->RemoveArenaSpellCooldowns();
		}
        GetPlayer()->CombatStopWithPets(true);
		if (sWorld.getConfig(CONFIG_DUEL_MOD))
			GetPlayer()->SetHealth(GetPlayer()->GetMaxHealth());
        if (GetPlayer()->duel->opponent)
		{
            GetPlayer()->duel->opponent->CombatStopWithPets(true);
           if (sWorld.getConfig(CONFIG_DUEL_MOD))
				GetPlayer()->duel->opponent->SetHealth(GetPlayer()->duel->opponent->GetMaxHealth());
		}

		if (sWorld.getConfig(CONFIG_DUEL_REWARD_SPELL_CAST) > 0)
		GetPlayer()->duel->opponent->CastSpell(GetPlayer(), sWorld.getConfig(CONFIG_DUEL_REWARD_SPELL_CAST), true);

        GetPlayer()->CastSpell(GetPlayer(), 7267, true);    // beg
        GetPlayer()->DuelComplete(DUEL_WON);
        return;
    }

    // player either discarded the duel using the "discard button"
    // or used "/forfeit" before countdown reached 0
    GetPlayer()->DuelComplete(DUEL_INTERUPTED);
}


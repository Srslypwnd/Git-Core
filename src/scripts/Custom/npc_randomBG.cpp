#include "ScriptPCH.h"

enum joiner_bg
{
    EVENT_SUMM = 1
};

int randomize = urand(0, 4); // Setting up our integer, giving it a value of random 0 - 4
struct joiner_bgAI : public Scripted_NoMovementAI
{
    joiner_bgAI(Creature *c) : Scripted_NoMovementAI(c) {}

    EventMap events;

    void Reset()
    {
        events.Reset();
        events.ScheduleEvent(EVENT_SUMM,1);
    }

    void UpdateAI(const uint32 diff)
    {
        events.Update(diff);
        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SUMM:
                    events.ScheduleEvent(EVENT_SUMM, 1800 * IN_MILLISECONDS); // repeat after 1800 sec
                    switch (randomize) // Switching our randomizer
                    {
                    case 0: // 0
                        me->SummonCreature(20269, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 1800 * IN_MILLISECONDS);
                        break;
                    case 1: // 1
                        me->SummonCreature(20274, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 1800 * IN_MILLISECONDS);
                        break;
                    case 2: // 2
                        me->SummonCreature(20384, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 1800 * IN_MILLISECONDS);
                        break;
                    case 3: // 3
                        me->SummonCreature(20269, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 1800 * IN_MILLISECONDS);
                        break;
                    }
                break;
            }
        }
    }
};

CreatureAI* GetAI_joiner_bg(Creature* creature)
{
    return new joiner_bgAI(creature);
}

void AddSC_joiner_bg()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="joiner_bg";
    newscript->GetAI = &GetAI_joiner_bg;
    newscript->RegisterSelf();
}
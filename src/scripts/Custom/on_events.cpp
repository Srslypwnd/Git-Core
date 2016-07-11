
    #include "ScriptPCH.h"
    #include <cstring>
     
    //This function is called when the player logs in (every login)
    void OnLogin(Player* pPlayer)
    {
            std::string ClassNameString = "";
            switch (pPlayer->getClass())
        {
            case CLASS_WARRIOR:
            ClassNameString = "|cffC79C6E";
            break;
            case CLASS_PALADIN:                
            ClassNameString = "|cffF58CBA";
            break;
            case CLASS_HUNTER:                
            ClassNameString = "|cffABD473";
            break;
            case CLASS_ROGUE:                  
            ClassNameString = "|cffFFF569";
             break;
            case CLASS_PRIEST:                
            ClassNameString = "|cffFFFFFF";
            break;
            case CLASS_SHAMAN:                
            ClassNameString = "|cff0070DE";
            break;
            case CLASS_MAGE:                  
            ClassNameString = "|cff69CCF0";
            break;
            case CLASS_WARLOCK:                
            ClassNameString = "|cff9482C9";
            break;
            case CLASS_DRUID:                  
            ClassNameString = "|cffFF7D0A";
            break;
        }
           
            if(pPlayer->GetTotalPlayedTime() <= 5)
            {
            if (pPlayer->GetTeam() == HORDE)
            {
    std:: string pname;
    pname = pPlayer->GetName();
    char ragezone[250];
    snprintf(ragezone, 250, "|TInterface\\ICONS\\INV_BannerPVP_01:15|t |CFFFE8A0E Vitej%s %s|r |CFFFE8A0Ena |CFFE55BB0ApokalipticWoW", ClassNameString.c_str(), pname.c_str());
    sWorld.SendGlobalText(ragezone,0);
    pPlayer->CastSpell(pPlayer,45153,false);
    return;
            }
            else
            {
    std:: string pname;
    pname = pPlayer->GetName();
    char ragezone[250];
    snprintf(ragezone, 250, "|TInterface\\ICONS\\INV_BannerPVP_02:15|t |CFFFE8A0E Vitej%s %s|r |CFFFE8A0Ena |CFFE55BB0ApokalipticWoW", ClassNameString.c_str(), pname.c_str());
    sWorld.SendGlobalText(ragezone,0);
    pPlayer->CastSpell(pPlayer,45153,false);
    return;
            }
            }
            else
            {
            }
    }


//This function is called when the player logs out
void OnLogout(Player *pPlayer)
{

}



//This function is called when the player kills another player
 void OnPVPKill(Player* killer, Player* killed)
    {
            bool OnlyInBattlegrounds = false;
            bool LooseTokenOnPvPDeath = true;
            int32 AmountOfItemsYouWantTheVictimToLoose = 1;
            bool AddTokenOnPvPKill = true;
            int32 ItemReward = 145713;
            int32 AmountOfRewardsOnKillStreak[9] = { 4, 6, 8, 10, 12, 14, 16, 18, 20 };
            int32 HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim = 2;
            const int32 KillerStreak1 = 05;
            const int32 KillerStreak2 = 10;
            const int32 KillerStreak3 = 15;
            const int32 KillerStreak4 = 20;
            const int32 KillerStreak5 = 30;
            const int32 KillerStreak6 = 40;
            const int32 KillerStreak7 = 50;
            const int32 KillerStreak8 = 60;
            const int32 KillerStreak9 = 70;
            int32 KillStreaks[9] = { KillerStreak1, KillerStreak2, KillerStreak3, KillerStreak4, KillerStreak5, KillerStreak6, KillerStreak7, KillerStreak8, KillerStreak9 };

            uint32 kGUID;
            uint32 vGUID;
            char msg[500];
            kGUID = killer->GetGUID();
            vGUID = killed->GetGUID();
            std:: string killername;
            std:: string killedname;
            killername = killer->GetName();
            killedname = killed->GetName();

            struct SystemInfo
            {
                uint32 KillStreak;
                uint32 LastGUIDKill;
                uint8 KillCount;
            };

            static std::map<uint32, SystemInfo> KillingStreak;

                if (kGUID == vGUID)
            {
                return;
            }
                if (KillingStreak[kGUID].LastGUIDKill == vGUID)
            {
                KillingStreak[kGUID].KillCount++;
                KillingStreak[vGUID].KillCount = 1;
               
                killer->AddItem(ItemReward, 1);
                if (LooseTokenOnPvPDeath == true)
                {
                    killed->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true, false);
                }
            }
            if (KillingStreak[kGUID].LastGUIDKill != vGUID)
            {
                KillingStreak[kGUID].KillCount = 1;
                KillingStreak[vGUID].KillCount = 1;
            }

            if (KillingStreak[kGUID].KillCount == HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim)
            {
                return;
            }

            if (OnlyInBattlegrounds == true)
            {
                if (!killer->GetMap()->IsBattleGround() || killer->GetMapId() == 30)
                {
                    return;
                }
            }

            if (KillingStreak[vGUID].KillStreak >= 5)
            {
                int killstreak = KillingStreak[vGUID].KillStreak;
                std::ostringstream ss;
                ss << "|cffFF0000[KillStreak Announcer]: |cff00FF00" << killer->GetName() << "|r Has Ended |cff00FF00" << killed->GetName() << "|r's killing streak of " << killstreak;
                sWorld.SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
            }

            KillingStreak[kGUID].KillStreak++;
            KillingStreak[vGUID].KillStreak = 0;
            KillingStreak[kGUID].LastGUIDKill = vGUID;
            KillingStreak[vGUID].LastGUIDKill = 0;

            if (AddTokenOnPvPKill == true)
            {
                killer->AddItem(145713, 1);
            }

            if (LooseTokenOnPvPDeath == true)
            {
                killed->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true);
            }

            switch(KillingStreak[kGUID].KillStreak)
            {
                case KillerStreak1:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF5|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
                    killer->ModifyHonorPoints(50);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak2:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF10|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[2]);
                    killer->ModifyHonorPoints(100);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak3:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF15|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[3]);
                    killer->ModifyHonorPoints(150);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak4:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF20|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[4]);
                    killer->ModifyHonorPoints(200);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak5:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF30|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[5]);
                    killer->ModifyHonorPoints(250);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak6:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF40|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[6]);
                    killer->ModifyHonorPoints(300);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak7:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF50|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[7]);
                    killer->ModifyHonorPoints(350);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak8:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF60|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[8]);
                    killer->ModifyHonorPoints(400);
                    killer->CastSpell(killer, 24378, true);
                    break;

                case KillerStreak9:
                    snprintf(msg, 500, "|cffFF0000[KillStreak Announcer]: |cff00FF00%s|r killed |cff00FF00%s|r and is on |cff00FFFF70|r kill streak.", killername.c_str(), killedname.c_str());
                    sWorld.SendServerMessage(SERVER_MSG_STRING, msg);
                    killer->AddItem(ItemReward, AmountOfRewardsOnKillStreak[9]);
                    KillingStreak[kGUID].KillStreak = 0;
                    killer->ModifyHonorPoints(450);
                    killer->CastSpell(killer, 24378, true);
                    break;
            }
        }

 void AddSC_onevents()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "scripted_on_events";
    newscript->pOnLogin = &OnLogin;
    newscript->pOnLogout = &OnLogout;
    newscript->pOnPVPKill = &OnPVPKill;

    newscript->RegisterSelf();
}

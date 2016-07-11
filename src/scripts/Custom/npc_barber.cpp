#include "ScriptPCH.h"

uint32 hair_type;
uint32 hair_color;
uint32 xicht;

struct maxStyles
{
unsigned short maxMale;
unsigned short maxFemale;
};

maxStyles maxHairStyles[MAX_RACES] =
{
    {0,0},  //                        0
    {11,18},// RACE_HUMAN           = 1,
    {6,6},  //  RACE_ORC            = 2,
    {10,13},// RACE_DWARF           = 3,
    {6,6},  // RACE_NIGHTELF        = 4,
    {10,9}, // RACE_UNDEAD_PLAYER   = 5,
    {7,6},  //  RACE_TAUREN         = 6,
    {6,6},  // RACE_GNOME           = 7,
    {5,4},  // RACE_TROLL           = 8,
    {0,0},  // RACE_GOBLIN          = 9,
    {9,13}, //  RACE_BLOODELF       = 10,
    {7,10}, //  RACE_DRAENEI        = 11
};

uint8 maxHairColorr[MAX_RACES] =
{
    0,  //                        0
    9,  // RACE_HUMAN           = 1,
    7,  //  RACE_ORC            = 2,
    9,  // RACE_DWARF           = 3,
    7,  // RACE_NIGHTELF        = 4,
    9,  // RACE_UNDEAD_PLAYER   = 5,
    2,  //  RACE_TAUREN         = 6,
    8,  // RACE_GNOME           = 7,
    9,  // RACE_TROLL           = 8,
    0,  // RACE_GOBLIN          = 9,
    9,  //  RACE_BLOODELF       = 10,
    6,  //  RACE_DRAENEI        = 11
};

maxStyles maxFacialFeatures[MAX_RACES] =
{
    {0,0},  //                        0
    {8,6},  // RACE_HUMAN           = 1,
    {10,6}, // RACE_ORC             = 2,
    {10,5}, // RACE_DWARF           = 3,
    {5,9},  // RACE_NIGHTELF        = 4,
    {16,7}, // RACE_UNDEAD_PLAYER   = 5,
    {6,4},  // RACE_TAUREN          = 6,
    {7,6},  // RACE_GNOME           = 7,
    {10,5}, // RACE_TROLL           = 8,
    {0,0},  // RACE_GOBLIN          = 9,
    {10,9}, // RACE_BLOODELF        = 10,
    {7,6},  // RACE_DRAENEI         = 11
};

void update(Player *player)
{
         player->SendUpdateToPlayer(player);
         WorldPacket data(SMSG_FORCE_DISPLAY_UPDATE, 8);
         data << player->GetGUID();
         player->SendMessageToSet(&data,true);
}

void change_hair(Player *player, short change)
{
        int max;
        switch(player->getGender())
        {
        case GENDER_FEMALE:
                max = maxHairStyles[player->getRace()].maxFemale;
                break;
        case GENDER_MALE:
                max = maxHairStyles[player->getRace()].maxMale;
                break;
        }

        int current = player->GetByteValue(PLAYER_BYTES, 2);
        current += change;

        if(current < 0)
                current = max;
        if(current > max)
                current = 0;

        player->SetByteValue(PLAYER_BYTES, 2, current);
        update(player);
}

void change_color(Player *player, short change)
{
        int max = maxHairColorr[player->getRace()];
        int current = player->GetByteValue(PLAYER_BYTES, 3);

        current += change;

        if ( current < 0 )
        current = max;
        if ( current > max )
        current = 0;

        player->SetByteValue(PLAYER_BYTES, 3, current);
        update(player);
}

/*void change_xicht(Player *player, short change)
{
        int max;

        switch(player->getGender())
        {
        case GENDER_MALE:
                max = maxFacialFeatures[player->getRace()].maxMale;
                break;
        case GENDER_FEMALE:
                max = maxFacialFeatures[player->getRace()].maxFemale;
                break;
        }

        int current = player->GetByteValue(PLAYER_BYTES_2, 0);
        current += change;

        if ( current < 0 )
        current = max;
        if ( current > max )
        current = 0;

        player->SetByteValue(PLAYER_BYTES_2, 0, current);
        update(player);
}
*/

void menu(short num, Player *player, Creature *npc) //Zobrazi menu na zaklade vlozeneho id(num)
{
        switch(num)
        {
        case 0: //hlavni menu
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(7, "Chci ostrihat", GOSSIP_SENDER_MAIN, 1);
                player->ADD_GOSSIP_ITEM(7, "Chci nabarvit vlasy", GOSSIP_SENDER_MAIN, 2);
                //player->ADD_GOSSIP_ITEM(7, "Chci upravit oblicej", GOSSIP_SENDER_MAIN, 3);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, npc->GetGUID());
                break;
        case 1: //menu strihano
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(10, "Dalsi", GOSSIP_SENDER_MAIN, 4);
                player->ADD_GOSSIP_ITEM(10, "Predchozi", GOSSIP_SENDER_MAIN, 5);
                player->ADD_GOSSIP_ITEM(5, "Vratit zmeny", GOSSIP_SENDER_MAIN, 100);
                player->ADD_GOSSIP_ITEM(5, "Hotovo", GOSSIP_SENDER_MAIN, 101);
                player->ADD_GOSSIP_ITEM(7, "Zpet do hlavniho menu", GOSSIP_SENDER_MAIN, 0);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, npc->GetGUID());
                break;
        case 2: //menu zmeny barvy
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(10, "Dalsi", GOSSIP_SENDER_MAIN, 6);
                player->ADD_GOSSIP_ITEM(10, "Predchozi", GOSSIP_SENDER_MAIN, 7);
                player->ADD_GOSSIP_ITEM(5, "Vratit zmeny", GOSSIP_SENDER_MAIN, 100);
                player->ADD_GOSSIP_ITEM(5, "Hotovo", GOSSIP_SENDER_MAIN, 101);
                player->ADD_GOSSIP_ITEM(7, "Zpet do hlavniho menu", GOSSIP_SENDER_MAIN, 0);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, npc->GetGUID());
                break;
       /* case 3: //menu zmeny obliceje
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(10, "Dalsi", GOSSIP_SENDER_MAIN, 8);
                player->ADD_GOSSIP_ITEM(10, "Predchozi", GOSSIP_SENDER_MAIN, 9);
                player->ADD_GOSSIP_ITEM(5, "Vratit zmeny", GOSSIP_SENDER_MAIN, 100);
                player->ADD_GOSSIP_ITEM(5, "Hotovo", GOSSIP_SENDER_MAIN, 101);
                player->ADD_GOSSIP_ITEM(7, "Zpet do hlavniho menu", GOSSIP_SENDER_MAIN, 0);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, npc->GetGUID());
                break;
			*/
        }
}

bool hello(Player *player, Creature *npc)
{
        //backup vzhledu hrace, pro pripad resetu vzhledu
        hair_type = player->GetByteValue(PLAYER_BYTES, 2);
        hair_color = player->GetByteValue(PLAYER_BYTES, 3);
        xicht = player->GetByteValue(PLAYER_BYTES_2, 0);

        menu(0, player, npc);
        return true;
}

bool select(Player * player, Creature *npc, uint32 sender, uint32 action)
{
        switch(action)
        {
        /*
        #######################
        #####Polozky menu######
        #######################
        */
        case 0: //z5 do menu...
                menu(0, player, npc);
                break;
        case 1: //strihani
                menu(1, player, npc);
                break;
        case 2: //barva
                menu(2, player, npc);
                break;
        case 3: //oblicej
                menu(3, player, npc);
                break;
        /*
        #########################
        ########Cinnosti#########
        #########################
        */
        case 4: //dalsi vlasy
                change_hair(player, 1);
                menu(1, player, npc);
                break;
        case 5: //predchozi vlasy
                change_hair(player, -1);
                menu(1, player, npc);
                break;
        case 6: //dalsi barva
                change_color(player, 1);
                menu(2, player, npc);
                break;
        case 7: //predchozi barva
                change_color(player, -1);
                menu(2, player, npc);
                break;
        /*case 8: //dalsi oblicej
                change_xicht(player, 1);
                menu(3, player, npc);
                break;
        case 9: //predchozi oblicej
                change_xicht(player, -1);
                menu(3, player, npc);
                break;
			*/
        case 100: //vratit zmeny
                player->SetByteValue(PLAYER_BYTES, 2, hair_type);
                player->SetByteValue(PLAYER_BYTES, 3, hair_color);
                player->SetByteValue(PLAYER_BYTES_2, 0, xicht);
                update(player);
                menu(0, player, npc);
                break;
        case 101: //hotovo
                player->CLOSE_GOSSIP_MENU();
                break;
        }
        return true;
}

void AddSC_barber()
{
Script *newscript;
newscript = new Script;
newscript->Name="barber";
newscript->pGossipHello = &hello;
newscript->pGossipSelect = &select;
newscript->RegisterSelf();
}
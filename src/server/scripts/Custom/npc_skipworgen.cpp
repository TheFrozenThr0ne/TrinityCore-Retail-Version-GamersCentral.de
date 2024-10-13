#include "Define.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "Unit.h"
#include "Pet.h"
#include "Player.h"
#include "ScriptPCH.h"
#include "ScriptedGossip.h"
#include "GossipDef.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Chat.h"
#include "Config.h"

class SkipWorgenAnnounce : public PlayerScript
{

public:

    SkipWorgenAnnounce() : PlayerScript("SkipWorgenAnnounce") {}

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
            // Announce Module
            if (sConfigMgr->GetBoolDefault("SkipWorgenNPC.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Skip Worgen - Starting - NPC");
            }
    }
};

class SkipWorgenNPC : public CreatureScript
{

public:

    SkipWorgenNPC() : CreatureScript("SkipWorgenNPC") { }

    // Passive Emotes
    struct SkipWorgenNPCAI : public ScriptedAI
    {
        SkipWorgenNPCAI(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            AddGossipItemFor(player, GossipOptionNpc::None, "Teleport me to Stormwind!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            if (player->GetLevel() == 1)
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Set Character to Level 30!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            }

            SendGossipMenuFor(player, 603000, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);

            switch (action)
            {
            case 1001:

                ClearGossipMenuFor(player);

                player->LearnSpell(68992, true);

                player->AddItem(52040, 1);

                player->SetReputation(1134, 3000);

                player->ModifyMoney(10000, true);

                player->TeleportTo(0, -8833.070312f, 622.778015f, 93.931702f, 0.677100f);
                break;
            case 1002:

                player->SetLevel(20, true);

                break;
            default:
                break;
            }

            ClearGossipMenuFor(player);

            player->LearnSpell(68992, true);

            player->AddItem(52040, 1);

            player->SetReputation(1134, 3000);

            player->ModifyMoney(10000, true);

            player->TeleportTo(0, -8833.070312f, 622.778015f, 93.931702f, 0.677100f);
           
            // Goodbye
            CloseGossipMenuFor(player);
            return true;
        }
    };

    // CREATURE AI
    CreatureAI* GetAI(Creature* creature) const override
    {
        return new SkipWorgenNPCAI(creature);
    }
};

void AddSC_SkipWorgenNPCScripts()
{
    new SkipWorgenAnnounce();
    new SkipWorgenNPC();
}

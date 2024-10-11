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

class SkipDeathKnightAnnounce : public PlayerScript
{

public:

    SkipDeathKnightAnnounce() : PlayerScript("SkipDeathKnightAnnounce") {}

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
            // Announce Module
            if (sConfigMgr->GetBoolDefault("SkipDeathKnightNPC.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Skip Dead Knight - Starting - NPC");
            }
    }
};

class SkipDeathKnightNPC : public CreatureScript
{

public:

    SkipDeathKnightNPC() : CreatureScript("SkipDeathKnightNPC") { }

    // Passive Emotes
    struct SkipDeathKnightNPCAI : public ScriptedAI
    {
        SkipDeathKnightNPCAI(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            switch (player->GetTeamId())
            {
            case TEAM_ALLIANCE:
                AddGossipItemFor(player, GossipOptionNpc::None, "Teleport me to Stormwind!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

                if (player->GetLevel() == 8)
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Set Character to Level 30!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                }

                break;
            case TEAM_HORDE:
                AddGossipItemFor(player, GossipOptionNpc::None, "Teleport me to Orgrimmar!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

                if (player->GetLevel() == 8)
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Set Character to Level 30!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                }

                break;
            default:
                break;
            }

            SendGossipMenuFor(player, 603000, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            //uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            player->LearnSpell(53428, true); // Runeforging
            player->LearnSpell(50977, true); // Death Gate
            player->ModifyMoney(50000, true);

            switch (gossipListId)
            {
            case 1001:

                player->SetReputation(72, 6000); // Stormwind Faction

                player->TeleportTo(0, -8833.070312f, 622.778015f, 93.931702f, 0.677100f);
                break;
            case 1002:

                player->SetReputation(76, 6000); // Orgrimmar Faction

                player->TeleportTo(1, 1570.931641f, -4396.939453f, 16.000856f, 0.452704f);
                break;
            case 1003:

                player->SetLevel(30, true);

                break;
            default:
                break;
            }
            // Goodbye
            CloseGossipMenuFor(player);
            return true;
        }
    };

    // CREATURE AI
    CreatureAI* GetAI(Creature* creature) const override
    {
        return new SkipDeathKnightNPCAI(creature);
    }
};

void AddSC_SkipDeathKnightNPCScripts()
{
    new SkipDeathKnightAnnounce();
    new SkipDeathKnightNPC();
}

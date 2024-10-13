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

class SkipExilesReachAnnounce : public PlayerScript
{

public:

    SkipExilesReachAnnounce() : PlayerScript("SkipExilesReachAnnounce") {}

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
            // Announce Module
            if (sConfigMgr->GetBoolDefault("SkipExilesReachNPC.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Skip Exile's Reach - Starting - NPC");
            }
    }
};

class SkipExilesReachNPC : public CreatureScript
{

public:

    SkipExilesReachNPC() : CreatureScript("SkipExilesReachNPC") { }

    // Passive Emotes
    struct SkipExilesReachNPCAI : public ScriptedAI
    {
        SkipExilesReachNPCAI(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            switch (player->GetTeamId())
            {
            case TEAM_ALLIANCE:
                AddGossipItemFor(player, GossipOptionNpc::None, "Teleport me to Stormwind!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                break;
            case TEAM_HORDE:
                AddGossipItemFor(player, GossipOptionNpc::None, "Teleport me to Orgrimmar!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                break;
            default:
                break;
            }

            if (player->GetLevel() == 4)
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Set Character to Level 10!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            }

            SendGossipMenuFor(player, 606000, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            if (player->GetClass() == CLASS_DRUID) {
                player->LearnSpell(783, true);
            }

            if (player->GetClass() == CLASS_HUNTER)
            {
                player->LearnSpell(83242, true);
            }

            if (player->GetClass() == CLASS_MAGE)
            {
                player->LearnSpell(118, true);
            }

            if (player->GetClass() == CLASS_MONK)
            {
                player->LearnSpell(322109, true);
            }

            if (player->GetClass() == CLASS_PALADIN)
            {
                player->LearnSpell(642, true);
            }

            if (player->GetClass() == CLASS_PRIEST)
            {
                player->LearnSpell(2006, true);
            }

            if (player->GetClass() == CLASS_ROGUE)
            {
                player->LearnSpell(315584, true);
            }

            if (player->GetClass() == CLASS_SHAMAN)
            {
                player->LearnSpell(2645, true);
            }

            if (player->GetClass() == CLASS_WARLOCK)
            {
                player->LearnSpell(697, true);
            }

            if (player->GetClass() == CLASS_WARRIOR)
            {
                player->LearnSpell(163201, true);
            }

            player->ModifyMoney(25000, true);

            switch (action)
            {
            case 1001:
                player->TeleportTo(0, -8833.070312f, 622.778015f, 93.931702f, 0.677100f);
                break;
            case 1002:
                player->TeleportTo(1, 1570.931641f, -4396.939453f, 16.000856f, 0.452704f);
                break;
            case 1003:
                player->SetLevel(10, true);
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
        return new SkipExilesReachNPCAI(creature);
    }
};

void AddSC_SkipExilesReachNPCScripts()
{
    new SkipExilesReachAnnounce();
    new SkipExilesReachNPC();
}

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

class SkipAlliedTeleporterAnnounce : public PlayerScript
{

public:

    SkipAlliedTeleporterAnnounce() : PlayerScript("SkipAlliedTeleporterAnnounce") {}

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
            // Announce Module
            if (sConfigMgr->GetBoolDefault("SkipAlliedTeleporterNPC.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Skip Allied Race - Starting - NPC");
            }
    }
};

class SkipAlliedTeleporterNPC : public CreatureScript
{

public:

    SkipAlliedTeleporterNPC() : CreatureScript("SkipAlliedTeleporterNPC") { }

    // Passive Emotes
    struct SkipAlliedTeleporterNPCAI : public ScriptedAI
    {
        SkipAlliedTeleporterNPCAI(Creature* creature) : ScriptedAI(creature) { }

        bool OnGossipHello(Player* player) override
        {
            switch (player->GetTeamId())
            {
            case TEAM_HORDE:
                AddGossipItemFor(player, GossipOptionNpc::None, "Teleport to Orgrimmar!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                break;
            case TEAM_ALLIANCE:
                AddGossipItemFor(player, GossipOptionNpc::None, "Teleport to Stormwind!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                break;
            default:
                break;
            }

            switch (player->GetRace())
            {
            case RACE_HIGHMOUNTAIN_TAUREN:
                if (!player->HasItemCount(141394, 1) || !player->HasItemCount(157757, 1) || !player->HasItemCount(157028, 1))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                }
                break;
            case RACE_NIGHTBORNE:
                if (!player->HasItemCount(156487, 1) || !player->HasSpell(258845))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                }
                break;
            case RACE_EARTHEN_DWARF_HORDE:
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                break;
            case RACE_EARTHEN_DWARF_ALLIANCE:
                AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                break;
            case RACE_ZANDALARI_TROLL:
                if (!player->HasItemCount(157870, 1) || !player->HasSpell(263707))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                }
                break;
            case RACE_VOID_ELF:
                if (!player->HasItemCount(156486, 1) || !player->HasSpell(259202))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                }
                break;
            case RACE_LIGHTFORGED_DRAENEI:
                if (!player->HasItemCount(155656, 1) || !player->HasSpell(258022))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                }
                break;
            case RACE_DARK_IRON_DWARF:
                if (!player->HasItemCount(161331, 1) || !player->HasSpell(271646))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                }
                break;
            case RACE_KUL_TIRAN:
                if (!player->HasItemCount(164762, 1) || !player->HasSpell(282682))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                }
                break;
            case RACE_MECHAGNOME:
                if (!player->HasItemCount(174067, 1) || !player->HasSpell(305592))
                {
                    AddGossipItemFor(player, GossipOptionNpc::None, "Give provided stuff for my Race!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                }
                break;
            default:
                break;
            }

            if (player->GetLevel() < 20)
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Set Level to 20!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            }

            SendGossipMenuFor(player, 603000, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            player->ModifyMoney(50000, true);

            switch (action)
            {
            case 1000: // HIGHMOUNTAIN TAUREN
                player->AddItem(141394, 1);
                player->AddItem(157757, 1);
                player->AddItem(157028, 1);
                player->ModifyCurrency(1553, 750);
                break;
            case 1001: // NIGHTBORNE
                player->AddItem(156487, 1);
                break;
            case 1002: // EARTHEN DWARF HORDE
                break;
            case 1003: // EARTHEN DWARF ALLIANCE
                break;
            case 1004: // ZANDALARI TROLL
                player->AddItem(157870, 1);
                break;
            case 1005: // VOID ELF
                player->AddItem(156486, 1);
                break;
            case 1006: // LIGHTFORGED DRAENEI
                player->AddItem(155656, 1);
                break;
            case 1007: // DARK IRON DWARF
                player->ModifyCurrency(1553, 1);
                player->AddItem(155656, 1);
                player->AddItem(161331, 1);
                break;
            case 1008: // KUL TIRAN
                player->AddItem(164762, 1);
                break;
            case 1009: // MECHAGNOME
                player->AddItem(174067, 1);
                break;
            case 1010: // HORDE TELEPORTER
                player->TeleportTo(1, 1570.931641f, -4396.939453f, 16.000856f, 0.452704f);
                break;
            case 1011: // ALLIANCE TELEPORTER
                player->TeleportTo(0, -8833.070312f, 622.778015f, 93.931702f, 0.677100f);
                break;
            case 1012: // SET PLAYER LEVEL TO 20
                player->SetLevel(20, true);
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
        return new SkipAlliedTeleporterNPCAI(creature);
    }
};

void AddSC_SkipAlliedTeleporterNPCScripts()
{
    new SkipAlliedTeleporterAnnounce();
    new SkipAlliedTeleporterNPC();
}

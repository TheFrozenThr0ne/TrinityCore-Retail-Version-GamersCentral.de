/* Credits: Micrah/Milestorme Module creator */

#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "Configuration/Config.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "Map.h"
#include "TempSummon.h"

enum Vendors
{
    NPC_VENDOR_A    = 128,
    NPC_VENDOR_H    = 128,
};



class pocket_portal : public ItemScript
{
public:
    pocket_portal() : ItemScript("pocket_portal") { }

        bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/, ObjectGuid /*castId*/) override
        {
            if (!sConfigMgr->GetBoolDefault("PocketPortal.Enable", true))
            {
                return false;
            }

            if (player->duel || player->GetMap()->IsBattleArena() || player->InBattleground() || player->isDead() || player->IsInCombat() || player->IsInFlight() || player->HasStealthAura() || player->HasInvisibilityAura())
            {
                return false;
            }

            player->PlayerTalkClass->ClearMenus();

            if (sConfigMgr->GetBoolDefault("PocketPortal.Enable", true))
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Pocket Portal", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
            }
            return false; // Cast the spell on use normally
        }

        void OnGossipSelect(Player* player, Item* /*item*/, uint32 /*menuId*/, uint32 action) override
        {
            ClearGossipMenuFor(player);

            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF + 1: /*portal*/
            {
                uint32 vendorId = 0;
                std::string salute;
                if (player->GetTeamId() == TEAM_ALLIANCE)
                {
                    vendorId = NPC_VENDOR_A;
                    salute = "Greetings";
                }
                else {
                    vendorId = NPC_VENDOR_H;
                    salute = "Zug zug";
                }

                SummonTempNPC(player, vendorId, salute.c_str());
                CloseGossipMenuFor(player);
                break;
            }

            }
        }

        void SummonTempNPC(Player* player, uint32 entry, const char* salute = "")
        {
            if (!player || entry == 0)
                return;

            int npcDuration = sConfigMgr->GetIntDefault("Portal.NpcDuration", 60) * IN_MILLISECONDS;
            if (npcDuration <= 0) // Safeguard
                npcDuration = 60;

            // Beschwörung der Kreatur
            Creature* creature = player->SummonCreature(entry, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, Seconds(npcDuration));

            if (creature) // Überprüfen, ob die Beschwörung erfolgreich war
            {
                // Verwende static_cast, wenn du sicher bist, dass creature ein TempSummon ist
                TempSummon* tempSummon = static_cast<TempSummon*>(creature);
                if (tempSummon)
                {
                    tempSummon->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, player->GetFollowAngle());
                    tempSummon->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
                    tempSummon->SetFaction(player->GetFaction());

                    if (salute && !(salute[0] == '\0'))
                        tempSummon->TextEmote(salute, player, false);
                }
            }
        }
};

void AddSC_pocket_portal()
{
    new pocket_portal();
}

/*

# creature_template

insert  into `creature_template`(`entry`,`KillCredit1`,`KillCredit2`,`name`,`femaleName`,`subname`,`TitleAlt`,`IconName`,`RequiredExpansion`,`VignetteID`,`faction`,`npcflag`,`speed_walk`,`speed_run`,`scale`,`Classification`,`dmgschool`,`BaseAttackTime`,`RangeAttackTime`,`BaseVariance`,`RangeVariance`,`unit_class`,`unit_flags`,`unit_flags2`,`unit_flags3`,`family`,`trainer_class`,`type`,`VehicleId`,`AIName`,`MovementType`,`ExperienceModifier`,`RacialLeader`,`movementId`,`WidgetSetID`,`WidgetSetUnitConditionID`,`RegenHealth`,`CreatureImmunitiesId`,`flags_extra`,`ScriptName`,`StringId`,`VerifiedBuild`) values
(500003,0,0,'Helpli',NULL,'Skip Worgen',NULL,NULL,0,0,35,1,1,1.14286,1,0,0,0,0,1,1,0,0,0,0,0,0,7,0,'SmartAI',0,1,0,0,0,0,1,0,2,'SkipWorgenNPC',NULL,56110);


# creature_template_model

insert  into `creature_template_model`(`CreatureID`,`Idx`,`CreatureDisplayID`,`DisplayScale`,`Probability`,`VerifiedBuild`) values
(500003,0,29466,1,1,56110);


# creature_template_gossip

insert  into `creature_template_gossip`(`CreatureID`,`MenuID`,`VerifiedBuild`) values
(500003,600000,0);


# gossip_menu

insert  into `gossip_menu`(`MenuID`,`TextID`,`VerifiedBuild`) values
(600000,68,0);

*/


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

                player->SetLevel(30, true);

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

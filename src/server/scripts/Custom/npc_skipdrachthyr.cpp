/*

# creature_template

insert  into `creature_template`(`entry`,`KillCredit1`,`KillCredit2`,`name`,`femaleName`,`subname`,`TitleAlt`,`IconName`,`RequiredExpansion`,`VignetteID`,`faction`,`npcflag`,`speed_walk`,`speed_run`,`scale`,`Classification`,`dmgschool`,`BaseAttackTime`,`RangeAttackTime`,`BaseVariance`,`RangeVariance`,`unit_class`,`unit_flags`,`unit_flags2`,`unit_flags3`,`family`,`trainer_class`,`type`,`VehicleId`,`AIName`,`MovementType`,`ExperienceModifier`,`RacialLeader`,`movementId`,`WidgetSetID`,`WidgetSetUnitConditionID`,`RegenHealth`,`CreatureImmunitiesId`,`flags_extra`,`ScriptName`,`StringId`,`VerifiedBuild`) values
(500004,0,0,'Helplingen',NULL,'Skip Drachthyr',NULL,NULL,0,0,35,1,1,1.14286,1,0,0,0,0,1,1,0,0,0,0,0,0,7,0,'SmartAI',0,1,0,0,0,0,1,0,2,'SkipDrachthyrNPC',NULL,56110);


# creature_template_model

insert  into `creature_template_model`(`CreatureID`,`Idx`,`CreatureDisplayID`,`DisplayScale`,`Probability`,`VerifiedBuild`) values
(500004,0,110189,1,1,56110);


# creature_template_gossip

insert  into `creature_template_gossip`(`CreatureID`,`MenuID`,`VerifiedBuild`) values
(500004,600000,0);


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

class SkipDrachthyrAnnounce : public PlayerScript
{

public:

    SkipDrachthyrAnnounce() : PlayerScript("SkipDrachthyrAnnounce") {}

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
            // Announce Module
            if (sConfigMgr->GetBoolDefault("SkipDrachthyrNPC.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Skip Drachthyr - Starting - NPC");
            }
    }
};

class SkipDrachthyrNPC : public CreatureScript
{

public:

    SkipDrachthyrNPC() : CreatureScript("SkipDrachthyrNPC") { }

    // Passive Emotes
    struct SkipDrachthyrNPCAI : public ScriptedAI
    {
        SkipDrachthyrNPCAI(Creature* creature) : ScriptedAI(creature) { }

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

            if (player->GetLevel() == 58)
            {
                AddGossipItemFor(player, GossipOptionNpc::None, "Set Character to Level 30!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            }

            SendGossipMenuFor(player, 603000, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            ClearGossipMenuFor(player);

            player->LearnSpell(356995, true);
            player->LearnSpell(381322, true);
            player->LearnSpell(355913, true);
            player->LearnSpell(358267, true);
            player->LearnSpell(357210, true);
            player->LearnSpell(351239, true);
            player->AddItem(193914, 1);
            player->ModifyMoney(5000000, true);

            switch (action)
            {
            case 1001:
                player->TeleportTo(0, -8833.070312f, 622.778015f, 93.931702f, 0.677100f);
                break;
            case 1002:
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
        return new SkipDrachthyrNPCAI(creature);
    }
};

void AddSC_SkipDrachthyrNPCScripts()
{
    new SkipDrachthyrAnnounce();
    new SkipDrachthyrNPC();
}

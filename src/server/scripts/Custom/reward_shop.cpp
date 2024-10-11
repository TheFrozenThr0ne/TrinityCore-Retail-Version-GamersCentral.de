/*

CREATE TABLE IF NOT EXISTS `reward_shop` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `action` int(11) NOT NULL DEFAULT '0',
  `action_data` int(11) NOT NULL DEFAULT '0',
  `quantity` int(11) NOT NULL DEFAULT '0',
  `code` char(50) NOT NULL,
  `status` int(11) NOT NULL DEFAULT '0',
  `PlayerGUID` int(11) NOT NULL DEFAULT '0',
  `PlayerIP` varchar(50) NOT NULL DEFAULT '0',
  `CreatedBy` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8 COMMENT='Database Actions:\r\n\r\n1 = item\r\n2 = gold\r\n3 = name change\r\n4 = faction change\r\n5 = race change';

INSERT INTO reward_shop VALUES (1, 2, 11, 0, 123, 0, 0, 0,0);

*/

/*

# creature_template

insert  into `creature_template`(`entry`,`KillCredit1`,`KillCredit2`,`name`,`femaleName`,`subname`,`TitleAlt`,`IconName`,`RequiredExpansion`,`VignetteID`,`faction`,`npcflag`,`speed_walk`,`speed_run`,`scale`,`Classification`,`dmgschool`,`BaseAttackTime`,`RangeAttackTime`,`BaseVariance`,`RangeVariance`,`unit_class`,`unit_flags`,`unit_flags2`,`unit_flags3`,`family`,`trainer_class`,`type`,`VehicleId`,`AIName`,`MovementType`,`ExperienceModifier`,`RacialLeader`,`movementId`,`WidgetSetID`,`WidgetSetUnitConditionID`,`RegenHealth`,`CreatureImmunitiesId`,`flags_extra`,`ScriptName`,`StringId`,`VerifiedBuild`) values
(500002,0,0,'Revil',NULL,'Code Reward',NULL,NULL,0,0,35,1,1,1.14286,1,0,0,0,0,1,1,0,0,0,0,0,0,7,0,'SmartAI',0,1,0,0,0,0,1,0,2,'reward_shop',NULL,56110);


# creature_template_model

insert  into `creature_template_model`(`CreatureID`,`Idx`,`CreatureDisplayID`,`DisplayScale`,`Probability`,`VerifiedBuild`) values
(500002,0,16804,1,1,56110);


# creature_template_gossip

insert  into `creature_template_gossip`(`CreatureID`,`MenuID`,`VerifiedBuild`) values
(500002,600000,0);


# gossip_menu

insert  into `gossip_menu`(`MenuID`,`TextID`,`VerifiedBuild`) values
(600000,68,0);

*/

/*

Database Actions:

1 = item
2 = gold
3 = name change
4 = faction change
5 = race change

script made by talamortis

*/

#include "Configuration/Config.h"
#include "Player.h"
#include "Creature.h"
#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Define.h"
#include "GossipDef.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Chat.h"

bool rewardShopAnnounceModule;

class reward_shopConfig : public WorldScript
{
public:
    reward_shopConfig() : WorldScript("reward_shopConfig") { }

    void OnConfigLoad(bool reload) override
    {
        if (!reload) {
            rewardShopAnnounceModule = sConfigMgr->GetBoolDefault("reward_shop.Announce", true);
        }
    }
};

class reward_shopAnnounce : public PlayerScript
{

public:

    reward_shopAnnounce() : PlayerScript("reward_shopAnnounce") {}

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
        // Announce Module
        if (rewardShopAnnounceModule)
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Codebox - NPC");
        }
    }
};

class reward_shop : public CreatureScript
{
public:
    reward_shop() : CreatureScript("reward_shop") {}

    struct npc_reward_shopAI : public ScriptedAI
    {
        npc_reward_shopAI(Creature* creature) : ScriptedAI(creature) {}

    bool failedcode;

    bool OnGossipHello(Player *player) override
    {
        if (player->IsInCombat())
            return false;

        if (!sConfigMgr->GetBoolDefault("RewardShopEnable", 1))
            return false;

        AddGossipItemFor(player, GossipOptionNpc::None, "I'd like to redeem my code.", GOSSIP_SENDER_MAIN, 1, "", 0, true);
        AddGossipItemFor(player, GossipOptionNpc::None, "How do i get a code?", GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, GossipOptionNpc::None, "I dont have a code.", GOSSIP_SENDER_MAIN, 3);

        if (sConfigMgr->GetBoolDefault("AllowGM", 1) && player->IsGameMaster())
        {
            AddGossipItemFor(player, GossipOptionNpc::None, "[GM] I would like generate a code.", GOSSIP_SENDER_MAIN, 4);
        }

        SendGossipMenuFor(player, 7780, me->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
    {
        uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
        player->PlayerTalkClass->ClearMenus();
        std::string info = sConfigMgr->GetStringDefault("WebsiteAddress", "You can get codes by visiting the online store at (website address)");
        uint32 rnd1 = urand(10000, 90000);
        uint32 rnd2 = urand(10000, 90000);
        uint32 rnd3 = urand(10000, 90000);
        uint32 rnd4 = urand(10000, 90000);
        uint32 rnd5 = urand(10000, 90000);

        std::string CreatedBy = player->GetName();
        std::ostringstream randomcode;
        randomcode << "GM-" << rnd1 << "-" << rnd2 << "-" << rnd3 << "-" << rnd4 << "-" << rnd5;

        switch (action)
        {
        case 2:
            me->Whisper(info.c_str(), LANG_UNIVERSAL, player);
            CloseGossipMenuFor(player);
            break;
        case 3:
            CloseGossipMenuFor(player);
            break;
        case 4:
            player->PlayerTalkClass->ClearMenus();
            AddGossipItemFor(player, GossipOptionNpc::None, "I'd like to generate a name change code.", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, GossipOptionNpc::None, "I'd like to generate a faction change code.", GOSSIP_SENDER_MAIN, 7);
            AddGossipItemFor(player, GossipOptionNpc::None, "I'd like to generate a race change code.", GOSSIP_SENDER_MAIN, 8);
            AddGossipItemFor(player, GossipOptionNpc::None, "I'd like to generate a random code no item.", GOSSIP_SENDER_MAIN, 9);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            break;
        case 6:
            CharacterDatabase.PQuery("INSERT INTO `reward_shop` (`action`, `action_data`, `quantity`, `code`, `status`, `PlayerGUID`, `PlayerIP`, `CreatedBy`) VALUES(3, 0, 0, '{}', 0, 0, '0', '{}')", randomcode.str().c_str(), CreatedBy.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("Code was successfully created your code is %s", randomcode.str().c_str());
            CloseGossipMenuFor(player);
            break;
        case 7:
            CharacterDatabase.PQuery("INSERT INTO `reward_shop` (`action`, `action_data`, `quantity`, `code`, `status`, `PlayerGUID`, `PlayerIP`,`CreatedBy`) VALUES(4, 0, 0, '{}', 0, 0, '0', '{}')", randomcode.str().c_str(), CreatedBy.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("Code was successfully created your code is %s", randomcode.str().c_str());
            CloseGossipMenuFor(player);
            break;
        case 8:
            CharacterDatabase.PQuery("INSERT INTO `reward_shop` (`action`, `action_data`, `quantity`, `code`, `status`, `PlayerGUID`, `PlayerIP`, `CreatedBy`) VALUES(5, 0, 0, '{}', 0, 0, '0', '{}')", randomcode.str().c_str(), CreatedBy.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("Code was successfully created your code is %s", randomcode.str().c_str());
            CloseGossipMenuFor(player);
            break;
        case 9:
            CharacterDatabase.PQuery("INSERT INTO `reward_shop` (`action`, `action_data`, `quantity`, `code`, `status`, `PlayerGUID`, `PlayerIP`, `CreatedBy`) VALUES(1, 0, 0, '{}', 0, 0, '0', '{}')", randomcode.str().c_str(), CreatedBy.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("Code was successfully created your code is %s", randomcode.str().c_str());
            CloseGossipMenuFor(player);
            break;
        }
        return true;
    }

    bool OnGossipSelectCode(Player *player, uint32 /* sender */, uint32, const char *code) override
    {
        ObjectGuid playerguid = player->GetGUID();
        std::string playerIP = player->GetSession()->GetRemoteAddress();
        std::string rewardcode = code;
        std::ostringstream messageCode;
        messageCode << "Sorry " << player->GetName() << ", that is not a valid code or has already been redeemed.";

        std::size_t found = rewardcode.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-");

        if (found != std::string::npos)
            return false;

        // check for code
        QueryResult result = CharacterDatabase.PQuery("SELECT id, action, action_data, quantity, status FROM reward_shop WHERE code = '{}'", rewardcode.c_str());

        if (!result)
        {
            player->PlayDirectSound(9638); // No
            me->Whisper(messageCode.str().c_str(), LANG_UNIVERSAL, player);
            me->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
            return false;
        }

        std::transform(rewardcode.begin(), rewardcode.end(), rewardcode.begin(), ::toupper);

        do
        {
            Field *fields = result->Fetch();
            uint32 action = fields[1].GetUInt32();
            uint32 action_data = fields[2].GetUInt32();
            uint32 quantity = fields[3].GetUInt32();
            uint32 status = fields[4].GetInt32();
            int count = 1;
            uint32 noSpaceForCount = 0;
            ItemPosCountVec dest;
            InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, action_data, quantity, &noSpaceForCount);

            if (status == 1)
            {
                player->PlayDirectSound(9638); // No
                me->Whisper(messageCode.str().c_str(), LANG_UNIVERSAL, player);
                me->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
                return false;
            }
            switch (action)
            {

            case 1: /* Item */
                if (msg != EQUIP_ERR_OK)
                    count -= noSpaceForCount;

                if (count == 0 || dest.empty())
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("Can not create item either item is unique or you do not have any space");
                    ChatHandler(player->GetSession()).SetSentErrorMessage(true);
                    return false;
                }

                if (count > 0 && action_data)
                {
                    player->AddItem(action_data, quantity);
                }
                break;
            case 2: /* Gold */
                player->ModifyMoney(action_data * 10000);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Successfully added [%u G]", action_data);
                break;
            case 3: /* Name Change */
                player->SetAtLoginFlag(AT_LOGIN_RENAME);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for name change.");
                break;
            case 4: /* Faction Change */
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for faction change.");
                break;
            case 5: /* Race Change */
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for race change.");
                break;
            }

        } while (result->NextRow());

        CharacterDatabase.PQuery("UPDATE reward_shop SET status = 1, PlayerGUID = '{}', PlayerIP = '{}' WHERE code = '{}'", playerguid.GetCounter(), playerIP.c_str(), rewardcode.c_str());
        return true;
    }

        uint32 say_timer;
        bool canSay;

        void Reset() override
        {
            say_timer = 1000;
            canSay = false;
        }

        void MoveInLineOfSight(Unit *who)
        {
            if (me->IsWithinDist(who, 5.0f) && who->GetTypeId() == TYPEID_PLAYER)
            {
                canSay = true;
            }
            else
                canSay = false;
        }

        void UpdateAI(uint32 diff)
        {
            if (say_timer <= diff)
            {
                if (canSay)
                {
                    me->Say("Do you have a code to redeem? Step right up!", LANG_UNIVERSAL);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                    say_timer = 61000;
                }
            }
            else
                say_timer -= diff;
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_reward_shopAI(creature);
    }
};

void AddRewardShopScripts()
{
    new reward_shopConfig();
    new reward_shopAnnounce();
    new reward_shop();
}

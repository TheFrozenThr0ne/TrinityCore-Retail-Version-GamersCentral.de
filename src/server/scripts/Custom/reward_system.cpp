/*

CREATE TABLE IF NOT EXISTS `reward_system` (
  `roll` int(11) NOT NULL,
  `item` int(11) NOT NULL,
  `quantity` int(11)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

*/

// Needs to be Implanted before: https://github.com/TrinityCore/TrinityCoreCustomChanges/commit/ebf94710f023e6d1bbf1b998d8014a3c7bdb5e31
// Player.cpp
// ScriptMgr.cpp
// ScriptMgr.h
//
// 
//
// 
// Lucky Number made by Talamortis

#include "Configuration/Config.h"
#include "Player.h"
#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Define.h"
#include "GossipDef.h"
#include "Chat.h"
#include "World.h"
#include "Mail.h"
#include "Item.h"

uint32 Max_roll;

class reward_system : public PlayerScript
{
public:
    reward_system() : PlayerScript("reward_system") { }
    
    uint32 initialTimer = (sConfigMgr->GetIntDefault("RewardTime", 1) * HOUR * IN_MILLISECONDS);
    uint32 RewardTimer = initialTimer;
    int32 roll;

    void OnLogin(Player* player, bool /*firstLogin*/) override
    {
        if (sConfigMgr->GetBoolDefault("RewardSystemEnable", true) && sConfigMgr->GetBoolDefault("RewardSystem.Announce", true)) {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Reward Time Played - (Timer Roll)");
        }
    }

    void OnUpdate(Player* player, uint32 p_time) override
    {
        if (sConfigMgr->GetBoolDefault("RewardSystemEnable", true))
        {
            if (RewardTimer > 0)
            {
                if (player->isAFK())
                    return;

                if (RewardTimer <= p_time)
                {
                    roll = urand(1, Max_roll);
                    // TODO: this should use a asynchronous query with a callback instead of a synchronous, blocking query
                    QueryResult result = CharacterDatabase.PQuery("SELECT item, quantity FROM reward_system WHERE roll = '{}'", roll);

                    if (!result)
                    {
                        
                        // Inform the player about the lose
                        ChatHandler(player->GetSession()).PSendSysMessage("[Lucky Number] Better luck next time! Your roll was %u.", roll);
                        RewardTimer = initialTimer;
                        return;
                    }

                    //Lets now get the item
                    do
                    {
                        Field* fields = result->Fetch();
                        uint32 pItem = fields[0].GetInt32();
                        uint32 quantity = fields[1].GetInt32();

                        // now lets add the item
                        //player->AddItem(pItem, quantity);
                        SendRewardToPlayer(player, pItem, quantity);
                    } while (result->NextRow());

                    // Inform the player about the win
                    ChatHandler(player->GetSession()).PSendSysMessage("[Lucky Number] Congratulations you have won with a roll of %u.", roll);

                    RewardTimer = initialTimer;
                }
                else  RewardTimer -= p_time;
            }
        }
    }

    void SendRewardToPlayer(Player* receiver, uint32 itemId, uint32 count)
    {
        if (receiver->IsInWorld() && receiver->AddItem(itemId, count))
            return;

        ChatHandler(receiver->GetSession()).PSendSysMessage("You will receive your item in your mailbox");
        // format: name "subject text" "mail text" item1[:count1] item2[:count2] ... item12[:count12]
        uint64 receiverGuid = receiver->GetGUID().GetCounter();
        std::string receiverName;

        std::string subject = "Lucky Number prize";
        std::string text = "Congratulations, you won a prize!";

        ItemTemplate const* item_proto = sObjectMgr->GetItemTemplate(itemId);

        if (!item_proto)
        {
            TC_LOG_ERROR("server.worldserver", "[Lucky Number] The itemId is invalid: {}", itemId);
            return;
        }

        if (count < 1 || (item_proto->GetMaxCount() > 0 && count > uint32(item_proto->GetMaxCount())))
        {
            TC_LOG_ERROR("server.worldserver", "[Lucky Number] The item count is invalid: {} : {}", itemId, count);
            return;
        }

        typedef std::pair<uint32, uint32> ItemPair;
        typedef std::list< ItemPair > ItemPairs;
        ItemPairs items;

        while (count > item_proto->GetMaxStackSize())
        {
            items.push_back(ItemPair(itemId, item_proto->GetMaxStackSize()));
            count -= item_proto->GetMaxStackSize();
        }

        items.push_back(ItemPair(itemId, count));

        if (items.size() > MAX_MAIL_ITEMS)
        {
            TC_LOG_ERROR("server.worldserver", "[Lucky Number] Maximum email items is {}, current size: {}", MAX_MAIL_ITEMS, items.size());
            return;
        }

        // from console show not existed sender
        MailSender sender(MAIL_NORMAL, receiver->GetSession() ? receiver->GetGUID().GetCounter() : 0, MAIL_STATIONERY_TEST);

        // fill mail
        MailDraft draft(subject, text);

        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

        for (ItemPairs::const_iterator itr = items.begin(); itr != items.end(); ++itr)
        {
            if (Item* item = Item::CreateItem(itr->first, itr->second, ItemContext::NONE, receiver->GetSession() ? receiver : 0))
            {
                item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                draft.AddItem(item);
            }
        }

        draft.SendMailTo(trans, MailReceiver(receiver, receiverGuid), sender);
        CharacterDatabase.CommitTransaction(trans);

        return;
    }

};

class reward_system_conf : public WorldScript
{
public:
    reward_system_conf() : WorldScript("reward_system_conf") { }

    void OnConfigLoad(bool reload) override
    {
        if (!reload) {
            Max_roll = sConfigMgr->GetIntDefault("MaxRoll", 1000);
        }
    }
};

void AddRewardSystemScripts()
{
    new reward_system();
    new reward_system_conf();
}

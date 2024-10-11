/*******************************************
* File: FallEvent.cpp
* Author: TheFrozenThr0ne & CC
* Description: Manages the custom Fall Event
*              in the game including NPCs,
*              objects, and event scripts.
********************************************/

/* // Condig Statements for worldserver.conf
* 
FallEvent.Announce = true

*/

// Global class for managing the Fall Event
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include <MapManager.h>
#include "UnitAI.h"
#include "ObjectGuid.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "GameObjectInfo.h"
#include "Chat.h"
#include "Config.h"
#include <algorithm>
#include <numeric>
#include <atomic>
#include <random>
#include <unordered_set>
#include <ctime>

// Constants
constexpr int TotalObjects = 16;
constexpr uint32 StartEventSound = 16037;
constexpr uint32 PlayerMusicID = 17289;
constexpr uint32 ObjectSoundID = 17442;
constexpr uint32 EventStarterGossipMenuID = 68;
constexpr uint32 InitialEventDelay = 15000; // 15 seconds
constexpr uint32 FinalEventDelay = 160000; // 160 seconds

// Initialize the event flag to false
std::atomic<bool> endevent{ true };
std::atomic<bool> objectsRecreated{ false };
std::map<ObjectGuid, GameObjectInfo> DespawnedObjectMap;

// Class to announce the Fall Event to players when they log in
class FallEventAnnounce : public PlayerScript
{
public:
    FallEventAnnounce() : PlayerScript("FallEventAnnounce") {}

    // Method called when a player logs in
    void OnLogin(Player* player, bool /*firstLogin*/) override
    {
        if (sConfigMgr->GetBoolDefault("FallEvent.Announce", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running |cff4CFF00Fall Event - Speedbarge - (Thousand Needles)");
        }
    }
};

// Creature script for the NPC "Eventstarter" which starts the Fall Event
class Eventstarter : public CreatureScript
{
public:
    Eventstarter() : CreatureScript("Eventstarter") {}

    struct EventstarterAI : public ScriptedAI
    {
        EventstarterAI(Creature* creature) : ScriptedAI(creature) {}

        void UpdateAI(uint32 /*diff*/) override
        {
            if (endevent)
            {
                me->PlayDirectMusic(0);
            }

            if (objectsRecreated)
            {
                me->SetVisible(true);
            }
        }

        bool OnGossipHello(Player* player) override
        {
            TC_LOG_ERROR("scripts", "Player {} has requested the event start option.", player->GetName());
            AddGossipItemFor(player, GossipOptionNpc::None, "Start Fall Event!", GOSSIP_SENDER_MAIN, 1);
            SendGossipMenuFor(player, EventStarterGossipMenuID, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            if (!player)
                return false;

            //uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);

            if (gossipListId == 1 && endevent) // Player selected to start the event
            {
                TC_LOG_INFO("scripts", "Player {} has started the Fall Event.", player->GetName().c_str());
                endevent = false; // Start the event
                objectsRecreated = false; // Start the event
                StartEvent(player); // Start the event sequence
            }

            CloseGossipMenuFor(player);
            return true;
        }

        private:
            void StartEvent(Player * player)
            {
                me->PlayDirectSound(StartEventSound); // NPC plays a sound
                player->PlayDirectMusic(PlayerMusicID); // Player hears event music
                me->SetVisible(false); // Hide the NPC

                // Fall object GUIDs
                constexpr int FallObjectGuid[TotalObjects] = { 9805103, 9805104, 9805105, 9805106, 9805107, 9805108, 9805109,
                                                               9805110, 9805111, 9805112, 9805113, 9805114, 9805115, 9805116,
                                                               9805117, 9805118 };

                // Shuffle the object indices
                int RandomData[TotalObjects] = {};
                std::iota(RandomData, RandomData + TotalObjects, 0);
                std::shuffle(RandomData, RandomData + TotalObjects, std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

                // Initialize fall objects
                GameObject* FallObjects[TotalObjects] = {};
                for (int i = 0; i < TotalObjects; ++i)
                {
                    TC_LOG_INFO("scripts", "Initialized FallObject with GUID {} for event.", FallObjectGuid[RandomData[i]]);
                    FallObjects[i] = ChatHandler(player->GetSession()).GetObjectFromPlayerMapByDbGuid(FallObjectGuid[RandomData[i]]);
                    if (FallObjects[i])
                    {
                        FallObjects[i]->AI()->SetData(1, i + 1); // Set object data
                    }
                    else
                    {
                        TC_LOG_ERROR("scripts", "FallObject with GUID {} not found.", FallObjectGuid[RandomData[i]]);
                        ChatHandler(player->GetSession()).PSendSysMessage("Object {} not found", FallObjectGuid[RandomData[i]]);
                    }
                }
            }
        };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new EventstarterAI(creature);
    }
};

// Script for handling Fall Event objects
class FallObject : public GameObjectScript
{
public:
    FallObject() : GameObjectScript("FallObject") {}

    struct FallObjectAI : public GameObjectAI
    {
        FallObjectAI(GameObject* go) : GameObjectAI(go) {}

        void SetData(uint32 type, uint32 data) override
        {
            if (type == 1)
            {
                TC_LOG_INFO("scripts", "Scheduled event for FallObject {} with data {}.", me->GetGUID().GetCounter(), data);
                ScheduleEvents(data);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            Events.Update(diff);

            while (uint32 eventId = Events.ExecuteEvent())
            {
                ExecuteEvent(eventId);
            }
        }

    private:
        EventMap Events;

        enum Events
        {
            EVENT_ACTIVATE = 1,
            EVENT_END = 2
        };

        // Methoden zum Hinzufügen und Entfernen von GameObjects.
        void AddDespawnedObject(GameObject* go)
        {
            if (go)
            {
                ObjectGuid guid = go->GetGUID();  // Get the complete ObjectGuid
                DespawnedObjectMap[guid] = GameObjectInfo{
                    go->GetEntry(),        // Entry ID of the object
                    go->GetPositionX(),    // X coordinate
                    go->GetPositionY(),    // Y coordinate
                    go->GetPositionZ(),    // Z coordinate
                    go->GetOrientation()   // Orientation of the object
                };
                TC_LOG_ERROR("scripts", "Added FallObject with GUID {} to the despawned list. Entry: {}, Position: (X: {}, Y: {}, Z: {}, O: {})", guid,
                    go->GetEntry(), go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetOrientation());
            }
        }

        void RespawnAllObjects()
        {
            for (const auto& [guid, objInfo] : DespawnedObjectMap)
            {
                Position pos = Position(objInfo.positionX, objInfo.positionY, objInfo.positionZ);
                QuaternionData rot = QuaternionData::fromEulerAnglesZYX(objInfo.orientation, 0.f, 0.f);

                if (me->SummonGameObject(objInfo.entryId, pos, rot, 0s))
                {
                    TC_LOG_INFO("scripts", "GameObject with GUID {} was not found, so a new instance was created and respawned.", guid);
                }
                else
                {
                    TC_LOG_ERROR("scripts", "Failed to respawn GameObject with GUID {}.", guid);
                }
            }

            objectsRecreated = true;
            DespawnedObjectMap.clear();
        }

        void ScheduleEvents(uint32 data)
        {
            switch (data)
            {
            case 1:
                Events.ScheduleEvent(EVENT_ACTIVATE, Milliseconds(InitialEventDelay));  // Start des ersten Events.
                break;
            case TotalObjects:
                Events.ScheduleEvent(EVENT_END, Milliseconds(FinalEventDelay));  // Letztes Objekt-Event.
                break;
            default:
                uint32 timer = 25000 + (data - 2) * 10000;  // Angepasster Timer für andere Objekte.
                Events.ScheduleEvent(EVENT_ACTIVATE, Milliseconds(timer));
                break;
            }
        }

        void ExecuteEvent(uint32 eventId)
        {
            switch (eventId)
            {
            case EVENT_ACTIVATE:
                AddDespawnedObject(me);  // Objekt zur Despawn-Liste hinzufügen.
                me->PlayDirectSound(ObjectSoundID);  // Ton für das Objekt abspielen.
                me->DespawnOrUnsummon();
                TC_LOG_ERROR("scripts", "FallObject with GUID {} has been despawned.", me->GetGUID());
                break;
            case EVENT_END:
                RespawnAllObjects();  // Alle Objekte respawnen.
                endevent = true;
                TC_LOG_INFO("scripts", "Fall Event ended. Respawning all objects.");
                break;
            default:
                break;
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new FallObjectAI(go);
    }
};

// Register all the scripts for the Fall Event
void AddSC_FallEvent()
{
    new FallEventAnnounce();
    new Eventstarter();
    new FallObject();
}


/*******************************************
* File: FallEventScript.cpp
* Author: TheFrozenThr0ne & CC
* Description: Manages the custom Fall Event
*              in the game including NPCs,
*              objects, and event scripts.
********************************************/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "UnitAI.h"
#include "GameObjectAI.h"
#include "Map.h"
#include "Random.h"
#include "Chat.h"
#include "Config.h"
#include "PhasingHandler.h"
#include <algorithm>
#include <numeric>
#include <atomic>
#include <random>
#include <MapManager.h>
#include <unordered_set>
#include <ctime>

// SQL Statements for Database Configuration
/*
# Insert creature template for the "Eventstarter" NPC
INSERT INTO creature_template (entry, KillCredit1, KillCredit2, name, femaleName, subname, TitleAlt, IconName, RequiredExpansion, VignetteID, faction, npcflag, speed_walk, speed_run, scale, Classification, dmgschool, BaseAttackTime, RangeAttackTime, BaseVariance, RangeVariance, unit_class, unit_flags, unit_flags2, unit_flags3, family, trainer_class, type, VehicleId, AIName, MovementType, ExperienceModifier, RacialLeader, movementId, WidgetSetID, WidgetSetUnitConditionID, RegenHealth, CreatureImmunitiesId, flags_extra, ScriptName, StringId, VerifiedBuild)
VALUES (555555, 0, 0, 'Eventstarter', NULL, 'Fall Event', NULL, NULL, 0, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'Eventstarter', NULL, 0);

# Define a creature model to assing it to the NPC
insert  into creature_template_model(CreatureID,Idx,CreatureDisplayID,DisplayScale,Probability,VerifiedBuild) values
(500010,0,7337,1,1,0);

# Define a gossip template to assing it to the NPC
insert  into creature_template_gossip(CreatureID,MenuID,VerifiedBuild) values
(500010,600000,0);

# Define a gossip menu and assign it to the NPC
INSERT INTO gossip_menu (MenuID, TextID, VerifiedBuild)
VALUES (600000, 68, 0);

# Define gameobject templates for the event objects
INSERT INTO gameobject_template (entry, type, displayId, name, IconName, castBarCaption, unk1, size, Data0, Data1, Data2, Data3, Data4, Data5, Data6, Data7, Data8, Data9, Data10, Data11, Data12, Data13, Data14, Data15, Data16, Data17, Data18, Data19, Data20, Data21, Data22, Data23, Data24, Data25, Data26, Data27, Data28, Data29, Data30, Data31, Data32, Data33, Data34, ContentTuningId, AIName, ScriptName, StringId, VerifiedBuild)
VALUES (555555, 5, 8277, 'FallEvent_object01', '', '', '', 0.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'FallObject', NULL, 0);

# Define spawn points for the game objects
INSERT INTO gameobject (guid, id, map, zoneId, areaId, spawnDifficulties, phaseUseFlags, PhaseId, PhaseGroup, terrainSwapMap, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state, ScriptName, StringId, VerifiedBuild)
VALUES
(9805103, 555555, 1, 0, 0, '0', 0, 0, 0, -1, -6082.18, -3962.04, 9.8267, 0.446274, -0, -0, -0.22129, -0.975208, 300, 255, 1, '', NULL, 0);

# Define gameobject spawns for the objects
insert  into gameobject(guid,id,map,zoneId,areaId,spawnDifficulties,phaseUseFlags,PhaseId,PhaseGroup,terrainSwapMap,position_x,position_y,position_z,orientation,rotation0,rotation1,rotation2,rotation3,spawntimesecs,animprogress,state,ScriptName,StringId,VerifiedBuild) values
(9805103,555555,1,0,0,'0',0,0,0,-1,-6082.18,-3962.04,9.8000,0.446274,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805104,555555,1,0,0,'0',0,0,0,-1,-6077.57,-3971.61,9.8000,0.446795,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805105,555555,1,0,0,'0',0,0,0,-1,-6072.97,-3981.13,9.8000,0.432934,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805106,555555,1,0,0,'0',0,0,0,-1,-6068.48,-3990.79,9.8000,0.446801,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805107,555555,1,0,0,'0',0,0,0,-1,-6071.25,-3957,9.8000,0.427199,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805108,555555,1,0,0,'0',0,0,0,-1,-6066.67,-3966.22,9.8000,0.423437,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805109,555555,1,0,0,'0',0,0,0,-1,-6062.08,-3976.09,9.8000,0.435565,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805110,555555,1,0,0,'0',0,0,0,-1,-6057.46,-3985.86,9.8000,0.423774,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805111,555555,1,0,0,'0',0,0,0,-1,-6060.29,-3951.8,9.8000,3.53371,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805112,555555,1,0,0,'0',0,0,0,-1,-6055.66,-3961.45,9.8000,0.396871,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805113,555555,1,0,0,'0',0,0,0,-1,-6050.95,-3971.2,9.8000,3.5365,-0,-0,-0.2215449,-0.97515,300,255,1,'',NULL,0),
(9805114,555555,1,0,0,'0',0,0,0,-1,-6046.38,-3980.84,9.8000,0.423919,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805115,555555,1,0,0,'0',0,0,0,-1,-6093.07,-3967.4,9.8000,3.58541,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805116,555555,1,0,0,'0',0,0,0,-1,-6088.43,-3976.92,9.8000,3.58227,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805117,555555,1,0,0,'0',0,0,0,-1,-6083.95,-3986.58,9.8000,0.4385,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805118,555555,1,0,0,'0',0,0,0,-1,-6079.4,-3996.06,9.8000,3.59191,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0);
*/

/* // Condig Statements for worldserver.conf Configuration
FallEvent.Announce = true
*/

// Global class for managing the Fall Event
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "UnitAI.h"
#include "ObjectGuid.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "GameObjectInfo.h"

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
            AddGossipItemFor(player, GossipOptionNpc::None, "Start Fall Event!", GOSSIP_SENDER_MAIN, 1);
            SendGossipMenuFor(player, EventStarterGossipMenuID, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            if (!player)
                return false;

            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);

            if (action == 1 && endevent) // Player selected to start the event
            {
                TC_LOG_INFO("scripts", "Player %s has started the Fall Event.", player->GetName().c_str());
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

                if (GameObject* newGO = me->SummonGameObject(objInfo.entryId, pos, rot, 0s))
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


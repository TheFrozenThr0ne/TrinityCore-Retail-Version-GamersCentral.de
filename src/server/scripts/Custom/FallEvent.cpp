/*

# creature_template

insert  into `creature_template`(`entry`,`KillCredit1`,`KillCredit2`,`name`,`femaleName`,`subname`,`TitleAlt`,`IconName`,`RequiredExpansion`,`VignetteID`,`faction`,`npcflag`,`speed_walk`,`speed_run`,`scale`,`Classification`,`dmgschool`,`BaseAttackTime`,`RangeAttackTime`,`BaseVariance`,`RangeVariance`,`unit_class`,`unit_flags`,`unit_flags2`,`unit_flags3`,`family`,`trainer_class`,`type`,`VehicleId`,`AIName`,`MovementType`,`ExperienceModifier`,`RacialLeader`,`movementId`,`WidgetSetID`,`WidgetSetUnitConditionID`,`RegenHealth`,`CreatureImmunitiesId`,`flags_extra`,`ScriptName`,`StringId`,`VerifiedBuild`) values
(555555,0,0,'Eventstarter',NULL,'Fall Event',NULL,NULL,0,0,35,1,1,1.14286,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,'SmartAI',0,1,0,0,0,0,1,0,0,'Eventstarter',NULL,0);


# creature_template_model

insert  into `creature_template_model`(`CreatureID`,`Idx`,`CreatureDisplayID`,`DisplayScale`,`Probability`,`VerifiedBuild`) values
(500010,0,7337,1,1,0);


# creature_template_gossip

insert  into `creature_template_gossip`(`CreatureID`,`MenuID`,`VerifiedBuild`) values
(500010,600000,0);


# gossip_menu

insert  into `gossip_menu`(`MenuID`,`TextID`,`VerifiedBuild`) values
(600000,68,0);


# gameobject_template

insert  into `gameobject_template`(`entry`,`type`,`displayId`,`name`,`IconName`,`castBarCaption`,`unk1`,`size`,`Data0`,`Data1`,`Data2`,`Data3`,`Data4`,`Data5`,`Data6`,`Data7`,`Data8`,`Data9`,`Data10`,`Data11`,`Data12`,`Data13`,`Data14`,`Data15`,`Data16`,`Data17`,`Data18`,`Data19`,`Data20`,`Data21`,`Data22`,`Data23`,`Data24`,`Data25`,`Data26`,`Data27`,`Data28`,`Data29`,`Data30`,`Data31`,`Data32`,`Data33`,`Data34`,`ContentTuningId`,`AIName`,`ScriptName`,`StringId`,`VerifiedBuild`) values
(555555,5,8277,'FallEvent_object01','','','',0.4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','FallObject',NULL,0);


# gameobject

insert  into `gameobject`(`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnDifficulties`,`phaseUseFlags`,`PhaseId`,`PhaseGroup`,`terrainSwapMap`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`,`ScriptName`,`StringId`,`VerifiedBuild`) values
(9805103,555555,1,0,0,'0',0,0,0,-1,-6082.18,-3962.04,9.8267,0.446274,-0,-0,-0.22129,-0.975208,300,255,1,'',NULL,0),
(9805104,555555,1,0,0,'0',0,0,0,-1,-6077.57,-3971.61,9.64355,0.446795,-0,-0,-0.221544,-0.97515,300,255,1,'',NULL,0),
(9805105,555555,1,0,0,'0',0,0,0,-1,-6072.97,-3981.13,9.46484,0.432934,-0,-0,-0.214781,-0.976662,300,255,1,'',NULL,0),
(9805106,555555,1,0,0,'0',0,0,0,-1,-6068.48,-3990.79,9.41696,0.446801,-0,-0,-0.221547,-0.97515,300,255,1,'',NULL,0),
(9805107,555555,1,0,0,'0',0,0,0,-1,-6071.25,-3957,9.76294,0.427199,-0,-0,-0.211979,-0.977274,300,255,1,'',NULL,0),
(9805108,555555,1,0,0,'0',0,0,0,-1,-6066.67,-3966.22,9.9439,0.423437,-0,-0,-0.21014,-0.977671,300,255,1,'',NULL,0),
(9805109,555555,1,0,0,'0',0,0,0,-1,-6062.08,-3976.09,9.68955,0.435565,-0,-0,-0.216065,-0.976379,300,255,1,'',NULL,0),
(9805110,555555,1,0,0,'0',0,0,0,-1,-6057.46,-3985.86,9.72708,0.423774,-0,-0,-0.210305,-0.977636,300,255,1,'',NULL,0),
(9805111,555555,1,0,0,'0',0,0,0,-1,-6060.29,-3951.8,10.0642,3.53371,-0,-0,-0.980842,0.194806,300,255,1,'',NULL,0),
(9805112,555555,1,0,0,'0',0,0,0,-1,-6055.66,-3961.45,10.3675,0.396871,-0,-0,-0.197136,-0.980376,300,255,1,'',NULL,0),
(9805113,555555,1,0,0,'0',0,0,0,-1,-6050.95,-3971.2,9.9129,3.5365,-0,-0,-0.980569,0.196175,300,255,1,'',NULL,0),
(9805114,555555,1,0,0,'0',0,0,0,-1,-6046.38,-3980.84,10.0047,0.423919,-0,-0,-0.210376,-0.977621,300,255,1,'',NULL,0),
(9805115,555555,1,0,0,'0',0,0,0,-1,-6093.07,-3967.4,10.0335,3.58541,-0,-0,-0.97548,0.22009,300,255,1,'',NULL,0),
(9805116,555555,1,0,0,'0',0,0,0,-1,-6088.43,-3976.92,9.83739,3.58227,-0,-0,-0.975824,0.218558,300,255,1,'',NULL,0),
(9805117,555555,1,0,0,'0',0,0,0,-1,-6083.95,-3986.58,9.61485,0.4385,-0,-0,-0.217498,-0.976061,300,255,1,'',NULL,0),
(9805118,555555,1,0,0,'0',0,0,0,-1,-6079.4,-3996.06,9.55618,3.59191,-0,-0,-0.974759,0.22326,300,255,1,'',NULL,0);

*/

#include "ScriptedCreature.h"
#include "GameObjectAI.h"
#include "ObjectAccessor.h"
#include "PhasingHandler.h"
#include "Player.h"
#include "EventMap.h"
#include "Chat.h"

bool endevent = false;
GuidList Eggs;

class Eventstarter : public CreatureScript
{
public:
    Eventstarter() : CreatureScript("Eventstarter") { }

    struct EventstarterAI : public ScriptedAI
    {
        EventstarterAI(Creature* creature) : ScriptedAI(creature) {}

        void UpdateAI(uint32 /*diff*/) override
        {
            if (endevent)
            {
                TC_LOG_ERROR("scripts", "Event has ended.");
                endevent = false;
            }
        }

        bool OnGossipHello(Player* player) override
        {
            TC_LOG_ERROR("scripts", "Player {} greeted Eventstarter.", player->GetName());

            AddGossipItemFor(player, GossipOptionNpc::None, "Start Event !!!", GOSSIP_SENDER_MAIN, 1);
            SendGossipMenuFor(player, 1, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            uint32 const uiAction = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);

            if (uiAction == 1)
            {
                TC_LOG_ERROR("scripts", "Player {} selected to start the event.", player->GetName());
                StartEvent(player);  // Start the event when selected by the player
            }
            else
            {
                TC_LOG_ERROR("scripts", "Unknown action {} selected by player {}.", uiAction, player->GetName());
            }

            CloseGossipMenuFor(player);
            return true;
        }

        void StartEvent(Player* player)
        {
            TC_LOG_ERROR("scripts", "Starting event for player {}.", player->GetName());
            endevent = false;

            int FallObjectGuids[16] = { 9805103, 9805104, 9805105, 9805106, 9805107, 9805108, 9805109, 9805110, 9805111, 9805112, 9805113, 9805114, 9805115, 9805116, 9805117, 9805118 };
            int RandomData[16] = {};
            GameObject* FallObjects[16] = {};

            // Generate a random order for objects
            for (int i = 0; i < 16; i++)
            {
                RandomData[i] = irand(0, 15);
                for (int j = 0; j < i; j++)
                {
                    if (RandomData[i] == RandomData[j])
                    {
                        i--;  // Regenerate if duplicate found
                        break;
                    }
                }
            }

            // Set the phases for the randomly selected objects
            for (int i = 0; i < 16; i++)
            {
                FallObjects[i] = ChatHandler(player->GetSession()).GetObjectFromPlayerMapByDbGuid(FallObjectGuids[RandomData[i]]);
                if (FallObjects[i])
                {
                    TC_LOG_INFO("scripts", "Setting data for FallObject with GUID {}.", FallObjectGuids[RandomData[i]]);
                    FallObjects[i]->AI()->SetData(1, i + 1);  // Setting data to trigger the object event
                }
                else
                {
                    TC_LOG_ERROR("scripts", "FallObject with GUID {} not found.", FallObjectGuids[RandomData[i]]);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new EventstarterAI(creature);
    }
};

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
                if (data >= 1 && data <= 15)
                {
                    uint32 timer = 1500 + (data - 1) * 1000;
                    Events.ScheduleEvent(1, Milliseconds(timer));
                    TC_LOG_ERROR("scripts", "Scheduled despawn event for FallObject with GUID {} in {} ms.", me->GetGUID(), timer);
                }
                else if (data == 16)
                {
                    Events.ScheduleEvent(2, Milliseconds(16000));  // Respawn in 150000 ms (150 seconds)
                    TC_LOG_ERROR("scripts", "Scheduled respawn event for FallObject with GUID {} in 150000 ms.", me->GetGUID());
                }
                else
                {
                    TC_LOG_ERROR("scripts", "Invalid data value {} for FallObject with GUID {}.", data, me->GetGUID());
                }
            }
            else
            {
                TC_LOG_ERROR("scripts", "Invalid type value {} for FallObject with GUID {}.", type, me->GetGUID());
            }
        }

        void UpdateAI(uint32 diff) override
        {
            Events.Update(diff);

            while (uint32 eventId = Events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 1:
                    HandleDespawn();  // Handle the despawn event
                    break;
                case 2:
                    HandleRespawn();  // Handle the respawn event
                    RespawnAllFallObjects();  // Respawn all objects when the event ends
                    break;
                default:
                    TC_LOG_ERROR("scripts", "Unhandled event ID {} for FallObject with GUID {}.", eventId, me->GetGUID());
                    break;
                }
            }
        }

        void RespawnAllFallObjects()
        {
            for (const ObjectGuid& guid : Eggs)
            {
                GameObject* egg = ObjectAccessor::GetGameObject(*me, guid);
                if (egg)
                {
                    if (!egg->IsInWorld())
                    {
                        TC_LOG_ERROR("scripts", "FallObject with GUID {} is not in the world, cannot respawn.", guid);
                        continue;
                    }

                    Map* map = egg->GetMap();
                    if (!map)
                    {
                        TC_LOG_ERROR("scripts", "Map for FallObject with GUID {} not found.", guid);
                        continue;
                    }
                    egg->SetRespawnTime(1);
                    egg->Respawn();
                    map->AddToMap(egg);
                    UpdateGameObjectVisibility(egg);
                    
                    TC_LOG_ERROR("scripts", "Respawned FallObject with GUID {}.", guid);
                }
                else
                {
                    TC_LOG_ERROR("scripts", "Failed to find FallObject with GUID {} for respawn.", guid);
                }
            }

            Eggs.clear();  // Clear the list of eggs after respawning
            TC_LOG_ERROR("scripts", "Cleared the Eggs list after respawning all objects.");
        }

    private:
        void HandleDespawn()
        {
            //uint32 newPhaseId = 2; // Beispiel-Phase

            // Ändere die Phase des GameObjects
            //PhasingHandler::ResetPhaseShift(me);
            //PhasingHandler::AddPhase(me, newPhaseId, true);

            // Setze Phase für den NPC
            //PhasingHandler::AddPhase(me, newPhaseId, true);
            Eggs.push_back(me->GetGUID());  // Store the GUID for later respawn
            //me->DestroyForNearbyPlayers();
            SetObjectInvisible(me);
            TC_LOG_ERROR("scripts", "FallObject with GUID {} has been despawned and made invisible.", me->GetGUID());
        }

        void HandleRespawn()
        {
            //PhasingHandler::AddPhase(me, 0, true);
            SetObjectVisible(me);
            TC_LOG_ERROR("scripts", "FallObject with GUID {} has been respawned and made visible.", me->GetGUID());
        }

        void SetObjectInvisible(GameObject* go)
        {
            go->SetLootState(GO_JUST_DEACTIVATED);
            TC_LOG_ERROR("scripts", "FallObject with GUID {} set to invisible.", go->GetGUID());
        }

        void SetObjectVisible(GameObject* go)
        {
            go->SetLootState(GO_READY);
            TC_LOG_ERROR("scripts", "FallObject with GUID {} set to visible.", go->GetGUID());
        }

        void UpdateGameObjectVisibility(GameObject* go)
        {
            if (!go || !go->IsInWorld())
                return;

            Map* map = go->GetMap();
            if (!map)
                return;

            // Aktualisiere die Sichtbarkeit für alle Spieler in der Nähe
            go->DestroyForNearbyPlayers();
            map->AddToMap(go);
        }

        EventMap Events;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new FallObjectAI(go);
    }
};

void AddSC_FallEvent()
{
    TC_LOG_INFO("scripts", "Loading FallEvent script.");
    new Eventstarter();
    new FallObject();
}

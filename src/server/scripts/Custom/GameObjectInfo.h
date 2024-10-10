// GameObjectInfo.h
#ifndef GAMEOBJECTINFO_H
#define GAMEOBJECTINFO_H

#include "ObjectGuid.h"  // Include necessary headers

struct GameObjectInfo
{
    uint32 entryId;          // Entry ID of the GameObject
    float positionX;         // X coordinate of the GameObject
    float positionY;         // Y coordinate of the GameObject
    float positionZ;         // Z coordinate of the GameObject
    float orientation;       // Orientation of the GameObject
};

#endif
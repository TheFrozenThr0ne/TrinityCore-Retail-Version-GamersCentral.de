SET

@TEXT_ID        := 300000; -- Must be same as in the Trinity_Portal_Master.sql

-- Gossip header texts
INSERT INTO `broadcast_text`(`Text`,`Text1`,`ID`,`LanguageID`,`ConditionID`,`EmotesID`,`Flags`,`ChatBubbleDurationMs`,`VoiceOverPriorityID`,`SoundKitID1`,`SoundKitID2`,`EmoteID1`,`EmoteID2`,`EmoteID3`,`EmoteDelay1`,`EmoteDelay2`,`EmoteDelay3`,`VerifiedBuild`) VALUES
('$B For the Horde!$B',NULL,@TEXT_ID,0,0,0,65,0,0,0,0,6,0,0,0,0,0,0),
('$B For The Alliance!$B',NULL,@TEXT_ID+1,0,0,0,65,0,0,0,0,6,0,0,0,0,0,0),
('$BUp for some dungeon exploring?$B',NULL,@TEXT_ID+2,0,0,0,65,0,0,0,0,6,0,0,0,0,0,0),
('$BBe careful with choosing raids, I won\'t be there if you wipe.$B',NULL,@TEXT_ID+3,0,0,0,65,0,0,0,0,6,0,0,0,0,0,0),
('$BWhere would you like to be ported?$B',NULL,@TEXT_ID+4,0,0,0,65,0,0,0,0,6,0,0,0,0,0,0);
SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;


CREATE TABLE `applications` (
  `jobId` int(11) NOT NULL,
  `userId` int(11) NOT NULL,
  UNIQUE KEY `UNIQUE` (`jobId`,`userId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `bankaccounts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `bankId` int(11) NOT NULL,
  `pin` int(11) NOT NULL,
  `pinAttempts` int(11) NOT NULL,
  `money` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `bankbranches` (
  `propertyId` int(11) NOT NULL,
  `bankId` int(11) NOT NULL,
  PRIMARY KEY (`propertyId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `banks` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `Name` (`name`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `bans` (
  `userId` int(11) NOT NULL,
  `ip` varchar(16) NOT NULL,
  `executorUserId` int(11) NOT NULL,
  `time` datetime NOT NULL,
  `reason` varchar(200) NOT NULL,
  UNIQUE KEY `Client` (`userId`,`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `chatlog` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userId` int(11) NOT NULL,
  `targetUserId` int(11) NOT NULL,
  `channel` varchar(16) NOT NULL,
  `time` datetime NOT NULL,
  `text` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `cmdaliases` (
  `userId` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `command` varchar(200) NOT NULL,
  UNIQUE KEY `Index` (`userId`,`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `friends` (
  `userId1` int(11) NOT NULL,
  `userId2` int(11) NOT NULL,
  `accepted` tinyint(1) NOT NULL,
  KEY `Index` (`userId1`,`userId2`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `hotelrooms` (
  `propertyId` int(11) NOT NULL,
  `roomId` int(11) NOT NULL,
  `price` float NOT NULL,
  `ownerUserId` int(11) NOT NULL,
  UNIQUE KEY `Room` (`propertyId`,`roomId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `infopickups` (
  `pickupId` int(11) NOT NULL,
  `stringId` int(11) NOT NULL,
  PRIMARY KEY (`pickupId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `jobs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `ownerUserId` int(11) NOT NULL,
  `employeeSalary` float NOT NULL,
  `employerSalary` float NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `Name` (`name`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `licenses` (
  `giverUserId` int(11) NOT NULL,
  `userId` int(11) NOT NULL,
  `type` varchar(50) NOT NULL,
  `date` datetime NOT NULL,
  UNIQUE KEY `UniqueLicense` (`userId`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `missioncheckpointgroups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `missioncheckpoints` (
  `missionId` int(11) NOT NULL,
  `checkpointId` int(11) NOT NULL,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL,
  UNIQUE KEY `Checkpoint` (`missionId`,`checkpointId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `missiondata` (
  `missionId` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  `value` varchar(200) NOT NULL,
  UNIQUE KEY `UNIQUE` (`missionId`,`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `missions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `jobId` int(11) NOT NULL,
  `creatorUserId` int(11) NOT NULL,
  `acceptUserId` int(11) NOT NULL,
  `creationTime` datetime NOT NULL,
  `acceptTime` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `moneytransactions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `userId` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `type` varchar(32) NOT NULL,
  `from` int(11) NOT NULL,
  `to` int(11) NOT NULL,
  `amount` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `navigationlocations` (
  `type` int(11) NOT NULL,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `navigationlocationtypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `Name` (`name`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `news` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` datetime NOT NULL,
  `authorId` int(11) NOT NULL,
  `title_en` varchar(200) NOT NULL,
  `text_en` text NOT NULL,
  `title_de` varchar(200) NOT NULL,
  `text_de` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `originalvehicles` (
  `id` int(11) NOT NULL,
  `modelId` int(11) NOT NULL,
  `color1` int(11) NOT NULL,
  `color2` int(11) NOT NULL,
  `angle` float NOT NULL,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL,
  `locked` int(11) NOT NULL,
  `frontLightId` int(11) NOT NULL,
  `hasNavi` int(11) NOT NULL,
  `jobId` int(11) NOT NULL,
  `mileAge` int(11) NOT NULL,
  `neonLightId` int(11) NOT NULL,
  `paintjobId` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `health` int(11) NOT NULL,
  `interior` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `permissions` (
  `userId` int(11) NOT NULL,
  `admin` tinyint(1) NOT NULL,
  `mapper` tinyint(1) NOT NULL,
  `moderator` tinyint(1) NOT NULL,
  `navi` tinyint(1) NOT NULL,
  `npcAdmin` tinyint(1) NOT NULL,
  `serverAdmin` tinyint(1) NOT NULL,
  `spawnVehicle` tinyint(1) NOT NULL,
  `teleport` tinyint(1) NOT NULL,
  PRIMARY KEY (`userId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `pickups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL,
  `type` varchar(20) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `Position` (`posX`,`posY`,`posZ`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `properties` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pickupId` int(11) NOT NULL,
  `interiorId` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  `price` float NOT NULL,
  `cameraPosX` float NOT NULL,
  `cameraPosY` float NOT NULL,
  `cameraPosZ` float NOT NULL,
  `ownerUserId` int(11) NOT NULL,
  `locked` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `PickupID` (`pickupId`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `teleports` (
  `name` varchar(100) NOT NULL,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL,
  `angle` float NOT NULL,
  `interior` int(11) NOT NULL,
  PRIMARY KEY (`name`),
  UNIQUE KEY `Name` (`name`),
  UNIQUE KEY `Position` (`posX`,`posY`,`posZ`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `tplinks` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pickupId` int(11) DEFAULT NULL,
  `posX` float DEFAULT NULL,
  `posY` float DEFAULT NULL,
  `posZ` float DEFAULT NULL,
  `angle` float DEFAULT NULL,
  `interior` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(32) NOT NULL,
  `password` varchar(32) NOT NULL,
  `sessionId` varchar(32) NOT NULL,
  `language` varchar(2) NOT NULL,
  `gender` varchar(1) NOT NULL,
  `birthDate` date NOT NULL,
  `location` varchar(100) NOT NULL,
  `mobilePhoneNumber` int(11) NOT NULL,
  `money` float(16,2) NOT NULL,
  `bankMoney` float(16,2) NOT NULL,
  `health` float NOT NULL,
  `skin` int(11) NOT NULL,
  `godMode` tinyint(1) NOT NULL,
  `chatMode` varchar(16) NOT NULL,
  `chatModeUserId` int(11) NOT NULL,
  `currentPropertyId` int(11) NOT NULL,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL,
  `angle` float NOT NULL,
  `interior` int(11) NOT NULL,
  `bankId` int(11) NOT NULL,
  `bankAccountId` int(11) NOT NULL,
  `jobId` int(11) NOT NULL,
  `registerTime` datetime NOT NULL,
  `loginTime` datetime NOT NULL,
  `onlineTime` int(11) NOT NULL,
  `clientVersion` varchar(50) NOT NULL,
  `lastPayDay` int(11) NOT NULL,
  `lastNewsId` int(11) NOT NULL,
  `showClock` tinyint(1) NOT NULL,
  `inTutorial` tinyint(1) NOT NULL,
  `deaths` int(11) NOT NULL,
  `wantedLevel` int(11) NOT NULL,
  `vehicleBought` tinyint(1) NOT NULL,
  `spawnVehicle` int(11) NOT NULL,
  `bladder` float NOT NULL,
  `energy` float NOT NULL,
  `hunger` float NOT NULL,
  `thirst` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

CREATE TABLE `vehiclecomponents` (
  `vehicleId` int(11) NOT NULL,
  `slot` int(11) NOT NULL,
  `component` int(11) NOT NULL,
  UNIQUE KEY `UNIQUE` (`vehicleId`,`slot`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `vehiclemodels` (
  `id` int(11) NOT NULL,
  `name` varchar(20) NOT NULL,
  `type` varchar(16) NOT NULL,
  `colors` varchar(100) NOT NULL,
  `fuelUsage` float NOT NULL,
  `maxFuel` float NOT NULL,
  `tax` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE `vehicles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `numberplate` varchar(8) NOT NULL,
  `posX` float NOT NULL,
  `posY` float NOT NULL,
  `posZ` float NOT NULL,
  `angle` float NOT NULL,
  `interior` int(11) NOT NULL,
  `mileAge` float NOT NULL,
  `health` float NOT NULL,
  `modelId` int(11) NOT NULL,
  `color1` int(11) NOT NULL,
  `color2` int(11) NOT NULL,
  `paintjobId` int(11) NOT NULL,
  `price` float NOT NULL,
  `currentFuel` float NOT NULL,
  `lastRadioStation` int(11) NOT NULL,
  `jobId` int(11) NOT NULL,
  `frontLightId` int(11) NOT NULL,
  `neonLightId` int(11) NOT NULL,
  `hasNavi` tinyint(1) NOT NULL,
  `locked` tinyint(1) NOT NULL,
  `allowDriveUserId` int(11) NOT NULL,
  `ownerSellerId` int(11) NOT NULL,
  `ownerUserId` int(11) NOT NULL,
  `radioStationId` int(11) NOT NULL,
  `sellerUserId` int(11) NOT NULL,
  `tax` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `NumberPlate` (`numberplate`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

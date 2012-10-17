-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 17, 2012 at 04:27 PM
-- Server version: 5.5.24
-- PHP Version: 5.3.10-1ubuntu3.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `d1_eveore`
--

-- --------------------------------------------------------

--
-- Table structure for table `resources`
--

CREATE TABLE IF NOT EXISTS `resources` (
  `id` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  `type` varchar(15) DEFAULT NULL,
  `group` int(11) DEFAULT NULL,
  `order` int(11) DEFAULT NULL,
  `volume` decimal(4,2) DEFAULT NULL,
  `batch` int(11) DEFAULT NULL,
  `yields` varchar(255) DEFAULT NULL,
  `jitaBuy` decimal(10,2) DEFAULT NULL,
  `jitaSell` decimal(10,2) DEFAULT NULL,
  `dodixieBuy` decimal(10,2) DEFAULT NULL,
  `dodixieSell` decimal(10,2) DEFAULT NULL,
  `amarrBuy` decimal(10,2) DEFAULT NULL,
  `amarrSell` decimal(10,2) DEFAULT NULL,
  `rensBuy` decimal(10,2) DEFAULT NULL,
  `rensSell` decimal(10,2) DEFAULT NULL,
  `hekBuy` decimal(10,2) DEFAULT NULL,
  `hekSell` decimal(10,2) DEFAULT NULL,
  `corpBuy` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ORDERING` (`type`,`group`,`order`),
  UNIQUE KEY `name` (`name`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `resources`
--

INSERT INTO `resources` (`id`, `name`, `type`, `group`, `order`, `volume`, `batch`, `yields`, `jitaBuy`, `jitaSell`, `dodixieBuy`, `dodixieSell`, `amarrBuy`, `amarrSell`, `rensBuy`, `rensSell`, `hekBuy`, `hekSell`, `corpBuy`) VALUES
(1230, 'Veldspar', 'Ore', 0, 1, 0.10, 333, 'tritanium~1000', 16.96, 18.89, 16.38, 18.50, 16.32, 18.48, 16.78, 17.55, 14.77, 17.37, 0.00),
(17470, 'Concentrated Veldspar', 'Ore', 0, 2, 0.10, 333, 'tritanium~1050', 17.04, 18.89, 16.72, 18.50, 16.72, 18.13, 16.63, 17.50, 16.00, 0.00, 0.00),
(17471, 'Dense Veldspar', 'Ore', 0, 3, 0.10, 333, 'tritanium~1100', 18.75, 19.60, 17.41, 19.78, 17.64, 18.99, 17.79, 18.80, 16.63, 0.00, 0.00),
(1228, 'Scordite', 'Ore', 1, 1, 0.15, 333, 'tritanium~pyerite~833~416', 28.86, 29.96, 26.56, 30.00, 28.06, 34.82, 27.61, 31.00, 24.80, 29.46, 0.00),
(17463, 'Condensed Scordite', 'Ore', 1, 2, 0.15, 333, 'tritanium~pyerite~875~437', 28.26, 29.80, 28.12, 30.32, 29.50, 33.60, 26.52, 28.10, 25.00, 33.87, 0.00),
(17464, 'Massive Scordite', 'Ore', 1, 3, 0.15, 333, 'tritanium~pyerite~916~458', 30.93, 32.00, 29.22, 32.40, 30.20, 0.00, 29.58, 30.25, 28.08, 31.98, 0.00),
(1224, 'Pyroxeres', 'Ore', 2, 1, 0.30, 333, 'tritanium~pyerite~mexallon~nocxium~844~59~120~11', 53.30, 58.93, 51.31, 64.00, 54.21, 57.20, 50.98, 69.99, 48.00, 0.00, 0.00),
(17459, 'Solid Pyroxeres', 'Ore', 2, 2, 0.30, 333, 'tritanium~pyerite~mexallon~nocxium~886~62~126~12', 57.36, 59.28, 44.24, 74.59, 55.37, 64.97, 52.09, 0.00, 51.00, 0.00, 0.00),
(17460, 'Viscous Pyroxeres', 'Ore', 2, 3, 0.30, 333, 'tritanium~pyerite~mexallon~nocxium~928~65~132~12', 58.74, 61.94, 43.94, 300.00, 59.39, 63.16, 57.83, 0.00, 53.00, 0.00, 0.00),
(18, 'Plagioclase', 'Ore', 3, 1, 0.35, 333, 'tritanium~pyerite~mexallon~256~512~256', 59.70, 65.24, 61.75, 65.80, 47.00, 88.55, 51.00, 61.85, 55.01, 65.00, 0.00),
(17455, 'Azure Plagioclase', 'Ore', 3, 2, 0.35, 333, 'tritanium~pyerite~mexallon~269~538~269', 62.00, 71.25, 63.78, 69.48, 50.70, 98.00, 55.00, 64.99, 56.02, 56.03, 0.00),
(17456, 'Rich Plagioclase', 'Ore', 3, 3, 0.35, 333, 'tritanium~pyerite~mexallon~282~563~282', 65.03, 73.96, 66.93, 73.00, 47.00, 90.00, 66.27, 0.00, 63.13, 0.00, 0.00),
(1227, 'Omber', 'Ore', 4, 1, 0.60, 500, 'tritanium~pyerite~isogen~307~123~307', 75.71, 92.36, 75.52, 76.00, 79.01, 105.82, 66.03, 93.86, 55.00, 80.00, 0.00),
(17867, 'Silvery Omber', 'Ore', 4, 2, 0.60, 500, 'tritanium~pyerite~isogen~322~129~322', 70.42, 84.49, 75.26, 79.99, 35.25, 124.30, 65.19, 93.99, 58.11, 83.99, 0.00),
(17868, 'Golden Omber', 'Ore', 4, 3, 0.60, 500, 'tritanium~pyerite~isogen~338~135~338', 66.91, 145.00, 64.17, 84.99, 57.58, 87.99, 70.27, 100.00, 61.90, 95.00, 0.00),
(20, 'Kernite', 'Ore', 5, 1, 1.20, 400, 'tritanium~mexallon~isogen~386~773~386', 231.13, 249.97, 180.27, 247.12, 214.17, 241.70, 198.06, 250.00, 219.20, 297.40, 0.00),
(17452, 'Luminous Kernite', 'Ore', 5, 2, 1.20, 400, 'tritanium~mexallon~isogen~405~812~405', 211.16, 238.00, 184.65, 0.00, 195.07, 254.97, 170.15, 300.00, 0.00, 0.00, 0.00),
(17453, 'Fiery Kernite', 'Ore', 5, 3, 1.20, 400, 'tritanium~mexallon~isogen~425~850~425', 207.61, 223.72, 171.05, 350.00, 207.40, 256.92, 172.03, 299.99, 200.00, 250.00, 0.00),
(1226, 'Jaspet', 'Ore', 6, 1, 2.00, 500, 'tritanium~pyerite~mexallon~nocxium~zydrine~259~437~518~259~8', 330.93, 425.83, 297.00, 475.00, 340.01, 534.96, 320.10, 600.00, 250.00, 0.00, 0.00),
(17448, 'Pure Jaspet', 'Ore', 6, 2, 2.00, 500, 'tritanium~pyerite~mexallon~nocxium~zydrine~272~459~544~272~8', 323.06, 489.98, 293.00, 0.00, 350.06, 892.81, 0.00, 573.33, 260.00, 0.00, 0.00),
(17449, 'Pristine Jaspet', 'Ore', 6, 3, 2.00, 500, 'tritanium~pyerite~mexallon~nocxium~zydrine~285~481~570~285~9', 310.01, 489.64, 320.00, 0.00, 385.10, 560.00, 0.00, 590.00, 350.00, 0.00, 0.00),
(1231, 'Hemorphite', 'Ore', 7, 1, 3.00, 500, 'tritanium~pyerite~mexallon~isogen~nocxium~zydrine~650~260~60~212~424~28', 501.00, 792.89, 300.07, 2000.00, 500.00, 699.99, 500.00, 999.89, 450.04, 2500.00, 0.00),
(17444, 'Vivid Hemorphite', 'Ore', 7, 2, 3.00, 500, 'tritanium~pyerite~mexallon~isogen~nocxium~zydrine~683~273~63~223~445~29', 555.76, 800.00, 0.00, 0.00, 520.00, 0.00, 500.00, 690.00, 500.00, 0.00, 0.00),
(17445, 'Radiant Hemorphite', 'Ore', 7, 3, 3.00, 500, 'tritanium~pyerite~mexallon~isogen~nocxium~zydrine~717~286~66~233~466~31', 495.81, 700.50, 0.00, 0.00, 555.08, 0.00, 0.00, 941.20, 0.00, 0.00, 0.00),
(21, 'Hedbergite', 'Ore', 8, 1, 3.00, 500, 'pyerite~isogen~nocxium~zydrine~290~708~354~32', 408.71, 698.00, 201.00, 0.00, 301.05, 698.00, 500.00, 0.00, 500.00, 0.00, 0.00),
(17440, 'Vitric Hedbergite', 'Ore', 8, 2, 3.00, 500, 'pyerite~isogen~nocxium~zydrine~305~743~372~34', 510.01, 700.00, 0.00, 0.00, 105.02, 1000.00, 0.00, 0.00, 300.00, 0.00, 0.00),
(17441, 'Glazed Hedbergite', 'Ore', 8, 3, 3.00, 500, 'pyerite~isogen~nocxium~zydrine~319~779~389~35', 355.21, 803.00, 0.00, 0.00, 251.07, 0.00, 0.00, 0.00, 420.00, 0.00, 0.00),
(1229, 'Gneiss', 'Ore', 9, 1, 5.00, 400, 'tritanium~mexallon~isogen~zydrine~171~171~343~171', 120.08, 644.86, 0.00, 0.00, 315.29, 687.82, 430.00, 0.00, 370.00, 0.00, 0.00),
(17865, 'Iridescent Gneiss', 'Ore', 9, 2, 5.00, 400, 'tritanium~mexallon~isogen~zydrine~180~180~360~180', 397.01, 397.01, 0.00, 0.00, 0.00, 0.00, 100.00, 599.00, 380.00, 0.00, 0.00),
(17866, 'Prismatic Gneiss', 'Ore', 9, 3, 5.00, 400, 'tritanium~mexallon~isogen~zydrine~188~188~377~188', 397.90, 500.91, 113.00, 0.00, 0.00, 0.00, 100.00, 599.00, 390.00, 0.00, 0.00),
(1232, 'Dark Ochre', 'Ore', 10, 1, 8.00, 400, 'tritanium~nocxium~zydrine~250~500~250', 1136.15, 1400.00, 577.00, 1999.95, 213.02, 4855.31, 710.00, 1899.88, 900.00, 3000.00, 0.00),
(17436, 'Onyx Ochre', 'Ore', 10, 2, 8.00, 400, 'tritanium~nocxium~zydrine~263~525~263', 639.07, 0.00, 296.41, 0.00, 0.01, 0.00, 0.00, 4499.00, 900.00, 0.00, 0.00),
(17437, 'Obsidian Ochre', 'Ore', 10, 3, 8.00, 400, 'tritanium~nocxium~zydrine~275~550~275', 501.31, 2702.00, 415.22, 0.00, 0.00, 0.00, 0.00, 2100.00, 900.00, 0.00, 0.00),
(19, 'Spodumain', 'Ore', 11, 1, 16.00, 250, 'tritanium~pyerite~megacyte~3190~410~140', 1185.25, 2385.58, 100.10, 0.00, 611.00, 2388.99, 24.00, 1999.88, 0.00, 2300.00, 0.00),
(17466, 'Bright Spodumain', 'Ore', 11, 2, 16.00, 250, 'tritanium~pyerite~megacyte~3350~431~147', 1001.02, 0.00, 0.00, 0.00, 0.01, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(17467, 'Gleaming Spodumain', 'Ore', 11, 3, 16.00, 250, 'tritanium~pyerite~megacyte~3509~451~154', 1170.01, 0.00, 0.00, 0.00, 0.01, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(1225, 'Crokite', 'Ore', 12, 1, 16.00, 250, 'tritanium~nocxium~zydrine~331~331~663', 2557.01, 3998.97, 131.01, 0.00, 1600.53, 0.00, 1311.74, 4499.93, 2050.00, 3500.00, 0.00),
(17432, 'Sharp Crokite', 'Ore', 12, 2, 16.00, 250, 'tritanium~nocxium~zydrine~348~348~696', 2000.01, 0.00, 0.00, 0.00, 0.02, 0.00, 0.00, 4650.00, 2050.00, 0.00, 0.00),
(17433, 'Crystalline Crokite', 'Ore', 12, 3, 16.00, 250, 'tritanium~nocxium~zydrine~364~364~729', 1003.91, 0.00, 0.00, 0.00, 2494.83, 0.00, 0.00, 4900.00, 2210.00, 0.00, 0.00),
(1223, 'Bistot', 'Ore', 13, 1, 16.00, 200, 'pyerite~zydrine~megacyte~170~341~170', 2120.91, 0.00, 1001.00, 0.00, 1000.00, 0.00, 200.00, 4729.81, 2000.00, 0.00, 0.00),
(17428, 'Triclinic Bistot', 'Ore', 13, 2, 16.00, 200, 'pyerite~zydrine~megacyte~179~358~179', 2914.91, 0.00, 2002.11, 0.00, 0.01, 0.00, 0.00, 10000.00, 2610.00, 0.00, 0.00),
(17429, 'Monoclinic Bistot', 'Ore', 13, 3, 16.00, 200, 'pyerite~zydrine~megacyte~187~375~187', 2830.92, 45000.00, 2002.11, 0.00, 0.01, 0.00, 0.00, 0.00, 2000.00, 0.00, 0.00),
(22, 'Arkonor', 'Ore', 14, 1, 16.00, 200, 'tritanium~zydrine~megacyte~300~166~333', 3300.15, 3844.87, 2877.01, 4098.98, 2930.03, 5250.00, 3510.59, 6299.78, 3200.01, 4599.00, 0.00),
(17425, 'Crimson Arkonor', 'Ore', 14, 2, 16.00, 200, 'tritanium~zydrine~megacyte~315~174~350', 3301.00, 7922.47, 3754.11, 0.00, 2791.48, 4500.00, 3480.00, 0.00, 3200.00, 0.00, 0.00),
(17426, 'Prime Arkonor', 'Ore', 14, 3, 16.00, 200, 'tritanium~zydrine~megacyte~330~183~366', 1501.50, 7898.39, 3754.21, 0.00, 1000.01, 4800.00, 0.00, 14674.00, 3200.00, 0.00, 0.00),
(11396, 'Mercoxit', 'Ore', 15, 1, 40.00, 250, 'morphite~530', 14105.99, 25656.75, 0.00, 0.00, 9299.81, 0.00, 8201.00, 80000.01, 483.34, 45000.00, 0.00),
(17869, 'Magma Mercoxit', 'Ore', 15, 2, 40.00, 250, 'morphite~557', 5000.01, 9000.01, 0.00, 0.00, 8000.01, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(17870, 'Vitreous Mercoxit', 'Ore', 15, 3, 40.00, 250, 'morphite~583', 5250.01, 35250.01, 0.00, 0.00, 8000.01, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(34, 'Tritanium', 'Minerals', -1, 1, 0.01, 0, '', 5.96, 6.02, 5.86, 5.92, 5.74, 5.86, 5.57, 5.94, 5.63, 5.75, 0.00),
(35, 'Pyerite', 'Minerals', -1, 2, 0.01, 0, '', 12.37, 12.49, 11.67, 11.97, 12.12, 12.42, 11.70, 12.00, 11.35, 11.97, 0.00),
(36, 'Mexallon', 'Minerals', -1, 3, 0.01, 0, '', 60.28, 61.56, 56.93, 59.22, 58.20, 59.77, 54.59, 59.45, 52.89, 58.32, 0.00),
(37, 'Isogen', 'Minerals', -1, 4, 0.01, 0, '', 118.45, 121.64, 114.24, 123.42, 115.22, 122.92, 111.02, 126.85, 112.63, 119.62, 0.00),
(38, 'Nocxium', 'Minerals', -1, 5, 0.01, 0, '', 622.03, 633.09, 625.62, 672.56, 607.00, 619.98, 593.14, 644.00, 635.07, 687.59, 0.00),
(39, 'Zydrine', 'Minerals', -1, 6, 0.01, 0, '', 621.53, 663.92, 670.00, 674.18, 610.22, 668.70, 618.23, 694.28, 572.00, 696.00, 0.00),
(40, 'Megacyte', 'Minerals', -1, 7, 0.01, 0, '', 1882.82, 1985.03, 1921.01, 2099.97, 1831.03, 1955.00, 1850.08, 1977.99, 1902.08, 2022.00, 0.00),
(11399, 'Morphite', 'Minerals', -1, 8, 0.01, 0, '', 5404.04, 5844.73, 4753.00, 6274.81, 5702.13, 6996.55, 4775.02, 7348.56, 4203.10, 5600.00, 0.00),
(16264, 'Blue Ice', 'Ice', 0, 1, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~oxygen isotopes~50~25~1~300', 112300.17, 267703.28, 152000.00, 224920.89, 1000.01, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(17975, 'Thick Blue Ice', 'Ice', 0, 2, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~oxygen isotopes~75~40~1~350', 178008.16, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(16263, 'Glacial Mass', 'Ice', 3, 1, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~hydrogen isotopes~50~25~1~300', 91005.39, 164999.37, 100000.01, 259999.00, 0.00, 249999.99, 108011.11, 150000.00, 105000.00, 119000.00, 0.00),
(17977, 'Smooth Glacial Mass', 'Ice', 3, 2, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~hydrogen isotopes~75~40~1~350', 119003.18, 99999999.99, 0.00, 0.00, 0.00, 0.00, 0.00, 3500000.00, 0.00, 0.00, 0.00),
(16265, 'White Glaze', 'Ice', 2, 1, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~nitrogen isotopes~50~25~1~300', 129576.23, 149999.23, 99999.00, 1000000.00, 72000.37, 194999.62, 0.00, 379999.00, 0.00, 400000.00, 0.00),
(17976, 'Pristine White Glaze', 'Ice', 2, 2, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~nitrogen isotopes~75~40~1~350', 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(16262, 'Clear Icicle', 'Ice', 1, 1, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~helium isotopes~50~25~1~300', 98000.13, 135000.00, 0.00, 150000.00, 107001.09, 107001.10, 34833.34, 139999.00, 0.00, 0.00, 0.00),
(17978, 'Enriched Clear Icicle', 'Ice', 1, 2, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~helium isotopes~75~40~1~350', 0.00, 0.00, 0.00, 0.00, 0.00, 466000.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(16269, 'Krystallos', 'Ice', 4, 1, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~100~250~100', 29000.46, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(16268, 'Gelidus', 'Ice', 4, 2, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~250~500~75', 50002.12, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(16267, 'Dark Glitter', 'Ice', 4, 3, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~500~1000~50', 230000.21, 399243.24, 0.00, 1400000.00, 150000.00, 795000.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(16266, 'Glare Crust', 'Ice', 4, 4, 99.99, 1, 'heavy water~liquid ozone~strontium clathrates~1000~500~25', 276000.09, 1000000.00, 0.00, 1525000.00, 0.00, 1525000.00, 0.00, 0.00, 0.00, 0.00, 0.00),
(16272, 'Heavy Water', 'Ice Products', -1, 1, 0.40, 0, '', 70.40, 73.92, 65.15, 70.69, 70.97, 78.80, 67.13, 0.00, 58.32, 68.98, 0.00),
(16273, 'Liquid Ozone', 'Ice Products', -1, 2, 0.40, 0, '', 252.99, 308.71, 320.10, 328.77, 316.37, 406.90, 325.03, 364.99, 320.89, 345.00, 0.00),
(16275, 'Strontium Clathrates', 'Ice Products', -1, 3, 3.00, 0, '', 207.05, 231.29, 237.08, 312.82, 235.02, 329.88, 137.51, 261.23, 166.06, 334.39, 0.00),
(17887, 'Oxygen Isotopes', 'Ice Products ', -1, 4, 0.15, 0, '', 695.17, 849.99, 550.25, 846.61, 445.70, 958.39, 401.20, 1024.97, 419.23, 1040.55, 0.00),
(17888, 'Nitrogen Isotopes', 'Ice Products', -1, 5, 0.15, 0, '', 420.04, 473.85, 425.03, 889.00, 391.51, 548.35, 395.05, 624.00, 300.07, 602.24, 0.00),
(16274, 'Helium Isotopes', 'Ice Products', -1, 6, 0.15, 0, '', 418.01, 433.99, 360.08, 402.71, 371.48, 427.06, 304.37, 504.37, 303.10, 497.00, 0.00),
(17889, 'Hydrogen Isotopes', 'Ice Products', -1, 7, 0.15, 0, '', 443.68, 454.98, 410.05, 434.77, 423.99, 484.84, 386.13, 443.79, 361.95, 436.54, 0.00);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

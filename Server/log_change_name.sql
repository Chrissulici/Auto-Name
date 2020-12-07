/*
 Navicat Premium Data Transfer

 Source Server         : helix vps
 Source Server Type    : MySQL
 Source Server Version : 50533
 Source Host           : 188.212.103.202:3306
 Source Schema         : log

 Target Server Type    : MySQL
 Target Server Version : 50533
 File Encoding         : 65001

 Date: 30/10/2020 01:58:47
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for log_change_name
-- ----------------------------
DROP TABLE IF EXISTS `log_change_name`;
CREATE TABLE `log_change_name`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `old_name` varchar(30) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `new_name` varchar(30) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `date` datetime NOT NULL,
  `gm` varchar(30) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;

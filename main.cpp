#include "b_plus_tree.hpp"
#include "value_pointer.hpp"

int main() {
	remove("test.info");
	remove("test.index");

	BPlusTree<Value, Pointer> b_plus_tree = BPlusTree<Value, Pointer>("test");
	Node<Value, Pointer> node;
	int pointer_num = (BLOCK_SIZE - sizeof(int) - sizeof(char) - sizeof(int) - sizeof(Pointer)) / (sizeof(Pointer) + sizeof(Value)) + 1;

	b_plus_tree.Insert(Value(0, "0", 0), 0);
	b_plus_tree.Insert(Value(1, "1", 0.1), 1);
	b_plus_tree.Insert(Value(2, "2", 0.2), 2);
	b_plus_tree.Insert(Value(3, "3", 0.3), 3);/*
	b_plus_tree.Insert(Value(4, "4", 0.4), 4);
	b_plus_tree.Insert(Value(5, "5", 0.5), 5);
	b_plus_tree.Insert(Value(6, "6", 0.6), 6);
	b_plus_tree.Insert(Value(7, "7", 0.7), 7);
	b_plus_tree.Insert(Value(8, "8", 0.8), 8);
	b_plus_tree.Insert(Value(9, "9", 0.9), 9);
	b_plus_tree.Insert(Value(10, "10", 1), 10);
	b_plus_tree.Insert(Value(11, "11", 1.1), 11);
	b_plus_tree.Insert(Value(12, "12", 1.2), 12);
	b_plus_tree.Insert(Value(13, "13", 1.3), 13);
	b_plus_tree.Insert(Value(14, "14", 1.4), 14);
	b_plus_tree.Insert(Value(15, "15", 1.5), 15);
	b_plus_tree.Insert(Value(16, "16", 1.6), 16);
	b_plus_tree.Insert(Value(17, "17", 1.7), 17);
	b_plus_tree.Insert(Value(18, "18", 1.8), 18);
	b_plus_tree.Insert(Value(19, "19", 1.9), 19);
	b_plus_tree.Insert(Value(20, "20", 2), 20);
	b_plus_tree.Insert(Value(21, "21", 2.1), 21);
	b_plus_tree.Insert(Value(22, "22", 2.2), 22);
	b_plus_tree.Insert(Value(23, "23", 2.3), 23);
	b_plus_tree.Insert(Value(24, "24", 2.4), 24);
	b_plus_tree.Insert(Value(25, "25", 2.5), 25);
	b_plus_tree.Insert(Value(26, "26", 2.6), 26);
	b_plus_tree.Insert(Value(27, "27", 2.7), 27);
	b_plus_tree.Insert(Value(28, "28", 2.8), 28);
	b_plus_tree.Insert(Value(29, "29", 2.9), 29);
	b_plus_tree.Insert(Value(30, "30", 3), 30);
	b_plus_tree.Insert(Value(31, "31", 3.1), 31);
	b_plus_tree.Insert(Value(32, "32", 3.2), 32);
	b_plus_tree.Insert(Value(33, "33", 3.3), 33);
	b_plus_tree.Insert(Value(34, "34", 3.4), 34);
	b_plus_tree.Insert(Value(35, "35", 3.5), 35);
	b_plus_tree.Insert(Value(36, "36", 3.6), 36);
	b_plus_tree.Insert(Value(37, "37", 3.7), 37);
	b_plus_tree.Insert(Value(38, "38", 3.8), 38);
	b_plus_tree.Insert(Value(39, "39", 3.9), 39);
	b_plus_tree.Insert(Value(40, "40", 4), 40);
	b_plus_tree.Insert(Value(41, "41", 4.1), 41);
	b_plus_tree.Insert(Value(42, "42", 4.2), 42);
	b_plus_tree.Insert(Value(43, "43", 4.3), 43);
	b_plus_tree.Insert(Value(44, "44", 4.4), 44);
	b_plus_tree.Insert(Value(45, "45", 4.5), 45);
	b_plus_tree.Insert(Value(46, "46", 4.6), 46);
	b_plus_tree.Insert(Value(47, "47", 4.7), 47);
	b_plus_tree.Insert(Value(48, "48", 4.8), 48);
	b_plus_tree.Insert(Value(49, "49", 4.9), 49);
	b_plus_tree.Insert(Value(50, "50", 5), 50);
	b_plus_tree.Insert(Value(51, "51", 5.1), 51);
	b_plus_tree.Insert(Value(52, "52", 5.2), 52);
	b_plus_tree.Insert(Value(53, "53", 5.3), 53);
	b_plus_tree.Insert(Value(54, "54", 5.4), 54);
	b_plus_tree.Insert(Value(55, "55", 5.5), 55);
	b_plus_tree.Insert(Value(56, "56", 5.6), 56);
	b_plus_tree.Insert(Value(57, "57", 5.7), 57);
	b_plus_tree.Insert(Value(58, "58", 5.8), 58);
	b_plus_tree.Insert(Value(59, "59", 5.9), 59);
	b_plus_tree.Insert(Value(60, "60", 6), 60);
	b_plus_tree.Insert(Value(61, "61", 6.1), 61);
	b_plus_tree.Insert(Value(62, "62", 6.2), 62);
	b_plus_tree.Insert(Value(63, "63", 6.3), 63);
	b_plus_tree.Insert(Value(64, "64", 6.4), 64);
	b_plus_tree.Insert(Value(65, "65", 6.5), 65);
	b_plus_tree.Insert(Value(66, "66", 6.6), 66);
	b_plus_tree.Insert(Value(67, "67", 6.7), 67);
	b_plus_tree.Insert(Value(68, "68", 6.8), 68);
	b_plus_tree.Insert(Value(69, "69", 6.9), 69);
	b_plus_tree.Insert(Value(70, "70", 7), 70);
	b_plus_tree.Insert(Value(71, "71", 7.1), 71);
	b_plus_tree.Insert(Value(72, "72", 7.2), 72);
	b_plus_tree.Insert(Value(73, "73", 7.3), 73);
	b_plus_tree.Insert(Value(74, "74", 7.4), 74);
	b_plus_tree.Insert(Value(75, "75", 7.5), 75);
	b_plus_tree.Insert(Value(76, "76", 7.6), 76);
	b_plus_tree.Insert(Value(77, "77", 7.7), 77);
	b_plus_tree.Insert(Value(78, "78", 7.8), 78);
	b_plus_tree.Insert(Value(79, "79", 7.9), 79);
	b_plus_tree.Insert(Value(80, "80", 8), 80);
	b_plus_tree.Insert(Value(81, "81", 8.1), 81);
	b_plus_tree.Insert(Value(82, "82", 8.2), 82);
	b_plus_tree.Insert(Value(83, "83", 8.3), 83);
	b_plus_tree.Insert(Value(84, "84", 8.4), 84);
	b_plus_tree.Insert(Value(85, "85", 8.5), 85);
	b_plus_tree.Insert(Value(86, "86", 8.6), 86);
	b_plus_tree.Insert(Value(87, "87", 8.7), 87);
	b_plus_tree.Insert(Value(88, "88", 8.8), 88);
	b_plus_tree.Insert(Value(89, "89", 8.9), 89);
	b_plus_tree.Insert(Value(90, "90", 9), 90);
	b_plus_tree.Insert(Value(91, "91", 9.1), 91);
	b_plus_tree.Insert(Value(92, "92", 9.2), 92);
	b_plus_tree.Insert(Value(93, "93", 9.3), 93);
	b_plus_tree.Insert(Value(94, "94", 9.4), 94);
	b_plus_tree.Insert(Value(95, "95", 9.5), 95);
	b_plus_tree.Insert(Value(96, "96", 9.6), 96);
	b_plus_tree.Insert(Value(97, "97", 9.7), 97);
	b_plus_tree.Insert(Value(98, "98", 9.8), 98);
	b_plus_tree.Insert(Value(99, "99", 9.9), 99);
	b_plus_tree.Insert(Value(100, "100", 10), 100);
	b_plus_tree.Insert(Value(101, "101", 10.1), 101);
	b_plus_tree.Insert(Value(102, "102", 10.2), 102);
	b_plus_tree.Insert(Value(103, "103", 10.3), 103);
	b_plus_tree.Insert(Value(104, "104", 10.4), 104);
	b_plus_tree.Insert(Value(105, "105", 10.5), 105);
	b_plus_tree.Insert(Value(106, "106", 10.6), 106);
	b_plus_tree.Insert(Value(107, "107", 10.7), 107);
	b_plus_tree.Insert(Value(108, "108", 10.8), 108);
	b_plus_tree.Insert(Value(109, "109", 10.9), 109);
	b_plus_tree.Insert(Value(110, "110", 11), 110);
	b_plus_tree.Insert(Value(111, "111", 11.1), 111);
	b_plus_tree.Insert(Value(112, "112", 11.2), 112);
	b_plus_tree.Insert(Value(113, "113", 11.3), 113);
	b_plus_tree.Insert(Value(114, "114", 11.4), 114);
	b_plus_tree.Insert(Value(115, "115", 11.5), 115);
	b_plus_tree.Insert(Value(116, "116", 11.6), 116);
	b_plus_tree.Insert(Value(117, "117", 11.7), 117);
	b_plus_tree.Insert(Value(118, "118", 11.8), 118);
	b_plus_tree.Insert(Value(119, "119", 11.9), 119);
	b_plus_tree.Insert(Value(120, "120", 12), 120);
	b_plus_tree.Insert(Value(121, "121", 12.1), 121);
	b_plus_tree.Insert(Value(122, "122", 12.2), 122);
	b_plus_tree.Insert(Value(123, "123", 12.3), 123);
	b_plus_tree.Insert(Value(124, "124", 12.4), 124);
	b_plus_tree.Insert(Value(125, "125", 12.5), 125);
	b_plus_tree.Insert(Value(126, "126", 12.6), 126);
	b_plus_tree.Insert(Value(127, "127", 12.7), 127);
	b_plus_tree.Insert(Value(128, "128", 12.8), 128);
	b_plus_tree.Insert(Value(129, "129", 12.9), 129);
	b_plus_tree.Insert(Value(130, "130", 13), 130);
	b_plus_tree.Insert(Value(131, "131", 13.1), 131);
	b_plus_tree.Insert(Value(132, "132", 13.2), 132);
	b_plus_tree.Insert(Value(133, "133", 13.3), 133);
	b_plus_tree.Insert(Value(134, "134", 13.4), 134);
	b_plus_tree.Insert(Value(135, "135", 13.5), 135);
	b_plus_tree.Insert(Value(136, "136", 13.6), 136);
	b_plus_tree.Insert(Value(137, "137", 13.7), 137);
	b_plus_tree.Insert(Value(138, "138", 13.8), 138);
	b_plus_tree.Insert(Value(139, "139", 13.9), 139);
	b_plus_tree.Insert(Value(140, "140", 14), 140);
	b_plus_tree.Insert(Value(141, "141", 14.1), 141);
	b_plus_tree.Insert(Value(142, "142", 14.2), 142);
	b_plus_tree.Insert(Value(143, "143", 14.3), 143);
	b_plus_tree.Insert(Value(144, "144", 14.4), 144);
	b_plus_tree.Insert(Value(145, "145", 14.5), 145);
	b_plus_tree.Insert(Value(146, "146", 14.6), 146);
	b_plus_tree.Insert(Value(147, "147", 14.7), 147);
	b_plus_tree.Insert(Value(148, "148", 14.8), 148);
	b_plus_tree.Insert(Value(149, "149", 14.9), 149);
	b_plus_tree.Insert(Value(150, "150", 15), 150);
	b_plus_tree.Insert(Value(151, "151", 15.1), 151);
	b_plus_tree.Insert(Value(152, "152", 15.2), 152);
	b_plus_tree.Insert(Value(153, "153", 15.3), 153);
	b_plus_tree.Insert(Value(154, "154", 15.4), 154);
	b_plus_tree.Insert(Value(155, "155", 15.5), 155);
	b_plus_tree.Insert(Value(156, "156", 15.6), 156);
	b_plus_tree.Insert(Value(157, "157", 15.7), 157);
	b_plus_tree.Insert(Value(158, "158", 15.8), 158);
	b_plus_tree.Insert(Value(159, "159", 15.9), 159);
	b_plus_tree.Insert(Value(160, "160", 16), 160);
	b_plus_tree.Insert(Value(161, "161", 16.1), 161);
	b_plus_tree.Insert(Value(162, "162", 16.2), 162);
	b_plus_tree.Insert(Value(163, "163", 16.3), 163);
	b_plus_tree.Insert(Value(164, "164", 16.4), 164);
	b_plus_tree.Insert(Value(165, "165", 16.5), 165);
	b_plus_tree.Insert(Value(166, "166", 16.6), 166);
	b_plus_tree.Insert(Value(167, "167", 16.7), 167);
	b_plus_tree.Insert(Value(168, "168", 16.8), 168);
	b_plus_tree.Insert(Value(169, "169", 16.9), 169);
	b_plus_tree.Insert(Value(170, "170", 17), 170);
	b_plus_tree.Insert(Value(171, "171", 17.1), 171);
	b_plus_tree.Insert(Value(172, "172", 17.2), 172);
	b_plus_tree.Insert(Value(173, "173", 17.3), 173);
	b_plus_tree.Insert(Value(174, "174", 17.4), 174);
	b_plus_tree.Insert(Value(175, "175", 17.5), 175);
	b_plus_tree.Insert(Value(176, "176", 17.6), 176);
	b_plus_tree.Insert(Value(177, "177", 17.7), 177);
	b_plus_tree.Insert(Value(178, "178", 17.8), 178);
	b_plus_tree.Insert(Value(179, "179", 17.9), 179);
	b_plus_tree.Insert(Value(180, "180", 18), 180);
	b_plus_tree.Insert(Value(181, "181", 18.1), 181);
	b_plus_tree.Insert(Value(182, "182", 18.2), 182);
	b_plus_tree.Insert(Value(183, "183", 18.3), 183);
	b_plus_tree.Insert(Value(184, "184", 18.4), 184);
	b_plus_tree.Insert(Value(185, "185", 18.5), 185);
	b_plus_tree.Insert(Value(186, "186", 18.6), 186);
	b_plus_tree.Insert(Value(187, "187", 18.7), 187);
	b_plus_tree.Insert(Value(188, "188", 18.8), 188);
	b_plus_tree.Insert(Value(189, "189", 18.9), 189);
	b_plus_tree.Insert(Value(190, "190", 19), 190);
	b_plus_tree.Insert(Value(191, "191", 19.1), 191);
	b_plus_tree.Insert(Value(192, "192", 19.2), 192);
	b_plus_tree.Insert(Value(193, "193", 19.3), 193);
	b_plus_tree.Insert(Value(194, "194", 19.4), 194);
	b_plus_tree.Insert(Value(195, "195", 19.5), 195);
	b_plus_tree.Insert(Value(196, "196", 19.6), 196);
	b_plus_tree.Insert(Value(197, "197", 19.7), 197);
	b_plus_tree.Insert(Value(198, "198", 19.8), 198);
	b_plus_tree.Insert(Value(199, "199", 19.9), 199);
	b_plus_tree.Insert(Value(200, "200", 20), 200);
	b_plus_tree.Insert(Value(201, "201", 20.1), 201);
	b_plus_tree.Insert(Value(202, "202", 20.2), 202);
	b_plus_tree.Insert(Value(203, "203", 20.3), 203);
	b_plus_tree.Insert(Value(204, "204", 20.4), 204);
	b_plus_tree.Insert(Value(205, "205", 20.5), 205);
	b_plus_tree.Insert(Value(206, "206", 20.6), 206);
	b_plus_tree.Insert(Value(207, "207", 20.7), 207);
	b_plus_tree.Insert(Value(208, "208", 20.8), 208);
	b_plus_tree.Insert(Value(209, "209", 20.9), 209);
	b_plus_tree.Insert(Value(210, "210", 21), 210);
	b_plus_tree.Insert(Value(211, "211", 21.1), 211);
	b_plus_tree.Insert(Value(212, "212", 21.2), 212);
	b_plus_tree.Insert(Value(213, "213", 21.3), 213);
	b_plus_tree.Insert(Value(214, "214", 21.4), 214);
	b_plus_tree.Insert(Value(215, "215", 21.5), 215);
	b_plus_tree.Insert(Value(216, "216", 21.6), 216);
	b_plus_tree.Insert(Value(217, "217", 21.7), 217);
	b_plus_tree.Insert(Value(218, "218", 21.8), 218);
	b_plus_tree.Insert(Value(219, "219", 21.9), 219);
	b_plus_tree.Insert(Value(220, "220", 22), 220);
	b_plus_tree.Insert(Value(221, "221", 22.1), 221);
	b_plus_tree.Insert(Value(222, "222", 22.2), 222);
	b_plus_tree.Insert(Value(223, "223", 22.3), 223);
	b_plus_tree.Insert(Value(224, "224", 22.4), 224);
	b_plus_tree.Insert(Value(225, "225", 22.5), 225);
	b_plus_tree.Insert(Value(226, "226", 22.6), 226);
	b_plus_tree.Insert(Value(227, "227", 22.7), 227);
	b_plus_tree.Insert(Value(228, "228", 22.8), 228);
	b_plus_tree.Insert(Value(229, "229", 22.9), 229);
	b_plus_tree.Insert(Value(230, "230", 23), 230);
	b_plus_tree.Insert(Value(231, "231", 23.1), 231);
	b_plus_tree.Insert(Value(232, "232", 23.2), 232);
	b_plus_tree.Insert(Value(233, "233", 23.3), 233);
	b_plus_tree.Insert(Value(234, "234", 23.4), 234);
	b_plus_tree.Insert(Value(235, "235", 23.5), 235);
	b_plus_tree.Insert(Value(236, "236", 23.6), 236);
	b_plus_tree.Insert(Value(237, "237", 23.7), 237);
	b_plus_tree.Insert(Value(238, "238", 23.8), 238);
	b_plus_tree.Insert(Value(239, "239", 23.9), 239);
	b_plus_tree.Insert(Value(240, "240", 24), 240);
	b_plus_tree.Insert(Value(241, "241", 24.1), 241);
	b_plus_tree.Insert(Value(242, "242", 24.2), 242);
	b_plus_tree.Insert(Value(243, "243", 24.3), 243);
	b_plus_tree.Insert(Value(244, "244", 24.4), 244);
	b_plus_tree.Insert(Value(245, "245", 24.5), 245);
	b_plus_tree.Insert(Value(246, "246", 24.6), 246);
	b_plus_tree.Insert(Value(247, "247", 24.7), 247);
	b_plus_tree.Insert(Value(248, "248", 24.8), 248);
	b_plus_tree.Insert(Value(249, "249", 24.9), 249);
	b_plus_tree.Insert(Value(250, "250", 25), 250);
	b_plus_tree.Insert(Value(251, "251", 25.1), 251);
	b_plus_tree.Insert(Value(252, "252", 25.2), 252);
	b_plus_tree.Insert(Value(253, "253", 25.3), 253);
	b_plus_tree.Insert(Value(254, "254", 25.4), 254);
	b_plus_tree.Insert(Value(255, "255", 25.5), 255);
	b_plus_tree.Insert(Value(256, "256", 25.6), 256);
	b_plus_tree.Insert(Value(257, "257", 25.7), 257);
	b_plus_tree.Insert(Value(258, "258", 25.8), 258);
	b_plus_tree.Insert(Value(259, "259", 25.9), 259);
	b_plus_tree.Insert(Value(260, "260", 26), 260);
	b_plus_tree.Insert(Value(261, "261", 26.1), 261);
	b_plus_tree.Insert(Value(262, "262", 26.2), 262);
	b_plus_tree.Insert(Value(263, "263", 26.3), 263);
	b_plus_tree.Insert(Value(264, "264", 26.4), 264);
	b_plus_tree.Insert(Value(265, "265", 26.5), 265);
	b_plus_tree.Insert(Value(266, "266", 26.6), 266);
	b_plus_tree.Insert(Value(267, "267", 26.7), 267);
	b_plus_tree.Insert(Value(268, "268", 26.8), 268);
	b_plus_tree.Insert(Value(269, "269", 26.9), 269);
	b_plus_tree.Insert(Value(270, "270", 27), 270);
	b_plus_tree.Insert(Value(271, "271", 27.1), 271);
	b_plus_tree.Insert(Value(272, "272", 27.2), 272);
	b_plus_tree.Insert(Value(273, "273", 27.3), 273);
	b_plus_tree.Insert(Value(274, "274", 27.4), 274);
	b_plus_tree.Insert(Value(275, "275", 27.5), 275);
	b_plus_tree.Insert(Value(276, "276", 27.6), 276);
	b_plus_tree.Insert(Value(277, "277", 27.7), 277);
	b_plus_tree.Insert(Value(278, "278", 27.8), 278);
	b_plus_tree.Insert(Value(279, "279", 27.9), 279);
	b_plus_tree.Insert(Value(280, "280", 28), 280);
	b_plus_tree.Insert(Value(281, "281", 28.1), 281);
	b_plus_tree.Insert(Value(282, "282", 28.2), 282);
	b_plus_tree.Insert(Value(283, "283", 28.3), 283);
	b_plus_tree.Insert(Value(284, "284", 28.4), 284);
	b_plus_tree.Insert(Value(285, "285", 28.5), 285);
	b_plus_tree.Insert(Value(286, "286", 28.6), 286);
	b_plus_tree.Insert(Value(287, "287", 28.7), 287);
	b_plus_tree.Insert(Value(288, "288", 28.8), 288);
	b_plus_tree.Insert(Value(289, "289", 28.9), 289);
	b_plus_tree.Insert(Value(290, "290", 29), 290);
	b_plus_tree.Insert(Value(291, "291", 29.1), 291);
	b_plus_tree.Insert(Value(292, "292", 29.2), 292);
	b_plus_tree.Insert(Value(293, "293", 29.3), 293);
	b_plus_tree.Insert(Value(294, "294", 29.4), 294);
	b_plus_tree.Insert(Value(295, "295", 29.5), 295);
	b_plus_tree.Insert(Value(296, "296", 29.6), 296);
	b_plus_tree.Insert(Value(297, "297", 29.7), 297);
	b_plus_tree.Insert(Value(298, "298", 29.8), 298);
	b_plus_tree.Insert(Value(299, "299", 29.9), 299);
	b_plus_tree.Insert(Value(300, "300", 30), 300);
	b_plus_tree.Insert(Value(301, "301", 30.1), 301);
	b_plus_tree.Insert(Value(302, "302", 30.2), 302);
	b_plus_tree.Insert(Value(303, "303", 30.3), 303);
	b_plus_tree.Insert(Value(304, "304", 30.4), 304);
	b_plus_tree.Insert(Value(305, "305", 30.5), 305);
	b_plus_tree.Insert(Value(306, "306", 30.6), 306);
	b_plus_tree.Insert(Value(307, "307", 30.7), 307);
	b_plus_tree.Insert(Value(308, "308", 30.8), 308);
	b_plus_tree.Insert(Value(309, "309", 30.9), 309);
	b_plus_tree.Insert(Value(310, "310", 31), 310);
	b_plus_tree.Insert(Value(311, "311", 31.1), 311);
	b_plus_tree.Insert(Value(312, "312", 31.2), 312);
	b_plus_tree.Insert(Value(313, "313", 31.3), 313);
	b_plus_tree.Insert(Value(314, "314", 31.4), 314);
	b_plus_tree.Insert(Value(315, "315", 31.5), 315);
	b_plus_tree.Insert(Value(316, "316", 31.6), 316);
	b_plus_tree.Insert(Value(317, "317", 31.7), 317);
	b_plus_tree.Insert(Value(318, "318", 31.8), 318);
	b_plus_tree.Insert(Value(319, "319", 31.9), 319);
	b_plus_tree.Insert(Value(320, "320", 32), 320);
	b_plus_tree.Insert(Value(321, "321", 32.1), 321);
	b_plus_tree.Insert(Value(322, "322", 32.2), 322);
	b_plus_tree.Insert(Value(323, "323", 32.3), 323);
	b_plus_tree.Insert(Value(324, "324", 32.4), 324);
	b_plus_tree.Insert(Value(325, "325", 32.5), 325);
	b_plus_tree.Insert(Value(326, "326", 32.6), 326);
	b_plus_tree.Insert(Value(327, "327", 32.7), 327);
	b_plus_tree.Insert(Value(328, "328", 32.8), 328);
	b_plus_tree.Insert(Value(329, "329", 32.9), 329);
	b_plus_tree.Insert(Value(330, "330", 33), 330);
	b_plus_tree.Insert(Value(331, "331", 33.1), 331);
	b_plus_tree.Insert(Value(332, "332", 33.2), 332);
	b_plus_tree.Insert(Value(333, "333", 33.3), 333);
	b_plus_tree.Insert(Value(334, "334", 33.4), 334);
	b_plus_tree.Insert(Value(335, "335", 33.5), 335);
	b_plus_tree.Insert(Value(336, "336", 33.6), 336);
	b_plus_tree.Insert(Value(337, "337", 33.7), 337);
	b_plus_tree.Insert(Value(338, "338", 33.8), 338);
	b_plus_tree.Insert(Value(339, "339", 33.9), 339);
	b_plus_tree.Insert(Value(340, "340", 34), 340);
	b_plus_tree.Insert(Value(341, "341", 34.1), 341);
	b_plus_tree.Insert(Value(342, "342", 34.2), 342);
	b_plus_tree.Insert(Value(343, "343", 34.3), 343);
	b_plus_tree.Insert(Value(344, "344", 34.4), 344);
	b_plus_tree.Insert(Value(345, "345", 34.5), 345);
	b_plus_tree.Insert(Value(346, "346", 34.6), 346);
	b_plus_tree.Insert(Value(347, "347", 34.7), 347);
	b_plus_tree.Insert(Value(348, "348", 34.8), 348);
	b_plus_tree.Insert(Value(349, "349", 34.9), 349);
	b_plus_tree.Insert(Value(350, "350", 35), 350);
	b_plus_tree.Insert(Value(351, "351", 35.1), 351);
	b_plus_tree.Insert(Value(352, "352", 35.2), 352);
	b_plus_tree.Insert(Value(353, "353", 35.3), 353);
	b_plus_tree.Insert(Value(354, "354", 35.4), 354);
	b_plus_tree.Insert(Value(355, "355", 35.5), 355);
	b_plus_tree.Insert(Value(356, "356", 35.6), 356);
	b_plus_tree.Insert(Value(357, "357", 35.7), 357);
	b_plus_tree.Insert(Value(358, "358", 35.8), 358);
	b_plus_tree.Insert(Value(359, "359", 35.9), 359);
	b_plus_tree.Insert(Value(360, "360", 36), 360);
	b_plus_tree.Insert(Value(361, "361", 36.1), 361);
	b_plus_tree.Insert(Value(362, "362", 36.2), 362);
	b_plus_tree.Insert(Value(363, "363", 36.3), 363);
	b_plus_tree.Insert(Value(364, "364", 36.4), 364);
	b_plus_tree.Insert(Value(365, "365", 36.5), 365);
	b_plus_tree.Insert(Value(366, "366", 36.6), 366);
	b_plus_tree.Insert(Value(367, "367", 36.7), 367);
	b_plus_tree.Insert(Value(368, "368", 36.8), 368);
	b_plus_tree.Insert(Value(369, "369", 36.9), 369);
	b_plus_tree.Insert(Value(370, "370", 37), 370);
	b_plus_tree.Insert(Value(371, "371", 37.1), 371);
	b_plus_tree.Insert(Value(372, "372", 37.2), 372);
	b_plus_tree.Insert(Value(373, "373", 37.3), 373);
	b_plus_tree.Insert(Value(374, "374", 37.4), 374);
	b_plus_tree.Insert(Value(375, "375", 37.5), 375);
	b_plus_tree.Insert(Value(376, "376", 37.6), 376);
	b_plus_tree.Insert(Value(377, "377", 37.7), 377);
	b_plus_tree.Insert(Value(378, "378", 37.8), 378);
	b_plus_tree.Insert(Value(379, "379", 37.9), 379);
	b_plus_tree.Insert(Value(380, "380", 38), 380);
	b_plus_tree.Insert(Value(381, "381", 38.1), 381);
	b_plus_tree.Insert(Value(382, "382", 38.2), 382);
	b_plus_tree.Insert(Value(383, "383", 38.3), 383);
	b_plus_tree.Insert(Value(384, "384", 38.4), 384);
	b_plus_tree.Insert(Value(385, "385", 38.5), 385);
	b_plus_tree.Insert(Value(386, "386", 38.6), 386);
	b_plus_tree.Insert(Value(387, "387", 38.7), 387);
	b_plus_tree.Insert(Value(388, "388", 38.8), 388);
	b_plus_tree.Insert(Value(389, "389", 38.9), 389);
	b_plus_tree.Insert(Value(390, "390", 39), 390);
	b_plus_tree.Insert(Value(391, "391", 39.1), 391);
	b_plus_tree.Insert(Value(392, "392", 39.2), 392);
	b_plus_tree.Insert(Value(393, "393", 39.3), 393);
	b_plus_tree.Insert(Value(394, "394", 39.4), 394);
	b_plus_tree.Insert(Value(395, "395", 39.5), 395);
	b_plus_tree.Insert(Value(396, "396", 39.6), 396);
	b_plus_tree.Insert(Value(397, "397", 39.7), 397);
	b_plus_tree.Insert(Value(398, "398", 39.8), 398);
	b_plus_tree.Insert(Value(399, "399", 39.9), 399);
	b_plus_tree.Insert(Value(400, "400", 40), 400);
	b_plus_tree.Insert(Value(401, "401", 40.1), 401);
	b_plus_tree.Insert(Value(402, "402", 40.2), 402);
	b_plus_tree.Insert(Value(403, "403", 40.3), 403);
	b_plus_tree.Insert(Value(404, "404", 40.4), 404);
	b_plus_tree.Insert(Value(405, "405", 40.5), 405);
	b_plus_tree.Insert(Value(406, "406", 40.6), 406);
	b_plus_tree.Insert(Value(407, "407", 40.7), 407);
	b_plus_tree.Insert(Value(408, "408", 40.8), 408);
	b_plus_tree.Insert(Value(409, "409", 40.9), 409);
	b_plus_tree.Insert(Value(410, "410", 41), 410);
	b_plus_tree.Insert(Value(411, "411", 41.1), 411);
	b_plus_tree.Insert(Value(412, "412", 41.2), 412);
	b_plus_tree.Insert(Value(413, "413", 41.3), 413);
	b_plus_tree.Insert(Value(414, "414", 41.4), 414);
	b_plus_tree.Insert(Value(415, "415", 41.5), 415);
	b_plus_tree.Insert(Value(416, "416", 41.6), 416);
	b_plus_tree.Insert(Value(417, "417", 41.7), 417);
	b_plus_tree.Insert(Value(418, "418", 41.8), 418);
	b_plus_tree.Insert(Value(419, "419", 41.9), 419);
	b_plus_tree.Insert(Value(420, "420", 42), 420);
	b_plus_tree.Insert(Value(421, "421", 42.1), 421);
	b_plus_tree.Insert(Value(422, "422", 42.2), 422);
	b_plus_tree.Insert(Value(423, "423", 42.3), 423);
	b_plus_tree.Insert(Value(424, "424", 42.4), 424);
	b_plus_tree.Insert(Value(425, "425", 42.5), 425);
	b_plus_tree.Insert(Value(426, "426", 42.6), 426);
	b_plus_tree.Insert(Value(427, "427", 42.7), 427);
	b_plus_tree.Insert(Value(428, "428", 42.8), 428);
	b_plus_tree.Insert(Value(429, "429", 42.9), 429);
	b_plus_tree.Insert(Value(430, "430", 43), 430);
	b_plus_tree.Insert(Value(431, "431", 43.1), 431);
	b_plus_tree.Insert(Value(432, "432", 43.2), 432);
	b_plus_tree.Insert(Value(433, "433", 43.3), 433);
	b_plus_tree.Insert(Value(434, "434", 43.4), 434);
	b_plus_tree.Insert(Value(435, "435", 43.5), 435);
	b_plus_tree.Insert(Value(436, "436", 43.6), 436);
	b_plus_tree.Insert(Value(437, "437", 43.7), 437);
	b_plus_tree.Insert(Value(438, "438", 43.8), 438);
	b_plus_tree.Insert(Value(439, "439", 43.9), 439);
	b_plus_tree.Insert(Value(440, "440", 44), 440);
	b_plus_tree.Insert(Value(441, "441", 44.1), 441);
	b_plus_tree.Insert(Value(442, "442", 44.2), 442);
	b_plus_tree.Insert(Value(443, "443", 44.3), 443);
	b_plus_tree.Insert(Value(444, "444", 44.4), 444);
	b_plus_tree.Insert(Value(445, "445", 44.5), 445);
	b_plus_tree.Insert(Value(446, "446", 44.6), 446);
	b_plus_tree.Insert(Value(447, "447", 44.7), 447);
	b_plus_tree.Insert(Value(448, "448", 44.8), 448);
	b_plus_tree.Insert(Value(449, "449", 44.9), 449);
	b_plus_tree.Insert(Value(450, "450", 45), 450);
	b_plus_tree.Insert(Value(451, "451", 45.1), 451);
	b_plus_tree.Insert(Value(452, "452", 45.2), 452);
	b_plus_tree.Insert(Value(453, "453", 45.3), 453);
	b_plus_tree.Insert(Value(454, "454", 45.4), 454);
	b_plus_tree.Insert(Value(455, "455", 45.5), 455);
	b_plus_tree.Insert(Value(456, "456", 45.6), 456);
	b_plus_tree.Insert(Value(457, "457", 45.7), 457);
	b_plus_tree.Insert(Value(458, "458", 45.8), 458);
	b_plus_tree.Insert(Value(459, "459", 45.9), 459);
	b_plus_tree.Insert(Value(460, "460", 46), 460);
	b_plus_tree.Insert(Value(461, "461", 46.1), 461);
	b_plus_tree.Insert(Value(462, "462", 46.2), 462);
	b_plus_tree.Insert(Value(463, "463", 46.3), 463);
	b_plus_tree.Insert(Value(464, "464", 46.4), 464);
	b_plus_tree.Insert(Value(465, "465", 46.5), 465);
	b_plus_tree.Insert(Value(466, "466", 46.6), 466);
	b_plus_tree.Insert(Value(467, "467", 46.7), 467);
	b_plus_tree.Insert(Value(468, "468", 46.8), 468);
	b_plus_tree.Insert(Value(469, "469", 46.9), 469);
	b_plus_tree.Insert(Value(470, "470", 47), 470);
	b_plus_tree.Insert(Value(471, "471", 47.1), 471);
	b_plus_tree.Insert(Value(472, "472", 47.2), 472);
	b_plus_tree.Insert(Value(473, "473", 47.3), 473);
	b_plus_tree.Insert(Value(474, "474", 47.4), 474);
	b_plus_tree.Insert(Value(475, "475", 47.5), 475);
	b_plus_tree.Insert(Value(476, "476", 47.6), 476);
	b_plus_tree.Insert(Value(477, "477", 47.7), 477);
	b_plus_tree.Insert(Value(478, "478", 47.8), 478);
	b_plus_tree.Insert(Value(479, "479", 47.9), 479);
	b_plus_tree.Insert(Value(480, "480", 48), 480);
	b_plus_tree.Insert(Value(481, "481", 48.1), 481);
	b_plus_tree.Insert(Value(482, "482", 48.2), 482);
	b_plus_tree.Insert(Value(483, "483", 48.3), 483);
	b_plus_tree.Insert(Value(484, "484", 48.4), 484);
	b_plus_tree.Insert(Value(485, "485", 48.5), 485);
	b_plus_tree.Insert(Value(486, "486", 48.6), 486);
	b_plus_tree.Insert(Value(487, "487", 48.7), 487);
	b_plus_tree.Insert(Value(488, "488", 48.8), 488);
	b_plus_tree.Insert(Value(489, "489", 48.9), 489);
	b_plus_tree.Insert(Value(490, "490", 49), 490);
	b_plus_tree.Insert(Value(491, "491", 49.1), 491);
	b_plus_tree.Insert(Value(492, "492", 49.2), 492);
	b_plus_tree.Insert(Value(493, "493", 49.3), 493);
	b_plus_tree.Insert(Value(494, "494", 49.4), 494);
	b_plus_tree.Insert(Value(495, "495", 49.5), 495);
	b_plus_tree.Insert(Value(496, "496", 49.6), 496);
	b_plus_tree.Insert(Value(497, "497", 49.7), 497);
	b_plus_tree.Insert(Value(498, "498", 49.8), 498);
	b_plus_tree.Insert(Value(499, "499", 49.9), 499);*/

	Pointer pointer = b_plus_tree.Find(Value(499, "499", 49.9));
	std::cout << pointer.num << std::endl;

	node = b_plus_tree.GetNode(68);
/*	std::cout << *(node.num) << " " << *(node.value_num) << " " << (int)*(node.state) << std::endl;
	for(int i = 0; i < pointer_num - 1; i++) std::cout << node.pointer[i] << " [" << node.value[i] << "] ";
	std::cout << node.pointer[pointer_num - 1] << std::endl;*/

	node = b_plus_tree.GetNode(0);
/*	while(node.pointer[pointer_num - 1].num != -1) {
		std::cout << *node.num << " ";
		node = b_plus_tree.GetNode(node.pointer[pointer_num - 1].num);
	}
	std::cout << *node.num << std::endl;*/

	std::vector<Pointer> p = b_plus_tree.FindFrom(Value(1, "1", 0.1), true);
	for(unsigned int i = 0; i < p.size(); i++)
		std::cout << p[i].num << " ";
	std::cout << std::endl;

	p = b_plus_tree.FindTo(Value(100, "100", 10), true);
	for(unsigned int i = 0; i < p.size(); i++)
		std::cout << p[i].num << " ";
	std::cout << std::endl;

	p = b_plus_tree.FindFromTo(Value(1, "1", 0.1), true, Value(1, "1", 0.1), true);
	for(unsigned int i = 0; i < p.size(); i++)
		std::cout << p[i].num << " ";
	std::cout << std::endl;

	return 0;
}

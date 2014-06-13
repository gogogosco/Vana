--[[
Copyright (C) 2008-2014 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
--]]
-- Gachapon - Victoria Road : Perion

dofile("scripts/utils/gachaponHelper.lua");

-- General rules:
-- Global item chance is significantly reduced
-- All gear for town class; weight derived at 20 / itemLevel
-- 10 random gears between levels 10 and 40 from other town classes; weight derived at 10 / itemLevel
-- All skills for the town class
-- All weapon scrolls for the town class' weapons

commonEquips = {};

warriorEquips = {
	{1002002, ["weight"] = 2.00}, {1002003, ["weight"] = 1.67},
	{1002004, ["weight"] = 0.57}, {1002005, ["weight"] = 0.80},
	{1002007, ["weight"] = 1.33}, {1002009, ["weight"] = 1.00},
	{1002011, ["weight"] = 1.00}, {1002021, ["weight"] = 0.50},
	{1002022, ["weight"] = 0.36}, {1002023, ["weight"] = 0.67},
	{1002024, ["weight"] = 0.43}, {1002025, ["weight"] = 0.50},
	{1002027, ["weight"] = 0.91}, {1002028, ["weight"] = 0.40},
	{1002029, ["weight"] = 0.33}, {1002030, ["weight"] = 0.29},
	{1002039, ["weight"] = 1.67}, {1002040, ["weight"] = 1.67},
	{1002043, ["weight"] = 2.00}, {1002044, ["weight"] = 2.00},
	{1002045, ["weight"] = 0.48}, {1002046, ["weight"] = 0.48},
	{1002047, ["weight"] = 0.57}, {1002048, ["weight"] = 0.57},
	{1002049, ["weight"] = 0.80}, {1002050, ["weight"] = 0.80},
	{1002051, ["weight"] = 1.33}, {1002052, ["weight"] = 1.33},
	{1002055, ["weight"] = 1.00}, {1002056, ["weight"] = 1.00},
	{1002058, ["weight"] = 1.00}, {1002059, ["weight"] = 1.00},
	{1002084, ["weight"] = 0.33}, {1002085, ["weight"] = 0.40},
	{1002086, ["weight"] = 0.40}, {1002087, ["weight"] = 0.91},
	{1002088, ["weight"] = 0.91}, {1002091, ["weight"] = 0.43},
	{1002092, ["weight"] = 0.50}, {1002093, ["weight"] = 0.50},
	{1002094, ["weight"] = 0.29}, {1002095, ["weight"] = 0.29},
	{1002098, ["weight"] = 0.50}, {1002099, ["weight"] = 0.50},
	{1002100, ["weight"] = 0.36}, {1002101, ["weight"] = 0.36},
	{1002338, ["weight"] = 0.25}, {1002339, ["weight"] = 0.25},
	{1002340, ["weight"] = 0.25}, {1002377, ["weight"] = 0.20},
	{1002378, ["weight"] = 0.20}, {1002379, ["weight"] = 0.20},
	{1002528, ["weight"] = 0.22}, {1002529, ["weight"] = 0.22},
	{1002530, ["weight"] = 0.22}, {1002531, ["weight"] = 0.22},
	{1002532, ["weight"] = 0.22}, {1002551, ["weight"] = 0.18},
	{1002578, ["weight"] = 0.57}, {1002776, ["weight"] = 0.17},
	{1002790, ["weight"] = 0.17}, {1040000, ["weight"] = 0.50},
	{1040009, ["weight"] = 1.33}, {1040012, ["weight"] = 1.00},
	{1040015, ["weight"] = 2.00}, {1040016, ["weight"] = 0.80},
	{1040021, ["weight"] = 0.67}, {1040026, ["weight"] = 0.67},
	{1040028, ["weight"] = 0.63}, {1040029, ["weight"] = 0.57},
	{1040030, ["weight"] = 0.57}, {1040037, ["weight"] = 1.33},
	{1040038, ["weight"] = 2.00}, {1040039, ["weight"] = 1.00},
	{1040040, ["weight"] = 0.80}, {1040041, ["weight"] = 0.80},
	{1040085, ["weight"] = 0.50}, {1040086, ["weight"] = 0.50},
	{1040087, ["weight"] = 0.40}, {1040088, ["weight"] = 0.40},
	{1040089, ["weight"] = 0.40}, {1040090, ["weight"] = 0.33},
	{1040091, ["weight"] = 0.33}, {1040092, ["weight"] = 0.33},
	{1040093, ["weight"] = 0.33}, {1040102, ["weight"] = 0.29},
	{1040103, ["weight"] = 0.29}, {1040104, ["weight"] = 0.29},
	{1040111, ["weight"] = 0.22}, {1040112, ["weight"] = 0.22},
	{1040113, ["weight"] = 0.22}, {1040120, ["weight"] = 0.20},
	{1040121, ["weight"] = 0.20}, {1040122, ["weight"] = 0.20},
	{1041014, ["weight"] = 2.00}, {1041019, ["weight"] = 1.00},
	{1041020, ["weight"] = 1.00}, {1041021, ["weight"] = 1.00},
	{1041022, ["weight"] = 0.80}, {1041023, ["weight"] = 0.80},
	{1041024, ["weight"] = 0.80}, {1041064, ["weight"] = 2.00},
	{1041084, ["weight"] = 0.50}, {1041085, ["weight"] = 0.50},
	{1041086, ["weight"] = 0.50}, {1041087, ["weight"] = 0.40},
	{1041088, ["weight"] = 0.40}, {1041089, ["weight"] = 0.40},
	{1041091, ["weight"] = 0.33}, {1041092, ["weight"] = 0.33},
	{1041093, ["weight"] = 0.33}, {1041097, ["weight"] = 0.29},
	{1041098, ["weight"] = 0.29}, {1041099, ["weight"] = 0.29},
	{1041119, ["weight"] = 0.22}, {1041120, ["weight"] = 0.22},
	{1041121, ["weight"] = 0.22}, {1041122, ["weight"] = 0.20},
	{1041123, ["weight"] = 0.20}, {1041124, ["weight"] = 0.20},
	{1050000, ["weight"] = 0.57}, {1050005, ["weight"] = 1.00},
	{1050006, ["weight"] = 1.00}, {1050007, ["weight"] = 1.00},
	{1050011, ["weight"] = 0.67}, {1050021, ["weight"] = 0.57},
	{1050022, ["weight"] = 0.57}, {1050080, ["weight"] = 0.25},
	{1050081, ["weight"] = 0.25}, {1050082, ["weight"] = 0.25},
	{1050083, ["weight"] = 0.25}, {1051000, ["weight"] = 1.33},
	{1051001, ["weight"] = 0.57}, {1051010, ["weight"] = 0.67},
	{1051011, ["weight"] = 0.67}, {1051012, ["weight"] = 0.67},
	{1051013, ["weight"] = 0.67}, {1051014, ["weight"] = 0.57},
	{1051015, ["weight"] = 0.57}, {1051016, ["weight"] = 0.57},
	{1051077, ["weight"] = 0.25}, {1051078, ["weight"] = 0.25},
	{1051079, ["weight"] = 0.25}, {1051080, ["weight"] = 0.25},
	{1052075, ["weight"] = 0.18}, {1052155, ["weight"] = 0.17},
	{1052160, ["weight"] = 0.17}, {1060000, ["weight"] = 0.50},
	{1060008, ["weight"] = 2.00}, {1060009, ["weight"] = 1.33},
	{1060010, ["weight"] = 1.00}, {1060011, ["weight"] = 0.80},
	{1060016, ["weight"] = 0.67}, {1060017, ["weight"] = 0.67},
	{1060018, ["weight"] = 0.67}, {1060019, ["weight"] = 0.67},
	{1060020, ["weight"] = 0.57}, {1060027, ["weight"] = 1.33},
	{1060028, ["weight"] = 2.00}, {1060029, ["weight"] = 1.00},
	{1060030, ["weight"] = 0.80}, {1060060, ["weight"] = 0.80},
	{1060074, ["weight"] = 0.50}, {1060075, ["weight"] = 0.50},
	{1060076, ["weight"] = 0.40}, {1060077, ["weight"] = 0.40},
	{1060078, ["weight"] = 0.40}, {1060079, ["weight"] = 0.33},
	{1060080, ["weight"] = 0.33}, {1060081, ["weight"] = 0.33},
	{1060082, ["weight"] = 0.33}, {1060090, ["weight"] = 0.29},
	{1060091, ["weight"] = 0.29}, {1060092, ["weight"] = 0.29},
	{1060100, ["weight"] = 0.22}, {1060101, ["weight"] = 0.22},
	{1060102, ["weight"] = 0.22}, {1060109, ["weight"] = 0.20},
	{1060110, ["weight"] = 0.20}, {1060111, ["weight"] = 0.20},
	{1061014, ["weight"] = 2.00}, {1061015, ["weight"] = 0.80},
	{1061016, ["weight"] = 1.00}, {1061017, ["weight"] = 1.00},
	{1061018, ["weight"] = 1.00}, {1061019, ["weight"] = 0.80},
	{1061020, ["weight"] = 0.80}, {1061023, ["weight"] = 2.00},
	{1061083, ["weight"] = 0.50}, {1061084, ["weight"] = 0.50},
	{1061085, ["weight"] = 0.50}, {1061086, ["weight"] = 0.40},
	{1061087, ["weight"] = 0.40}, {1061088, ["weight"] = 0.40},
	{1061090, ["weight"] = 0.33}, {1061091, ["weight"] = 0.33},
	{1061092, ["weight"] = 0.33}, {1061096, ["weight"] = 0.29},
	{1061097, ["weight"] = 0.29}, {1061098, ["weight"] = 0.29},
	{1061118, ["weight"] = 0.22}, {1061119, ["weight"] = 0.22},
	{1061120, ["weight"] = 0.22}, {1061121, ["weight"] = 0.20},
	{1061122, ["weight"] = 0.20}, {1061123, ["weight"] = 0.20},
	{1072000, ["weight"] = 0.50}, {1072002, ["weight"] = 0.57},
	{1072003, ["weight"] = 0.67}, {1072007, ["weight"] = 1.00},
	{1072009, ["weight"] = 1.33}, {1072011, ["weight"] = 0.80},
	{1072039, ["weight"] = 0.67}, {1072040, ["weight"] = 0.67},
	{1072041, ["weight"] = 0.67}, {1072046, ["weight"] = 1.00},
	{1072047, ["weight"] = 1.00}, {1072050, ["weight"] = 1.33},
	{1072051, ["weight"] = 0.80}, {1072052, ["weight"] = 0.80},
	{1072053, ["weight"] = 0.80}, {1072112, ["weight"] = 0.57},
	{1072113, ["weight"] = 0.57}, {1072126, ["weight"] = 0.50},
	{1072127, ["weight"] = 0.50}, {1072132, ["weight"] = 0.40},
	{1072133, ["weight"] = 0.40}, {1072134, ["weight"] = 0.40},
	{1072135, ["weight"] = 0.40}, {1072147, ["weight"] = 0.33},
	{1072148, ["weight"] = 0.33}, {1072149, ["weight"] = 0.33},
	{1072154, ["weight"] = 0.29}, {1072155, ["weight"] = 0.29},
	{1072156, ["weight"] = 0.29}, {1072168, ["weight"] = 0.67},
	{1072196, ["weight"] = 0.22}, {1072197, ["weight"] = 0.22},
	{1072198, ["weight"] = 0.22}, {1072210, ["weight"] = 0.25},
	{1072211, ["weight"] = 0.25}, {1072212, ["weight"] = 0.25},
	{1072220, ["weight"] = 0.20}, {1072221, ["weight"] = 0.20},
	{1072222, ["weight"] = 0.20}, {1072273, ["weight"] = 0.18},
	{1072355, ["weight"] = 0.17}, {1072361, ["weight"] = 0.17},
	{1082000, ["weight"] = 1.33}, {1082001, ["weight"] = 0.80},
	{1082003, ["weight"] = 2.00}, {1082004, ["weight"] = 1.00},
	{1082005, ["weight"] = 0.67}, {1082006, ["weight"] = 0.67},
	{1082007, ["weight"] = 0.67}, {1082008, ["weight"] = 0.57},
	{1082009, ["weight"] = 0.40}, {1082010, ["weight"] = 0.40},
	{1082011, ["weight"] = 0.40}, {1082023, ["weight"] = 0.50},
	{1082024, ["weight"] = 0.50}, {1082025, ["weight"] = 0.50},
	{1082035, ["weight"] = 0.57}, {1082036, ["weight"] = 0.57},
	{1082059, ["weight"] = 0.33}, {1082060, ["weight"] = 0.33},
	{1082061, ["weight"] = 0.33}, {1082103, ["weight"] = 0.29},
	{1082104, ["weight"] = 0.29}, {1082105, ["weight"] = 0.29},
	{1082114, ["weight"] = 0.25}, {1082115, ["weight"] = 0.25},
	{1082116, ["weight"] = 0.25}, {1082117, ["weight"] = 0.25},
	{1082128, ["weight"] = 0.22}, {1082129, ["weight"] = 0.22},
	{1082130, ["weight"] = 0.22}, {1082139, ["weight"] = 0.20},
	{1082140, ["weight"] = 0.20}, {1082141, ["weight"] = 0.20},
	{1082168, ["weight"] = 0.18}, {1082218, ["weight"] = 0.29},
	{1082234, ["weight"] = 0.17}, {1082239, ["weight"] = 0.17},
	{1092000, ["weight"] = 1.33}, {1092001, ["weight"] = 0.80},
	{1092002, ["weight"] = 0.67}, {1092004, ["weight"] = 0.40},
	{1092005, ["weight"] = 2.00}, {1092006, ["weight"] = 1.00},
	{1092007, ["weight"] = 0.57}, {1092009, ["weight"] = 0.33},
	{1092010, ["weight"] = 0.33}, {1092011, ["weight"] = 0.33},
	{1092012, ["weight"] = 0.50}, {1092013, ["weight"] = 0.50},
	{1092014, ["weight"] = 0.50}, {1092015, ["weight"] = 0.29},
	{1092016, ["weight"] = 0.29}, {1092017, ["weight"] = 0.29},
	{1092023, ["weight"] = 0.25}, {1092024, ["weight"] = 0.25},
	{1092025, ["weight"] = 0.25}, {1092026, ["weight"] = 0.22},
	{1092027, ["weight"] = 0.22}, {1092028, ["weight"] = 0.22},
	{1092036, ["weight"] = 0.20}, {1092037, ["weight"] = 0.20},
	{1092038, ["weight"] = 0.20}, {1092058, ["weight"] = 0.17},
	{1092060, ["weight"] = 0.18}, {1092061, ["weight"] = 0.20},
	{1302002, ["weight"] = 1.00}, {1302004, ["weight"] = 0.57},
	{1302005, ["weight"] = 1.33}, {1302008, ["weight"] = 0.67},
	{1302009, ["weight"] = 0.50}, {1302010, ["weight"] = 0.40},
	{1302011, ["weight"] = 0.33}, {1302012, ["weight"] = 0.29},
	{1302015, ["weight"] = 0.44}, {1302018, ["weight"] = 0.25},
	{1302019, ["weight"] = 0.44}, {1302023, ["weight"] = 0.22},
	{1302037, ["weight"] = 0.32}, {1302056, ["weight"] = 0.20},
	{1302059, ["weight"] = 0.18}, {1302068, ["weight"] = 0.44},
	{1302079, ["weight"] = 0.29}, {1302081, ["weight"] = 0.17},
	{1302086, ["weight"] = 0.17}, {1302114, ["weight"] = 0.17},
	{1312001, ["weight"] = 1.33}, {1312003, ["weight"] = 0.80},
	{1312005, ["weight"] = 0.67}, {1312006, ["weight"] = 0.57},
	{1312007, ["weight"] = 0.50}, {1312008, ["weight"] = 0.40},
	{1312009, ["weight"] = 0.33}, {1312010, ["weight"] = 0.29},
	{1312011, ["weight"] = 0.25}, {1312015, ["weight"] = 0.22},
	{1312016, ["weight"] = 1.00}, {1312030, ["weight"] = 0.20},
	{1312031, ["weight"] = 0.18}, {1312037, ["weight"] = 0.17},
	{1312038, ["weight"] = 0.17}, {1312044, ["weight"] = 0.17},
	{1322014, ["weight"] = 0.67}, {1322015, ["weight"] = 0.57},
	{1322016, ["weight"] = 0.50}, {1322017, ["weight"] = 0.40},
	{1322018, ["weight"] = 0.33}, {1322019, ["weight"] = 0.29},
	{1322020, ["weight"] = 0.27}, {1322028, ["weight"] = 0.25},
	{1322029, ["weight"] = 0.22}, {1322045, ["weight"] = 0.20},
	{1322052, ["weight"] = 0.18}, {1322059, ["weight"] = 0.29},
	{1322060, ["weight"] = 0.17}, {1322061, ["weight"] = 0.17},
	{1322062, ["weight"] = 0.17}, {1322072, ["weight"] = 0.17},
	{1402000, ["weight"] = 1.00}, {1402002, ["weight"] = 0.67},
	{1402003, ["weight"] = 0.40}, {1402004, ["weight"] = 0.25},
	{1402005, ["weight"] = 0.22}, {1402006, ["weight"] = 0.57},
	{1402007, ["weight"] = 0.50}, {1402008, ["weight"] = 0.80},
	{1402011, ["weight"] = 0.33}, {1402012, ["weight"] = 0.29},
	{1402015, ["weight"] = 0.25}, {1402016, ["weight"] = 0.22},
	{1402017, ["weight"] = 0.31}, {1402018, ["weight"] = 1.33},
	{1402035, ["weight"] = 0.20}, {1402036, ["weight"] = 0.18},
	{1402037, ["weight"] = 0.20}, {1402046, ["weight"] = 0.17},
	{1402047, ["weight"] = 0.17}, {1402048, ["weight"] = 0.25},
	{1402049, ["weight"] = 0.22}, {1402050, ["weight"] = 0.22},
	{1402051, ["weight"] = 0.25}, {1402061, ["weight"] = 0.17},
	{1412000, ["weight"] = 0.80}, {1412002, ["weight"] = 1.00},
	{1412003, ["weight"] = 0.40}, {1412004, ["weight"] = 0.57},
	{1412005, ["weight"] = 0.50}, {1412006, ["weight"] = 0.67},
	{1412007, ["weight"] = 0.33}, {1412008, ["weight"] = 0.29},
	{1412009, ["weight"] = 0.25}, {1412010, ["weight"] = 0.22},
	{1412012, ["weight"] = 1.33}, {1412021, ["weight"] = 0.20},
	{1412026, ["weight"] = 0.18}, {1412032, ["weight"] = 0.29},
	{1412033, ["weight"] = 0.17}, {1412034, ["weight"] = 0.17},
	{1412040, ["weight"] = 0.22}, {1412041, ["weight"] = 0.17},
	{1422001, ["weight"] = 0.67}, {1422002, ["weight"] = 1.33},
	{1422003, ["weight"] = 1.00}, {1422005, ["weight"] = 0.40},
	{1422007, ["weight"] = 0.50}, {1422008, ["weight"] = 0.57},
	{1422009, ["weight"] = 0.33}, {1422010, ["weight"] = 0.29},
	{1422012, ["weight"] = 0.25}, {1422013, ["weight"] = 0.22},
	{1422027, ["weight"] = 0.20}, {1422028, ["weight"] = 0.18},
	{1422030, ["weight"] = 0.19}, {1422031, ["weight"] = 0.19},
	{1422037, ["weight"] = 0.17}, {1422038, ["weight"] = 0.17},
	{1422044, ["weight"] = 0.17}, {1432002, ["weight"] = 0.67},
	{1432003, ["weight"] = 0.57}, {1432004, ["weight"] = 0.40},
	{1432005, ["weight"] = 0.50}, {1432006, ["weight"] = 0.33},
	{1432007, ["weight"] = 0.29}, {1432010, ["weight"] = 0.25},
	{1432011, ["weight"] = 0.22}, {1432030, ["weight"] = 0.20},
	{1432038, ["weight"] = 0.18}, {1432045, ["weight"] = 0.29},
	{1432047, ["weight"] = 0.17}, {1432048, ["weight"] = 0.19},
	{1432049, ["weight"] = 0.17}, {1432056, ["weight"] = 0.20},
	{1442001, ["weight"] = 0.67}, {1442002, ["weight"] = 0.17},
	{1442003, ["weight"] = 0.57}, {1442005, ["weight"] = 0.40},
	{1442006, ["weight"] = 1.33}, {1442007, ["weight"] = 1.00},
	{1442008, ["weight"] = 0.29}, {1442009, ["weight"] = 0.50},
	{1442010, ["weight"] = 0.33}, {1442019, ["weight"] = 0.25},
	{1442020, ["weight"] = 0.22}, {1442044, ["weight"] = 0.20},
	{1442045, ["weight"] = 0.18}, {1442060, ["weight"] = 0.29},
	{1442063, ["weight"] = 0.17}, {1442067, ["weight"] = 0.17},
};

magicianEquips = {
	{1002075, ["weight"] = 1.00}, {1050035, ["weight"] = 0.26},
	{1002151, ["weight"] = 0.25}, {1051023, ["weight"] = 0.26},
	{1072089, ["weight"] = 0.29}, {1072115, ["weight"] = 0.25},
	{1072076, ["weight"] = 0.33}, {1040018, ["weight"] = 0.56},
	{1382017, ["weight"] = 0.33}, {1072072, ["weight"] = 0.40},
};

bowmanEquips = {
	{1040011, ["weight"] = 0.67}, {1041061, ["weight"] = 1.00},
	{1040076, ["weight"] = 0.29}, {1040003, ["weight"] = 0.50},
	{1072059, ["weight"] = 1.00}, {1082017, ["weight"] = 0.40},
	{1002114, ["weight"] = 0.67}, {1041066, ["weight"] = 0.29},
	{1060057, ["weight"] = 0.33}, {1040007, ["weight"] = 0.67},
};

thiefEquips = {
	{1072032, ["weight"] = 0.33}, {1472011, ["weight"] = 0.29},
	{1082037, ["weight"] = 0.40}, {1040059, ["weight"] = 0.33},
	{1040084, ["weight"] = 0.25}, {1040043, ["weight"] = 0.50},
	{1072085, ["weight"] = 0.40}, {1040031, ["weight"] = 1.00},
	{1332031, ["weight"] = 0.25}, {1082075, ["weight"] = 0.25},
};

pirateEquips = {
	{1482001, ["weight"] = 0.67}, {1492002, ["weight"] = 0.50},
	{1052113, ["weight"] = 0.25}, {1002616, ["weight"] = 0.50},
	{1072294, ["weight"] = 0.33}, {1492004, ["weight"] = 0.33},
	{1482006, ["weight"] = 0.25}, {1082192, ["weight"] = 0.29},
	{1082189, ["weight"] = 0.33}, {1082195, ["weight"] = 0.25},
};

scrolls = {
	2043000, 2043001, 2043002, 2043004, 2043005, 2043006, 2043007, 2043008, 2043009, 2043010,
	2043015, 2043017, 2043019, 2044000, 2044001, 2044002, 2044004, 2044005, 2044010, 2044012,
	2044014, 2043200, 2043201, 2043202, 2043204, 2043205, 2043210, 2043212, 2043214, 2044200,
	2044201, 2044202, 2044204, 2044205, 2044210, 2044212, 2044214, 2044300, 2044301, 2044302,
	2044304, 2044305, 2044310, 2044312, 2044314, 2044400, 2044401, 2044402, 2044404, 2044405,
	2044410, 2044412, 2044414,
};

skills = {
	{2290000, ["weight"] = mastery_book_20}, {2290001, ["weight"] = mastery_book_30},
	{2290002, ["weight"] = mastery_book_20}, {2290003, ["weight"] = mastery_book_30},
	{2290004, ["weight"] = mastery_book_20}, {2290005, ["weight"] = mastery_book_30},
	{2290006, ["weight"] = mastery_book_20}, {2290007, ["weight"] = mastery_book_30},
	{2290008, ["weight"] = mastery_book_20}, {2290009, ["weight"] = mastery_book_30},
	{2290010, ["weight"] = mastery_book_20}, {2290011, ["weight"] = mastery_book_30},
	{2290012, ["weight"] = mastery_book_20}, {2290013, ["weight"] = mastery_book_30},
	{2290014, ["weight"] = mastery_book_20}, {2290015, ["weight"] = mastery_book_30},
	{2290016, ["weight"] = mastery_book_20}, {2290017, ["weight"] = mastery_book_30},
	{2290018, ["weight"] = mastery_book_20},
	{2290019, ["weight"] = mastery_book_20},
	{2290020, ["weight"] = mastery_book_20}, {2290021, ["weight"] = mastery_book_30},
	{2290022, ["weight"] = mastery_book_20}, {2290023, ["weight"] = mastery_book_30},
};

items = merge(commonEquips, warriorEquips, magicianEquips, bowmanEquips, thiefEquips, pirateEquips, scrolls, skills);

gachapon({
	["items"] = items,
	-- Decrease the chance of getting things from the global item list
	["globalItemWeightModifier"] = .5,
});
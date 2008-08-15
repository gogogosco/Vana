/*
Copyright (C) 2008 Vana Development Team

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
*/
#ifndef QUESTS_H
#define QUESTS_H

#include <vector>
#include <unordered_map>

using std::vector;
using std::tr1::unordered_map;

class Player;
class ReadPacket;

struct QuestRequestInfo {
	bool ismob;
	bool isitem;
	bool isquest;
	int id;
	short count;
};

typedef vector <QuestRequestInfo> QuestRequestsInfo;


struct QuestRewardInfo {
	bool start;
	bool ismesos;
	bool isitem;
	bool isexp;
	bool isfame;
	bool isskill;
	int id;
	short count;
	char gender;
	char job;
	char prop;
};

typedef vector <QuestRewardInfo> QuestRewardsInfo;

struct QuestInfo {
	QuestRequestsInfo requests;
	QuestRewardsInfo rewards;
	int nextquest;
};

struct QuestComp {
	int id;
	__int64 time;
};

struct QuestMob {
	int id;
	int count;
};

struct Quest {
	int id;
	bool done;
	vector <QuestMob> mobs;
};

namespace Quests {
	extern unordered_map<int, QuestInfo> quests;
	void addRequest(int id, QuestRequestsInfo request);
	void addReward(int id, QuestRewardsInfo raws);
	void setNextQuest(int id, int questid);
	void getQuest(Player *player, ReadPacket *packet);
	bool giveItem(Player *player, int itemid, int amount);
	bool giveMesos(Player *player, int amount);
};

#endif

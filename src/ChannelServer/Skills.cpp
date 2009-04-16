/*
Copyright (C) 2008-2009 Vana Development Team

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
#include "Skills.h"
#include "Buffs.h"
#include "GameConstants.h"
#include "GameLogicUtilities.h"
#include "Inventory.h"
#include "MapPacket.h"
#include "Maps.h"
#include "PacketReader.h"
#include "Party.h"
#include "Player.h"
#include "Players.h"
#include "Randomizer.h"
#include "SkillsPacket.h"
#include "Summons.h"
#include "Timer/Time.h"
#include "Timer/Timer.h"
#include <functional>

using std::tr1::bind;

unordered_map<int32_t, SkillsLevelInfo> Skills::skills;
unordered_map<int32_t, uint8_t> Skills::maxlevels;
unordered_map<uint8_t, MobSkillsLevelInfo> Skills::mobskills;

void Skills::addSkillLevelInfo(int32_t skillid, uint8_t level, SkillLevelInfo levelinfo) {
	skills[skillid][level] = levelinfo;

	if (maxlevels.find(skillid) == maxlevels.end() || maxlevels[skillid] < level) {
		maxlevels[skillid] = level;
	}
}

void Skills::addMobSkillLevelInfo(uint8_t skillid, uint8_t level, MobSkillLevelInfo levelinfo) {
	mobskills[skillid][level] = levelinfo;
}

void Skills::addSkill(Player *player, PacketReader &packet) {
	packet.skipBytes(4);
	int32_t skillid = packet.get<int32_t>();
	if (!GameLogicUtilities::isBeginnerSkill(skillid)) {
		if (player->getSp() == 0) {
			// hacking
			return;
		}
		if (!player->isGm() && ((skillid / 1000000 != player->getJob() / 100) || (skillid / 10000 > player->getJob()))) {
			// hacking
			return;
		}
	}
	if (player->getSkills()->addSkillLevel(skillid, 1) && !GameLogicUtilities::isBeginnerSkill(skillid)) {
		player->setSp(player->getSp() - 1);
	}
}

void Skills::cancelSkill(Player *player, PacketReader &packet) {
	stopSkill(player, packet.get<int32_t>());
}

void Skills::stopSkill(Player *player, int32_t skillid, bool fromTimer) {
	switch (skillid) {
		case Jobs::Bowmaster::Hurricane:
		case Jobs::Marksman::PiercingArrow:
		case Jobs::FPArchMage::BigBang:
		case Jobs::ILArchMage::BigBang:
		case Jobs::Bishop::BigBang:
		case Jobs::Corsair::RapidFire: // Special skills like hurricane, monster magnet, rapid fire, and etc
			SkillsPacket::endSpecialSkill(player, player->getSpecialSkillInfo());
			player->setSpecialSkill(SpecialSkillInfo());
			break;
		default:
			if (skillid == Jobs::SuperGm::Hide) // GM Hide
				MapPacket::showPlayer(player);
			player->getActiveBuffs()->removeBuff(skillid, fromTimer);
			Buffs::Instance()->endBuff(player, skillid);
			break;
	}
}

const vector<Player *> Skills::getAffectedPartyMembers(Party *party, int8_t affected, int8_t members) {
	vector<Player *> ret;
	if (affected & GameLogicUtilities::getPartyMember1(members))
		ret.push_back(party->getMemberByIndex(1));
	if (affected & GameLogicUtilities::getPartyMember2(members))
		ret.push_back(party->getMemberByIndex(2));
	if (affected & GameLogicUtilities::getPartyMember3(members))
		ret.push_back(party->getMemberByIndex(3));
	if (affected & GameLogicUtilities::getPartyMember4(members))
		ret.push_back(party->getMemberByIndex(4));
	if (affected & GameLogicUtilities::getPartyMember5(members))
		ret.push_back(party->getMemberByIndex(5));
	if (affected & GameLogicUtilities::getPartyMember6(members))
		ret.push_back(party->getMemberByIndex(6));
	return ret;
}

void Skills::useSkill(Player *player, PacketReader &packet) {
	packet.skipBytes(4); // Ticks
	int32_t skillid = packet.get<int32_t>();
	int16_t addedinfo = 0;
	uint8_t level = packet.get<int8_t>();
	uint8_t type = 0;
	uint8_t direction = 0;
	if (level == 0 || player->getSkills()->getSkillLevel(skillid) != level) {
		// hacking
		return;
	}
	switch (skillid) {
		case Jobs::Corsair::Battleship:
			if (player->getActiveBuffs()->getBattleshipHp() == 0)
				player->getActiveBuffs()->resetBattleshipHp();
			break;
		case Jobs::Hero::MonsterMagnet:
		case Jobs::Paladin::MonsterMagnet:
		case Jobs::DarkKnight::MonsterMagnet: {
			int32_t mobs = packet.get<int32_t>();
			for (int8_t k = 0; k < mobs; k++) {
				int32_t mapmobid = packet.get<int32_t>();
				uint8_t success = packet.get<int8_t>();
				SkillsPacket::showMagnetSuccess(player, mapmobid, success);
			}
			direction = packet.get<uint8_t>();
			break;
		}
		case Jobs::Page::Threaten:
		case Jobs::FPWizard::Slow:
		case Jobs::ILWizard::Slow:
		case Jobs::FPMage::Seal:
		case Jobs::ILMage::Seal:
		case Jobs::Priest::Doom:
		case Jobs::Hermit::ShadowWeb: {
			uint8_t mobs = packet.get<int8_t>();
			for (uint8_t k = 0; k < mobs; k++) {
				if (Mob *mob = Maps::getMap(player->getMap())->getMob(packet.get<int32_t>())) {
					Mobs::handleMobStatus(player, mob, skillid, 0);
				}
			}
			break;
		}
		case Jobs::Cleric::Heal: { // Heal
			uint16_t healrate = skills[skillid][level].hpP;
			if (healrate > 100)
				healrate = 100;
			player->modifyHp(healrate * player->getMHp() / 100);
			break;
		}
		case Jobs::Fighter::Rage:
		case Jobs::Spearman::IronWill:
		case Jobs::Spearman::HyperBody:
		case Jobs::FPWizard::Meditation:
		case Jobs::ILWizard::Meditation:
		case Jobs::Cleric::Bless:
		case Jobs::Priest::HolySymbol:
		case Jobs::Bishop::Resurrection:
		case Jobs::Bowmaster::SharpEyes:
		case Jobs::Marksman::SharpEyes:
		case Jobs::Assassin::Haste:
		case Jobs::Hermit::MesoUp:
		case Jobs::Bandit::Haste:
		case Jobs::Buccaneer::SpeedInfusion:
		case Jobs::Buccaneer::TimeLeap: 
		case Jobs::Hero::MapleWarrior:
		case Jobs::Paladin::MapleWarrior:
		case Jobs::DarkKnight::MapleWarrior:
		case Jobs::FPArchMage::MapleWarrior:
		case Jobs::ILArchMage::MapleWarrior:
		case Jobs::Bishop::MapleWarrior:
		case Jobs::Bowmaster::MapleWarrior:
		case Jobs::Marksman::MapleWarrior:
		case Jobs::NightLord::MapleWarrior:
		case Jobs::Shadower::MapleWarrior:
		case Jobs::Buccaneer::MapleWarrior:
		case Jobs::Corsair::MapleWarrior: {
			Party *party = player->getParty();
			if (skillid == Jobs::Buccaneer::TimeLeap)
				player->removeAllCooldowns();
			if (party != 0) {
				int8_t affected = packet.get<int8_t>();
				int8_t pmembers = party->getMembersCount();
				vector<Player *> members = getAffectedPartyMembers(party, affected, pmembers);
				for (size_t i = 0; i < members.size(); i++) {
					Player *cmem = members[i];
					if (cmem != 0 && cmem != player && cmem->getMap() == player->getMap()) {
						SkillsPacket::showSkill(cmem, skillid, level, direction, true, true);
						SkillsPacket::showSkill(cmem, skillid, level, direction, true);
						Buffs::Instance()->addBuff(cmem, skillid, level, addedinfo);
						if (skillid == Jobs::Buccaneer::TimeLeap)
							cmem->removeAllCooldowns();
					}
				}
			}
			break;
		}
		case Jobs::Beginner::EchoOfHero:
		case Jobs::SuperGm::HealPlusDispel:
		case Jobs::SuperGm::Haste:
		case Jobs::SuperGm::HolySymbol:
		case Jobs::SuperGm::Bless:
		case Jobs::SuperGm::Resurrection:
		case Jobs::SuperGm::HyperBody: {
			uint8_t players = packet.get<int8_t>();
			for (uint8_t i = 0; i < players; i++) {
				int32_t playerid = packet.get<int32_t>();
				Player *target = Players::Instance()->getPlayer(playerid);
				if (target != 0 && target != player) { // ???
					SkillsPacket::showSkill(target, skillid, level, direction, true, true);
					SkillsPacket::showSkill(target, skillid, level, direction, true);
					Buffs::Instance()->addBuff(target, skillid, level, addedinfo);
					if (skillid == Jobs::SuperGm::Resurrection)
						target->setHp(target->getMHp());
					else if (skillid == Jobs::SuperGm::HealPlusDispel) {
						target->setHp(target->getMHp());
						target->setMp(target->getMMp());
					}
				}
			}
			break;
		}
		case Jobs::SuperGm::Hide:
			MapPacket::removePlayer(player);
			break;
		default:
			type = packet.get<int8_t>();
			switch (type) {
				case 0x80:
					addedinfo = packet.get<int16_t>();
					break;
			}
			break;
	}
	applySkillCosts(player, skillid, level);
	if (skillid != Jobs::Cleric::Heal)
		SkillsPacket::showSkill(player, skillid, level, direction);
	if (Buffs::Instance()->addBuff(player, skillid, level, addedinfo))
		return;
	else if (GameLogicUtilities::isSummon(skillid))
		Summons::useSummon(player, skillid, level);
}

void Skills::applySkillCosts(Player *player, int32_t skillid, uint8_t level, bool elementalamp) {
	int16_t cooltime = skills[skillid][level].cooltime;
	int16_t mpuse = skills[skillid][level].mp;
	int16_t hpuse = skills[skillid][level].hp;
	int16_t moneycon = skills[skillid][level].moneycon;
	int32_t item = skills[skillid][level].item;
	if (mpuse > 0) {
		if (player->getActiveBuffs()->getActiveSkillLevel(Jobs::Bowmaster::Concentrate) > 0) { // Reduced MP usage for Concentration
			int16_t mprate = skills[Jobs::Bowmaster::Concentrate][player->getActiveBuffs()->getActiveSkillLevel(Jobs::Bowmaster::Concentrate)].x;
			int16_t mploss = (mpuse * mprate) / 100;
			player->modifyMp(-mploss, true);
		}
		else {
			if (elementalamp) {
				int32_t sid = ((player->getJob() / 10) == 22 ? (int32_t)Jobs::ILMage::ElementAmplification : (int32_t)Jobs::FPMage::ElementAmplification);
				int8_t slv = player->getSkills()->getSkillLevel(sid);
				if (slv > 0)
					player->modifyMp(-1 * (mpuse * skills[sid][slv].x / 100), true);
				else
					player->modifyMp(-mpuse, true);
			}
			else
				player->modifyMp(-mpuse, true);
		}
	}
	else
		player->setMp(player->getMp(), true);
	if (hpuse > 0)
		player->modifyHp(-hpuse);
	if (item > 0)
		Inventory::takeItem(player, item, skills[skillid][level].itemcount);
	if (cooltime > 0 && skillid != Jobs::Corsair::Battleship)
		startCooldown(player, skillid, cooltime);
	if (moneycon > 0) {
		int16_t mesos_min = moneycon - (80 + level * 5);
		int16_t mesos_max = moneycon + (80 + level * 5);
		int16_t difference = mesos_max - mesos_min; // Randomize up to this, add minimum for range
		int16_t amount = Randomizer::Instance()->randShort(difference) + mesos_min;
		int32_t mesos = player->getInventory()->getMesos();
		if (mesos - amount > -1)
			player->getInventory()->modifyMesos(-amount);
		else {
			// Hacking
			return;
		}
	}
}

void Skills::useAttackSkill(Player *player, int32_t skillid) {
	uint8_t level = player->getSkills()->getSkillLevel(skillid);
	if (skills.find(skillid) == skills.end() || level == 0)
		return;
	applySkillCosts(player, skillid, level, true);
}

void Skills::useAttackSkillRanged(Player *player, int32_t skillid, int16_t pos, uint8_t display) {
	uint8_t level = 0;
	if (skillid != 0) {
		level = player->getSkills()->getSkillLevel(skillid);
		if (skills.find(skillid) == skills.end() || level == 0)
			return;
		applySkillCosts(player, skillid, level);
	}
	uint16_t hits = 1;
	if (skills[skillid][level].bulletcon > 0)
		hits = skills[skillid][level].bulletcon;
	if (display == 0x08)
		hits = hits * 2;
	if (pos > 0 && (!((display & 0x40) == 0x40 || display == 0x02)))
		// Display is 0x40 for Shadow Claw and 0x48 for Shadow Claw + Shadow Partner
		// Bitwise and with 0x40 will make it 0x40 for both
		Inventory::takeItemSlot(player, 2, pos, hits);
}

void Skills::heal(Player *player, int16_t value, int32_t skillid) {
	if (player->getHp() < player->getMHp() && player->getHp() > 0) {
		player->modifyHp(value);
		SkillsPacket::healHP(player, value);
	}
}

void Skills::hurt(Player *player, int16_t value, int32_t skillid) {
	if (player->getHp() - value > 1) {
		player->modifyHp(-value);
		SkillsPacket::showSkillEffect(player, skillid);
	}
	else {
		Buffs::Instance()->endBuff(player, skillid);
	}
}

void Skills::startCooldown(Player *player, int32_t skillid, int16_t cooltime, bool sendpacket) {
	if (isCooling(player, skillid)) {
		// Hacking
		return;
	}
	if (sendpacket)
		SkillsPacket::sendCooldown(player, skillid, cooltime);

	player->addCooldown(skillid, cooltime);

	new Timer::Timer(bind(&Skills::stopCooldown, player, skillid),
		Timer::Id(Timer::Types::CoolTimer, skillid, 0),
		player->getTimers(), Timer::Time::fromNow(cooltime * 1000));
}

void Skills::stopCooldown(Player *player, int32_t skillid) {
	player->removeCooldown(skillid);
	SkillsPacket::sendCooldown(player, skillid, 0);
	if (skillid == Jobs::Corsair::Battleship) {
		player->getActiveBuffs()->resetBattleshipHp();
	}

	Timer::Id id(Timer::Types::CoolTimer, skillid, 0);
	if (player->getTimers()->checkTimer(id) > 0) {
		player->getTimers()->removeTimer(id);
	}
}

bool Skills::isCooling(Player *player, int32_t skillid) {
	Timer::Id id(Timer::Types::CoolTimer, skillid, 0);
	return player->getTimers()->checkTimer(id) > 0;
}

int16_t Skills::getCooldownTimeLeft(Player *player, int32_t skillid) {
	int16_t cooltime = 0;
	if (isCooling(player, skillid)) {
		Timer::Id id(Timer::Types::CoolTimer, skillid, 0);
		cooltime = static_cast<int16_t>(player->getTimers()->checkTimer(id) / 1000);
	}
	return cooltime;
}
/*
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
*/
#pragma once

#include "AbstractConnection.hpp"
#include "MovableLife.hpp"
#include "Npc.hpp"
#include "PlayerActiveBuffs.hpp"
#include "PlayerBuddyList.hpp"
#include "PlayerInventory.hpp"
#include "PlayerMonsterBook.hpp"
#include "PlayerMounts.hpp"
#include "PlayerPets.hpp"
#include "PlayerQuests.hpp"
#include "PlayerSkills.hpp"
#include "PlayerStats.hpp"
#include "PlayerStorage.hpp"
#include "PlayerSummons.hpp"
#include "PlayerVariables.hpp"
#include "SkillDataProvider.hpp"
#include "TauswortheGenerator.hpp"
#include <ctime>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

class Instance;
class Map;
class PacketBuilder;
class PacketReader;
class Party;
struct PortalInfo;
struct SplitPacketBuilder;

class Player : public AbstractConnection, public MovableLife {
	NONCOPYABLE(Player);
public:
	Player();
	~Player();

	auto setGmChat(bool chat) -> void { m_gmChat = chat; }
	auto setSaveOnDc(bool save) -> void { m_saveOnDc = save; }
	auto setTrading(bool state) -> void { m_tradeState = state; }
	auto setChangingChannel(bool v) -> void { m_changingChannel = v; }
	auto setSkin(int8_t id) -> void;
	auto setFallCounter(int8_t falls) -> void { m_fallCounter = falls; }
	auto setMapChair(int16_t s) -> void { m_mapChair = s; }
	auto setEyes(int32_t id) -> void;
	auto setHair(int32_t id) -> void;
	auto setMap(int32_t mapId, PortalInfo *portal = nullptr, bool instance = false) -> void;
	auto setBuddyListSize(uint8_t size) -> void;
	auto setConnectionTime(int64_t newtime) -> void { m_onlineTime = newtime; }
	auto setTradeId(int32_t id) -> void { m_tradeId = id; }
	auto setShop(int32_t shopId) -> void { m_shop = shopId; }
	auto setChair(int32_t chair) -> void { m_chair = chair; }
	auto setItemEffect(int32_t effect) -> void { m_itemEffect = effect; }
	auto setChalkboard(const string_t &msg) -> void { m_chalkboard = msg; }
	auto setChargeOrStationarySkill(const ChargeOrStationarySkillInfo &info) -> void { m_info = info; }
	auto setNpc(Npc *npc) -> void { m_npc.reset(npc); }
	auto setParty(Party *party) -> void { m_party = party; }
	auto setFollow(Player *target) -> void { m_follow = target; }
	auto setInstance(Instance *instance) -> void { m_instance = instance; }
	auto parseTransferPacket(PacketReader &reader) -> void;

	auto isGm() const -> bool { return m_gmLevel > 0; }
	auto isGmChat() const -> bool { return m_gmChat; }
	auto isAdmin() const -> bool { return m_admin; }
	auto isChangingChannel() const -> bool { return m_changingChannel; }
	auto isTrading() const -> bool { return m_tradeState; }
	auto isDisconnecting() const -> bool { return m_disconnecting; }
	auto hasGmEquip() const -> bool;
	auto isUsingGmHide() const -> bool;
	auto hasGmBenefits() const -> bool;
	auto hasChargeOrStationarySkill() const -> bool { return m_info.skillId != 0; }
	auto getWorldId() const -> world_id_t { return m_worldId; }
	auto getGender() const -> int8_t { return m_gender; }
	auto getSkin() const -> int8_t { return m_skin; }
	auto getMapPos() const -> int8_t { return m_mapPos; }
	auto getFallCounter() const -> int8_t { return m_fallCounter; }
	auto getBuddyListSize() const -> uint8_t { return m_buddylistSize; }
	auto getPortalCount(bool add = false) -> uint8_t;
	auto getMapChair() const -> int16_t { return m_mapChair; }
	auto getId() const -> int32_t { return m_id; }
	auto getUserId() const -> int32_t { return m_userId; }
	auto getEyes() const -> int32_t { return m_eyes; }
	auto getHair() const -> int32_t { return m_hair; }
	auto getMapId() const -> int32_t { return m_map; }
	auto getLastMapId() const -> int32_t { return m_lastMap; }
	auto getShop() const -> int32_t { return m_shop; }
	auto getChair() const -> int32_t { return m_chair; }
	auto getItemEffect() const -> int32_t { return m_itemEffect; }
	auto getGmLevel() const -> int32_t { return m_gmLevel; }
	auto getTradeId() const -> int32_t { return m_tradeId; }
	auto getConnectionTime() const -> int64_t { return m_onlineTime; }
	auto getConnectedTime() const -> int64_t { return time(nullptr) - m_onlineTime; }
	auto getChalkboard() const -> string_t { return m_chalkboard; }
	auto getMedalName() -> string_t;
	auto getName() const -> string_t { return m_name; }
	auto getChargeOrStationarySkillInfo() const -> ChargeOrStationarySkillInfo { return m_info; }
	auto getTransferPacket() const -> PacketBuilder;

	auto getMap() const -> Map *;
	auto getFollow() const -> Player * { return m_follow; }
	auto getNpc() const -> Npc * { return m_npc.get(); }
	auto getParty() const -> Party * { return m_party; }
	auto getInstance() const -> Instance * { return m_instance; }
	auto getActiveBuffs() const -> PlayerActiveBuffs * { return m_activeBuffs.get(); }
	auto getBuddyList() const -> PlayerBuddyList * { return m_buddyList.get(); }
	auto getInventory() const -> PlayerInventory * { return m_inventory.get(); }
	auto getMonsterBook() const -> PlayerMonsterBook * { return m_monsterBook.get(); }
	auto getMounts() const -> PlayerMounts * { return m_mounts.get(); }
	auto getPets() const -> PlayerPets * { return m_pets.get(); }
	auto getQuests() const -> PlayerQuests * { return m_quests.get(); }
	auto getSkills() const -> PlayerSkills * { return m_skills.get(); }
	auto getStats() const -> PlayerStats * { return m_stats.get(); }
	auto getStorage() const -> PlayerStorage * { return m_storage.get(); }
	auto getSummons() const -> PlayerSummons * { return m_summons.get(); }
	auto getVariables() const -> PlayerVariables * { return m_variables.get(); }
	auto getRandStream() const -> TauswortheGenerator * { return m_randStream.get(); }
	auto getTimerContainer() const -> ref_ptr_t<Timer::Container> { return getTimers(); }

	auto addUsedPortal(int8_t portalId) -> void { m_usedPortals.insert(portalId); }
	auto usedPortal(int8_t portalId) const -> bool { return m_usedPortals.find(portalId) != std::end(m_usedPortals); }

	auto changeChannel(channel_id_t channel) -> void;
	auto saveAll(bool saveCooldowns = false) -> void;
	auto setOnline(bool online) -> void;
	auto setLevelDate() -> void;
	auto acceptDeath(bool wheel) -> void;
	auto initializeRng(PacketBuilder &packet) -> void;

	auto send(const PacketBuilder &builder) -> void;
	auto send(const SplitPacketBuilder &builder) -> void;
	auto sendMap(const PacketBuilder &builder, bool excludeSelf = false) -> void;
	auto sendMap(const SplitPacketBuilder &builder) -> void;
protected:
	auto handleRequest(PacketReader &reader) -> void override;
private:
	auto playerConnect(PacketReader &reader) -> void;
	auto changeKey(PacketReader &reader) -> void;
	auto changeSkillMacros(PacketReader &reader) -> void;
	auto saveStats() -> void;

	bool m_tradeState = false;
	bool m_saveOnDc = true;
	bool m_isConnect = false;
	bool m_changingChannel = false;
	bool m_admin = false;
	bool m_gmChat = false;
	bool m_disconnecting = false;
	world_id_t m_worldId = -1;
	int8_t m_mapPos = -1;
	int8_t m_gender = -1;
	int8_t m_skin = 0;
	int8_t m_fallCounter = 0;
	uint8_t m_buddylistSize = 0;
	uint8_t m_portalCount = 0;
	int16_t m_mapChair = 0;
	int32_t m_id = 0;
	int32_t m_userId = 0;
	int32_t m_eyes = 0;
	int32_t m_hair = 0;
	int32_t m_map = 0;
	int32_t m_lastMap = 0;
	int32_t m_shop = 0;
	int32_t m_itemEffect = 0;
	int32_t m_chair = 0;
	int32_t m_gmLevel = 0;
	int32_t m_tradeId = 0;
	int64_t m_onlineTime = 0;
	Instance *m_instance = nullptr;
	Party *m_party = nullptr;
	Player *m_follow = nullptr;
	string_t m_chalkboard;
	string_t m_name;
	ChargeOrStationarySkillInfo m_info;
	owned_ptr_t<Npc> m_npc;
	owned_ptr_t<PlayerActiveBuffs> m_activeBuffs;
	owned_ptr_t<PlayerBuddyList> m_buddyList;
	owned_ptr_t<PlayerInventory> m_inventory;
	owned_ptr_t<PlayerMonsterBook> m_monsterBook;
	owned_ptr_t<PlayerMounts> m_mounts;
	owned_ptr_t<PlayerPets> m_pets;
	owned_ptr_t<PlayerQuests> m_quests;
	owned_ptr_t<PlayerSkills> m_skills;
	owned_ptr_t<PlayerStats> m_stats;
	owned_ptr_t<PlayerStorage> m_storage;
	owned_ptr_t<PlayerSummons> m_summons;
	owned_ptr_t<PlayerVariables> m_variables;
	owned_ptr_t<TauswortheGenerator> m_randStream;
	hash_set_t<int8_t> m_usedPortals;
};
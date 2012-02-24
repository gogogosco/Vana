/*
Copyright (C) 2008-2012 Vana Development Team

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

#include "noncopyable.hpp"
#include "Types.h"
#include <unordered_map>

using std::unordered_map;

class PacketCreator;
class Pet;
class Player;

class PlayerPets : boost::noncopyable {
public:
	PlayerPets(Player *player) : m_player(player) { }

	void save();
	void petInfoPacket(PacketCreator &packet);
	void connectData(PacketCreator &packet);

	Pet * getPet(int64_t petId);
	Pet * getSummoned(int8_t index);

	void addPet(Pet *pet);
	void setSummoned(int8_t index, int64_t petId);
private:
	unordered_map<int64_t, Pet *> m_pets;
	unordered_map<int8_t, int64_t> m_summoned;
	Player *m_player;
};
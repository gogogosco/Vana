/*
Copyright (C) 2008-2011 Vana Development Team

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
#include "ScriptDataProvider.h"
#include "Database.h"
#include "FileUtilities.h"
#include "InitializeCommon.h"
#include "StringUtilities.h"
#include <iostream>
#include <string>

using FileUtilities::fileExists;
using Initializing::outputWidth;

ScriptDataProvider * ScriptDataProvider::singleton = nullptr;

void ScriptDataProvider::loadData() {
	std::cout << std::setw(outputWidth) << std::left << "Initializing Scripts... ";

	m_npcScripts.clear();
	m_reactorScripts.clear();
	m_questScripts.clear();
	m_mapEntryScripts.clear();
	m_firstMapEntryScripts.clear();
	m_itemScripts.clear();

	mysqlpp::Query query = Database::getDataDb().query("SELECT * FROM scripts");
	mysqlpp::UseQueryResult res = query.use();
	int8_t modifier;
	int32_t objectId;
	string script;
	string scriptType;

	enum ScriptData {
		ScriptType = 0,
		Modifier, ObjectId, Script
	};

	while (MYSQL_ROW row = res.fetch_raw_row()) {
		objectId = atoi(row[ObjectId]);
		scriptType = row[ScriptType];
		script = row[Script];
		modifier = atoi(row[Modifier]);

		if (scriptType == "npc") m_npcScripts[objectId] = script;
		else if (scriptType == "reactor") m_reactorScripts[objectId] = script;
		else if (scriptType == "map_enter") m_mapEntryScripts[objectId] = script;
		else if (scriptType == "map_first_enter") m_firstMapEntryScripts[objectId] = script;
		else if (scriptType == "item") m_itemScripts[objectId] = script;
		else if (scriptType == "quest") {
			m_questScripts[static_cast<int16_t>(objectId)][modifier] = script;
		}

		m_scripts[script] = objectId;
	}

	std::cout << "DONE" << std::endl;
}

string ScriptDataProvider::getScript(int32_t objectId, ScriptTypes::ScriptTypes type) {
	if (hasScript(objectId, type)) {
		string s = "scripts/" + resolvePath(type) + "/" + resolve(type)[objectId] + ".lua";
		if (fileExists(s)) {
			return s;
		}
	}
	std::ostringstream filestream;
	filestream << "scripts/" << resolvePath(type) << "/" << objectId << ".lua";
	string g(filestream.str());
	return g;
}

string ScriptDataProvider::getQuestScript(int16_t questId, int8_t state) {
	if (hasQuestScript(questId, state)) {
		string s = "scripts/quests/" + m_questScripts[questId][state] + ".lua";
		if (fileExists(s)) {
			return s;
		}
	}
	std::ostringstream filestream;
	filestream << "scripts/quests/" << questId << (state == 0 ? "s" : "e") << ".lua";
	string g(filestream.str());
	return g;
}

bool ScriptDataProvider::hasScript(int32_t objectId, ScriptTypes::ScriptTypes type) {
	unordered_map<int32_t, string> &map = resolve(type);
	return (map.find(objectId) != map.end());
}

bool ScriptDataProvider::hasQuestScript(int16_t questId, int8_t state) {
	return (m_questScripts.find(questId) != m_questScripts.end());
}

unordered_map<int32_t, string> & ScriptDataProvider::resolve(ScriptTypes::ScriptTypes type) {
	switch (type) {
		case ScriptTypes::Item: return m_itemScripts; break;
		case ScriptTypes::MapEntry: return m_mapEntryScripts; break;
		case ScriptTypes::FirstMapEntry: return m_firstMapEntryScripts; break;
		case ScriptTypes::Npc: return m_npcScripts; break;
		case ScriptTypes::Reactor: return m_reactorScripts; break;
	}
	// No point, just return something in global scope
	return m_itemScripts;
}

string ScriptDataProvider::resolvePath(ScriptTypes::ScriptTypes type) {
	switch (type) {
		case ScriptTypes::Item: return "item"; break;
		case ScriptTypes::MapEntry: return "map_entry"; break;
		case ScriptTypes::FirstMapEntry: return "first_map_entry"; break;
		case ScriptTypes::Npc: return "npc"; break;
		case ScriptTypes::Reactor: return "reactor"; break;
	}
	return "";
}
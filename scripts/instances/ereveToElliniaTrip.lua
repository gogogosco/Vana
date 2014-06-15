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

dofile("scripts/utils/boatHelper.lua");

function beginInstance()
	initBoatMaps({
		200090031,
		200090033,
		200090035,
		200090037,
		200090039,
		200090041,
		200090043,
		200090045,
		200090047,
		200090049,
		200090051,
		200090053,
		200090055,
		200090057,
		200090059,
	});
end

function timerEnd(name, fromTimer)
	if fromTimer then
		idx = name:find("done_");
		if idx ~= nil then
			playerId = tonumber(name:sub(6));
			if setPlayer(playerId) then
				setMap(101000400);
				revertPlayer(playerId);
			end
		end
	end
end

function playerDisconnect(playerId, isPartyLeader)
	if setPlayer(playerId) then
		cleanMap(playerId, getMap());
		revertPlayer();
	end
end

function cleanMap(playerId, mapId)
	stopInstanceTimer("done_" .. playerId);
	clearBoatMap(mapId);
end

function changeMap(playerId, newMap, oldMap, isPartyLeader)
	if not isInstanceMap(newMap) then
		removeInstancePlayer(playerId);
		cleanMap(playerId, oldMap);
	elseif not isInstanceMap(oldMap) then
		boatTime = 2 * 60;
		addInstancePlayer(playerId);
		showMapTimer(newMap, boatTime);
		startInstanceTimer("done_" .. playerId, boatTime);
		takeBoatMap(newMap);
	end
end
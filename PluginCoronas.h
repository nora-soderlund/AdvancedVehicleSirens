#pragma once

#include "plugin.h"

#include "game_sa/CEntity.h"
#include "game_sa/CCoronas.h"
#include "game_sa/CCamera.h"

#include "PluginConfig.h"
#include "PluginMultiplayer.h"

class PluginCoronas {
	public:
		static void RegisterEvents();

		static void Add(CEntity* attachTo, int id, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn, float size, float farClip, eCoronaType coronaType, eCoronaFlareType flaretype);

		static void AddWithAngle(CEntity* attachTo, int id, float cameraAngle, float angle, float radius, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn, float size, float farClip, eCoronaType coronaType, eCoronaFlareType flaretype);
};

#include "PluginCoronas.h"

//std::map<CEntity*, 

void PluginCoronas::Add(CEntity* attachTo, int id, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn, float size, float farClip, eCoronaType coronaType, eCoronaFlareType flaretype) {
	return CCoronas::RegisterCorona(id, attachTo, red, green, blue, alpha, posn,
		size, farClip, coronaType, flaretype, false, false, 0, 0.0f, false, 0.5f, 0, 100.0f, false, false);
};

void PluginCoronas::AddWithAngle(CEntity* attachTo, int id, float cameraAngle, float angle, float radius, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const& posn, float size, float farClip, eCoronaType coronaType, eCoronaFlareType flaretype) {
	float differenceAngle = ((cameraAngle > angle) ? (cameraAngle - angle) : (angle - cameraAngle));

	float diameter = (radius / 2.0f);

	if (differenceAngle < diameter || differenceAngle > (360.0f - diameter))
		return;

	if (PluginConfig::Lights->Enhancement->InertiaEnabled) {
		float alphaFloat = static_cast<float>(alpha);

		alphaFloat = (alphaFloat < 0.0f) ? (alphaFloat * -1) : (alphaFloat);

		if (differenceAngle < diameter + PluginConfig::Lights->Enhancement->InertiaAngle) {
			float angle = diameter - differenceAngle;

			float multiplier = (angle / PluginConfig::Lights->Enhancement->InertiaAngle);

			alpha = static_cast<char>(alphaFloat * multiplier);
		}
		else if (differenceAngle > (360.0f - diameter) - PluginConfig::Lights->Enhancement->InertiaAngle) {
			float angle = PluginConfig::Lights->Enhancement->InertiaAngle - (differenceAngle - ((360.0f - diameter) - PluginConfig::Lights->Enhancement->InertiaAngle));

			float multiplier = angle / PluginConfig::Lights->Enhancement->InertiaAngle;

			alpha = static_cast<char>(alphaFloat * multiplier);
		}
	}

	return Add(attachTo, id, red, green, blue, alpha, posn, size, farClip, coronaType, flaretype);
};

void PluginCoronas::RegisterEvents() {

};
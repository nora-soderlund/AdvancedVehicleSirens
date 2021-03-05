#include "VehicleSpotlightData.h"
#include "PluginData.h"

VehicleSpotlightData::VehicleSpotlightData(CVehicle* vehicle) {
	Frame = NULL;

	Enabled = false;

	Vehicle = vehicle;

	FindNodesRecursive((RwFrame*)vehicle->m_pRwClump->object.parent, vehicle);
};

void VehicleSpotlightData::FindNodesRecursive(RwFrame* frame, CVehicle* vehicle) {
	while (frame) {
		const std::string name = GetFrameNodeName(frame);

		if (name != "spotlight_dummy") {
			if (RwFrame* newFrame = frame->child)
				FindNodesRecursive(newFrame, vehicle);

			if (RwFrame* newFrame = frame->next)
				FindNodesRecursive(newFrame, vehicle);

			return;
		}

		Frame = frame;

		return;
	}
};

void VehicleSpotlightData::OnHudRender() {
	if (plugin::KeyPressed(PluginConfig::Keys->SpotlightToggle) && !PluginMultiplayer::GetMouseState()) {
		uint64_t now = timeSinceEpochMillisec();
		
		if (now - PluginData::KeyTimestamp > PluginConfig::Keys->KeyDelay) {
			PluginData::KeyTimestamp = now;

			Enabled = !Enabled;

			PluginMultiplayer::AddChatMessage(std::string("You turned the spotlight " + std::string((Enabled)?("on"):("off")) + "!").c_str());


			VehicleTextures::Read();
		}
	}

	if (!plugin::KeyPressed(0x02))
		return;

	CCamera* camera = (CCamera*)0xB6F028;

	float heading = camera->GetHeading();

	CMatrix matrix;

	matrix = camera->m_mCameraMatrix;

	Frame->modelling.at.x = matrix.at.x;
	Frame->modelling.at.y = matrix.at.y;
	Frame->modelling.at.z = matrix.at.z;

	Frame->modelling.right.x = matrix.right.x;
	Frame->modelling.right.y = matrix.right.y;
	Frame->modelling.right.z = matrix.right.z;

	Frame->modelling.up.x = matrix.up.x;
	Frame->modelling.up.y = matrix.up.y;
	Frame->modelling.up.z = matrix.up.z;

	float vehicleHeading = Vehicle->GetHeading();
	
	vehicleHeading = vehicleHeading * 180.0f / 3.14f;

	RwFrameRotate(Frame, (RwV3d*)0x008D2E18, vehicleHeading, rwCOMBINEPRECONCAT);

	//RwFrameRotate(Frame, (RwV3d*)0x008D2E18, heading, rwCOMBINEREPLACE);
};

void VehicleSpotlightData::OnVehicleRender() {
	if (!Enabled || Frame == NULL)
		return;

	CCamera* camera = (CCamera*)0xB6F028;

	float cameraHeading = camera->GetHeading();

	float vehicleHeading = Vehicle->GetHeading();

	CMatrix matrix = CMatrix(new RwMatrix(Frame->modelling), true);

	matrix.pos += ((RwFrame*)Frame->object.parent)->modelling.pos;

	float vehicleAngle = vehicleHeading * 180.0f / 3.14f;

	float cameraAngle = cameraHeading * 180.0f / 3.14f;

	float differenceAngle = ((cameraAngle > vehicleAngle) ? (cameraAngle - vehicleAngle) : (vehicleAngle - cameraAngle));

	if (differenceAngle > 90.0f && differenceAngle < 270.0f) {
		CVector position = CVector(matrix.pos);

		CCoronas::RegisterCorona(reinterpret_cast<unsigned int>(Vehicle) + 49, Vehicle, 255, 255, 255, 128, position,
			0.3f, PluginConfig::Siren->StreamDistance, eCoronaType::CORONATYPE_SHINYSTAR, eCoronaFlareType::FLARETYPE_NONE, false, false, 0, 90.0f, false, 1.0f, 0, 50.0f, false, true);
	}

	matrix.RotateZ(vehicleHeading);

	/*CShadows::StoreShadowToBeRendered(SHADOW_DEFAULT, VehicleTextures::Spotlight, new CVector(Vehicle->GetPosition()),
		0.0f, 2.0f, 0.0f, 2.0f,
		1,
		255, 255, 255,
		160.0f, false, 1.0f, new CRealTimeShadow(), true);*/

	/*CShadows::StoreCarLightShadow(Vehicle, reinterpret_cast<unsigned int>(Vehicle) + 25, VehicleTextures::Spotlight, &Vehicle->GetPosition(),
		2.0f, 0.0f, 0.0f, 2.0f,
		128, 128, 128, 0.0f);*/

	/*CVector Pos = CModelInfo::ms_modelInfoPtrs[Vehicle->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMin;

	CVector center = Vehicle->TransformFromObjectSpace(CVector(0.0f, 0.0f, 0.0f));

	CVector up = Vehicle->TransformFromObjectSpace(CVector(0.0f, -Pos.y - 0.5f, 0.0f)) - center;
	CVector right = Vehicle->TransformFromObjectSpace(CVector(Pos.x + 0.2f, 0.0f, 0.0f)) - center;
	CShadows::StoreShadowToBeRendered(2, VehicleTextures::Spotlight, &center, up.x, up.y, right.x, right.y, 255, 128, 128, 128, 2.0f, false, 1.0f, 0, true);*/

	Vehicle->DoHeadLightReflectionSingle(matrix, 1);
};

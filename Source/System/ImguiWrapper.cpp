/**
* @file ImguiWrapper.h
* @brief Imgui�̐ÓI�N���X
* @author shiihara_kiyosumi
* @date 2022_12_20
*/

#include "ImguiWrapper.h"
#include "Game/Image/Image.h"
#include "Game/Camera/Camera.h"
#include "Game/Camera/CameraStruct.h"
#include "Game/Camera/TellCameraData.h"

// ���̂܂܂��ƒ����̂Ŗ��O��Z�k
using Func = std::function<void()>;

// �ÓI�����o�ϐ��̒�`
int ImguiWrapper::idCount = 0;

std::map<Mode, std::function<void(void**)>> ImguiWrapper::funcs = { {Mode::All, AllMode},{Mode::Scale, ScaleMode},{Mode::Rotate, RotateMode},{Mode::Pos, PosMode} };

// �������O���
// ���������P�[�W���邽��
namespace
{
	// �z��̔ԍ����킽���ƃ��Z�b�g�{�^����u����(�ǂ��ł��g����킯�ł͂Ȃ�)
	void ResetButton(int num, Camera& camera)
	{
		auto camData = camera.GetCameraData();
		auto pos = camData.pos;
		auto gPos = camData.gazePos;
		auto near = camData.near;
		auto far = camData.far;
		Func FuncX = [&]()    { camera.SetCameraPositionGaze(0.0f, pos.y, pos.z, gPos.x, gPos.y, gPos.z, near, far); };
		Func FuncY = [&]()    { camera.SetCameraPositionGaze(pos.x, 0.0f, pos.z, gPos.x, gPos.y, gPos.z, near, far); };
		Func FuncZ = [&]()    { camera.SetCameraPositionGaze(pos.x, pos.y, -2.0, gPos.x, gPos.y, gPos.z, near, far); };
		Func FuncGX = [&]()   { camera.SetCameraPositionGaze(pos.x, pos.y, pos.z, 0.0f, gPos.y, gPos.z, near, far); };
		Func FuncGY = [&]()   { camera.SetCameraPositionGaze(pos.x, pos.y, pos.z, gPos.x, 0.0f, gPos.z, near, far); };
		Func FuncGZ = [&]()   { camera.SetCameraPositionGaze(pos.x, pos.y, pos.z, gPos.x, gPos.y, 0.0f, near, far); };
		Func FuncNear = [&]() { camera.SetCameraPositionGaze(pos.x, pos.y, pos.z, gPos.x, gPos.y, gPos.z, 0.1f, far); };
		Func FuncFar = [&]()  { camera.SetCameraPositionGaze(pos.x, pos.y, pos.z, gPos.x, gPos.y, gPos.z, near, 100.0f); };
		std::vector<Func> functions = { FuncX, FuncY, FuncZ, FuncGX, FuncGY, FuncGZ, FuncNear, FuncFar };
		ImGui::SameLine();
		if (ImGui::Button("Reset"))
		{
			functions[num]();
		}
	}
}


void ImguiWrapper::Action(void** setting)
{
	if (NULL_CHECK(*setting)) { return; }
	auto settingPointer = (Setting*)setting;
	funcs[settingPointer->mode]((void**)settingPointer);
}

void ImguiWrapper::AllMode(void** setting)
{
	if (NULL_CHECK(*setting)) { return; }

	auto settingPointer = (Setting*)setting;
	// Switch�����g�������Ȃ��Ċ֐��|�C���^�ő�p
	// �J�����p�̊֐�
	Func cameraFunc = [&]()
	{
		auto camera = (Camera*)(settingPointer->instance);
		using namespace ImGui;
		Begin(settingPointer->windowName);
		CameraData camData = camera->GetCameraData();
		auto pos = camData.pos;
		auto gazePos = camData.gazePos;
#undef near
#undef far
		auto near = camData.near;
		auto far = camData.far;
		DragFloat("posX", &pos.x, 0.5f);
		DragFloat("posY", &pos.y, 0.5f);
		DragFloat("posZ", &pos.z, 0.5f);
		DragFloat("gazePosX", &gazePos.x, 0.5f);
		DragFloat("gazePosY", &gazePos.y, 0.5f);
		DragFloat("gazePosZ", &gazePos.z, 0.5f);
		DragFloat("near", &near, 0.1f);
		DragFloat("far", &far, 0.1f);
		camera->SetCameraPositionGaze(pos.x, pos.y, pos.z, gazePos.x, gazePos.y, gazePos.z, near, far);
		
		if (Button("ALLReset"))
		{
			camera->SetCameraPositionGaze(0.0f, 0.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.1f, 100.0f);
		}

		TellCameraData::Update(camera->GetCameraData(), CAMERA_NUMBER::CAMERA_0);
		End();
	};

	// �摜�p�̊֐�
	Func imageFunc = [&]()
	{
		auto image = (Image*)(settingPointer->instance);
		using namespace ImGui;
		Begin(settingPointer->windowName);
		auto scale = image->GetScale();
		auto rotate = image->GetRotate();
		auto pos = image->GetPos();
		DragFloat("scaleX", &scale.x, 0.005f, 0.0f, 10.0f);
		DragFloat("scaleY", &scale.y, 0.005f, 0.0f, 10.0f);
		DragFloat("rotateZ", &rotate.z, 0.005f, 0.0f, 360.0f * 3.14f / 180.0f);
		DragFloat("posX", &pos.x, 0.5f, 0.0f, WINDOW_WIDTH);
		DragFloat("posY", &pos.y, 0.5f, 0.0f, WINDOW_HEIGHT);
		image->SetScale(scale);
		image->SetRotate(rotate);
		image->SetPos(pos);

		if (Button("Save"))
		{
			File::FileData data(pos.x, pos.y, scale.x, scale.y, rotate.z);
			File::OutputFile(settingPointer->fileName, data);
			settingPointer->saveButtonCounter++;
		}
		if (settingPointer->saveButtonCounter != 0)
		{
			SameLine(); Text("SaveComplete!!");
			settingPointer->saveButtonCounter = 0;
		}

		End();
	};

	std::map<Setting::ClassName, Func> funcs = {{Setting::ClassName::Camera, cameraFunc}, {Setting::ClassName::Image, imageFunc}};
	funcs[settingPointer->className]();
}

void Setting::Init(void** instance, ClassName className, const char* windowName, const char* fileName, Mode mode)
{
	if (NULL_CHECK(*instance)) { return; }
	this->instance = *instance;
	this->className = className;
	this->windowName = windowName;
	this->fileName = fileName;
	this->mode = mode;
}

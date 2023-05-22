/**
* @file TinyObjTestScene.h
* @brief ���[�_�[�̃e�X�g�V�[��
* @details Scene���p�����Ă���
* @author shiihara_kiyosumi
* @date 2022_12_10
*/

// �w�b�_�[�t�@�C���̃C���N���[�h
#include "TinyObjTestScene.h"
#include <Windows.h>
#include <iostream>
#include "System/Input/Input.h"
#include "D3D11/Direct3D11.h"
#include "imgui.h"
#include "System/ImguiWrapper.h"
#include "System/Common.h"
#include "System/Transform.h"
#include "Game/ObjMesh/ObjMesh.h"
#include "Game/Camera/Camera.h"
#include "Game/Camera/CameraStruct.h"
#include "Game/Camera/TellCameraData.h"

/**
* @fn TinyObjTestScene
* @brief �R���X�g���N�^
*/
TinyObjTestScene::TinyObjTestScene()
	: objMesh(nullptr)
{
	// Camera�N���X�̏�����
	camera = new Camera();
	camera->SetCameraNumber(CAMERA_NUMBER::CAMERA_0);
	camera->SetCameraPositionGaze(0, 0.0f, -2.0f, 0, 0, 0, 0.1f,100.0f);
	TellCameraData::AddCamera(camera->GetCameraData());

	// GUI���g�����߂̃N���X�̏�����
	setting = new Setting();
	setting->Init(reinterpret_cast<void**>(&camera), Setting::ClassName::Camera, "Camera", "", Mode::All);

	// 3D���f���`��N���X�̏�����
	objMesh = new ObjMesh();
	if (FAILED(objMesh->Init(Direct3D11::GetDevice(), Direct3D11::GetDeviceContext(), "model/CatGirl.obj")))
	{
		MessageBox(0, "ObjMesh���������s", NULL, MB_OK);
		return;
	}
}

/**
* @fn ~TinyObjTestScene
* @brief �f�X�g���N�^
*/
TinyObjTestScene::~TinyObjTestScene()
{
	TellCameraData::SubCamera(CAMERA_NUMBER::CAMERA_0);
	SAFE_DELETE(objMesh);
	SAFE_DELETE(setting);
}

/**
* @fn Update
* @brief �X�V
* @return TAG_SCENE �V�[���̎��
*/
TAG_SCENE TinyObjTestScene::Update()
{

	if (Input::IsDown(BUTTON_ID_START))
	{
		return TAG_SCENE::OVER;
	}
	ImguiWrapper::Action((void**)setting);
	return TAG_SCENE::NONE;
}

/**
* @fn Draw
* @brief �`��
*/
void TinyObjTestScene::Draw()
{
	OutputDebugString("TinyObjTestScene\n");
	auto tran = Transform();
	tran.SetPos(Vector3D(0.0f, -0.5f, 0.0f));
	static float rot = 180.0f;
	rot += 0.03f;
	tran.SetRotate(Vector3D(0.0f, rot * 3.14f / 180.0f,0.0f));
	objMesh->Draw(tran);
}
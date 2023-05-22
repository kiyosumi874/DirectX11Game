/**
* @file ImguiWrapper.h
* @brief Imgui�̐ÓI�N���X
* @author shiihara_kiyosumi
* @date 2022_12_20
* @detail
* ���̃N���X�͕s���S�Ő���r���ł��B
* ���̒i�K�ł͈�̃N���X�̃p�����[�^�����f�o�b�O�E�B���h�E���o�����Ƃ��ł��܂���B
*/
#pragma once
#include <functional>
#include <map>
#include "imgui.h"
#include "System/File.h"
#include "System/Common.h"


/**
* @enum Mode
* @brief Setting�̃p�����[�^�[�Ƃ��Ďg�p����
* @details Imgui�łǂ���ύX�ł���悤�ɂ��邩���߂�
*/
enum class Mode
{
	All,
	Scale,
	Rotate,
	Pos
};


/**
* @class ImguiWrapper
* @brief Imgui�̂܂Ƃ߃N���X
*/
class ImguiWrapper
{
public:


	/**
	* @fn Action
	* @brief �X�V
	* @detail ���̃N���X��ێ����Ă���N���X��Update�ɏ����Γ����܂�
	*/
	static void Action(void** setting);

	static void AddID() { idCount++; }
	static int GetID() { return idCount; }

private:
	/**
	* @fn ImguiWrapper
	* @brief ����J�R���X�g���N�^
	*/
	ImguiWrapper() { /*���̃R���X�g���N�^���Ăяo�����\���͂Ȃ��̂Ŏ����������ׂ��ł͂Ȃ�*/ }

	static int idCount;

	static std::map<Mode, std::function<void(void**)>> funcs;

	static void AllMode(void** setting);

	static void ScaleMode(void** setting)
	{

	}

	static void RotateMode(void** setting)
	{

	}

	static void PosMode(void** setting)
	{

	}
	
};

/**
* @struct Setting
*/
class Setting
{
public:
	enum class ClassName
	{
		Image,
		Camera,
		Exception
	};

	/**
	* @fn Setting
	* @brief �R���X�g���N�^
	*/
	Setting()
	{
		instance = nullptr;
		className = ClassName::Exception;
		windowName = "";
		fileName = "";
		mode = Mode::All;
		id = ImguiWrapper::GetID();
		ImguiWrapper::AddID();
		saveButtonCounter = 0;
	}

	/**
	* @fn Init
	* @brief ������
	* @detail �ŏ��ɌĂяo���֐�
	*/
	void Init(void** instance, ClassName className, const char* windowName, const char* fileName, Mode mode);

	void* instance;
	ClassName className;
	const char* windowName;
	const char* fileName;
	Mode mode;
	int id;
	int saveButtonCounter;
};
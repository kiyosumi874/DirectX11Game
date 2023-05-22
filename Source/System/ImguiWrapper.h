/**
* @file ImguiWrapper.h
* @brief Imguiの静的クラス
* @author shiihara_kiyosumi
* @date 2022_12_20
* @detail
* このクラスは不完全で製作途中です。
* 今の段階では一つのクラスのパラメータしかデバッグウィンドウを出すことができません。
*/
#pragma once
#include <functional>
#include <map>
#include "imgui.h"
#include "System/File.h"
#include "System/Common.h"


/**
* @enum Mode
* @brief Settingのパラメーターとして使用する
* @details Imguiでどこを変更できるようにするか決める
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
* @brief Imguiのまとめクラス
*/
class ImguiWrapper
{
public:


	/**
	* @fn Action
	* @brief 更新
	* @detail このクラスを保持しているクラスのUpdateに書けば動きます
	*/
	static void Action(void** setting);

	static void AddID() { idCount++; }
	static int GetID() { return idCount; }

private:
	/**
	* @fn ImguiWrapper
	* @brief 非公開コンストラクタ
	*/
	ImguiWrapper() { /*このコンストラクタが呼び出される可能性はないので実装を書くべきではない*/ }

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
	* @brief コンストラクタ
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
	* @brief 初期化
	* @detail 最初に呼び出す関数
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
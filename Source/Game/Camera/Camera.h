/**
* @file Camera.h
* @brief Camera
* @author shiihara_kiyosumi
* @date 2022_08_02
*/

// ヘッダーファイルのインクルード
#pragma once
#include <d3dx10.h>
#include "CameraStruct.h"
#include "System/Vector3D.h"

/**
* @class Camera
* @brief Cameraクラス
*/
class Camera
{
public:
	/**
	* @fn コンストラクタ
	* @brief 生成したときに最初に一回だけ走る関数
	*/
	Camera()
	{
		isGaze = false;
		key = CAMERA_NUMBER::CAMERA_NONE;
		near = 0.1f;
		far = 100.0f;
	}

	/**
	* @fn SetCameraNumber
	* @brief key設定
	*/
	void SetCameraNumber(const CAMERA_NUMBER key);

	/**
	* @fn SetCameraPosition
	* @brief cameraの位置をセット
	* @param[in] x カメラのX座標
	* @param[in] y カメラのY座標
	* @param[in] z カメラのZ座標
	*/
	void SetCameraPosition(float x, float y, float z);

	/**
	* @fn SetCameraPositionGaze
	* @brief cameraの位置と注視の位置をセット
	* @param[in] x カメラのX座標
	* @param[in] y カメラのY座標
	* @param[in] z カメラのZ座標
	* @param[in] gx 注視するX座標
	* @param[in] gy 注視するY座標
	* @param[in] gz 注視するZ座標
	*/
	void SetCameraPositionGaze(float x, float y, float z, float gx, float gy, float gz, float near, float far);

	/**
	* @fn GetCameraData
	* @brief カメラのデータ取得
	* @return CameraData カメラのデータ
	*/
	const CameraData GetCameraData() const
	{
		CameraData data;
		data.matrixView = matrixView;
		data.matrixProj = matrixProj;
		data.pos = pos;
		data.gazePos = gazePos;
		data.near = near;
		data.far = far;
		data.key = key;
		return data;
	}

private:
	/**
	* @fn SetViewProj
	* @brief ビュー行列とプロジェクション行列を計算
	*/
	void SetViewProj();
#undef near
#undef far
	Vector3D pos; // カメラの位置
	Vector3D gazePos; // カメラの注視
	float near; // カメラの手前の描画距離
	float far; // カメラの奥の描画距離
	bool isGaze; // true->注視ありモード
	D3DXMATRIX matrixView; // ビュー行列
	D3DXMATRIX matrixProj; // プロジェクション行列
	CAMERA_NUMBER key; // カメラの識別ID
};
/**
* @file Camera.h
* @brief Camera(コンポーネント)
* @author shiihara_kiyosumi
* @date 2022_08_02
*/

// ヘッダーファイルのインクルード
#include "Camera.h"
#include "System/Common.h"

// 必要なライブラリファイルのロード
#pragma comment(lib,"d3dx10.lib")

/**
* @fn SetCameraNumber
* @brief key設定
*/
void Camera::SetCameraNumber(const CAMERA_NUMBER key)
{
	this->key = key;
}

/**
* @fn SetCameraPosition
* @brief cameraの位置をセット
* @param[in] x カメラのX座標
* @param[in] y カメラのY座標
* @param[in] z カメラのZ座標
*/
void Camera::SetCameraPosition(float x, float y, float z)
{
	pos = Vector3D(x, y, z);
	SetViewProj();
}

/**
* @fn SetCameraPositionGaze
* @brief cameraの位置と注視の位置をセット
* @param[in] x カメラのX座標
* @param[in] y カメラのY座標
* @param[in] z カメラのZ座標
* @param[in] gx 注視するX座標
* @param[in] gy 注視するY座標
* @param[in] gz 注視するZ座標
* @param[in] near 手前の描画距離
* @param[in] far 奥の描画距離
*/
void Camera::SetCameraPositionGaze(float x, float y, float z, float gx, float gy, float gz, float near, float far)
{
	pos = Vector3D(x, y, z);
	gazePos = Vector3D(gx, gy, gz);
	this->near = near;
	this->far = far;
	isGaze = true;
	SetViewProj();
}

/**
* @fn SetViewProj
* @brief ビュー行列とプロジェクション行列を計算
*/
void Camera::SetViewProj()
{
	// ビュー
	if (!isGaze)
	{
		D3DXVECTOR3 vEyePt(pos.x, pos.y, pos.z); // カメラ(視点)位置
		D3DXVECTOR3 vLookatPt(pos.x, pos.y, pos.z + 1); // 注視位置
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f); // 上方位置

		D3DXMatrixLookAtLH(&matrixView, &vEyePt, &vLookatPt, &vUpVec);
	}
	else
	{
		D3DXVECTOR3 vEyePt(pos.x, pos.y, pos.z); // カメラ(視点)位置
		D3DXVECTOR3 vLookatPt(gazePos.x, gazePos.y, gazePos.z); // 注視位置
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f); // 上方位置

		D3DXMatrixLookAtLH(&matrixView, &vEyePt, &vLookatPt, &vUpVec);
	}
	isGaze = false;

	// プロジェクション
	D3DXMatrixPerspectiveFovLH(&matrixProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, near, far);

}

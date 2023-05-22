/**
* @file Camera.h
* @brief Camera
* @author shiihara_kiyosumi
* @date 2022_08_02
*/

// �w�b�_�[�t�@�C���̃C���N���[�h
#pragma once
#include <d3dx10.h>
#include "CameraStruct.h"
#include "System/Vector3D.h"

/**
* @class Camera
* @brief Camera�N���X
*/
class Camera
{
public:
	/**
	* @fn �R���X�g���N�^
	* @brief ���������Ƃ��ɍŏ��Ɉ�񂾂�����֐�
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
	* @brief key�ݒ�
	*/
	void SetCameraNumber(const CAMERA_NUMBER key);

	/**
	* @fn SetCameraPosition
	* @brief camera�̈ʒu���Z�b�g
	* @param[in] x �J������X���W
	* @param[in] y �J������Y���W
	* @param[in] z �J������Z���W
	*/
	void SetCameraPosition(float x, float y, float z);

	/**
	* @fn SetCameraPositionGaze
	* @brief camera�̈ʒu�ƒ����̈ʒu���Z�b�g
	* @param[in] x �J������X���W
	* @param[in] y �J������Y���W
	* @param[in] z �J������Z���W
	* @param[in] gx ��������X���W
	* @param[in] gy ��������Y���W
	* @param[in] gz ��������Z���W
	*/
	void SetCameraPositionGaze(float x, float y, float z, float gx, float gy, float gz, float near, float far);

	/**
	* @fn GetCameraData
	* @brief �J�����̃f�[�^�擾
	* @return CameraData �J�����̃f�[�^
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
	* @brief �r���[�s��ƃv���W�F�N�V�����s����v�Z
	*/
	void SetViewProj();
#undef near
#undef far
	Vector3D pos; // �J�����̈ʒu
	Vector3D gazePos; // �J�����̒���
	float near; // �J�����̎�O�̕`�拗��
	float far; // �J�����̉��̕`�拗��
	bool isGaze; // true->�������胂�[�h
	D3DXMATRIX matrixView; // �r���[�s��
	D3DXMATRIX matrixProj; // �v���W�F�N�V�����s��
	CAMERA_NUMBER key; // �J�����̎���ID
};
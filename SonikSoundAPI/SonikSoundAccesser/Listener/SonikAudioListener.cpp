/*
 * SonikAudioListener.cpp
 *
 *  Created on: 2024/01/04
 *      Author: SONIC
 */

#include "SonikAudioListener.h"

namespace SonikAudio
{

	//コンストラクタ
	SonikAudioListener::SonikAudioListener(void)
	:PosX(0.0)
	,PosY(0.0)
	,PosZ(0.0)
	,p_PosX(&PosX)
	,p_PosY(&PosY)
	,p_PosZ(&PosZ)
	{

	};

	//デストラクタ
	SonikAudioListener::~SonikAudioListener(void)
	{
		//no porcess;
	};

	//ポジションのセット
	void SonikAudioListener::SetPosition(double x, double y, double z)
	{
		(*p_PosX) = x;
		(*p_PosY) = y;
		(*p_PosZ) = z;
	};

	void SonikAudioListener::SetPositionX(double x)
	{
		(*p_PosX) = x;
	};

	void SonikAudioListener::SetPositionY(double y)
	{
		(*p_PosY) = y;
	};

	void SonikAudioListener::SetPositionZ(double z)
	{
		(*p_PosZ) = z;
	};

	//ポジションのゲット
	void SonikAudioListener::GetPosition(double& x, double& y, double& z)
	{
		x = (*p_PosX);
		y = (*p_PosY);
		z = (*p_PosZ);
	};

	void SonikAudioListener::GetPosition(double*& x, double*& y, double*& z)
	{
		x = p_PosX;
		y = p_PosY;
		z = p_PosZ;
	};

	double SonikAudioListener::GetPositionX(void)
	{
		return (*p_PosX);
	};

	const double* SonikAudioListener::GetPositionX(void)
	{
		return p_PosX;
	};

	const double& SonikAudioListener::GetPositionX(void)
	{
		return (*p_PosX);
	};

	double SonikAudioListener::GetPositionY(void)
	{
		return (*p_PosY);
	};

	const double* SonikAudioListener::GetPositionY(void)
	{
		return p_PosY;
	};
	const double& SonikAudioListener::GetPositionY(void)
	{
		return (*p_PosY);
	};

	double SonikAudioListener::GetPositionZ(void)
	{
		return (*p_PosZ);
	};

	const double* SonikAudioListener::GetPositionZ(void)
	{
		return p_PosZ;
	};

	const double& SonikAudioListener::GetPositionZ(void)
	{
		return (*p_PosZ);
	};

};


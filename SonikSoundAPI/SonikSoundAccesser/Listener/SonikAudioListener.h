/*
 * SonikAudioListener.h
 *
 *  Created on: 2023/12/24
 *      Author: SONIC
 */

#ifndef LISTENER_SONIKAUDIOLISTENER_H_
#define LISTENER_SONIKAUDIOLISTENER_H_

namespace SonikMathDataBox
{
	class Sonik3DPoint;
};

namespace SonikAudio
{
	//オーディオリスナーさん
	//現状リスナーとプレイヤーの距離のためのものなので位置情報のみ。
	//音響などはまだまだ先だよねぇ。
	class SonikAudioListener
	{
	private:
		double max_listen_distance; //聞こえる範囲
		double listen_volume; //聞こえるボリューム
		SonikMathDataBox::Sonik3DPoint* m_3dpos;	//3D座標
		SonikMathDataBox::Sonik3DPoint* m_3ddir;  //3D方向
	public:
		//コンストラクタ
		SonikAudioListener(void);
		//デストラクタ
		~SonikAudioListener(void);

		//最大聞こえる距離のセットゲット
		void SetMaxListenDistance(double _setmaxdistance_);
		double GetMaxListernDistance(void);

		//聞こえる音量(マスターボリューム)のセットゲット
		void SetListenVolume(double setvolume);
		double GetListenVolume(void);

		//ポジションのセット
		void SetPosition(double x, double y, double z);
		void SetPositionX(double x);
		void SetPositionY(double y);
		void SetPositionZ(double z);

		//ポジションのゲット
		void GetPosition(double& x, double& y, double& z);
		SonikMathDataBox::Sonik3DPoint& GetPosition(void);
		double GetPositionX(void);
		double GetPositionY(void);
		double GetPositionZ(void);

		//方向のセット
		void SetDirection(double x, double y, double z);
		void SetDirectionX(double x);
		void SetDirectionY(double y);
		void SetDirectionZ(double z);

		//方向のゲット
		void GetDirection(double& x, double& y, double& z);
		SonikMathDataBox::Sonik3DPoint& GetDirection(void);
		double GetDirectionX(void);
		double GetDirectionY(void);
		double GetDirectionZ(void);



	};


};



#endif /* LISTENER_SONIKAUDIOLISTENER_H_ */

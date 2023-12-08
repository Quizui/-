/*
 * SonikNormalize.h
 *
 *  Created on: 2019/01/20
 *      Author: SONIC
 */

#ifndef MATHBIT_SONIKNORMALIZE_H_
#define MATHBIT_SONIKNORMALIZE_H_


namespace SonikMath
{
	float Normalize_Zero_to_OneF(unsigned long NormalizeTargetValue);
	double Normalize_Zero_to_One(unsigned long long NormalizeTargetValue);

	float Normalize_Max_to_MinF(long NormalizeTargetValue, long TargetMax, long TargetMin);
	double Normalize_Max_to_Min(long long NormalizeTargetValue, long long TargetMax, long long TargetMin);

};


#endif /* MATHBIT_SONIKNORMALIZE_H_ */

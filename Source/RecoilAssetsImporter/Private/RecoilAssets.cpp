// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilAssets.h"

FVector2D URecoilAssets::GetAbsoluteRecoilVector(const float SampleValue, const int32 TotalBulletNumber) const
{
	if (SampleValue >= 1.0f)
	{
		return AbsoluteRecoilDataList.Last();
	}
	const float TargetSampleValue = SampleValue * TotalBulletNumber;
	const float ValueAfterPoint = TargetSampleValue - FMath::Floor(TargetSampleValue);
	return FMath::Lerp(AbsoluteRecoilDataList[FMath::FloorToInt32(TargetSampleValue)], AbsoluteRecoilDataList[FMath::CeilToInt32(TargetSampleValue)], ValueAfterPoint);
}

FVector2D URecoilAssets::GetDiffRecoilVector(const float SampleValue, const int32 TotalBulletNumber) const
{
	if (SampleValue >= 1.0f)
	{
		return DiffRecoilDataList.Last();
	}
	const float TargetSampleValue = SampleValue * TotalBulletNumber;
	const float ValueAfterPoint = TargetSampleValue - FMath::Floor(TargetSampleValue);
	return FMath::Lerp(DiffRecoilDataList[FMath::FloorToInt32(TargetSampleValue)], DiffRecoilDataList[FMath::CeilToInt32(TargetSampleValue)], ValueAfterPoint);
}

void URecoilAssets::AddRecoilData(FVector2D NewData)
{
	if (DiffRecoilDataList.IsEmpty())
	{
		AbsoluteRecoilDataList.Add(NewData);
		DiffRecoilDataList.Add(NewData);
		return;
	}
	
	const FVector2D LastDataBeforeAdd = AbsoluteRecoilDataList.Last();
	AbsoluteRecoilDataList.Add(NewData);
	DiffRecoilDataList.Add(NewData - LastDataBeforeAdd);
}

void URecoilAssets::RemoveLastRecoilData()
{
	if (!AbsoluteRecoilDataList.IsEmpty() && !DiffRecoilDataList.IsEmpty())
	{
		AbsoluteRecoilDataList.RemoveAt(AbsoluteRecoilDataList.Num()-1);
		DiffRecoilDataList.RemoveAt(DiffRecoilDataList.Num()-1);
	}
}

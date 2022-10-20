// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RecoilAssets.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RECOILASSETSIMPORTER_API URecoilAssets : public UObject
{
	GENERATED_BODY()

public:

	// 绝对后坐力表
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Recoil Assets Data", DisplayName="绝对后坐力")
	TArray<FVector2D> AbsoluteRecoilDataList;

	// 差值后坐力数组
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Recoil Assets Data", DisplayName="差值后坐力")
	TArray<FVector2D> DiffRecoilDataList;

	/*
	 *	@brief : 获取绝对后坐力
	 *	@param : 采样数值，其范围为[0, 1]
	 *	@param : 一个弹匣总弹药数
	 *	@return FVector2D : 返回的绝对后坐力 
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Recoil"))
	FVector2D GetAbsoluteRecoilVector(const float SampleValue, const int32 TotalBulletNumber) const;

	/*
	 *	@brief : 获取插值后坐力
	 *	@param : 采样数值，其范围为[0, 1]
	 *	@param : 一个弹匣总弹药数
	 *	@return FVector2D : 返回的插值后坐力 
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Recoil"))
	FVector2D GetDiffRecoilVector(const float SampleValue, const int32 TotalBulletNumber) const;

	/*
	 *	@brief : 添加一个后坐力数据
	 *	@param : 新的后坐力数据（绝对后坐力）
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Recoil"))
	void AddRecoilData(FVector2D NewData);

	/*
	 *	@brief : 移除最后一发子弹的后坐力数据
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Recoil"))
	void RemoveLastRecoilData();
};

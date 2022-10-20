// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RecoilAssetsEditorSettings.generated.h"

/**
 * 
 */

UCLASS(Config="RecoilAssetsImporter", DefaultConfig)
class RECOILASSETSIMPORTEREDITOR_API URecoilAssetsEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	UPROPERTY(config, BlueprintReadOnly, EditDefaultsOnly, Category="网格设置", DisplayName="最小网格间距")
	float MinGridGap = 2.5f;

	UPROPERTY(config, BlueprintReadOnly, EditDefaultsOnly, Category="网格设置", DisplayName="最大网格间距")
	float MaxGridGap = 20.0f;;

	UPROPERTY(config, BlueprintReadOnly, EditDefaultsOnly, Category="视图操作", DisplayName="视图缩放速度")
	float ViewGraphZoomSpeed = 0.25f;

	/**
	 *	@brief : 获取设置
	 */
	UFUNCTION(BlueprintCallable)
	static URecoilAssetsEditorSettings* GetRecoilAssetsEditorSettings();

	/** 目录设置 */
	UFUNCTION(BlueprintCallable)
	virtual FName GetContainerName() const override { return TEXT("Editor"); }

	UFUNCTION(BlueprintCallable)
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }

	UFUNCTION(BlueprintCallable)
	virtual FName GetSectionName() const override { return TEXT("RecoilAssetsImporter"); }
};

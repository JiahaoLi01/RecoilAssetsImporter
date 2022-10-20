// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "UObject/Object.h"

/**
 * 
 */
class RECOILASSETSIMPORTEREDITOR_API FRecoilAssetTypeAction : public FAssetTypeActions_Base
{
public:
	// Set assets color in graph view.
	virtual FColor GetTypeColor() const override;

	// get assets name, and show in graph.
	virtual FText GetName() const override;

	// which class that the operation used.
	virtual UClass* GetSupportedClass() const override;

	// category in assets manager.
	virtual uint32 GetCategories() override;

	// 显示对应的资产的编辑器界面
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;

	// 编辑器图标
	virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;
};
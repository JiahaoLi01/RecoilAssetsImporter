// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurveEditor.h"

/**
 * 
 */
class FRecoilAssetTypeAction;
class URecoilAssets;
class RECOILASSETSIMPORTEREDITOR_API FRecoilAssetEditorToolKit : public FAssetEditorToolkit
{
public:
	/** 继承自父类，需要手动实现的虚函数 */
	FORCEINLINE virtual FName GetToolkitFName() const override {return FName("RecoilAssetEditorToolKit");}
	FORCEINLINE virtual FText GetBaseToolkitName() const override {return NSLOCTEXT("RecoilAssetsImporter", "REcoilAssetEditorToolKit", "后坐力资产编辑器");}
	FORCEINLINE virtual FString GetWorldCentricTabPrefix() const override {return NSLOCTEXT("RecoilAssetsImporter", "TabPrefix", "后坐力资产").ToString();}
	FORCEINLINE virtual FLinearColor GetWorldCentricTabColorScale() const override {return FLinearColor::Green;}

	/** 核心函数，注册页签与注销页签 */
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	/** 初始化编辑器 */
	void Initialize(UObject* InAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);

protected:

	/*
	 *	@brief : 生成细节面板
	 *	@param SpawnTabArgs : 生成细节面板需要的参数
	 *	@return TSharedRef<SDockTab> : 生成的细节面板
	 */
	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs);

	// 正在编辑的Object
	TObjectPtr<UObject> CurrentEditingObject = nullptr;
	
};

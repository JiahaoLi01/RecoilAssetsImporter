// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilAssetsActionType.h"

#include "RecoilAssetEdtior.h"
#include "RecoilAssetsImporter/Public/RecoilAssets.h"

FColor FRecoilAssetTypeAction::GetTypeColor() const
{
	return FColor::Green;
}

UClass* FRecoilAssetTypeAction::GetSupportedClass() const
{
	return URecoilAssets::StaticClass();
}

uint32 FRecoilAssetTypeAction::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}

void FRecoilAssetTypeAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type ToolKitModeType = EditWithinLevelEditor ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	
	//变量对象数组，如果拿到我们的资源对象，就执行Toolkit初始化
	for (auto ObjectIterator = InObjects.CreateConstIterator(); ObjectIterator; ++ObjectIterator)
	{
		if (URecoilAssets* RecoilAssets = Cast<URecoilAssets>(*ObjectIterator))
		{
			const TSharedRef<FRecoilAssetEditorToolKit> RecoilAssetEditorToolKit = MakeShareable(new FRecoilAssetEditorToolKit());
			RecoilAssetEditorToolKit->Initialize(RecoilAssets, ToolKitModeType, EditWithinLevelEditor);
		}
	}
}

TSharedPtr<SWidget> FRecoilAssetTypeAction::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	const FSlateDynamicImageBrush* Icon =
		new FSlateDynamicImageBrush(
			*(FPaths::ProjectPluginsDir() / "RecoilAssetsImporter" / "Resources" / "AssetsIcon.png"),
			FVector2D(256, 256));

	return SNew(SBorder)
		.BorderImage(FEditorStyle::GetNoBrush())
		.Visibility(EVisibility::HitTestInvisible)
		.Padding(FMargin(0.0f, 0.0f, 0.0f, 3.0f))
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		[
			SNew(SImage)
			.Image(Icon)
		];
}

FText FRecoilAssetTypeAction::GetName() const
{
	return NSLOCTEXT("RecoilAssetsImporter", "AssetTypeActions_RecoilAssets", "后坐力资产");
}



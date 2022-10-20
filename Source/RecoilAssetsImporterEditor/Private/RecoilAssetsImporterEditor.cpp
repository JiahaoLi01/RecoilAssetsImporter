// Copyright Epic Games, Inc. All Rights Reserved.

#include "RecoilAssetsImporterEditor.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "RecoilAssetsActionType.h"

#define LOCTEXT_NAMESPACE "FRecoilAssetsImporterEditorModule"

void FRecoilAssetsImporterEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FRecoilAssetTypeAction()));
}

void FRecoilAssetsImporterEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRecoilAssetsImporterEditorModule, RecoilAssetsImporterEditor)
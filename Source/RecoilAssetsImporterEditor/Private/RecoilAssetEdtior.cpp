// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilAssetEdtior.h"

#include "MiniCurveEditor.h"
#include "PropertyEditing.h"
#include "SRecoilCurveEditorView.h"
#include "CurveEditor/Public/SCurveEditorPanel.h"

void FRecoilAssetEditorToolKit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(FName("RecoilAssetPropertyTab"), FOnSpawnTab::CreateRaw(this, &FRecoilAssetEditorToolKit::SpawnDetailTab));
	InTabManager->RegisterTabSpawner(FName("RecoilAssetPropertyImageTab"), FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& SpawnTabArgs)
	{
		return SNew(SDockTab)
		[
			SNew(SRecoilCurveEditorView)
			.RecoilAssets(Cast<URecoilAssets>(this->CurrentEditingObject))
		];
	}));
}

void FRecoilAssetEditorToolKit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(FName("RecoilAssetPropertyTab"));
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

void FRecoilAssetEditorToolKit::Initialize(UObject* InAsset, const EToolkitMode::Type InMode,
	const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	CurrentEditingObject = InAsset;
	const TSharedRef<FTabManager::FLayout> StandaloneRecoilAssetLayout = FTabManager::NewLayout("StandaloneRecoilAssetLayout_Layout")
			->AddArea
			(
				FTabManager::NewPrimaryArea()
				->Split(FTabManager::NewStack()->AddTab(FName("RecoilAssetPropertyTab"), ETabState::OpenedTab))
			);
	InitAssetEditor(InMode, InToolkitHost, FName("RecoilAssetEditor"), StandaloneRecoilAssetLayout, true, true, InAsset);
	RegenerateMenusAndToolbars();

}

TSharedRef<SDockTab> FRecoilAssetEditorToolKit::SpawnDetailTab(const FSpawnTabArgs& SpawnTabArgs)
{
	//加载属性编辑器模块
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::Get().LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs;
	//创建属性编辑器的Slate
	const TSharedRef<IDetailsView> AssetPropertyView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	//将对象传入，这样就是自动生成对象的属性面板
	AssetPropertyView->SetObject(GetEditingObject());
	return SNew(SDockTab)
	[
		AssetPropertyView
	];
}

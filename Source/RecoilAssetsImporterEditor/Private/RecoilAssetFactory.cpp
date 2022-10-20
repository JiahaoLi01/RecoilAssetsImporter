// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilAssetFactory.h"

#include "Misc/FeedbackContext.h"
#include "Misc/FileHelper.h"
#include "RecoilAssetsImporter/Public/RecoilAssets.h"

DEFINE_LOG_CATEGORY_STATIC(LogFactory, Log, All);

URecoilAssetFactory::URecoilAssetFactory()
{

	Formats.Add(FString(TEXT("recoilassets;recoil")));
	
	SupportedClass = URecoilAssets::StaticClass();
	bCreateNew = false;
	bEditAfterNew = true;
	bEditorImport = true;
}

UObject* URecoilAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UE_LOG(LogFactory, Log, TEXT("Recoil asset object created."));
	check(InClass->IsChildOf(URecoilAssets::StaticClass()));
	return NewObject<URecoilAssets>(InParent, InClass, InName, Flags);
}

UObject* URecoilAssetFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UObject* RecoilObject = NewObject<URecoilAssets>(InParent, InClass, InName, Flags);

	FString Data;
	TArray<FString> SplitStringData;
	FFileHelper::LoadFileToString(Data, *Filename);

	UE_LOG(LogFactory, Log, TEXT("Loading recoil asset file"));
	
	Data.ParseIntoArray(SplitStringData, TEXT(" "));

	UE_LOG(LogFactory, Log, TEXT("%d recoil bullet detected"), SplitStringData.Num());

	URecoilAssets* RecoilAssetsPtr = Cast<URecoilAssets>(RecoilObject);
	
	for (int i = 0; i < SplitStringData.Num(); i += 2)
	{
		RecoilAssetsPtr->AbsoluteRecoilDataList.Add(FVector2D(FCString::Atof(*SplitStringData[i]), FCString::Atof(*SplitStringData[i+1])));
	}

	RecoilAssetsPtr->DiffRecoilDataList.SetNum(RecoilAssetsPtr->AbsoluteRecoilDataList.Num());
	
	if (RecoilAssetsPtr->AbsoluteRecoilDataList.Num() >= 1)
	{
		RecoilAssetsPtr->DiffRecoilDataList[0] = RecoilAssetsPtr->AbsoluteRecoilDataList[0];
	}

	for (int i = 1; i < RecoilAssetsPtr->AbsoluteRecoilDataList.Num(); ++i)
	{
		RecoilAssetsPtr->DiffRecoilDataList[i] = RecoilAssetsPtr->AbsoluteRecoilDataList[i] - RecoilAssetsPtr->AbsoluteRecoilDataList[i - 1];
	}

	bOutOperationCanceled = false;
	return RecoilObject;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UObject/Object.h"
#include "RecoilAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class RECOILASSETSIMPORTEREDITOR_API URecoilAssetFactory : public UFactory
{
	GENERATED_BODY()

public:

	URecoilAssetFactory();
	
	FORCEINLINE virtual bool CanCreateNew() const override { return false; }
	FORCEINLINE virtual bool ShouldShowInNewMenu() const override { return true; }
	
	// import file
	FORCEINLINE virtual bool FactoryCanImport(const FString& Filename) override { return true; }
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilAssetsEditorSettings.h"

URecoilAssetsEditorSettings* URecoilAssetsEditorSettings::GetRecoilAssetsEditorSettings()
{
	URecoilAssetsEditorSettings* RecoilAssetsEditorSettings = GetMutableDefault<URecoilAssetsEditorSettings>();
	return RecoilAssetsEditorSettings;
}

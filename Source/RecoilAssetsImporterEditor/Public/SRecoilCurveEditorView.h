// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RecoilAssets.h"
#include "SCurveEditorView.h"
#include "Widgets/SCanvas.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"

class FCurveEditor;
/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(LogRecoilImporter, Log, All)

class RECOILASSETSIMPORTEREDITOR_API SRecoilCurveEditorView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRecoilCurveEditorView)
	{
	}

	SLATE_ARGUMENT(URecoilAssets*, RecoilAssets)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

protected:
	
	TSharedPtr<SConstraintCanvas> BackgroundCanvas;
	TArray<TSharedPtr<SWidget>> DotWidgetsOnCanvas;
	FSlateDynamicImageBrush* DotSlateDynamicImageBrush = nullptr;
	FSlateFontInfo IndexSlateFontInfo;

	void RefreshDotContent();
	void DrawGrid() const;

	void DrawHorizonLine(int Index, FSlateDynamicImageBrush* HorizonSlateDynamicImageBrush) const;
	void DrawVerticalLine(int Index, FSlateDynamicImageBrush* VerticalSlateDynamicImageBrush) const;
	void DrawRecoilDot() const;

	// UE SCanvas的GetRenderTransform有奇怪的问题，为了防止出现错误，手动记录Transform
	FTransform2D BackgroundCanvasTransform;
	
private:

	URecoilAssets* EditingRecoilAssets = nullptr;
	bool bRightMouseButtonHold = false;
	FVector2D MouseLocationBeforeRightButtonUp;
	FVector2D MouseLocationLastFrame;
	float GridLineGap = 5.0f;

public:

	/** 外设输入事件 */
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "SRecoilCurveEditorView.h"

#include "CurveEditorScreenSpace.h"
#include "SlateOptMacros.h"
#include "CurveEditor.h"
#include "RecoilAssetsEditorSettings.h"

DEFINE_LOG_CATEGORY(LogRecoilImporter)

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRecoilCurveEditorView::Construct(const FArguments& InArgs)
{
	EditingRecoilAssets = InArgs._RecoilAssets;
	
	DotSlateDynamicImageBrush = 
		new FSlateDynamicImageBrush(*(FPaths::ProjectPluginsDir() / "RecoilAssetsImporter" / "Resources" / "white_dot.png"),
			FVector2D(16, 16));

	IndexSlateFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	IndexSlateFontInfo.Size = 8.0f;

	GridLineGap = 5.0f;
	RefreshDotContent();
}

void SRecoilCurveEditorView::RefreshDotContent()
{
	BackgroundCanvas.Reset();
	BackgroundCanvas = SNew(SConstraintCanvas);
	BackgroundCanvas->SetRenderTransform(BackgroundCanvasTransform);
	
	ChildSlot
	[
		BackgroundCanvas.ToSharedRef()
	];
	DrawGrid();
	DrawRecoilDot();
}

void SRecoilCurveEditorView::DrawGrid() const
{
	FSlateDynamicImageBrush* HorizonGridLineSlateDynamicImageBrush =
		new FSlateDynamicImageBrush(*(FPaths::ProjectPluginsDir() / "RecoilAssetsImporter" / "Resources" / "white_pixel.png"),
			FVector2D(3840, 1));

	FSlateDynamicImageBrush* VerticalGridLineSlateDynamicImageBrush =
		new FSlateDynamicImageBrush(*(FPaths::ProjectPluginsDir() / "RecoilAssetsImporter" / "Resources" / "white_pixel.png"),
			FVector2D(1, 3840));
	
	// 绘制水平线
	for (int i = 0; i < 18; ++i)
	{
		DrawHorizonLine(i, HorizonGridLineSlateDynamicImageBrush);
		DrawHorizonLine(-i, HorizonGridLineSlateDynamicImageBrush);
	}

	// 绘制垂直线
	for (int i = 0; i < 18; ++i)
	{
		DrawVerticalLine(i, VerticalGridLineSlateDynamicImageBrush);
		DrawVerticalLine(-i, VerticalGridLineSlateDynamicImageBrush);
	}
}

void SRecoilCurveEditorView::DrawHorizonLine(int Index,
	FSlateDynamicImageBrush* HorizonSlateDynamicImageBrush) const
{
	const FString CurrentRadius = FString::FromInt(Index * 5);
	BackgroundCanvas->AddSlot()
	.Anchors(FAnchors(0.5, 1.0))
	.Offset(FMargin(0, -Index * GridLineGap * 18))
	.Alignment(FVector2D(0.5, 0.5))
	.AutoSize(true)
	[
		SNew(SImage)
		.Image(HorizonSlateDynamicImageBrush)
		.ColorAndOpacity(FLinearColor(1.0, 1.0, 1.0, 0.5))
	];
	if ((Index & 1) == 0)
	{
		BackgroundCanvas->AddSlot()
		.Anchors(FAnchors(0.0, 1.0))
		.Offset(FMargin(15, -Index * GridLineGap * 18 - GridLineGap))
		.Alignment(FVector2D(0.5, 0.5))
		.AutoSize(true)
		[
			SNew(STextBlock)
			.Text(FText::FromString(CurrentRadius))
			.Font(IndexSlateFontInfo)
		];
	}
}

void SRecoilCurveEditorView::DrawVerticalLine(int Index,
	FSlateDynamicImageBrush* VerticalSlateDynamicImageBrush) const
{
	const FString CurrentRadius = FString::FromInt(Index * 5);
	const FString MinusCurrentRadius = FString::FromInt(-Index * 5);
	
	BackgroundCanvas->AddSlot()
	.Anchors(FAnchors(0.5, 0.5))
	.Offset(FVector2D(Index * GridLineGap * 18, 0))
	.Alignment(FVector2D(0.5, 0.5))
	.AutoSize(true)
	[
		SNew(SImage)
		.Image(VerticalSlateDynamicImageBrush)
		.ColorAndOpacity(FLinearColor(1.0, 1.0, 1.0, 0.5))
	];

	if ((Index & 1) == 0)
	{
		BackgroundCanvas->AddSlot()
		.Anchors(FAnchors(0.5, 1.0))
		.Offset(FMargin(Index * GridLineGap * 18 + GridLineGap, -15))
		.Alignment(FVector2D(0.5, 0.5))
		.AutoSize(true)
		[
			SNew(STextBlock)
			.Text(FText::FromString(CurrentRadius))
			.Font(IndexSlateFontInfo)
		];
	}
}

void SRecoilCurveEditorView::DrawRecoilDot() const
{
	for (int i = 0; i < EditingRecoilAssets->AbsoluteRecoilDataList.Num(); ++i)
	{
		FString CurrentIndexString = FString::FromInt(i);

		BackgroundCanvas->AddSlot()
	   .Anchors(FAnchors(0.5, 1.0))
	   .Offset(FMargin(EditingRecoilAssets->AbsoluteRecoilDataList[i].X * 18 * GridLineGap / 5.0f,
		   EditingRecoilAssets->AbsoluteRecoilDataList[i].Y * -18 * GridLineGap / 5.0f))
	   .AutoSize(true)
	   [
		   SNew(SOverlay)
		   + SOverlay::Slot()
		   .HAlign(HAlign_Center)
		   .VAlign(VAlign_Center)
		   [
			   SNew(SImage)
			   .Image(DotSlateDynamicImageBrush)
			   .ColorAndOpacity(FLinearColor(1.0, 1.0, 1.0, 1.0))
		   ]
		   +SOverlay::Slot()
		   .HAlign(HAlign_Center)
		   .VAlign(VAlign_Center)
		   [
			   SNew(STextBlock)
			   .Text(FText::FromString(CurrentIndexString))
			   .Font(IndexSlateFontInfo)
			   .ColorAndOpacity(FLinearColor::Black)
		   ]
	   ];
	}
}

FReply SRecoilCurveEditorView::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		const FVector2D AnchorPosition = MyGeometry.GetLocalPositionAtCoordinates(FVector2D(0.5, 1.0));
		FVector2D MousePositionAtGraphCoord = MyGeometry.AbsoluteToLocal(MouseEvent.GetLastScreenSpacePosition()) - AnchorPosition;
		MousePositionAtGraphCoord = MousePositionAtGraphCoord - BackgroundCanvasTransform.GetTranslation();
		UE_LOG(LogRecoilImporter, Log, TEXT("%f, %f"), BackgroundCanvasTransform.GetTranslation().X, BackgroundCanvasTransform.GetTranslation().Y);
		MousePositionAtGraphCoord.Y *= -1.0f;
		
		EditingRecoilAssets->AddRecoilData(MousePositionAtGraphCoord / 18 / GridLineGap * 5.0f);
		RefreshDotContent();
		return FReply::Handled();
	}
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		MouseLocationBeforeRightButtonUp = MouseEvent.GetScreenSpacePosition();
		MouseLocationLastFrame = MouseLocationBeforeRightButtonUp;
		bRightMouseButtonHold = true;
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SRecoilCurveEditorView::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bRightMouseButtonHold)
	{
		const FVector2D CurrentMouseLocation = MouseEvent.GetScreenSpacePosition();
		const FVector2D DiffMouseLocation = CurrentMouseLocation - MouseLocationLastFrame;
		MouseLocationLastFrame = CurrentMouseLocation;

		if (DiffMouseLocation.Length() <= 1.0)
		{
			return FReply::Unhandled();
		}
		
		BackgroundCanvasTransform = BackgroundCanvasTransform.Concatenate(FTransform2D(DiffMouseLocation));
		BackgroundCanvas->SetRenderTransform(BackgroundCanvasTransform);
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SRecoilCurveEditorView::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		bRightMouseButtonHold = false;
		const FVector2D CurrentMouseLocation = MouseEvent.GetScreenSpacePosition();
		if ((CurrentMouseLocation - MouseLocationBeforeRightButtonUp).Length() <= 1.0)
		{
			EditingRecoilAssets->RemoveLastRecoilData();
			RefreshDotContent();
		}
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SRecoilCurveEditorView::OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	GridLineGap += MouseEvent.GetWheelDelta() * URecoilAssetsEditorSettings::GetRecoilAssetsEditorSettings()->ViewGraphZoomSpeed;
	GridLineGap = FMath::Clamp(GridLineGap, URecoilAssetsEditorSettings::GetRecoilAssetsEditorSettings()->MinGridGap,
		URecoilAssetsEditorSettings::GetRecoilAssetsEditorSettings()->MaxGridGap);

	RefreshDotContent();
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

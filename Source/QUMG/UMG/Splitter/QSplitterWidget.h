// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Widgets/SUserWidget.h"
#include "Components/PanelWidget.h"
#include "Runtime/Slate/Public/Widgets/Layout/SSplitter.h"
#include "QSplitterWidget.generated.h"

/**
 * Slate分割控件/UMG封装类
 */
UCLASS()
class QUMG_API UQSplitterWidget : public UUserWidget
{
	GENERATED_BODY()
public:	

#if WITH_EDITOR
	virtual const FText GetPaletteCategory()  override;	
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};

UCLASS()
class QUMG_API UCppWgt_UPanelWidget : public UPanelWidget
{
	GENERATED_BODY()
	
};

class QUMG_API SMySlateWidget : public SUserWidget
{
	public:
		SLATE_USER_ARGS(SMySlateWidget)
		{}
		SLATE_END_ARGS()
	
	public:
		virtual void Construct(const FArguments& InArgs);

	protected:
		FSlateBrush brush;
};

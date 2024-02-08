// Fill out your copyright notice in the Description page of Project Settings.


#include "SpriteAnimation.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

void USpriteAnimation::SetCurrentFrame(int frame)
{
	//Set currentFrame value
	currentFrame = frame;

	//Clamp currentFrame
	currentFrame = FMath::Clamp(currentFrame, 0, totalFrames - 1);

	//Sync properties
	SynchronizeProperties();

}

void USpriteAnimation::PlayAnimation()
{
	if (isPlaying)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Animation already playing."));
		return;
	}

	if (playOnce && timesPlayed >= 1)
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}


	//UE_LOG(LogTemp, Warning, TEXT("Play Animation"));
	
	//Was this timer handle every initialized
	if (!TimerHandle.IsValid())
	{
		SetVisibility(ESlateVisibility::Visible);
		//UE_LOG(LogTemp, Warning, TEXT("Timer Handle was valid"));
		isPlaying = true;
;		GetWorld()->GetTimerManager().SetTimer
		(
			TimerHandle,
			this,
			&USpriteAnimation::Tick,
			1.0f / framesPerSecond,
			true
		);
	}

}

void USpriteAnimation::StopAnimation()
{
	if (TimerHandle.IsValid())
	{
		//UE_LOG(LogTemp, Warning, TEXT("STOP!!!"));
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		TimerHandle.Invalidate();
		isPlaying = false;
	}
}

void USpriteAnimation::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	//UE_LOG(LogTemp, Warning, TEXT("SynchronizeProperties"));
	//Cast this texture into brush
	UTexture2D * CurrentTex = Cast<UTexture2D>(Brush.GetResourceObject());
	if (CurrentTex == nullptr)
		return;

	FVector2D CurrentTexSize(CurrentTex->GetSizeX(), CurrentTex->GetSizeY());

	int maxColumns = FMath::FloorToInt(CurrentTexSize.X / Brush.ImageSize.X);
	int rows = FMath::FloorToInt(currentFrame / maxColumns);
	int columns = currentFrame % maxColumns;

	FVector2D minVector(Brush.ImageSize.X * columns, Brush.ImageSize.Y * rows);
	FVector2D maxVector = minVector + Brush.ImageSize;
	FBox2D UVCoords(minVector / CurrentTexSize, maxVector / CurrentTexSize);
	UVCoords.bIsValid = true;

	Brush.SetUVRegion(MoveTemp(UVCoords));

}

void USpriteAnimation::Tick()
{
	currentFrame++;
	if (currentFrame > totalFrames - 1)
	{
		if (playOnce)
		{
			SetVisibility(ESlateVisibility::Hidden);
			StopAnimation();
		}
		timesPlayed++;
		currentFrame = 0;
	
	}

	SynchronizeProperties();
}

void USpriteAnimation::Reset()
{
	timesPlayed = 0;
}
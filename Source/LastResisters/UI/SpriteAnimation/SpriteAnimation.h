// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "SpriteAnimation.generated.h"

UCLASS()
class LASTRESISTERS_API USpriteAnimation : public UImage
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpriteAnimation")
		int framesPerSecond = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpriteAnimation")
		int currentFrame = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpriteAnimation")
		int totalFrames = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpriteAnimation")
		bool playOnce = false;

	//Boolean that checks if an animation is already playing.
	bool isPlaying = false;

	int timesPlayed = 0;

	void Reset();

	void Tick();

	FTimerHandle TimerHandle;

public:

	UFUNCTION(BlueprintCallable, Category = "SpriteAnimation")
		void SetCurrentFrame(int frame);

	UFUNCTION(BlueprintCallable, Category = "SpriteAnimation")
		void PlayAnimation();

	UFUNCTION(BlueprintCallable, Category = "SpriteAnimation")
		void StopAnimation();

	virtual void SynchronizeProperties();


};

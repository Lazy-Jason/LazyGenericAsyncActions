// // Copyright (C) 2024 Job Omondiale - All Rights Reserved


#include "AsyncActions/AsyncLazyDelayedAction.h"

void UAsyncLazyDelayedAction::Activate()
{
	if(!IsValid(NewWorldContextObject))
	{
		SetReadyToDestroy();
		return;
	}
	
	ElapsedTime = 0.0f;
	NewWorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAsyncLazyDelayedAction::UpdateProgress, Interval, true);
}

UAsyncLazyDelayedAction* UAsyncLazyDelayedAction::AsyncDelayActionWithProgress(UObject* WorldContextObject,
	float DelayDuration, float UpdateInterval)
{
	UAsyncLazyDelayedAction* Action = NewObject<UAsyncLazyDelayedAction>();

	Action->NewWorldContextObject = WorldContextObject;
	Action->Duration = DelayDuration;
	Action->Interval = UpdateInterval;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UAsyncLazyDelayedAction::UpdateProgress()
{
	ElapsedTime += Interval;
	const float Progress = FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f);
    
	OnProgress.Broadcast(Progress);

	if (Progress >= 1.0f)
	{
		OnComplete.Broadcast();
		if(IsValid(NewWorldContextObject))
		{
			NewWorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		SetReadyToDestroy();
	}
}

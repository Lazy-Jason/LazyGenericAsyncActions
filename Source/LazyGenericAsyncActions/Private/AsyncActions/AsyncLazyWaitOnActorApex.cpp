// // Copyright (C) 2024 Job Omondiale - All Rights Reserved


#include "AsyncActions/AsyncLazyWaitOnActorApex.h"

void UAsyncLazyWaitOnActorApex::Activate()
{
	if (!IsValid(TargetActor) || !IsValid(NewWorldContextObject))
	{
		SetReadyToDestroy();
		return;
	}

	LastZPosition = TargetActor->GetActorLocation().Z;
	bIsAscending = true;
	NewWorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAsyncLazyWaitOnActorApex::CheckApex, Interval, true);
}

UAsyncLazyWaitOnActorApex* UAsyncLazyWaitOnActorApex::AsyncCheckActorApex(UObject* WorldContextObject, AActor* ActorToCheck,
	float CheckInterval)
{
	UAsyncLazyWaitOnActorApex* Action = NewObject<UAsyncLazyWaitOnActorApex>();

	Action->NewWorldContextObject = WorldContextObject;
	Action->TargetActor = ActorToCheck;
	Action->Interval = CheckInterval;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UAsyncLazyWaitOnActorApex::CheckApex()
{
	if (!IsValid(TargetActor))
	{
		SetReadyToDestroy();
		return;
	}

	// storing the current Z location.
	const float CurrentZ = TargetActor->GetActorLocation().Z;

	if (bIsAscending && CurrentZ < LastZPosition)
	{
		// We've reached the apex
		OnApexReached.Broadcast(LastZPosition);
		bIsAscending = false;
	}
	// the next frame after we have reached the apex
	else if (!bIsAscending && CurrentZ < LastZPosition)
	{
		// We've passed the apex and are descending
		OnApexPassed.Broadcast();
		NewWorldContextObject->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		SetReadyToDestroy();
	}

	LastZPosition = CurrentZ;
}

// // Copyright (C) 2024 Job Omondiale - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncLazyDelayedAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelayedActionProgressSignature, float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelayedActionCompleteSignature);

/**
 * Asynchronous action to perform a delayed action with progress updates.
 * This action waits for a specified duration, providing periodic progress updates,
 * and then completes the action.
 */
UCLASS()
class LAZYGENERICASYNCACTIONS_API UAsyncLazyDelayedAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	
	/**
	 * Called periodically to report progress of the delayed action.
	 * Progress is reported as a value between 0.0 and 1.0.
	 */
	UPROPERTY(BlueprintAssignable)
	FDelayedActionProgressSignature OnProgress;

	/**
	 * Called when the delayed action is complete.
	 */
	UPROPERTY(BlueprintAssignable)
	FDelayedActionCompleteSignature OnComplete;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<UObject> NewWorldContextObject;
	
	float Duration;
	float Interval;
	float ElapsedTime;
	FTimerHandle TimerHandle;

public:
	/**
	 * Begins the delayed action process.
	 */
	virtual void Activate() override;
	
	/**
	 * Creates and initializes a new instance of the delayed action.
	 *
	 * @param WorldContextObject The world context object.
	 * @param DelayDuration The total duration of the delay (in seconds).
	 * @param UpdateInterval The time interval between progress updates (in seconds).
	 * @return The created UDelayedActionWithProgressAsync object.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Lazy Async Action")
	static UAsyncLazyDelayedAction* AsyncDelayActionWithProgress(UObject* WorldContextObject, float DelayDuration, float UpdateInterval = 0.1f);

private:
	void UpdateProgress();
};

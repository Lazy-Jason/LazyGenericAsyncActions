// // Copyright (C) 2024 Job Omondiale - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncLazyWaitOnActorApex.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnApexReachedSignature, float, ApexHeight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnApexPassedSignature);

/**
 * Asynchronous action to check when an actor reaches its apex (highest point).
 * This action monitors the actor's Z position and fires events when the apex is reached and passed.
 */
UCLASS()
class LAZYGENERICASYNCACTIONS_API UAsyncLazyWaitOnActorApex : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/**
	 * Called when the apex (highest point) is reached.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnApexReachedSignature OnApexReached;

	/**
	 * Called when the actor has passed its apex and started descending.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnApexPassedSignature OnApexPassed;

private:

	UPROPERTY()
	AActor* TargetActor;

	UPROPERTY(Transient)
	TObjectPtr<UObject> NewWorldContextObject;
	
	float Interval;
	float LastZPosition;
	bool bIsAscending;
	FTimerHandle TimerHandle;

public:
	/**
	* Begins the apex checking process.
	*/
	virtual void Activate() override;

	/**
	 * Creates and initializes a new instance of the apex checking action.
	 *
	 * @param ActorToCheck The actor whose apex we want to detect.
	 * @param CheckInterval The time interval between position checks (in seconds).
	 * @return The created UCheckActorApexAsync object.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Lazy Async Action")
	static UAsyncLazyWaitOnActorApex* AsyncCheckActorApex(UObject* WorldContextObject, AActor* ActorToCheck, float CheckInterval = 0.1f);
	
private:
	void CheckApex();
};

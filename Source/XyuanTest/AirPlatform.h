// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirPlatform.generated.h"

class UStaticMeshComponent;
class UPrimitiveComponent;
struct FHitResult;
/**
 *
 */
UCLASS()
class XYUANTEST_API AAirPlatform : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditDefaultsOnly, Category = Fall)
	float DelayToFall = 1.0;
	
public:	
	// Sets default values for this actor's properties
	AAirPlatform();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void PlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	void StartFall();

};

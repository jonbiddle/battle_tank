// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& CameraWorldLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector TargetLocation, FVector& HitLocation) const;

	void DebugLine(FVector Start, FVector End, FColor Color) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
	bool DebugLineTracesEnabled = false;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

};

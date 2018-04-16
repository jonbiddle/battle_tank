// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "Tank.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController DOES NOT have a Tank"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing Tank: %s"), *GetControlledTank()->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out param


	// Raycast from center of view to point on screen
	// aim the tank

	if (GetSightRayHitLocation(OUT HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, OUT FVector& CameraWorldLocation, OUT FVector& LookDirection) const
{
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraWorldLocation,
		OUT LookDirection
	);
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{

	FVector PlayerCrosshairLocation;
	FVector PlayerCrosshairDirection;
	FRotator PlayerViewAimpointOffset = FRotator(11.f, 0.f, 0.f);
	FVector PlayerTargetLocation;

	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation,
		ViewportSizeY * CrosshairYLocation
	);
	///UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())

	// deproject screen position of crosshair to world direction
	// line trace from view to aim location

	if (GetLookDirection(ScreenLocation, OUT PlayerCrosshairLocation, OUT PlayerCrosshairDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerCrosshairLocation: %s, PlayerCrosshairDirection: %s"), *PlayerCrosshairLocation.ToString(), *PlayerCrosshairDirection.ToString());
		if (GetLookVectorHitLocation(PlayerCrosshairLocation + PlayerCrosshairDirection * LineTraceRange, HitLocation)) {
			return true;
		}
	}
	HitLocation = FVector(0);
	return false;


	//PlayerTargetLocation = PlayerCrosshairLocation + PlayerCrosshairDirection * LineTraceRange;

	
	/*
	GetPlayerViewPoint(
	OUT PlayerViewLocation,
	OUT PlayerViewRotation
	);
	HitLocation = PlayerViewLocation + (PlayerViewRotation + PlayerViewAimpointOffset).Vector() * 500000;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewLocation,
		PlayerTargetLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParams
	);


	*/

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector TargetLocation, OUT FVector& HitLocation) const
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult,
		StartLocation,
		TargetLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		DebugLine(StartLocation, HitLocation, FColor(0, 255, 0));
		return true;
	} 
	DebugLine(StartLocation, TargetLocation, FColor(255, 0, 255));
	return false;
}

void ATankPlayerController::DebugLine(FVector Start, FVector End, FColor Color) const {

	if (DebugLineTracesEnabled) {
		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			Color,
			0.f,
			0,
			10.f
		);
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



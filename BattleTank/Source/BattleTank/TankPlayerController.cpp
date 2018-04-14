// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"



ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController DOES NOT have a Tank"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing Tank: %s"), *GetControlledTank()->GetName());
	}
}
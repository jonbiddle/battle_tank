// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIControlled Tank DOES NOT have a Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController posessing Tank: %s"), *ControlledTank->GetName());
	}

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIControlled could not find the PlayerTank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found the PlayerTank: %s"), *PlayerTank->GetName());
	}

}

void ATankAIController::Tick(float DeltaSeconds) {

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (!ControlledTank) { return; }
	if (!PlayerTank) { return; }

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const {
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (!PlayerController) {
		return nullptr;
	}

	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerController);

	return TankPlayerController->GetControlledTank();

}
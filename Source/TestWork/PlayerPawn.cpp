// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"

#include "Engine.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveAction", EInputEvent::IE_Pressed, this, &APlayerPawn::MoveActionPressed);

	PlayerInputComponent->BindAction("BarrierAction", EInputEvent::IE_Pressed, this, &APlayerPawn::BarrierActionPressed);

}

void APlayerPawn::MoveActionPressed()
{
	//
	APlayerController *PC= (APlayerController*)GetWorld()->GetFirstPlayerController();
	//
	FHitResult Hit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	//
//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, Hit.Location.ToString());
	//
	if (Hit.Actor == nullptr)
		return;

	if (Hit.GetActor()->GetActorLabel() == TEXT("Landscape1")) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, Hit.Location.ToString());
	}
	else if (Hit.GetActor()->GetActorLabel() == TEXT("Cube5")) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, Hit.Location.ToString());
	}
	FString T = Hit.GetActor()->GetActorLabel();
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, T);
	//
}

void APlayerPawn::BarrierActionPressed()
{
//	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, FString::Printf(TEXT("%s"), TEXT("BarrierAction")));

}


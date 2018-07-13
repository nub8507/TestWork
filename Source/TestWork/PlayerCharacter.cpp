

#include "PlayerCharacter.h"

#include "Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::OnHit(AActor* HitComp, AActor* OtherActor, const FHitResult& Hit)
{
	//
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("PC EventHIT"));
	//
}


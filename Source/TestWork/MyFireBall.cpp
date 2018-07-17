

#include "MyFireBall.h"


// Sets default values
AMyFireBall::AMyFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->BaseProjectileMovement = nullptr;
}

// Called when the game starts or when spawned
void AMyFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	this->TTL = 10;
}

// Called every frame
void AMyFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->TTL -= DeltaTime;
	//
	if (this->TTL < 0) this->Destroy();
	//
}

void AMyFireBall::InitSpeed(float Speed,float Time)
{
	//
	if (!(this->BaseProjectileMovement == nullptr)) {
		this->BaseProjectileMovement->InitialSpeed = Speed;
		this->BaseProjectileMovement->MaxSpeed = Speed;
	}
	//
	this->TTL = Time;
}


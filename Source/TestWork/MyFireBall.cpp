

#include "MyFireBall.h"


// Sets default values
AMyFireBall::AMyFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFireBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

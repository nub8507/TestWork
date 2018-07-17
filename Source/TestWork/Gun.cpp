

#include "Gun.h"

#include "MyFireBall.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	this->SpawnTime = 5;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SpawnTime -= DeltaTime;
	//
	if (this->SpawnTime < 0) {

		TSubclassOf<class AMyFireBall> aPlayerProjectile;
		aPlayerProjectile = FindOrLoadBluePrintClass(TEXT("Blueprint'/Game/GameBP/Actors/BPFireBall.BPFireBall_C'"));
		AMyFireBall* Proj;
		Proj = GetWorld()->SpawnActor<AMyFireBall>(aPlayerProjectile.Get(), this->GetActorLocation(), this->GetActorRotation());
		Proj->InitSpeed(300.f,15);
		//
		this->SpawnTime = 5;
	}
	//
}

TSubclassOf<class UObject> AGun::FindOrLoadBluePrintClass(const TCHAR* path)
{

	UObject* something = StaticLoadObject(UObject::StaticClass(), nullptr, path);

	if (something == nullptr) return nullptr;

	TSubclassOf<class UObject> MyItemBlueprint;
	MyItemBlueprint = (UClass*)something;

	return MyItemBlueprint;
}



#include "EnemyCharacter.h"

#include "Engine.h"
#include "MyWay.h"
#include "StaticLogic.h"
#include "MyLevelScriptActor.h"
#include "TwoDimensionalArray.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//
	RecalcWay(true);
	this->LastPosition = UStaticLogic::FindClickPosition(this->GetActorLocation().X, this->GetActorLocation().Y);
	//
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	if (Way->WayPoints.Num() == 0)
		RecalcWay(true);
	//
	ExecMove(DeltaTime);
	//
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::ExecMove(float Delta)
{
	//
	float MoveSpeed = 250.f;
	//
	FVector CurrPos = this->GetActorLocation();
	FVector Dest = UStaticLogic::FindPositionFromPoint(this->LastPosition, CurrPos.Z);
	FVector DistVector;
	DistVector = Dest - CurrPos;
	DistVector = DistVector.GetClampedToMaxSize2D(1.0f);
	//
	const FVector Movement = DistVector * MoveSpeed * Delta;
	//
	if ((Dest - CurrPos).Size2D() <= 1.5f * Movement.Size2D()) {
		//
		this->LastPosition = UStaticLogic::FindNextPoint(this->Way, this->LastPosition);
		Dest = UStaticLogic::FindPositionFromPoint(this->LastPosition, CurrPos.Z);
		this->MoveRotation = DistVector.Rotation();
		//
		if (Way->WayPoints.Num() > 0) {
			//
			if (this->LastPosition == Way->WayPoints[Way->WayPoints.Num() - 1])
				Way->MoveDirection = false;
			else if (this->LastPosition == Way->WayPoints[0])
				Way->MoveDirection = true;
			//
		}
		//
		if (this->NeedRecalcWay){
			if (this->LastPosition == this->StartPoint)
				RecalcWay(true);
			else if (this->LastPosition == this->FinishPoint) 
				RecalcWay(false);
		}
		//
		return;
	}
	//
	RootComponent->MoveComponent(Movement, this->MoveRotation, true);
	//
}

void AEnemyCharacter::RecalcWay(bool Direction)
{
	AMyLevelScriptActor* Level = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (Level == nullptr) return;
	//
	this->Way = UStaticLogic::FindWay(this->StartPoint, this->FinishPoint, Level->Map, this, Level);
	this->Way->MoveDirection = Direction;
	this->Way->WayCyclical = true;
	//
	this->NeedRecalcWay = false;
	//
}


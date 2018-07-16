

#include "PlayerCharacter.h"

#include "Engine.h"
#include "Landscape.h"
#include "MyWay.h"
#include "StaticLogic.h"
#include "MyLevelScriptActor.h"
#include "TwoDimensionalArray.h"
#include "Barrier.h"


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
	
	this->LastPosition = FIntPoint(0, 0);
	//
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	this->ExecMove(DeltaTime);
	//
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveAction", EInputEvent::IE_Pressed, this, &APlayerCharacter::MoveActionPressed);

	PlayerInputComponent->BindAction("BarrierAction", EInputEvent::IE_Pressed, this, &APlayerCharacter::BarrierActionPressed);

}

void APlayerCharacter::OnHit(AActor* HitComp, AActor* OtherActor, const FHitResult& Hit)
{
	//
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("PC EventHIT"));
	//
}

void APlayerCharacter::MoveActionPressed()
{
	//
	APlayerController *PC = (APlayerController*)GetWorld()->GetFirstPlayerController();
	//
	FHitResult Hit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	//
	//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, Hit.Location.ToString());
	//
	if (Hit.Actor == nullptr)
		return;

	if (Cast<ALandscape>(Hit.GetActor())!=nullptr)	{
		AMyLevelScriptActor* Level = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (Level == nullptr) return;
		//
		FIntPoint F = UStaticLogic::FindClickPosition(Hit.Location.X, Hit.Location.Y);
		UMyWay *T = UStaticLogic::FindWay(this->LastPosition, F, Level->Map, this, Level);
		this->Way = T;
	}
	//
}

void APlayerCharacter::BarrierActionPressed()
{
	//	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, FString::Printf(TEXT("%s"), TEXT("BarrierAction")));
	APlayerController *PC = (APlayerController*)GetWorld()->GetFirstPlayerController();
	//
	FHitResult Hit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	//
	if (Hit.Actor == nullptr)
		return;
	//
	if (Cast<ALandscape>(Hit.GetActor()) != nullptr) {
		AMyLevelScriptActor* Level = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (Level == nullptr) return;
		//
		FIntPoint F = UStaticLogic::FindClickPosition(Hit.Location.X, Hit.Location.Y);
		//
		if (F == this->LastPosition)return;
		//

		//
		Level->Map->Set(F.X, F.Y, -1);
		//
		FVector PosBarrier=UStaticLogic::FindPositionFromPoint(F);
		//
		TSubclassOf<class ABarrier> aBarrier;
		aBarrier = FindOrLoadBluePrintClass(TEXT("Blueprint'/Game/GameBP/Actors/BPBarrier.BPBarrier_C'"));
		if (aBarrier != nullptr) {
			GetWorld()->SpawnActor<ABarrier>(aBarrier.Get(), PosBarrier, FRotator(0,0,0));
		}
		//
	}
	else if (Cast<ABarrier>(Hit.GetActor()) != nullptr) {
		AMyLevelScriptActor* Level = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (Level == nullptr) return;
		//
		FIntPoint F = UStaticLogic::FindClickPosition(Hit.Location.X, Hit.Location.Y);
		Level->Map->Set(F.X, F.Y, 0);
		Hit.GetActor()->Destroy();
	}
	

}

void APlayerCharacter::ExecMove(float Delta)
{
	//
	float MoveSpeed = 200.f;
	//
	FVector CurrPos = this->GetActorLocation();
	FVector Dest = UStaticLogic::FindPositionFromPoint(this->LastPosition);
	FVector DistVector;
	DistVector = Dest - CurrPos;
	DistVector = DistVector.GetClampedToMaxSize2D(1.0f);
	//
	const FVector Movement = DistVector * MoveSpeed * Delta;
	//
	if (DistVector.Size2D() < 0.5f) {
		this->LastPosition = UStaticLogic::FindNextPoint(this->Way, this->LastPosition);
		Dest = UStaticLogic::FindPositionFromPoint(this->LastPosition);
		this->MoveRotation = (Dest - CurrPos).Rotation();
		return;
	}
	//
	RootComponent->MoveComponent(Movement, this->MoveRotation, true);
	//
}

TSubclassOf<class UObject> APlayerCharacter::FindOrLoadBluePrintClass(const TCHAR* path)
{

	UObject* something = StaticLoadObject(UObject::StaticClass(), nullptr, path);

	if (something == nullptr) return nullptr;

	TSubclassOf<class UObject> MyItemBlueprint;
	MyItemBlueprint = (UClass*)something;

	return MyItemBlueprint;
}


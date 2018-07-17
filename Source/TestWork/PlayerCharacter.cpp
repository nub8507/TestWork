

#include "PlayerCharacter.h"

#include "Engine.h"
#include "Landscape.h"
#include "MyWay.h"
#include "StaticLogic.h"
#include "MyLevelScriptActor.h"
#include "TwoDimensionalArray.h"
#include "Barrier.h"
#include "MenuComponent.h"
#include "EnemyCharacter.h"


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
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	MyPlayer->SetPause(true);
	TSubclassOf<class UUserWidget> wMainMenu;
	wMainMenu = FindOrLoadBluePrintClass(TEXT("Blueprint'/Game/GameBP/Actors/MenuDefeat.MenuDefeat_C'"));
	UMenuComponent* UW = CreateWidget<UMenuComponent>(MyPlayer, wMainMenu);
	if (UW)
	{
		UW->AddToViewport(9999);
		//
		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetHideCursorDuringCapture(true);
		MyPlayer->SetInputMode(Mode);
		MyPlayer->bShowMouseCursor = true;
	}
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
		for (int i = 0; i < Level->WayList.Num(); i++) {
			AEnemyCharacter*T= Cast<AEnemyCharacter>(Level->WayList[i]->Owner);
			if (T != nullptr && T->LastPosition == F)return;
		}
		//
		Level->Map->Set(F.X, F.Y, -1);
		//
		FVector PosBarrier=UStaticLogic::FindPositionFromPoint(F,10);
		//
		TSubclassOf<class ABarrier> aBarrier;
		aBarrier = FindOrLoadBluePrintClass(TEXT("Blueprint'/Game/GameBP/Actors/BPBarrier.BPBarrier_C'"));
		if (aBarrier != nullptr) {
			GetWorld()->SpawnActor<ABarrier>(aBarrier.Get(), PosBarrier, FRotator(0,0,0));
		}
		//
		RecalcWays(FindWaysForRecalc(F));
		//
	}
	else if (Cast<ABarrier>(Hit.GetActor()) != nullptr) {
		AMyLevelScriptActor* Level = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (Level == nullptr) return;
		//
		FIntPoint F = UStaticLogic::FindClickPosition(Hit.Location.X, Hit.Location.Y);
		Level->Map->Set(F.X, F.Y, 0);
		Hit.GetActor()->Destroy();
		//
		RecalcWays(Level->WayList);
		//
	}
	
}

void APlayerCharacter::ExecMove(float Delta)
{
	//
	float MoveSpeed = 200.f;
	//
	FVector CurrPos = this->GetActorLocation();
	FVector Dest = UStaticLogic::FindPositionFromPoint(this->LastPosition, CurrPos.Z);
	FVector DistVector;
	DistVector = Dest - CurrPos;
	DistVector = DistVector.GetClampedToMaxSize2D(1.0f);
	//
	const FVector Movement = DistVector * MoveSpeed * Delta;
	//
	if ((Dest - CurrPos).Size2D() < 2.f) {
		//
		if (this->LastPosition == FIntPoint(30, 30)){
			ShowMenuWin();
			return;
		}
		//
		this->LastPosition = UStaticLogic::FindNextPoint(this->Way, this->LastPosition);
		Dest = UStaticLogic::FindPositionFromPoint(this->LastPosition, CurrPos.Z);
		this->MoveRotation = DistVector.Rotation();
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

void APlayerCharacter::ShowMenuWin()
{
	//
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	MyPlayer->SetPause(true);
	TSubclassOf<class UUserWidget> wMainMenu;
	wMainMenu = FindOrLoadBluePrintClass(TEXT("Blueprint'/Game/GameBP/Actors/MenuWin.MenuWin_C'"));
	UMenuComponent* UW = CreateWidget<UMenuComponent>(MyPlayer, wMainMenu);
	if (UW)
	{
		UW->AddToViewport(9999);
		//
		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetHideCursorDuringCapture(true);
		MyPlayer->SetInputMode(Mode);
		MyPlayer->bShowMouseCursor = true;
	}
	//
}

TArray<UMyWay*> APlayerCharacter::FindWaysForRecalc(FIntPoint Barrier)
{
	TArray<UMyWay*> WayList;
	WayList.Empty();
	//
	AMyLevelScriptActor* Level = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	for (int i = 0; i < Level->WayList.Num(); i++) {
		for (int j = 0; j < Level->WayList[i]->WayPoints.Num(); j++) {
			if (Level->WayList[i]->WayPoints[j] == Barrier) WayList.Add(Level->WayList[i]);
		}
	}
	//
	return WayList;
}

void APlayerCharacter::RecalcWays(TArray<UMyWay*> WayList)
{
	AMyLevelScriptActor* Level = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	//
	for (int i = 0; i < WayList.Num(); i++) {
		if (!WayList[i]->WayCyclical) {
			UStaticLogic::FindWay(this->LastPosition, WayList[i]->WayPoints[WayList[i]->WayPoints.Num()-1], Level->Map, this, Level);
		}
		else {
			AEnemyCharacter* T = Cast<AEnemyCharacter>(WayList[i]->Owner);
			if (WayList[i]->MoveDirection) {
				UStaticLogic::FindWay(T->LastPosition, WayList[i]->WayPoints[WayList[i]->WayPoints.Num() - 1], Level->Map, T, Level);
				T->NeedRecalcWay = true;
			}
			else {
				UStaticLogic::FindWay(T->LastPosition, WayList[i]->WayPoints[0], Level->Map, T, Level);
				T->NeedRecalcWay = true;
			}
		}
	}

	//
}


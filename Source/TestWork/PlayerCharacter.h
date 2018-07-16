

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

class ALandscape;
class UMyWay;

UCLASS()
class TESTWORK_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyData")
		FRotator MoveRotation;
	
	UFUNCTION(BlueprintCallable)
		void OnHit(AActor* HitComp, AActor* OtherActor, const FHitResult& Hit);

private:

	void MoveActionPressed();

	void BarrierActionPressed();

	UPROPERTY()
		FIntPoint LastPosition;

	UMyWay* Way;

	void ExecMove(float Delta);

	TSubclassOf<class UObject> FindOrLoadBluePrintClass(const TCHAR* path);
};

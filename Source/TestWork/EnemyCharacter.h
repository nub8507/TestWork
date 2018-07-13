

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class TESTWORK_API AEnemyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void OnHit(AActor* HitComp, AActor* OtherActor, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyData")
		FIntPoint StartPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyData")
		FIntPoint FinishPoint;


};

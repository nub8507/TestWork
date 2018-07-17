#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "GameFramework/Actor.h"
#include "MyFireBall.generated.h"

UCLASS()
class TESTWORK_API AMyFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFireBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* BaseProjectileMovement;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitSpeed(float Speed,float Time);
	
private:
	float TTL;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ReflectArrow.generated.h"

UCLASS()
class NEOPLETESTP_KJH_API AReflectArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReflectArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);//Hit 이벤트,부딪혔을때 액터 삭제

	float CurrentLife;
private:	
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;//Root, Box 형태 Collision

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ActorMesh;//Root 자식관계로, 화살표 Mesh

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;//발사체의 움직임을 위한 Projectilemovement

	AActor* PlayerPawn;//플레이어가 조종한 Pawn

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AReflectArrow> ActorToSpawn;

	
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* MaterialBlue;
};

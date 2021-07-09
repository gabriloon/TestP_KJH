// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectArrow.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AReflectArrow::AReflectArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision= CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));//BoxCollision 생성
	BoxCollision->SetBoxExtent(FVector(50.f, 35.f, 30.f));//Box 의 범위 세팅
	BoxCollision->SetCollisionProfileName("Projectile");//콜리전 프리셋:IgnoreOnlyPawn , 문제 상으로 상관없는데 적 캐릭터 맞게 하기 위해서는 Custom으로 변경
	RootComponent=BoxCollision;//BoxCollision 을 Root로 지정
	ActorMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));//Mesh 생성
	ActorMesh->SetupAttachment(RootComponent);//Mesh 를 Box 의 자식 관계로 세팅
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ArrowMeshAsset(TEXT("/Game/StarterContent/Blueprints/Assets/SM_Arrows"));//Mesh 의 모습을 화살표로
	ActorMesh->SetStaticMesh(ArrowMeshAsset.Object);
	ActorMesh->SetRelativeLocation(FVector(-30.0f,0.f,0.f));//화살표 Mesh의 겉모습이 Box의 중심위치로 보이게 이동 
	ActorMesh->SetRelativeScale3D(FVector(0.1f));//화살표 크기 조정
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));//ProjectileMovement 생성
	ProjectileMovementComponent->SetUpdatedComponent(BoxCollision);
	ProjectileMovementComponent->InitialSpeed=100.0f;//속도 100
	ProjectileMovementComponent->ProjectileGravityScale=0.0f;//중력 영향 받지 않게 0
	InitialLifeSpan = 5.f;//5초후에 자동 삭제
	MaterialBlue=CreateDefaultSubobject<UMaterialInterface>("MaterialBlue");
}

// Called when the game starts or when spawned
void AReflectArrow::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn= UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//플레이어 Pawn 호출
	BoxCollision->OnComponentHit.AddDynamic(this, &AReflectArrow::OnHit);//BoxCollision 의 Hit 이벤트 초기 작업
	ActorMesh->SetMaterial(0,MaterialBlue);
}

// Called every frame
void AReflectArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReflectArrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	
	if((OtherActor!=nullptr)&&(OtherActor!=this)&&(OtherComp !=nullptr)&&(OtherActor!=PlayerPawn))//플레이어와 ArrowActor 를 제외하고 Hit이벤트 발생 체크,반대방향으로 진행방향 전환
	{
 	 FRotator Rotation=GetActorRotation()+FRotator(0.0f,180.0f,0.0f);
	 BoxCollision->SetRelativeRotation(Rotation);
	 Destroy();//기존 Arrow 삭제
	CurrentLife=GetLifeSpan();
	FActorSpawnParameters SpawnParams;
    FVector Location=GetActorLocation();
	AReflectArrow* SplitAr1 = GetWorld()->SpawnActor<AReflectArrow>(ActorToSpawn,Location,Rotation, SpawnParams);
	SplitAr1->CurrentLife=5.0f-CurrentLife;
	SplitAr1->SetLifeSpan(SplitAr1->CurrentLife);
	}
}


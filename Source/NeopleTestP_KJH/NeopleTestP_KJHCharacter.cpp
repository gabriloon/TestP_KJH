// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeopleTestP_KJHCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ANeopleTestP_KJHCharacter::ANeopleTestP_KJHCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}


void ANeopleTestP_KJHCharacter::BeginPlay() //Widget 영향
{
    Super::BeginPlay();
}

void ANeopleTestP_KJHCharacter::Tick(float DeltaTime) 
{
	 Super::Tick(DeltaTime);
	APlayerController* PlayerController=UGameplayStatics::GetPlayerController(this, 0);//플레이어 컨트롤러 호출
 if(PlayerController==nullptr)
    {return;}
 
 if(PlayerController->IsInputKeyDown(EKeys::Q)){//플레이어가 Q 키 누를경우 CountFloat에 저장
 CountFloat=PlayerController->GetInputKeyTimeDown(EKeys::Q);
 }
}


//////////////////////////////////////////////////////////////////////////
// Input

void ANeopleTestP_KJHCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ANeopleTestP_KJHCharacter::ShootArrow);
	
	//PlayerInputComponent->BindAction("SpecialShoot", IE_Released, this, &ANeopleTestP_KJHCharacter::SpecialShootArrow);
	PlayerInputComponent->BindAction("SpecialShoot", IE_Pressed, this, &ANeopleTestP_KJHCharacter::SpecialShootArrow);
	
	PlayerInputComponent->BindAxis("MoveRight", this, &ANeopleTestP_KJHCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ANeopleTestP_KJHCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ANeopleTestP_KJHCharacter::TouchStopped);

}

void ANeopleTestP_KJHCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ANeopleTestP_KJHCharacter::ShootArrow() //Q 키 공격 관련 함수
{
	const FVector Location = GetActorLocation()+FVector(20.0f, 0.0f, -46.0f);
	const FRotator Rotation = GetActorRotation();//발사체 위치 및 방향 세팅

	if(CountFloat>=3.0f){//Q 키를 3초 넘게 눌렀을 경우
	GetWorld()->SpawnActor<AActor>(ChargeArrowActor,Location,Rotation);
		//CountFloat=0.0f;
	}else{
	GetWorld()->SpawnActor<AActor>(NormalArrowActor,Location,Rotation);
	}
}

void ANeopleTestP_KJHCharacter::SpecialShootArrow() //W 키 공격 관련 함수
{
	const FVector Location = GetActorLocation()+FVector(20.0f, 0.0f, -46.0f);
	const FRotator Rotation = GetActorRotation();//발사체 위치 및 방향 세팅
	APlayerController* PlayerController=UGameplayStatics::GetPlayerController(this, 0);
 	if(PlayerController==nullptr)
    	{return;}

if(PlayerController->IsInputKeyDown(EKeys::Q))//Q 키를 눌렀을 경우에
{
	if(CountFloat<=1.0f){//CountFloat 를 확인해보고 Q 키 누른시간 1초 이하일때
    GetWorld()->SpawnActor<AActor>(SplitArrowActor,Location,Rotation);//분리 발사체 호출
    }else{//플레이어가 W,Q 키를 눌렀지만 Q 키 누른 시간이 1초 초과한 경우에
	GetWorld()->SpawnActor<AActor>(ReverseArrowActor,Location,Rotation);//반사 발사체 호출
	}
}else{//W키만 눌렀을 경우에
	GetWorld()->SpawnActor<AActor>(ReverseArrowActor,Location,Rotation);//반사 발사체 호출
}

}


void ANeopleTestP_KJHCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ANeopleTestP_KJHCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}


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


void ANeopleTestP_KJHCharacter::BeginPlay() //Widget ??????
{
    Super::BeginPlay();
}

void ANeopleTestP_KJHCharacter::Tick(float DeltaTime) 
{
	 Super::Tick(DeltaTime);
	APlayerController* PlayerController=UGameplayStatics::GetPlayerController(this, 0);//???????????? ???????????? ??????
 if(PlayerController==nullptr)
    {return;}
 
 if(PlayerController->IsInputKeyDown(EKeys::Q)){//??????????????? Q ??? ???????????? CountFloat??? ??????
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

void ANeopleTestP_KJHCharacter::ShootArrow() //Q ??? ?????? ?????? ??????
{
	const FVector Location = GetActorLocation()+FVector(20.0f, 0.0f, -46.0f);
	const FRotator Rotation = GetActorRotation();//????????? ?????? ??? ?????? ??????

	if(CountFloat>=3.0f){//Q ?????? 3??? ?????? ????????? ??????
	GetWorld()->SpawnActor<AActor>(ChargeArrowActor,Location,Rotation);
		//CountFloat=0.0f;
	}else{
	GetWorld()->SpawnActor<AActor>(NormalArrowActor,Location,Rotation);
	}
}

void ANeopleTestP_KJHCharacter::SpecialShootArrow() //W ??? ?????? ?????? ??????
{
	const FVector Location = GetActorLocation()+FVector(20.0f, 0.0f, -46.0f);
	const FRotator Rotation = GetActorRotation();//????????? ?????? ??? ?????? ??????
	APlayerController* PlayerController=UGameplayStatics::GetPlayerController(this, 0);
 	if(PlayerController==nullptr)
    	{return;}

if(PlayerController->IsInputKeyDown(EKeys::Q))//Q ?????? ????????? ?????????
{
	if(CountFloat<=1.0f){//CountFloat ??? ??????????????? Q ??? ???????????? 1??? ????????????
    GetWorld()->SpawnActor<AActor>(SplitArrowActor,Location,Rotation);//?????? ????????? ??????
    }else{//??????????????? W,Q ?????? ???????????? Q ??? ?????? ????????? 1??? ????????? ?????????
	GetWorld()->SpawnActor<AActor>(ReverseArrowActor,Location,Rotation);//?????? ????????? ??????
	}
}else{//W?????? ????????? ?????????
	GetWorld()->SpawnActor<AActor>(ReverseArrowActor,Location,Rotation);//?????? ????????? ??????
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


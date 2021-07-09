// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NeopleTestP_KJHCharacter.generated.h"

UCLASS(config=Game)
class ANeopleTestP_KJHCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	/** Called for side to side input */
	void MoveRight(float Val);
	void ShootArrow();//Q 키 입력시 발사 기능 조절 함수
	void SpecialShootArrow();//W 키 입력시 발사 기능 조절 함수


	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	ANeopleTestP_KJHCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
 
 float CountFloat=0.0f;//Q키 누른 시간 변수로 저장

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> NormalArrowActor;//Q키 기본 발사체

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> ChargeArrowActor;//Q키 길게 차지 발사체

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> SplitArrowActor;//Q,W 키 분리 발사체

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TSubclassOf<AActor> ReverseArrowActor;//W 키 반사 발사체
};

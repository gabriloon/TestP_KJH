// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectileUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class NEOPLETESTP_KJH_API UProjectileUserWidget : public UUserWidget
{
	GENERATED_BODY()



	public:

	protected:
	

	UPROPERTY(meta=(BindWidget))
	class UButton* ResetBtn;//UI 에서 Reset 버튼

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* InfoText;//발사체 카운터를 의미하는 텍스트
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ResetText;//Reset Button 내에 있는 Reset 텍스트

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ArrowText;//Q 키 입력시 반영 되는 개수 텍스트
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CArrowText;//Q 키 길게 입력시 반영 되는 개수 텍스트
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* SArrowText;//Q,W 키 입력시 반영 되는 개수 텍스트
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* RArrowText;//W 키 입력시 반영 되는 개수 텍스트
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ChargeBar;//Q 키 길게 입력시 반영되는 ProgressBar	

	int Arrow=0;// Q키 누를시에 나오는 기본 화살의 개수
	int C_Arrow=0;//Q키 길게 누를시에 나오는 차지 속성 화살의 개수
	int R_Arrow=0;//W 키 누를시에 나오는 튕기는 속성을 가지는 화살의 개수
	int S_Arrow=0;//Q키와 W키를 누를시에 나오는 분열하는 속성을 가지는 화살의 개수
	int CountFloat=0;//버튼을 누르는 시간을 변수로 저장
	float ChargeTime=3.0f;

	virtual bool Initialize();//게임 시작시 UI 설정 함수
 	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
	UFUNCTION()
	void Click_ResetBtn();//Reset Button Click 시에 화살 개수 초기화 함수

};

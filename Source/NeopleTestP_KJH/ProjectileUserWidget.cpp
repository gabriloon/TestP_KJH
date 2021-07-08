// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

bool UProjectileUserWidget::Initialize() 
{   
    //게임 시작 시 반영
    Super::Initialize();
    FString Value = FString(TEXT("발사체 카운터"));
    FString Value2= FString(TEXT("RESET"));
    InfoText->SetText(FText::FromString(Value));//UI 텍스트 Value에 따라 내용 설정
    ResetText->SetText(FText::FromString(Value2));//UI 텍스트 Value2에 따라 내용 설정

    //사용한 화살의 개수에 따라 UI 텍스트 변경
    ArrowText->SetText(FText::FromString(FString::Printf(TEXT("Normal Arrow: %d"), Arrow)));
    CArrowText->SetText(FText::FromString(FString::Printf(TEXT("Charge Arrow: %d"), Arrow)));
    RArrowText->SetText(FText::FromString(FString::Printf(TEXT("Reverse Arrow: %d"), Arrow)));
    SArrowText->SetText(FText::FromString(FString::Printf(TEXT("Split Arrow: %d"), Arrow)));

    //리셋 버튼 활성화 
    ResetBtn->OnClicked.AddDynamic(this, &UProjectileUserWidget::Click_ResetBtn);
    //Progressbar 비가시화
    ChargeBar->SetVisibility(ESlateVisibility::Hidden);
    
    return true;
}


void UProjectileUserWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime) 
{
    //플레이어 컨트롤러 호출 및 변수로 저장
    APlayerController* PlayerController=UGameplayStatics::GetPlayerController(this, 0);
 if(PlayerController==nullptr)
    {return;}


    //플레이어가 Q 키를 눌렀을 경우에 
    if(PlayerController->IsInputKeyDown(EKeys::Q)){
        //Q 키 누르고 있는 시간을 CountFloat 에 저장
        CountFloat=PlayerController->GetInputKeyTimeDown(EKeys::Q);
        //Progressbar 가시화 및 CountFloat에 따라 바 진행도 변경
        ChargeBar->SetVisibility(ESlateVisibility::Visible);
        ChargeBar->SetPercent(CountFloat/ChargeTime);
  }
    
    //플레이어가 Q 키를 놓았을 경우에
    if(PlayerController->WasInputKeyJustReleased(EKeys::Q)){
        //Q 키 누르고 있는 시간 값에 따라 서로 다른 화살 개수 반영
        if(CountFloat>=ChargeTime){
    C_Arrow++;
    CArrowText->SetText(FText::FromString(FString::Printf(TEXT("Charge Arrow: %d"), C_Arrow)));
        }
        else{
     Arrow++;
    ArrowText->SetText(FText::FromString(FString::Printf(TEXT("Normal Arrow: %d"), Arrow)));
        }
        //Q 키를 놓았으니 ProgressBar도 비가시화
    ChargeBar->SetVisibility(ESlateVisibility::Hidden);
    }

    //플레이어가 W 키를 눌렀을 경우에
    if(PlayerController->WasInputKeyJustPressed(EKeys::W)){
         //W 키를 누른 상태에서 Q 키 입력이 있을 경우에
        if(PlayerController->IsInputKeyDown(EKeys::Q))
         {//Q 키 입력시간에 따라 서로 다른 화살 개수 반영
            if(CountFloat<=1.0f){
        S_Arrow++;
        SArrowText->SetText(FText::FromString(FString::Printf(TEXT("Split Arrow: %d"), S_Arrow)));
            }else{//플레이어가 W,Q 키를 눌렀지만 Q 키 누른 시간이 1초 초과한 경우에
    R_Arrow++;
    RArrowText->SetText(FText::FromString(FString::Printf(TEXT("Reverse Arrow: %d"), R_Arrow)));
                }
         }else{//플레이어가 W 키만 눌렀을 경우에
    R_Arrow++;
    RArrowText->SetText(FText::FromString(FString::Printf(TEXT("Reverse Arrow: %d"), R_Arrow)));
         } 
    }
}


void UProjectileUserWidget::Click_ResetBtn() //Reset Button Click 시에 화살 개수 초기화 함수
{
    //사용한 화살 개수 및 텍스트 0으로 초기화
    Arrow=0;
    C_Arrow=0;
    R_Arrow=0;
    S_Arrow=0;
    ArrowText->SetText(FText::FromString(FString::Printf(TEXT("Normal Arrow: %d"), Arrow)));
    CArrowText->SetText(FText::FromString(FString::Printf(TEXT("Charge Arrow: %d"), C_Arrow)));
    RArrowText->SetText(FText::FromString(FString::Printf(TEXT("Reverse Arrow: %d"), R_Arrow)));
    SArrowText->SetText(FText::FromString(FString::Printf(TEXT("Split Arrow: %d"), S_Arrow)));
}





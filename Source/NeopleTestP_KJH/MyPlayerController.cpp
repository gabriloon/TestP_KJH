// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMyPlayerController::BeginPlay() 
{
    Super::BeginPlay();
	//UE4 4.6 버전에서 PlayerController 내에 위젯 생성 시 Crash 되는 오류가 있어가지고
	//Create Widget 및 AddToViewport 의 경우에는 Blueprint 내에서 실행하겠습니다.
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "SplitArrowActor.h"
#include "Kismet/KismetMathLibrary.h"

ASplitArrowActor::ASplitArrowActor() 
{
    InitialLifeSpan = 0.f;//기존 Arrow 3초-> 제한없음(어차피 타이머 끝날때 액터 삭제)
}

void ASplitArrowActor::BeginPlay() 
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle,this,&ASplitArrowActor::SplitFunction,1.0f,false,3.0f);//3초후에 SplitFunction 함수 실행, 반복없음
}

void ASplitArrowActor::SplitFunction() 
{
    FActorSpawnParameters SpawnParams;
    FVector Location=GetActorLocation();
    FRotator Rotation=GetActorRotation();
    FRotator Rotation2=Rotation+FRotator(0.0f,45.0f,0.0f);
    FRotator Rotation3=Rotation+FRotator(0.0f,-45.0f,0.0f);
    Destroy();//기존 Arrow 삭제
	AActor* SplitAr1 = GetWorld()->SpawnActor<AActor>(ActorToSpawn,Location,Rotation, SpawnParams);//ArrowActor 방향만 다르게 해서 3개 생성 
    AActor* SplitAr2 = GetWorld()->SpawnActor<AActor>(ActorToSpawn,Location,Rotation2, SpawnParams);
    AActor* SplitAr3 = GetWorld()->SpawnActor<AActor>(ActorToSpawn,Location,Rotation3, SpawnParams);
    
    GetWorldTimerManager().ClearTimer(TimerHandle);
}

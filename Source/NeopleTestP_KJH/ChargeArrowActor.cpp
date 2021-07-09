// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargeArrowActor.h"


AChargeArrowActor::AChargeArrowActor() 
{
    this->ArrowSettingSize(FVector(150.f, 35.f, 30.f),FVector(0.3f,0.1f,0.1f));//ArrowActor 에서 상속받아 사용하는 함수,Collision,Mesh 크기 변경
    InitialLifeSpan = 5.f;//기존 Arrow 3초->5초로 변경
}

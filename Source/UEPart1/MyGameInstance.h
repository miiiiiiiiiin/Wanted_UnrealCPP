// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY() 

public:
	// 생성자
	UMyGameInstance();

private:
	// 게임 인스턴스 초기화 함수
	virtual void Init() override; 


private:
	// 프로퍼티 지정하면 변수 가져감
	UPROPERTY()
	FString SchoolName;

};

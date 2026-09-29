// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// 학생 데이터를 관리할 구조체 선언
USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("홍길동");
		Order = -1;
	}

	FStudentData(const FString& InName, int32 InOrder)
		: Name(InName), Order(InOrder)
	{
	}

	// TSet에 구조체를 저장하기 위해 필요한 함수/연산자 구현
	bool operator==(const FStudentData& InOrder) const
	{
		return Order == InOrder.Order;
	}

	// 외부의 함수를 내부에 구현
	friend FORCEINLINE int32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

/**
 * 
 */
// 전방선언
class UStudent;
class FStudentManager;

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

	// 게임 인스턴스 종료 함수.
	virtual void Shutdown() override;
private:
	TObjectPtr<UStudent> NonPropStudent;

	UPROPERTY()
	TObjectPtr<UStudent> PropStudent;

	TArray<TObjectPtr<UStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<UStudent>> PropStudents;

	FStudentManager* StudentManager = nullptr;

};

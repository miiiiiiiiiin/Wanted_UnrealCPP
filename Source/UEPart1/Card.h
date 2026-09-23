// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Card.generated.h"

// 카드 타입
UENUM() // 언리얼 향상된 열거형
enum class ECardType : uint8 // 열거형 타입 지정
{
	Student = 1 UMETA(DisplayName = "For Student"), 
	Teacher = 2 UMETA(DisplayName = "For Teacher"),
	Staff UMETA(DisplayName = "For Staff"),
	Invalid
};

/**
 * 
 */

UCLASS()
class UEPART1_API UCard : public UObject
{
	GENERATED_BODY()
public:
	UCard();

	// 게터세터
	inline ECardType GetCardtype() const { return CardType; }
	inline void SetCardType(ECardType InCardType) { CardType = InCardType; }

private:
	// 카드 타입 열거형 변수
	UPROPERTY()
	ECardType CardType;

	// 아이디
	UPROPERTY()
	int32 Id;

};

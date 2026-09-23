// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Person.generated.h"

/**
 * 
 */
// 전방선언
class UCard;

UCLASS()
class UEPART1_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();

	// 게터
	FORCEINLINE void SetName(const FString& name) { Name = name; }
	FORCEINLINE FString& GetName() { return Name; }

	FORCEINLINE UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(UCard* InCard) { Card = InCard; }

protected:
	UPROPERTY()
	FString Name;

	// 카드 객체 추가 일반 포인터는 TObjectPtr로 감싸서 만든다. 
	TObjectPtr<UCard> Card;
};

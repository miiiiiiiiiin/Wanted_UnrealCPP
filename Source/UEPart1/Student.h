// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UStudent : public UObject
{
	GENERATED_BODY()

public:
	UStudent();

	virtual void Serialize(FArchive& Ar) override;

	// getter/Setter
	FORCEINLINE int32 GetOrder() const { return Order; }
	FORCEINLINE void SetOrder(int32 Inorder) { Order = Inorder; }

	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString InName) { Name = InName; }

private:
	UPROPERTY()
	int32 Order;

	UPROPERTY()
	FString Name;
};

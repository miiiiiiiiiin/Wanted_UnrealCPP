// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CourseInfo.generated.h"

// 델리게이트 선언
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCourseInfoChangedSignature, 
	const FString& /*학교이름(역할 적기)*/, const FString& /*내용*/);

/**
 * 
 */
UCLASS()
class UEPART1_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();

	// 델리게이트 변수 선언
	FOnCourseInfoChangedSignature OnChanged;

	// 새로운 학사 정보 발행 함수
	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	// 학사 정보
	FString Contents;
};

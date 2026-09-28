// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "LessonInterface.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UStudent : public UPerson, public ILessonInterface
{
	GENERATED_BODY()

public:
	UStudent();

	// 알림 메세지를 수신할 함수 선언
	void GetNotification(const FString& School, const FString& NewCourseInfo);
	
private:
	// ILessonInterface을(를) 통해 상속됨
	void DoLesson() override;

};

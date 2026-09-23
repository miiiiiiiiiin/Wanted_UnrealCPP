// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "LessonInterface.h"
#include "Teacher.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UTeacher : public UPerson, public ILessonInterface
{
	GENERATED_BODY()
public:
	UTeacher();

private:
	// ILessonInterface을(를) 통해 상속됨
	virtual void DoLesson() override;
};



#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "Staff.generated.h"

/**
 * 
 */
UCLASS()
class UEPART1_API UStaff : public UPerson
{
	GENERATED_BODY()


public:
	UStaff();

	// 알림 메세지를 수신할 함수 선언
	void GetNotification(const FString& School, const FString& NewCourseInfo);
};

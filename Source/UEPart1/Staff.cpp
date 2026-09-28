


#include "Staff.h"
#include "Card.h"


void UStaff::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	UE_LOG(LogTemp, Log,
		TEXT("[Staff] %s님이 %s로부터 받은 메세지: %s"),
		*Name, *School, *NewCourseInfo
	);
}

UStaff::UStaff()
{
	// 기본 값 설정
	Name = TEXT("교직원");

	Card->SetCardType(ECardType::Staff);

}

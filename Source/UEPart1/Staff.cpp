


#include "Staff.h"
#include "Card.h"


UStaff::UStaff()
{
	// 기본 값 설정
	Name = TEXT("교직원");

	Card->SetCardType(ECardType::Staff);

}

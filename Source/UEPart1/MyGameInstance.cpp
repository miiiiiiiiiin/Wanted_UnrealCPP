// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"

UMyGameInstance::UMyGameInstance()
{
	// 기본값 설정
	// 생성자에서 설정하는 기본값은 cdo 템플릿 객체에 지정됨
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();  // super: UGameInstance

	UE_LOG(LogTemp, Log, TEXT("===================="));
	TArray<UPerson*> Persons =
	{
		NewObject<UStudent>(),
		NewObject<UTeacher>(),
		NewObject<UStaff>(),


	};

	// 범위 기반 루프 활용 이름 출력
	for (const auto Person : Persons)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("구성원 이름: %s"),
			*Person->GetName()
		)
	}

	// 인터페이스 구현 여부에 따른 수업 참여 구분
	// 구현 여부 확인하는 방법 -> 해당 인터페이스로 형변환(다운캐스팅)
	// 다운캐스팅->RTTI-> 메모리어케되냐 일케물어봄..
	for (const auto Person : Persons)
	{
		// 형변환을 통한 인터페이스 구현 여부 확인
		ILessonInterface* LessonInterface =
			Cast<ILessonInterface>(Person); // 퍼슨을 레슨인터페이스로 다운캐스팅

		// 형변환 성공-> 구현
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다. "), *Person->GetName());
		}
		// 형변환 실패 (null)-> 안구현
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다.. "), *Person->GetName());
		}
	}
	
	// 구성원의 카드 타입 출력
	for (const auto Person : Persons)
	{
		const UCard* OwnCard = Person->GetCard();
		ensure(OwnCard); // null체크. 출력로그에서 빨간경고띄움

		//OwnCard->GetCardtype();
		// 열거형의 메타정보를 출력해본다..
		// Enum객체를 가져온다
		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UEPart1.ECardType"));
		if (CardEnumType)
		{
			// GetDisplayNameTextByValue 함수: FText를 반환함. -> ToString으로 변환.
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue(static_cast<int64>(OwnCard->GetCardtype())).ToString();

			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류: %s"), *Person->GetName(), *CardMetaData);

		}


	}

	UE_LOG(LogTemp, Log, TEXT("===================="));


}
//void UMyGameInstance::Init()
//{
//	Super::Init();  // super: UGameInstance
//
//	// 출력 로그에 메시지 출력(출력카테고리, 출력유형(오류인지뭔지), 출력할문자열)
//	// TEXT는 와이드문자열표현하기위해 감싸는 함수임 L 대체용
//	// 언리얼은 UTF16(wchar)만 씀.
//	// 각종 타입으로 변경할 수 있는 헬퍼 함수 제공. 
//	//UE_LOG(LogTemp, Log, TEXT("Hello Unreal!"));
//
//	// TCHAR | FString
//	TCHAR LogCharArray[] = TEXT("Hello Unreal");
//	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);
//
//	FString LogCharString = LogCharArray;
//	// FString의 문자열 데이터를 가리키는 TCHAR*가 필요하므로 * 연산자로 역참조
//	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);
//
//	// 문자열 복사
//	TCHAR LogCharArrayWithSize[100] = {};
//	FCString::Strncpy(LogCharArrayWithSize, *LogCharString, LogCharString.Len());
//	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArrayWithSize);
//
//	// 문자열 자르기
//	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
//	{
//		// 문자열을 검색해 시작 인덱스 얻기
//		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
//		FString EndString = LogCharString.Mid(Index); // index부터끝까지자르기
//		UE_LOG(LogTemp, Log, TEXT("%s"), *EndString);
//	}
//
//	// 문자열 나누기
//	FString Left, Right;
//	if (LogCharString.Split(TEXT(" "), &Left, &Right))
//	{
//		UE_LOG(LogTemp, Log, TEXT("Split Test:%s / %s"), *Left, *Right)
//	}
//
//	// 문자열 조합
//	int32 IntValue = 40;
//	float FloatValue = 3.141592f;
//
//	FString FloatIntString = FString::Printf(TEXT("Int: %d, Float: %f"), IntValue, FloatValue);
//	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
//
//	// FName특성 살펴보기: 대소문자 구별하지 않음
//	FName Key1(TEXT("PELVIS"));
//	FName Key2(TEXT("pelvis"));
//
//	UE_LOG(LogTemp, Log, TEXT("FName비교 결과: %s"), (Key1 == Key2 ? TEXT("같음") : TEXT("다름")));
//}

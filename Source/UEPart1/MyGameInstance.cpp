// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"


UMyGameInstance::UMyGameInstance()
{
	// 기본값 설정
	// 생성자에서 설정하는 기본값은 cdo 템플릿 객체에 지정됨
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();  // super: UGameInstance

	// 학사 정보 객체 생성
	CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Log, TEXT("===================="));
	
	// 3개의 학생 객체 생성
	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("학생1"));

	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));

	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	// 교직원 객체 생성
	UStaff* Staff1 = NewObject<UStaff>();

	// 학사 정보 객체와 학생 객체의 연결
	// 발생 주체와 구독 주체의 연결(의존성을 피할 수 없는 부분)
	// MyGameInstance는 일종의 관리자(매니저) 성격의 객체.

	// 구독 처리. student1, 2, 3에게 함수포인터를 호출받게 한다.
	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	CourseInfo->OnChanged.AddUObject(Staff1, &UStaff::GetNotification);

	// 새로운 학사 정보 발행
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

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

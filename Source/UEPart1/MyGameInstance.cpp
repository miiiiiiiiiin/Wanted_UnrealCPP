// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

#include <Algo/Accumulate.h>

// 이름 값을 랜덤으로 생성하는 함수
FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은연원");

	TArray<TCHAR> RandArray;
	// 세 글자로 이름을 만들기 위해 3개의 공간 확보
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)]; // 0부터 3개 -> 0~2
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)]; // 0부터 3개 -> 0~2
	RandArray[2] = LastChar[FMath::RandRange(0, 3)]; // 0부터 3개 -> 0~2

	// 이름 문자열로 변환하여 반환(알아서 FString으로 변환된다)
	return RandArray.GetData();  

}

UMyGameInstance::UMyGameInstance()
{
	// 기본값 설정
	// 생성자에서 설정하는 기본값은 cdo 템플릿 객체에 지정됨
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();  // super: UGameInstance

	//  TArray 활용
	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 i = 1; i <= ArrayNum; i++)
	{
		Int32Array.Add(i);
	}

	// 조건에 부합하는 요소 모두 제거
	Int32Array.RemoveAll(
		[](int32 Value)
		{ return Value % 2 == 0; } // 2의 배수만 제거.
	);

	// 배열에 요소 한 번에 추가
	Int32Array += {2, 4, 6, 8, 10};

	// 두 번째 배열 선언
	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	// 공간 준비
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	// 값 복사.
	FMemory::Memcpy(
		Int32ArrayCompare.GetData(),
		CArray,
		sizeof(int32) * ArrayNum
	);

	// 두 배열이 같은지 확인
	ensure(Int32Array == Int32ArrayCompare);

	// 배열의 합계 구하기
	int32 Sum = 0;
	for (const int32& Value : Int32Array)
	{
		Sum += Value;
	}

	// 알고리즘을 활용한 합계 구하기
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum == SumByAlgo);

	// Set 활용
	TSet<int32> Int32Set;
	Int32Set.Reserve(ArrayNum);

	// 데이터 추가
	for (int32 Index = 1; Index <= ArrayNum; Index++)
	{
		Int32Set.Add(Index);
	}

	// 제거
	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);


	// 추가
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	// 학생 데이터 생성
	const int32 StudentNum = 300;
	for (int32 i = 1; i <= StudentNum; i++)
	{
		StudentData.Emplace(FStudentData(MakeRandomName(), i));
	}

	// 학생 데이터를 TArray<FString> 배열로 변환
	TArray<FString> AllStudentsNames;
	Algo::Transform(
		StudentData,
		AllStudentsNames,
		[](const FStudentData& Value)
		{
			return Value.Name;
		}
	);

	// 배열 요소 수 출력
	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수: %d"), AllStudentsNames.Num());

	// 학생의 이름을 Set에 저장
	// Set은 중복을 허용하지 않음 Key가 곧 Value
	TSet<FString> AllUniqueNames;
	Algo::Transform(
		StudentData,
		AllUniqueNames,
		[](const FStudentData& Value)
		{
			return Value.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수: %d"), AllUniqueNames.Num());


	// 학생 데이터를 Map으로 변환
	Algo::Transform(
		StudentData,
		StudentMap,
		[](const FStudentData& Value)
		{
			return TPair<int32, FString>(Value.Order, Value.Name);
		}
	);
	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수: %d"), StudentMap.Num());

	// 이름(문자열)을 키로 사용하는 맵 선언
	TMap<FString, int32> StudentsMapByUniqueName;

	// 학생 데이터를 맵으로 변환
	Algo::Transform(
		StudentData,
		StudentsMapByUniqueName,
		[](const FStudentData& Value)
		{
			return TPair<FString, int32>(Value.Name, Value.Order);
		}
	);
	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수: %d"), StudentsMapByUniqueName.Num());

	// 검색
	const FString TargetName(TEXT("최지연"));
	int32* Result = StudentsMapByUniqueName.Find(TargetName);
	if (Result)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 이름의 데이터 확인"), *TargetName);
	}

	// 테스트
	TSet<FStudentData> StudentsSet;
	for (int32 i = 0; i <= StudentNum; i++)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), i));
	}
	//StudentsSet.Add(StudentData[0]);
}

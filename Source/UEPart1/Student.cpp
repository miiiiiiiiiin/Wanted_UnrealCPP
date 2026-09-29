// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	// 기본 값 설정
	Order = -1;
	Name = TEXT("홍길동");
}

// 직렬화 UObject 가상함수 
void UStudent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	// 직렬화
	Ar << Order;
	Ar << Name;

}

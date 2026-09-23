// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"


UPerson::UPerson()
{
	// 초기값 설정.
	Name = TEXT("홍길동");

	// 시작할 때 카드가 생성되도록 객체 생성(CDO에서 관리됨)
	// CreateDefaultSubobject 함수는 생성자에서만 사용 
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_CARD"));
}

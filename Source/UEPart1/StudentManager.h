#pragma once

#include "CoreMinimal.h"

class UStudent;

// 언리얼 오브젝트가 아닌 곳에서 GC관리하도록 만들기. -> FGCObject 상속
class UEPART1_API FStudentManager : public FGCObject
{
public:
	FStudentManager(UStudent* student)
		: SafeStudent(student)
	{
	}

	// 게터
	UStudent* GetStudent() const { return SafeStudent; }

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	/** Overload this method to report a name for your referencer */
	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}
private:
	UStudent* SafeStudent = nullptr;
};
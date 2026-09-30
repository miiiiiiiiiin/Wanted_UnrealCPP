// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include <JsonObjectConverter.h>
#include <UObject/SavePackage.h>

// student 정보 출력 함수
void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	// 출력
	UE_LOG(
		LogTemp,
		Log,
		TEXT("[%s] 이름: %s, 순번: %d"),
		*InTag,
		*InStudent->GetName(),
		InStudent->GetOrder()
	);


}

UMyGameInstance::UMyGameInstance()
{
// 오브젝트 경로 만들기
	// 오브젝트 경로(ObjectPath): 패키지경로.에셋이름
	const FString TopSoftObjectPath
		= FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 로드(1번만 로드하기 위해 static)
	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_TopStudent(
		*TopSoftObjectPath
	);

	// 로드 성공 시 로그 출력
	if (UASSET_TopStudent.Succeeded())
	{
		PrintStudentInfo(UASSET_TopStudent.Object, TEXT("Constructor"));
	}
}

void UMyGameInstance::Init()
{
	Super::Init();  // super: UGameInstance

	FStudentData RawDataSource(TEXT("김민지"), 24);

	// 파일로 다루기 위해 경로 설정
	// 프로젝트 경로/Saved 경로 지정
	const FString SavedPath
		= FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));

	// 경로 출력
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더: %s"), *SavedPath);

	// 직렬화 구간
	{
		// 저장할 파일 이름
		const FString RawDataFileName(TEXT("RawData.bin"));

		// 파일 이름을 포함한 최종 경로
		FString RawDataAbsolutePath = FPaths::Combine(SavedPath, RawDataFileName);

		// 경로 출력(테스트)
		UE_LOG(
			LogTemp, Log, 
			TEXT("저장할 전체 파일 경로: %s"), *RawDataAbsolutePath
		);

		// 경로 정리 MakeStandardFilename -> 알아서 경로 정리해줌 절대경로??
		FPaths::MakeStandardFilename(RawDataAbsolutePath);

		// 변경된 경로 출력
		UE_LOG(
			LogTemp, Log,
			TEXT("변경된 전체 파일 경로: %s"), *RawDataAbsolutePath
		);

		//// 오브젝트 직렬화
		//// 1. 직렬화 처리를 위한 아카이브 생성
		//FArchive* RawFileWriteAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);

		//if (RawFileWriteAr)
		//{
		//	// 2. 아카이브에 오브젝트 직렬화
		//	// -> 연산자 오버로딩(<<)함수 호출
		//	*RawFileWriteAr << RawDataSource; 

		//	// 파일 닫기
		//	RawFileWriteAr->Close();

		//	// 사용한 리소스 해제
		//	delete RawFileWriteAr;
		//	RawFileWriteAr = nullptr;
		//}

		// 역직렬화 구간
		TUniquePtr<FArchive> RawFileReaderAr(
			IFileManager::Get().CreateFileReader(*RawDataAbsolutePath)
		);

		// 파일로부터 데이터를 복원할 객체
		FStudentData RawDataDeserialized;
		if (RawFileReaderAr)
		{
			// 역직렬화(연산자오버로딩함수)
			*RawFileReaderAr << RawDataDeserialized;

			// 파일 닫기
			RawFileReaderAr->Close();

			// 로드한 데이터 출력
			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름: %s, 순번: %d"), *RawDataDeserialized.Name,
				RawDataDeserialized.Order);
		}

	}

	// 언리얼 오브젝트 직렬화
	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetOrder(100);
	StudentSrc->SetName(TEXT("minji"));
	{
		// 파일 이름
		const FString& ObjectDataFileName(TEXT("ObjectData.bin"));

		// 최종 경로 설정
		FString ObjectDataPath 
			= FPaths::Combine(SavedPath, ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataPath);

		//// 직렬화 
		//// 1. 메모리 직렬화
		//TArray<uint8> Buffer;
		//FMemoryWriter MemoryWriter(Buffer); // 버퍼에 써가져온다
		//// 오브젝트 직렬화
		//StudentSrc->Serialize(MemoryWriter);

		//// 2. 파일에 기록
		//TUniquePtr<FArchive> FileWriter  // 원시포인터를 스마트 포인터로 형변환해서 만들기
		//	= TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataPath)
		//);

		//if (FileWriter)
		//{
		//	// 기록
		//	*FileWriter << Buffer;

		//	// 파일 닫기
		//	FileWriter->Close();
		//}

		// 역직렬화
		// 1. 파일 로드 -> 바이트 배열
		TArray<uint8> BufferFromFile;
		TUniquePtr<FArchive> FileReader(IFileManager::Get().CreateFileReader(*ObjectDataPath));

		if (FileReader)
		{
			// 파일에 로드한 데이터를 바이트 배열에 저장
			*FileReader << BufferFromFile;
			// 파일 닫기
			FileReader->Close();

			// 2. 바이트 배열 -> 오브젝트로 복원 
			FMemoryReader MemoryReader(BufferFromFile);

			// 테스트를 위한 임시 객체 생성
			UStudent* NewStudent = NewObject<UStudent>();
			NewStudent->Serialize(MemoryReader);

			// 로드한 데이터 출력
			UE_LOG(LogTemp, Log, TEXT("[ObjectData] 이름: %s, 순번: %d"),
				*NewStudent->GetName(),
				NewStudent->GetOrder()
			);
		}

	}

	// Json 직렬화
	{
		// Object -> Json Object ->Json 문자열 -> 파일로 기록

		// 파일 이름(지정자 없어서 보통 txt로 마니씀 .json도마니씀..)
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		// 경로
		FString JsonDataPath = FPaths::Combine(SavedPath, JsonDataFileName);
		// 경로 정리
		FPaths::MakeStandardFilename(JsonDataPath);

	//	// JsonObject 공유 레퍼런스 객체 생성
	//	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	//	// 언리얼 오브젝트 -> Json 오브젝트로 변환
	//	FJsonObjectConverter::UStructToJsonObject(
	//		StudentSrc->GetClass(),
	//		StudentSrc,
	//		JsonObject
	//	);

	//	// JsonObject -> Json 문자열
	//	FString JsonString;
	//	TSharedRef<TJsonWriter<TCHAR>> JsonWriter 
	//		= TJsonWriterFactory<TCHAR>::Create(&JsonString);
	//	// 직렬화: JsonObject -> Json 문자열
	//	if (FJsonSerializer::Serialize(JsonObject, JsonWriter))
	//	{
	//		// Json 문자열->파일로 기록
	//		FFileHelper::SaveStringToFile(JsonString, *JsonDataPath);
	//	}


		// Json 역직렬화
		// Object -> Json Object ->Json 문자열 -> 파일로 기록
		// 파일 로드g -> Json 문자열g -> Json Object -> Object
		// 1. 파일 로드g -> Json 문자열
		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataPath);

		// 2. Json 문자열g -> Json Object
		TSharedRef<TJsonReader<TCHAR>> JsonReader 
		= TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject> JsonObject;
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			// 3. Json Object->Object
			UStudent* JsonStudent = NewObject<UStudent>();
			if(FJsonObjectConverter::JsonObjectToUStruct(
				JsonObject.ToSharedRef(),
				JsonStudent->GetClass(),
				JsonStudent
			))
			{
				// Json으로부터 읽은 데이터 출력
				UE_LOG(
					LogTemp,
					Log,
					TEXT("[JsonData] 이름: %s, 순번: %d"),
					*JsonStudent->GetName(),
					JsonStudent->GetOrder()
				);

			}
		}
	}
	// 패키지 저장 및 로드
	//SaveStudentPackge();
	LoadStudentPackge();
	LoadStudentObject();

	// 에셋 스트리밍을 통한 에셋 로드
	const FString TopSoftObjectPath
		= FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 비동기 에셋 로드 요청
	Handle = StreamableManager.RequestAsyncLoad(
		TopSoftObjectPath,
		[&]() // 이 람다는 로드가 완료되면 실행됨
		{
			// 제대로 로드 됐는지 확인
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				// Student 객체 불러오기
				UStudent* TopStudent = Cast<UStudent>(Handle->GetLoadedAsset());
				if (TopStudent)
				{
					PrintStudentInfo(TopStudent, TEXT("AsyncLoad"));
				}

				// 사용할 핸들 해제 및 초기화
				Handle->ReleaseHandle();
				Handle.Reset();
			}
		}
	);
}
void UMyGameInstance::SaveStudentPackge() const
{
	// 패키지 생성. 패키지 생성 시 플래그 지정해야됨
	UPackage* StudentPackage = CreatePackage(*PackageName);
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	// 패키지 안에 저장할 언리얼 오브젝트 생성
	UStudent* TopStudent = NewObject<UStudent>(
		StudentPackage,
		UStudent::StaticClass(),
		*AssetName,
		ObjectFlag
	);

	// 속성 설정
	TopStudent->SetName(TEXT("김민지"));
	TopStudent->SetOrder(1000);

	// 패키지 저장
	// 파일 경로 만들기
	FString PackageFileName = FPackageName::LongPackageNameToFilename(
		PackageName,
		FPackageName::GetAssetPackageExtension() // .uasset 확장자 설정하는 함수임
	);

	// 경로 값 정리
	FPaths::MakeStandardFilename(PackageFileName);

	// 저장
	FSavePackageArgs SaveArgs;
	// 패키지의 메인 에셋 플래그 담기
	SaveArgs.TopLevelFlags = ObjectFlag;
	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지가 성공적으로 저장됨."));
	}
}

void UMyGameInstance::LoadStudentPackge() const
{
	// 저장된 패키지 로드
	UPackage* StudentPackage = LoadPackage(nullptr, *PackageName, LOAD_None);
	if (!StudentPackage)
	{
		UE_LOG(LogTemp, Log, TEXT("패키지를 찾지 못함"));
		return;
	}

	// 완전히 로드 처리
	StudentPackage->FullyLoad();

	// 에셋 - 대표 언리얼 오브젝트 로드
	UStudent* TopStudent = FindObject<UStudent>(StudentPackage, *AssetName);
	if (TopStudent)
	{
		PrintStudentInfo(TopStudent, TEXT("FindObject Asset"));
	}

}

void UMyGameInstance::LoadStudentObject() const
{
	// 패키지를 로드해두지 않은 상태에서 경로 값을 활용해 언리얼 오브젝트 로드
	const FString TopSoftObjectPath
		= FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 오브젝트 로드
	UStudent* TopStudent = LoadObject<UStudent>(nullptr, *TopSoftObjectPath);

	// 로드 성공 시 로그 출력
	if (TopStudent)
	{
		PrintStudentInfo(TopStudent, TEXT("LoadObject Asset"));
	}
}

#include "MyRandomMover.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

AMyRandomMover::AMyRandomMover()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMyRandomMover::BeginPlay()
{
	Super::BeginPlay();

	// 기초 환경 설정 
	TotalDistance = 0.f;
	EventCount = 0;
	CurrentStep = 0;

	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &AMyRandomMover::TimerStep, 1.0f, true);
}

void AMyRandomMover::TimerStep()
{
	// 스텝을 1 올립니다.
	CurrentStep++;

	// 이동 전 위치 기억
	FVector PreviousLocation = GetActorLocation();

	// 이동과 회전 함수 실행 (실제로 큐브가 움직임)
	Move();
	Turn();

	// 거리 계산 및 누적
	float StepDistance = FVector::Dist(PreviousLocation, GetActorLocation());
	TotalDistance += StepDistance;

	// 50% 확률 이벤트
	if (FMath::RandRange(0, 1) == 1)
	{
		TriggerEvent();
	}

	// 상태 정보 실시간 출력
	if (GEngine)
	{
		FVector CurrentRealLoc = GetActorLocation();
		FString Msg = FString::Printf(TEXT("Step %d, X=%.1f, Y=%.1f, Z=%.1f"), CurrentStep, CurrentRealLoc.X, CurrentRealLoc.Y, CurrentRealLoc.Z);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Msg);
	}

	// 최종 결과
	if (CurrentStep >= 10)
	{
		// 타이머 정지
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);

		// 최종 결과 리포트 출력
		if (GEngine)
		{
			FString FinalMsg = FString::Printf(TEXT("Total Dist: %.2f / Event Count: %d"), TotalDistance, EventCount);
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FinalMsg);
		}
	}
}

void AMyRandomMover::Move()
{
	// 현재 액터의 위치
	FVector Location = GetActorLocation();

	Location.X += FMath::RandRange(-100.f, 100.f);
	Location.Y += FMath::RandRange(-100.f, 100.f);

	SetActorLocation(Location);
}

void AMyRandomMover::Turn()
{
	float RandomYaw = FMath::RandRange(0.f, 360.f);
	UE_LOG(LogTemp, Warning, TEXT("Turn: %f"), RandomYaw);
}

void AMyRandomMover::TriggerEvent()
{
	EventCount++;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("*** Event ***"));
	}
}
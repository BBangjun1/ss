

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRandomMover.generated.h"

UCLASS()
class RM_API AMyRandomMover : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyRandomMover();

protected:
	virtual void BeginPlay() override;

public:	
	void Move();
	void Turn();
	void TriggerEvent();
	void TimerStep();

	float TotalDistance;     // 총 이동 거리
	int32 EventCount;        // 이벤트 발생 횟수
	int32 CurrentStep;            // 현재 몇 번째 이동인지 기억할 변수
	FTimerHandle MoveTimerHandle; // 타이머를 멈추거나 관리

};

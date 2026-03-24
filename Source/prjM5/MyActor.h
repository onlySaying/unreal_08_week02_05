// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class PRJM5_API AMyActor : public AActor
{
	GENERATED_BODY()	

public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private :
	// 1. 이동 함수
	void MoveActor();
	// 2. 회전 함수
	void RotateActor();
	// 3. 실행을 관리할 타이머 함수
	void ExecuteRandomAction();

	FTimerHandle ActionTimerHandle;
	int32 ExecutionCount = 0; // 실행 횟수 카운트
	const int32 MaxExecutions = 10; // 총 실행 횟수
};

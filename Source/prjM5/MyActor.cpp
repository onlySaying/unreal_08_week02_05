// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
    GetWorldTimerManager().SetTimer(ActionTimerHandle, this, &AMyActor::ExecuteRandomAction, 1.0f, true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyActor::ExecuteRandomAction()
{
    if (ExecutionCount >= MaxExecutions)
    {
        GetWorldTimerManager().ClearTimer(ActionTimerHandle);
        UE_LOG(LogTemp, Error, TEXT("모든 실행이 완료되었습니다."));
        return;
    }

    // 0 또는 1 중 랜덤으로 숫자를 뽑습니다.
    int32 RandomChoice = FMath::RandRange(0, 1);

    if (RandomChoice == 0)
    {
        MoveActor();
    }
    else
    {
        RotateActor();
    }

    ExecutionCount++;
    UE_LOG(LogTemp, Log, TEXT("현재 실행 횟수: %d / %d"), ExecutionCount, MaxExecutions);

    FString ActionName = (RandomChoice == 0) ? TEXT("이동(Move)") : TEXT("회전(Rotate)");

    FVector Loc = GetActorLocation();
    FString DebugMessage = FString::Printf(TEXT("[%d/%d] %s | 위치: X=%.1f, Y=%.1f"),
        ExecutionCount, MaxExecutions, *ActionName, Loc.X, Loc.Y);
    GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Cyan, DebugMessage);
}

void AMyActor::MoveActor()
{
    // 현재 액터의 위치를 가져옵니다.
    FVector CurrentLocation = GetActorLocation();

    // 액터가 현재 바라보고 있는 정면 방향(Local X) 벡터를 가져옵니다.
    // 이 벡터는 길이는 1이고 방향만 나타내는 '단위 벡터'입니다.
    FVector ForwardDirection = GetActorForwardVector();

    float RandomDistance = FMath::RandRange(-100.f, 100.f);

    // 새로운 위치 계산: 현재 위치 + (정면 방향 * 이동 거리)
    FVector NewLocation = CurrentLocation + (ForwardDirection * RandomDistance);

    SetActorLocation(NewLocation);

    UE_LOG(LogTemp, Warning, TEXT("[Action] Actor가 이동했습니다! (New Loc: %s)"), *NewLocation.ToString());
}

void AMyActor::RotateActor()
{
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += FMath::RandRange(0.f, 90.f);

    SetActorRotation(NewRotation);
    UE_LOG(LogTemp, Warning, TEXT("[Action] Actor가 회전했습니다! (New Rot: %s)"), *NewRotation.ToString());
}

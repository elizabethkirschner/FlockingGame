// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKING_API AFlockingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AFlockingGameModeBase();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent * AgentMesh;

	class UFlockingManager *Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
 
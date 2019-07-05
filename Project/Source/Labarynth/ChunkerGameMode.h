// Copyright 2019 Wild Ovation Games
// Author: Donovan Drews (donovancarldrews@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Engine/World.h"
#include "Chunk.h"
#include <string>
#include <math.h>
#include <unordered_map>
#include "ChunkerGameMode.generated.h"

UCLASS()
class LABARYNTH_API AChunkerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	void EvaluateChunks(); //call with a timer every second or so
	//DON: even better, space each one for a different player
	void VerifyOrSpawnNew(int32 X, int32 Y);

	int32 GetEntrance(int32 X, int32 Y, int32 Side);

	FTimerHandle MemberTimerHandle;
	std::unordered_map<std::string, AChunk*> chunk_holding;

    int32 salt;
public:
	AChunkerGameMode();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AChunk> chunkClass;

};

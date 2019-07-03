// Copyright 2019 Wild Ovation Games
// Author: Donovan Drews (donovancarldrews@gmail.com)

#include "ChunkerGameMode.h"

void AChunkerGameMode::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AChunkerGameMode::EvaluateChunks, 0.5f, true, 0.0f);
}

void AChunkerGameMode::EvaluateChunks()
{
    AGameStateBase* state = GetWorld()->GetGameState();

    //for each connected player
    for(APlayerState* player : state->PlayerArray)
    {
        //get their world position
        if(player->GetPawn())
        {
            FVector playerPos = player->GetPawn()->GetActorLocation();
            int32 chunkX = floor(playerPos.X / CHUNK_SIZE);
            int32 chunkY = floor(playerPos.Y / CHUNK_SIZE);

            //check all adjacent chunks
            VerifyOrSpawnNew(chunkX - 1, chunkY - 1);
            VerifyOrSpawnNew(chunkX - 1, chunkY);
            VerifyOrSpawnNew(chunkX - 1, chunkY + 1);
            VerifyOrSpawnNew(chunkX, chunkY - 1);
            VerifyOrSpawnNew(chunkX, chunkY);
            VerifyOrSpawnNew(chunkX, chunkY + 1);
            VerifyOrSpawnNew(chunkX + 1, chunkY - 1);
            VerifyOrSpawnNew(chunkX + 1, chunkY);
            VerifyOrSpawnNew(chunkX + 1, chunkY + 1);
        }
    }

}

void AChunkerGameMode::VerifyOrSpawnNew(int32 X, int32 Y)
{
    std::string key = std::to_string(X) + "_" + std::to_string(Y);
    
    auto location = chunk_holding.find(key);
    bool isCenter = X == 0 && Y == 0;

    //if the key doesn't exist, spawn a new chunk
    //unless it is chunk 0,0
    if(location == chunk_holding.end() && !isCenter)
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawning new chunk at X=%d Y=%d"), X, Y);
        //spawn into level
        FVector spawnLoc((X * CHUNK_SIZE) + (CHUNK_SIZE / 2.0f), (Y * CHUNK_SIZE) + (CHUNK_SIZE / 2.0f), 0);
        AChunk* newChunk = GetWorld()->SpawnActorDeferred<AChunk>(AChunk::StaticClass(), FTransform(spawnLoc));
        newChunk->SetHashAndGenerate(X, Y);
        newChunk->FinishSpawning(FTransform(spawnLoc));

        //add to hashmap
        chunk_holding.insert({key, newChunk});
    }
}
// Copyright 2019 Wild Ovation Games
// Author: Donovan Drews (donovancarldrews@gmail.com)

#include "ChunkerGameMode.h"
#include "time.h"

AChunkerGameMode::AChunkerGameMode()
{
    salt = time(NULL);
}

void AChunkerGameMode::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AChunkerGameMode::EvaluateChunks, 0.5f, true, 0.0f);
}

std::string printRow(std::vector<std::vector<char>>& grid, int32 i)
{

    std::string out = "";

    for(int32 j = 0; j < CHUNK_DIM; j++)
    {
        char pos = grid[i][j];
        if(!pos)
            out += 'O';
        else
            out += pos;
    }
    return out;
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
            

            std::string key = std::to_string(chunkX) + "_" + std::to_string(chunkY);
            auto location = chunk_holding.find(key);

            /* if(GEngine)
            {                
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Player Chunk X=%d Y=%d"), chunkX, chunkY));
                if(location != chunk_holding.end())
                {
                    auto chunk = chunk_holding.at(key);
                    for(int i = CHUNK_DIM - 1; i >= 0; i--)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString(printRow(chunk->characterLayout, i).c_str())); 
                    }
                }    
            }  */  
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
    std::vector<int32> ltrb;

    //if the key doesn't exist, spawn a new chunk
    //unless it is chunk 0,0
    if(location == chunk_holding.end())
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawning new chunk at X=%d Y=%d"), X, Y);
        //spawn into level
        FVector spawnLoc((X * CHUNK_SIZE) + (CHUNK_SIZE / 2.0f), (Y * CHUNK_SIZE) + (CHUNK_SIZE / 2.0f), 0);
        AChunk* newChunk = GetWorld()->SpawnActorDeferred<AChunk>(chunkClass, FTransform(spawnLoc));

        ltrb.push_back(GetEntrance(X + 1 ,Y , (int32) SIDE::RIGHT));
        ltrb.push_back(GetEntrance(X ,Y + 1 , (int32) SIDE::BOTTOM));
        ltrb.push_back(GetEntrance(X - 1 ,Y , (int32) SIDE::LEFT));
        ltrb.push_back(GetEntrance(X ,Y - 1 , (int32) SIDE::TOP));

        newChunk->SetHashAndGenerate(X, Y, salt, ltrb, isCenter);
        newChunk->FinishSpawning(FTransform(spawnLoc));
        newChunk->SetReplicates(true);

        //add to hashmap
        chunk_holding.insert({key, newChunk});
    }
}

int32 AChunkerGameMode::GetEntrance(int32 X, int32 Y, int32 Side)
{
    std::string key = std::to_string(X) + "_" + std::to_string(Y);
    
    auto location = chunk_holding.find(key);

    //if the key doesn't exist, spawn a new chunk
    //unless it is chunk 0,0
    if(location != chunk_holding.end())
    {
        auto chunk = chunk_holding.at(key);
        return chunk->ltrbEntrances[Side];
    }
    else
    {
        return -1;
    }
    
}
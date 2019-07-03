// Copyright 2019 Wild Ovation Games
// Author: Donovan Drews (donovancarldrews@gmail.com)

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/ActorComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include <string>
#include <functional>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "Chunk.generated.h"

const float CHUNK_SIZE = 4096.0f;

UCLASS()
class LABARYNTH_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	// Called after deffered spawn but before loading into world
	// Adds all subcomponents and sets values
	void SetHashAndGenerate(int32 x, int32 y);

	//Used as a seed for random function to determine layout of chunk
	UPROPERTY(VisibleAnywhere)
	int32 hash;

	//X component
	UPROPERTY(VisibleAnywhere)
	int32 xIndex;

	//Y Component
	UPROPERTY(VisibleAnywhere)
	int32 yIndex;

	//Vector holding all of our dynamic prefab actors
	//ALWAYS check for existence, pointers may be hanging
	std::vector<UActorComponent*> subCompList;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//All of our prefabs to spawn
	UStaticMesh* floorMesh;
	UMaterialInterface* textMat;

};
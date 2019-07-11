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

const float CHUNK_SIZE = 4800.0f;
const int CHUNK_DIM = 8;

enum class SIDE
{
	LEFT = 0,
	TOP,
	RIGHT,
	BOTTOM
};

enum class HallTileTypes
{
	none,
    hall00, // dead end hallway
    hall01, // straight hallway
    hall02, // corner hallway
    hall03, // t intersection hallway
    hall04 // 4-way intersection hallway
};

enum RSIDE
{
	NONE,
    ROOM,
    DOOR
};

struct point
{
    point(){}

    point(int i, int j)
    {
        x = i;
        y = j;
    }

    bool operator== (const point& p2)
    {
        return (this->x == p2.x) && (this->y == p2.y);
    }

    point& operator+=(const point& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    point deltaTo(point finish)
    {
        point temp(0, 0);

        if(finish.x > this->x)
            temp.x = 1;
        else if(finish.x < this->x)
            temp.x = -1;

        if(finish.y > this->y)
            temp.y = 1;
        else if(finish.y < this->y)
            temp.y = -1;

        return temp;
    }

    //finds if point contains hallway or door
    //checks for out-of-bounds conditions
    bool checkOccupancy(std::vector<std::vector<char>>& grid, bool findRooms=false)
    {
        if(x > CHUNK_DIM - 1 || x < 0 || y > CHUNK_DIM - 1 || y < 0)
        {
            //OOB
            return false;
        }
        else
        {
			if(!findRooms)
			{
				if(grid[y][x] == 'H' || grid[y][x] == 'D')
				{
					return true;
				}
			}
			else
            {
				if(grid[y][x] == 'R')
				{
					return true;
				}
			}
			
			return false;
        }
        
    }

    //finds if the addition of this point to the grid would cause a double hallway
    /* Layout of bools
    abc
    d?e
    fgh
     */
    bool doubleHallway(std::vector<std::vector<char>>& grid)
    {
        //all adjacent sides
        bool a = point(x - 1, y + 1).checkOccupancy(grid);
        bool b = point(x, y + 1).checkOccupancy(grid);
        bool c = point(x + 1, y + 1).checkOccupancy(grid);
        bool d = point(x - 1, y).checkOccupancy(grid);
        bool e = point(x + 1, y).checkOccupancy(grid);
        bool f = point(x - 1, y - 1).checkOccupancy(grid);
        bool g = point(x, y - 1).checkOccupancy(grid);
        bool h = point(x + 1, y - 1).checkOccupancy(grid);

        //each possible 2x2 section
        bool tl = a && b && d;
        bool tr = b && c && e;
        bool bl = d && f && g;
        bool br = e && h && g;

        return tl || tr || bl || br;
    }

    int x;
    int y;
};

struct room
{
    point location;
    point size;
    std::vector<point> doors;
};

UCLASS()
class LABARYNTH_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	// Called after deffered spawn but before loading into world
	// Adds all subcomponents and sets values
	void SetHashAndGenerate(int32 x, int32 y, int32 salt, std::vector<int32> ltrb, bool isCenter);

	UClass* rotationalRoomEquivalent(int& rotation, std::vector<RSIDE> ltrb);

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
	std::vector<AActor*> subCompList;

	//2D array of the char representation of the chunk layout
	//Filled by generator
	std::vector<std::vector<char>> characterLayout;

	//vector of the ltrb chunk entraces
	//all values must be between 1 and 6 inclusive
	std::vector<int32> ltrbEntrances;

	//vector of all rooms within chunk
	std::vector<room> roomSpecs;

	/*
		HALLWAY PREFABS
	*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> hall00_fab;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> hall01_fab;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> hall02_fab;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> hall03_fab;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> hall04_fab;

	/*
		ROOM PREFABS
	 */
	UPROPERTY(EditAnywhere)	
    TSubclassOf<class AActor> floor_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> floor_corner_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> floor_side_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> floor_u_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> door_corner00_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> door_corner01_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> door_corner02_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> door_side_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> door_u00_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> door_u01_fab;

	UPROPERTY(EditAnywhere)
    TSubclassOf<class AActor> door_u02_fab;

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

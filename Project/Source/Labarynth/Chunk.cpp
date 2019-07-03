// Copyright 2019 Wild Ovation Games
// Author: Donovan Drews (donovancarldrews@gmail.com)

#include "Chunk.h"

//***********************************************************
//***********************************************************
//             CHUNK GEN SPAGHETTI CODE GARBAGE
//***********************************************************
//***********************************************************

using namespace std;

const int CHUNK_DIM = 8;

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
    bool checkOccupancy(vector<vector<char>>& grid)
    {
        if(x > CHUNK_DIM - 1 || x < 0 || y > CHUNK_DIM - 1 || y < 0)
        {
            //OOB
            return false;
        }
        else
        {
            if(grid[y][x] == 'H' || grid[y][x] == 'D')
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        
    }

    //finds if the addition of this point to the grid would cause a double hallway
    /* Layout of bools
    abc
    d?e
    fgh
     */
    bool doubleHallway(vector<vector<char>>& grid)
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
    point door1;
    point door2;
    bool two_doors;
    int sizex;
    int sizey;
};

struct path
{
    point start;
    point end;
    int length = 0; //in manhattan grid units //-1 if invalid
    bool x_then_y;

    bool operator== (const path& p2)
    {
        //either order is still the same path
        return ((this->start == p2.start) && (this->end == p2.end)) ||
               ((this->end == p2.start) && (this->start == p2.end));
    }

    void trace(vector<vector<char>>& grid, point begin, point finish, point delta, bool raster = false)
    {
        point current = begin;
        while(!(current == finish))
        {
            current += delta;

            if((!grid[current.y][current.x] || grid[current.y][current.x] == 'H' || grid[current.y][current.x] == 'D') && !current.doubleHallway(grid))
            {
                if(!grid[current.y][current.x])
                {
                    //only add length if creating new pathways
                    length++;
                    if(raster)
                        grid[current.y][current.x] = 'H';
                }
            }
            else
            {
                //we hit an object, path not viable
                length = -1;
                return;
            }
        }
    }

    //finds actual representation on a grid
    void findOnGrid(vector<vector<char>>& grid, bool raster = false)
    {
        point zeroVec(0, 0);
        point middle;
        point delta1;
        point delta2;

        if(x_then_y)
        {
            middle = point(end.x, start.y);
        }
        else
        {
            middle = point(start.x, end.y);
        }
        
        delta1 = start.deltaTo(middle);
        delta2 = middle.deltaTo(end);

        if(!(delta1 == zeroVec))
        {
            trace(grid, start, middle, delta1, raster);
            if(length == -1)
                return;
        }

        if(!(delta2 == zeroVec))
        {
            trace(grid, middle, end, delta2, raster);
            if(length == -1)
                return;
        }
    }
};

//Keep commented until needed
/*
void printGrid(vector<vector<char>>& grid)
{
    for(int i = CHUNK_DIM - 1; i >= 0; i--)
    {
        auto row = grid[i];
        for(char pos : row)
        {
            if(!pos)
                cout << '-';
            cout << pos;
        }

        cout << endl;
    }
    cout << endl;
}
*/

bool makeChunk(vector<vector<char>>& grid, int l, int t, int r, int b)
{
    //place hallways at entrances
    grid[l][0] = 'H';
    grid[r][CHUNK_DIM - 1] = 'H';
    grid[0][t] = 'H';
    grid[CHUNK_DIM - 1][b] = 'H';

    //determine if 1 or 2 rooms in this chunk
    int numRooms = rand() % 2 + 1;
    vector<room> rooms(numRooms);

    for(room& iRoom : rooms)
    {
        //find size of room
        int roomChance = rand() % 100;
        
        if(roomChance < 25) //25%
        {
            iRoom.sizex = 1;
            iRoom.sizey = 2;
        }
        else if(roomChance < 50) //25%
        {
            iRoom.sizex = 2;
            iRoom.sizey = 1;
        }
        else if(roomChance < 75) //25%
        {
            iRoom.sizex = 2;
            iRoom.sizey = 2;
        }
        else if(roomChance < 85) //10%
        {
            iRoom.sizex = 2;
            iRoom.sizey = 3;
        }
        else if(roomChance < 95) //10%
        {
            iRoom.sizex = 3;
            iRoom.sizey = 2;
        }
        else //5%
        {
            iRoom.sizex = 3;
            iRoom.sizey = 3;
        }

        //spawn into chunk
        vector<point> possibleLocs;

        //check each root position in the chunk
        for(int x = 0; x < CHUNK_DIM - iRoom.sizex; x++)
        {
            for(int y = 0; y < CHUNK_DIM - iRoom.sizey; y++)
            {
                bool occupied = false;
                //check each room pos for emptiness
                for(int roomx = 0; roomx < iRoom.sizex; roomx++)
                {
                    for(int roomy = 0; roomy < iRoom.sizey; roomy++)
                    {
                        if(grid[y + roomy][x + roomx])
                            occupied = true;
                    }
                }

                //if none are filled, add to possible locations
                if(!occupied)
                    possibleLocs.push_back(point(x, y));
            }
        }

        //choose a location
        if(possibleLocs.size() == 0)
        {
            return true;
        }
        point roomLoc = possibleLocs[rand() % possibleLocs.size()];
        iRoom.location = roomLoc;

        //add R characters to the graph
        for(int roomx = 0; roomx < iRoom.sizex; roomx++)
        {
            for(int roomy = 0; roomy < iRoom.sizey; roomy++)
            {
                grid[roomLoc.y + roomy][roomLoc.x + roomx] = 'R';
            }
        }

        //find all possible door locations
        vector<point> doorLocs;

        //spaces on left side
        if(iRoom.location.x != 0)
        {
            for(int y = iRoom.location.y; y < iRoom.location.y + iRoom.sizey; y++)
            {
                if(!grid[y][iRoom.location.x - 1])
                {
                    doorLocs.push_back(point(iRoom.location.x - 1, y));
                }
            }
        }
        
        //spaces on right side
        if(iRoom.location.x + iRoom.sizex != CHUNK_DIM)
        {
            for(int y = iRoom.location.y; y < iRoom.location.y + iRoom.sizey; y++)
            {
                if(!grid[y][iRoom.location.x + iRoom.sizex])
                {
                    doorLocs.push_back(point(iRoom.location.x + iRoom.sizex, y));
                }
            }
        }
        
        //spaces on bottom side
        if(iRoom.location.y != 0)
        {
            for(int x = iRoom.location.x; x < iRoom.location.x + iRoom.sizex; x++)
            {
                if(!grid[iRoom.location.y - 1][x])
                {
                    doorLocs.push_back(point(x, iRoom.location.y - 1));
                }
            }
        }

        //spaces on top side
        if(iRoom.location.y + iRoom.sizey != CHUNK_DIM)
        {
            for(int x = iRoom.location.x; x < iRoom.location.x + iRoom.sizex; x++)
            {
                if(!grid[iRoom.location.y + iRoom.sizey][x])
                {
                    doorLocs.push_back(point(x, iRoom.location.y + iRoom.sizey));
                }
            }
        }

        //choose door locations
        if(doorLocs.size() < 2)
        {
            return true;
        }
        int firstIndex = rand() % doorLocs.size();
        point firstDoor = doorLocs[firstIndex];
        doorLocs.erase(doorLocs.begin() + firstIndex);
        iRoom.door1 = firstDoor;
        grid[firstDoor.y][firstDoor.x] = 'D';

        if(iRoom.sizex == 3 || iRoom.sizey == 3)
        {
            //Large room, two doors
            iRoom.two_doors = true;
            int secondIndex = rand() % doorLocs.size();
            point secondDoor = doorLocs[secondIndex];
            iRoom.door2 = secondDoor;
            grid[secondDoor.y][secondDoor.x] = 'D';
        }

        
    }

    //printGrid(grid);

    //construct a graph by choosing vertices that align with entraces to the chunk
    //and room doors. draw edges between that provide for the fewest hallway additions
    vector<point> vertices;
    vector<path> edges;

    //add all door entrances
    for(room i : rooms)
    {
        vertices.push_back(i.door1);
        if(i.two_doors)
            vertices.push_back(i.door2);
    }

    //add all chunk entrances
    vertices.push_back(point(0, l));
    vertices.push_back(point(CHUNK_DIM - 1, r));
    vertices.push_back(point(t, 0));
    vertices.push_back(point(b, CHUNK_DIM - 1));

    //randomize the order in which paths are created
    //DON: not sure if this uses rand()
    std::random_shuffle(vertices.begin(), vertices.end());

    //each point must create a new, unique path starting from itself (-1)
    //this mathematically gurantees a connection to all points
    for(int i = 0; i < vertices.size(); i++)
    {
        //list of all vertices except the one we are looking at
        vector<point> otherVerts = vertices;
        otherVerts.erase(otherVerts.begin() + i);

        //collect a temp list of all possible paths
        vector<path> possiblePaths;

        for(point otherPoint : otherVerts)
        {
            path temp1;
            temp1.start = vertices[i];
            temp1.end = otherPoint;
            temp1.x_then_y = true;
            temp1.findOnGrid(grid); //this finds the length (or -1 if invalid)

            //if path exists and is unique, store
            if(temp1.length != -1 && find(edges.begin(), edges.end(), temp1) == edges.end())
            {
                possiblePaths.push_back(temp1);
            }

            path temp2;
            temp2.start = vertices[i];
            temp2.end = otherPoint;
            temp2.x_then_y = false;
            temp2.findOnGrid(grid); //this finds the length (or -1 if invalid)

            if(temp2.length != -1 && find(edges.begin(), edges.end(), temp2) == edges.end())
            {
                possiblePaths.push_back(temp2);
            }
        }

        //find the shortest path of possibles
        if(possiblePaths.size() == 0)
        {
            return true;
        }
        path shortestPath = possiblePaths[0];
        for(path j : possiblePaths)
        {
            if(j.length < shortestPath.length)
                shortestPath = j;
        }

        //add to edges, and raster onto grid
        edges.push_back(shortestPath);
        shortestPath.findOnGrid(grid, true);
    }

    //printGrid(grid);
    return false;
}

//***********************************************************
//***********************************************************
//          END OF CHUNK GEN SPAGHETTI CODE GARBAGE
//***********************************************************
//***********************************************************

// Sets default values
AChunk::AChunk()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	floorMesh = CubeMeshAsset.Object;

	//Setup TextRenderMaterial
	static ConstructorHelpers::FObjectFinder<UMaterial> TextMaterial(TEXT("Material'/Engine/EngineMaterials/AntiAliasedTextMaterialTranslucent.AntiAliasedTextMaterialTranslucent'"));
	textMat = TextMaterial.Object;
}

void AChunk::SetHashAndGenerate(int32 x, int32 y)
{
	//hash location
	std::string identifier = std::to_string(x) + "_" + std::to_string(y);
	hash = std::hash<std::string>{}(identifier);
	xIndex = x;
	yIndex = y;
}

void AChunk::OnConstruction(const FTransform& Transform)
{
	UStaticMeshComponent* floorComp = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	if(floorComp)
	{
		floorComp->SetStaticMesh(floorMesh);
		floorComp->SetupAttachment(RootComponent);
		floorComp->SetWorldScale3D(FVector(CHUNK_SIZE / 100.0f, CHUNK_SIZE / 100.0f, 1.0f));
		floorComp->RegisterComponent();
		subCompList.push_back(floorComp);
	}

	std::string identifier = std::to_string(xIndex) + "_" + std::to_string(yIndex);
	UTextRenderComponent* floorLabel = NewObject<UTextRenderComponent>(this, UTextRenderComponent::StaticClass());
	if(floorLabel)
	{
		floorLabel->SetTextMaterial(textMat);
		floorLabel->SetupAttachment(RootComponent);
		floorLabel->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
		floorLabel->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
		floorLabel->SetRelativeScale3D(FVector(1.0f, 10.0f, 10.0f));
		floorLabel->SetText(FString(identifier.c_str()));
		floorLabel->RegisterComponent();
		subCompList.push_back(floorLabel);
	}
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
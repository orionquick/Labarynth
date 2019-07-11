// Copyright 2019 Wild Ovation Games
// Author: Donovan Drews (donovancarldrews@gmail.com)

#include "Chunk.h"

//***********************************************************
//***********************************************************
//             CHUNK GEN SPAGHETTI CODE GARBAGE
//***********************************************************
//***********************************************************

using namespace std;

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

bool makeCenterChunk(vector<vector<char>>& grid, vector<room>& rooms, int l, int t, int r, int b)
{
    //clear grid
    for(auto& row : grid)
    {
        row.clear();
        row.resize(CHUNK_DIM);
    }

    //place doors at entrances
    std::vector<point> doorsLTRB;
            
    doorsLTRB.push_back(point(CHUNK_DIM - 1, l));
    doorsLTRB.push_back(point(t, CHUNK_DIM - 1));
    doorsLTRB.push_back(point(0, r));
    doorsLTRB.push_back(point(b, 0));

    rooms.clear();
    room center;

    for(point d : doorsLTRB)
    {
        grid[d.y][d.x] = 'D';
        center.doors.push_back(d);
    }

    center.location = point(1, 1);
    center.size = point(CHUNK_DIM - 2, CHUNK_DIM - 2);

    //add R characters to the graph
    for(int x = 0; x < center.size.x; x++)
    {
        for(int y = 0; y < center.size.y; y++)
        {
            grid[center.location.y + y][center.location.x + x] = 'R';
        }
    }
    rooms.push_back(center);

    return false;
}

bool makeChunk(vector<vector<char>>& grid, vector<room>& rooms, int numRooms, int l, int t, int r, int b, bool backup=false)
{
    //clear grid
    for(auto& row : grid)
    {
        row.clear();
        row.resize(CHUNK_DIM);
    }

    //place hallways at entrances
    grid[l][CHUNK_DIM - 1] = 'H';
    grid[r][0] = 'H';
    grid[CHUNK_DIM - 1][t] = 'H';
    grid[0][b] = 'H';

    rooms.clear();
    //backup generator does not place any rooms
    if(!backup)
    {
        rooms.resize(numRooms);

        for(room& iRoom : rooms)
        {
            //find size of room
            int roomChance = rand() % 100;
            
            if(roomChance < 20) //20%
            {
                iRoom.size.x = 1;
                iRoom.size.y = 2;
            }
            else if(roomChance < 40) //20%
            {
                iRoom.size.x = 2;
                iRoom.size.y = 1;
            }
            else if(roomChance < 70) //30%
            {
                iRoom.size.x = 2;
                iRoom.size.y = 2;
            }
            else if(roomChance < 80) //10%
            {
                iRoom.size.x = 2;
                iRoom.size.y = 3;
            }
            else if(roomChance < 90) //10%
            {
                iRoom.size.x = 3;
                iRoom.size.y = 2;
            }
            else //10%
            {
                iRoom.size.x = 3;
                iRoom.size.y = 3;
            }

            //spawn into chunk
            vector<point> possibleLocs;

            //check each root position in the chunk
            for(int x = 0; x < CHUNK_DIM - iRoom.size.x - 1; x++)
            {
                for(int y = 0; y < CHUNK_DIM - iRoom.size.y - 1; y++)
                {
                    bool occupied = false;
                    //check each room pos for emptiness
                    for(int roomx = 0; roomx < iRoom.size.x; roomx++)
                    {
                        for(int roomy = 0; roomy < iRoom.size.y; roomy++)
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
            for(int roomx = 0; roomx < iRoom.size.x; roomx++)
            {
                for(int roomy = 0; roomy < iRoom.size.y; roomy++)
                {
                    grid[roomLoc.y + roomy][roomLoc.x + roomx] = 'R';
                }
            }

            //find all possible door locations
            vector<point> doorLocs;

            //spaces on left side
            if(iRoom.location.x != 0)
            {
                for(int y = iRoom.location.y; y < iRoom.location.y + iRoom.size.y; y++)
                {
                    if(!grid[y][iRoom.location.x - 1])
                    {
                        doorLocs.push_back(point(iRoom.location.x - 1, y));
                    }
                }
            }
            
            //spaces on right side
            if(iRoom.location.x + iRoom.size.x != CHUNK_DIM)
            {
                for(int y = iRoom.location.y; y < iRoom.location.y + iRoom.size.y; y++)
                {
                    if(!grid[y][iRoom.location.x + iRoom.size.x])
                    {
                        doorLocs.push_back(point(iRoom.location.x + iRoom.size.x, y));
                    }
                }
            }
            
            //spaces on bottom side
            if(iRoom.location.y != 0)
            {
                for(int x = iRoom.location.x; x < iRoom.location.x + iRoom.size.x; x++)
                {
                    if(!grid[iRoom.location.y - 1][x])
                    {
                        doorLocs.push_back(point(x, iRoom.location.y - 1));
                    }
                }
            }

            //spaces on top side
            if(iRoom.location.y + iRoom.size.y != CHUNK_DIM)
            {
                for(int x = iRoom.location.x; x < iRoom.location.x + iRoom.size.x; x++)
                {
                    if(!grid[iRoom.location.y + iRoom.size.y][x])
                    {
                        doorLocs.push_back(point(x, iRoom.location.y + iRoom.size.y));
                    }
                }
            }

            int doorAmt = 1;
            if(iRoom.size.x == 3 || iRoom.size.y == 3)
                doorAmt++;

            //choose door locations
            if(doorLocs.size() < doorAmt)
            {
                return true;
            }

            for(int i = 0; i < doorAmt; i++)
            {
                int firstIndex = rand() % doorLocs.size();
                point door = doorLocs[firstIndex];
                doorLocs.erase(doorLocs.begin() + firstIndex);
                iRoom.doors.push_back(door);
                grid[door.y][door.x] = 'D';
            }

            
        }
    }

    if(backup)
    {
        //simply trace a path from left to right and top to bottom
        point left(CHUNK_DIM - 1, l);
        point right(0, r);
        point top(t, CHUNK_DIM - 1);
        point bottom(b, 0);

        path l_to_r;
        l_to_r.start = left;
        l_to_r.end = right;

        path t_to_b;
        t_to_b.start = top;
        t_to_b.end = bottom;

        //try all combinations of x_then_y to find valid path
        for(int i = 0; i < 4; i++)
        {
            l_to_r.x_then_y = (i % 2);
            t_to_b.x_then_y = (i / 2);
            l_to_r.length = 0;
            t_to_b.length = 0;

            l_to_r.findOnGrid(grid, false);
            t_to_b.findOnGrid(grid, false);

            if(l_to_r.length != -1 && t_to_b.length != -1)
            {
                //valid path
                l_to_r.findOnGrid(grid, true);
                t_to_b.findOnGrid(grid, true);
                break;
            }
        }

        return false;
    }

    //printGrid(grid);

    //construct a graph by choosing vertices that align with entraces to the chunk
    //and room doors. draw edges between that provide for the fewest hallway additions
    vector<point> vertices;
    vector<path> edges;

    //add all door entrances
    for(room rm : rooms)
    {
        for(point d : rm.doors)
            vertices.push_back(d);
    }

    //add all chunk entrances
    vertices.push_back(point(CHUNK_DIM - 1, l));
    vertices.push_back(point(0, r));
    vertices.push_back(point(t, CHUNK_DIM - 1));
    vertices.push_back(point(b, 0));

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

//determines required piece and rotation to match a given hallway situation
void rotationalHallEquivalent(HallTileTypes& part, int& rotation, std::vector<bool> ltrb)
{
    vector<bool> deadend = {false, true, false, false};
    vector<bool> straight = {false, true, false, true};
    vector<bool> corner = {true, true, false, false};
    vector<bool> tee = {true, true, false, true};
    vector<bool> quad = {true, true, true, true};
    rotation = 0;
    //check all rotations
    for(int i = 0; i < 4; i++)
    {
        if(ltrb == deadend)
        {
            part = HallTileTypes::hall00;
            return;
        }
        
        if(ltrb == straight)
        {
            part = HallTileTypes::hall01;
            return;
        }

        if(ltrb == corner)
        {
            part = HallTileTypes::hall02;
            return;
        }

        if(ltrb == tee)
        {
            part = HallTileTypes::hall03;
            return;
        }

        if(ltrb == quad)
        {
            part = HallTileTypes::hall04;
            return;
        }

        //move to the next rotation
        rotation += 90;
        bool temp = ltrb[0];
        for(int j = 0; j < 3; j++)
        {
            ltrb[j] = ltrb[j + 1];
        }
        ltrb[3] = temp;
    }

    part = HallTileTypes::none;
    return;
}

//determines required piece and rotation to match a given hallway situation
UClass* AChunk::rotationalRoomEquivalent(int& rotation, std::vector<RSIDE> ltrb)
{
    /*
    vector<bool> deadend = {false, true, false, false};
    vector<bool> straight = {false, true, false, true};
    vector<bool> corner = {true, true, false, false};
    vector<bool> tee = {true, true, false, true};
    vector<bool> quad = {true, true, true, true};
    */

    vector<RSIDE> floor = {ROOM, ROOM, ROOM, ROOM};
    vector<RSIDE> floor_corner = {ROOM, ROOM, NONE, NONE};
    vector<RSIDE> floor_side = {ROOM, ROOM, ROOM, NONE};
    vector<RSIDE> floor_u = {NONE, ROOM, NONE, NONE};
    vector<RSIDE> door_corner00 = {ROOM, ROOM, DOOR, NONE};
    vector<RSIDE> door_corner01 = {ROOM, ROOM, NONE, DOOR};
    vector<RSIDE> door_corner02 = {ROOM, ROOM, DOOR, DOOR};
    vector<RSIDE> door_side = {ROOM, ROOM, ROOM, DOOR};
    vector<RSIDE> door_u00 = {NONE, ROOM, DOOR, NONE};
    vector<RSIDE> door_u01 = {NONE, ROOM, NONE, DOOR};
    vector<RSIDE> door_u02 = {DOOR, ROOM, NONE, NONE};

    rotation = 0;
    //check all rotations
    for(int i = 0; i < 4; i++)
    {
        if(ltrb == floor)
            return floor_fab;
        else if(ltrb == floor_corner)
            return floor_corner_fab;
        else if(ltrb == floor_side)
            return floor_side_fab;
        else if(ltrb == floor_u)
            return floor_u_fab;
        else if(ltrb == door_corner00)
            return door_corner00_fab;
        else if(ltrb == door_corner01)
            return door_corner01_fab;
        else if(ltrb == door_corner02)
            return door_corner02_fab;
        else if(ltrb == door_side)
            return door_side_fab;
        else if(ltrb == door_u00)
            return door_u00_fab;
        else if(ltrb == door_u01)
            return door_u01_fab;
        else if(ltrb == door_u02)
            return door_u02_fab;

        //move to the next rotation
        rotation += 90;
        RSIDE temp = ltrb[0];
        for(int j = 0; j < 3; j++)
        {
            ltrb[j] = ltrb[j + 1];
        }
        ltrb[3] = temp;
    }
    return nullptr;
}

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



void AChunk::SetHashAndGenerate(int32 x, int32 y, int32 salt, std::vector<int32> ltrb, bool isCenter)
{
	//hash location
	std::string identifier = std::to_string(x) + "_" + std::to_string(y);
	hash = std::hash<std::string>{}(identifier);
	xIndex = x;
	yIndex = y;

    //seed our random gen
    srand(hash + salt);

    //generate grid
    characterLayout = std::vector<std::vector<char>>(CHUNK_DIM, std::vector<char>(CHUNK_DIM, 0));
    bool failed = true;
    int iterator = 0;
    //determine number of rooms before generation
    //constant across all tries
    int numRooms = rand() % 3 + 1;

    if(!isCenter)
    {
        while(failed && iterator < 1000)
        {
            ltrbEntrances = ltrb;
            for(int& edge : ltrbEntrances)
            {
                if(edge == -1)
                {
                    edge = rand() % (CHUNK_DIM - 2) + 1;
                }
            }

            failed = makeChunk(characterLayout, roomSpecs, numRooms, ltrbEntrances[(int32) SIDE::LEFT], ltrbEntrances[(int32) SIDE::TOP], ltrbEntrances[(int32) SIDE::RIGHT], ltrbEntrances[(int32) SIDE::BOTTOM]);
            UE_LOG(LogTemp, Warning, TEXT("Try X: %d Y: %d"), x, y);
            iterator++;
        }

        if(failed)
        {
            ltrbEntrances = ltrb;
            for(int& edge : ltrbEntrances)
            {
                if(edge == -1)
                {
                    edge = rand() % (CHUNK_DIM - 2) + 1;
                }
            }
            UE_LOG(LogTemp, Warning, TEXT("Backup Chunk X: %d Y: %d"), x, y);
            //backup boring chunk gen that cannot fail
            makeChunk(characterLayout, roomSpecs, numRooms, ltrbEntrances[(int32) SIDE::LEFT], ltrbEntrances[(int32) SIDE::TOP], ltrbEntrances[(int32) SIDE::RIGHT], ltrbEntrances[(int32) SIDE::BOTTOM], true);
        }
    }
    else
    {
        ltrbEntrances = ltrb;
        for(int& edge : ltrbEntrances)
        {
            if(edge == -1)
            {
                edge = rand() % (CHUNK_DIM - 2) + 1;
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("Making Center Chunk"));
        makeCenterChunk(characterLayout, roomSpecs, ltrbEntrances[(int32) SIDE::LEFT], ltrbEntrances[(int32) SIDE::TOP], ltrbEntrances[(int32) SIDE::RIGHT], ltrbEntrances[(int32) SIDE::BOTTOM]);
    }
}

//finds if point contains hallway or door
//checks for out-of-bounds conditions
//also checks for chunk entrances
bool checkOccupancyEdges(int32 x, int32 y, vector<vector<char>>& grid, vector<int32> ltrb)
{
    if(x >= CHUNK_DIM)
    {
        //OOB
        if(ltrb[(int32) SIDE::LEFT] == y)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    else if(y >= CHUNK_DIM)
    {
        //OOB
        if(ltrb[(int32) SIDE::TOP] == x)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    else if(x < 0)
    {
        //OOB
        if(ltrb[(int32) SIDE::RIGHT] == y)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }  
    else if(y < 0)
    {
        //OOB
        if(ltrb[(int32) SIDE::BOTTOM] == x)
        {
            return true;
        }
        else
        {
            return false;
        }
        
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

bool isInsideRoom(point tile, room r)
{
    if(tile.x >= r.location.x + r.size.x)
        return false;
    else if(tile.y >= r.location.y + r.size.y)
        return false;
    else if(tile.x < r.location.x)
        return false;
    else if(tile.y < r.location.y)
        return false;
    else
        return true;                          
}

void AChunk::OnConstruction(const FTransform& Transform)
{
    if(!characterLayout.empty())
    {
        //add in all hallways
        for(int x = 0; x < CHUNK_DIM; x++)
        {
            for(int y = 0; y < CHUNK_DIM; y++)
            {
                if(characterLayout[y][x] == 'H')
                {
                    //fill array with status of adjacents
                    vector<bool> dirs;
                    //UE_LOG(LogTemp, Warning, TEXT("Vector len: %d"), ltrbEntrances.size());
                    dirs.push_back(checkOccupancyEdges(x + 1, y, characterLayout, ltrbEntrances));
                    dirs.push_back(checkOccupancyEdges(x, y + 1, characterLayout, ltrbEntrances));
                    dirs.push_back(checkOccupancyEdges(x - 1, y, characterLayout, ltrbEntrances));
                    dirs.push_back(checkOccupancyEdges(x, y - 1, characterLayout, ltrbEntrances));

                    //find what part and rotation to use
                    int rot = 0;
                    HallTileTypes tile;
                    rotationalHallEquivalent(tile, rot, dirs);

                    UClass* prefab;
                    if(tile == HallTileTypes::hall00)
                        prefab = hall00_fab;
                    else if(tile == HallTileTypes::hall01)
                        prefab = hall01_fab;
                    else if(tile == HallTileTypes::hall02)
                        prefab = hall02_fab;
                    else if(tile == HallTileTypes::hall03)
                        prefab = hall03_fab;
                    else if(tile == HallTileTypes::hall04)
                        prefab = hall04_fab;
                    else
                        continue;

                    float xPos = x * (CHUNK_SIZE / CHUNK_DIM) + 300;
                    float yPos = y * (CHUNK_SIZE / CHUNK_DIM) + 300;
                    xPos += CHUNK_SIZE * xIndex;
                    yPos += CHUNK_SIZE * yIndex;

                    AActor* spawnedFab = GetWorld()->SpawnActor<AActor>(prefab, FVector(xPos, yPos, 0.0f), FRotator(0.0f, rot, 0.0f));
                    if(spawnedFab)
                    {
                        //UE_LOG(LogTemp, Warning, TEXT("Spawned hallway"));
                        spawnedFab->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                        spawnedFab->SetReplicates(true);
                        subCompList.push_back(spawnedFab);
                    }
                }
            }
        }
        //add in all rooms and doors
        for(room r : roomSpecs)
        {
            for(point d : r.doors)
            {
                //fill array with status of adjacents
                vector<bool> dirs;
                dirs.push_back(checkOccupancyEdges(d.x + 1, d.y, characterLayout, ltrbEntrances));
                dirs.push_back(checkOccupancyEdges(d.x, d.y + 1, characterLayout, ltrbEntrances));
                dirs.push_back(checkOccupancyEdges(d.x - 1, d.y, characterLayout, ltrbEntrances));
                dirs.push_back(checkOccupancyEdges(d.x, d.y - 1, characterLayout, ltrbEntrances));

                if(d.x == r.location.x + r.size.x)
                {
                    dirs[(int32)SIDE::RIGHT] = true;
                }
                else if(d.y == r.location.y + r.size.y)
                {
                    dirs[(int32)SIDE::BOTTOM] = true;
                }
                else if(d.x == r.location.x - 1)
                {
                    dirs[(int32)SIDE::LEFT] = true;
                }
                else if(d.y == r.location.y - 1)
                {
                    dirs[(int32)SIDE::TOP] = true;
                }

                //find what part and rotation to use
                int rot = 0;
                HallTileTypes tile;
                rotationalHallEquivalent(tile, rot, dirs);

                UClass* prefab;
                if(tile == HallTileTypes::hall00)
                    prefab = hall00_fab;
                else if(tile == HallTileTypes::hall01)
                    prefab = hall01_fab;
                else if(tile == HallTileTypes::hall02)
                    prefab = hall02_fab;
                else if(tile == HallTileTypes::hall03)
                    prefab = hall03_fab;
                else if(tile == HallTileTypes::hall04)
                    prefab = hall04_fab;
                else
                    continue;

                float xPos = d.x * (CHUNK_SIZE / CHUNK_DIM) + 300;
                float yPos = d.y * (CHUNK_SIZE / CHUNK_DIM) + 300;
                xPos += CHUNK_SIZE * xIndex;
                yPos += CHUNK_SIZE * yIndex;

                AActor* spawnedFab = GetWorld()->SpawnActor<AActor>(prefab, FVector(xPos, yPos, 0.0f), FRotator(0.0f, rot, 0.0f));
                if(spawnedFab)
                {
                    //UE_LOG(LogTemp, Warning, TEXT("Spawned hallway"));
                    spawnedFab->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                    spawnedFab->SetReplicates(true);
                    subCompList.push_back(spawnedFab);
                }
            }

            //iterate through all room tiles
            for(int x = r.location.x; x < r.location.x + r.size.x; x++)
            {
                for(int y = r.location.y; y < r.location.y + r.size.y; y++)
                {
                    //fill array with status of adjacents
                    vector<RSIDE> dirs;
                    dirs.push_back(isInsideRoom(point(x + 1, y), r) ? ROOM : NONE);
                    dirs.push_back(isInsideRoom(point(x, y + 1), r) ? ROOM : NONE);
                    dirs.push_back(isInsideRoom(point(x - 1, y), r) ? ROOM : NONE);
                    dirs.push_back(isInsideRoom(point(x, y - 1), r) ? ROOM : NONE);

                    //add door to directions vector if applicable
                    point left(x + 1, y);
                    point top(x, y + 1);
                    point right(x - 1, y);
                    point bottom(x, y - 1);
                    
                    for(point d : r.doors)
                    {
                        if(d == left)
                            dirs[(int32)SIDE::LEFT] = DOOR;                    
                        if(d == top)
                            dirs[(int32)SIDE::TOP] = DOOR;
                        if(d == right)
                            dirs[(int32)SIDE::RIGHT] = DOOR;
                        if(d == bottom)
                            dirs[(int32)SIDE::BOTTOM] = DOOR;
                    }
                    //find what part and rotation to use
                    int rot = 0;
                    UClass* roomFab = rotationalRoomEquivalent(rot, dirs);

                    if(!roomFab)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Couldn't find room fab LTRB: %d %d %d %d"), dirs[0], dirs[1], dirs[2], dirs[3]);
                        continue;
                    }

                    float xPos = x * (CHUNK_SIZE / CHUNK_DIM) + 300;
                    float yPos = y * (CHUNK_SIZE / CHUNK_DIM) + 300;
                    xPos += CHUNK_SIZE * xIndex;
                    yPos += CHUNK_SIZE * yIndex;

                    AActor* spawnedFab = GetWorld()->SpawnActor<AActor>(roomFab, FVector(xPos, yPos, 0.0f), FRotator(0.0f, rot, 0.0f));
                    if(spawnedFab)
                    {
                        //UE_LOG(LogTemp, Warning, TEXT("Spawned room"));
                        spawnedFab->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                        spawnedFab->SetReplicates(true);
                        subCompList.push_back(spawnedFab);
                    }
                }
            }


        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Chunk was found empty"));
    }

	UStaticMeshComponent* floorComp = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	if(floorComp)
	{
		floorComp->SetStaticMesh(floorMesh);
		floorComp->SetupAttachment(RootComponent);
        floorComp->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
		floorComp->SetWorldScale3D(FVector(CHUNK_SIZE / 100.0f, CHUNK_SIZE / 100.0f, 1.0f));
		floorComp->RegisterComponent();
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
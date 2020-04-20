// RacingGame.cpp: A program using the TL-Engine
//Daniel MacArthur

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace tle;

const string MapFileName = "map.txt";
const int NumberOfThings = 24;

//2d vector structure for Player Movement
struct Vector2D
{
	float X;
	float Z;
};

//Scalar Multiplication
Vector2D Scalar(float s, Vector2D v)
{
	return{ s * v.X, s * v.Z };
}

//Add the 3 X's and 3 Z's together
Vector2D Sum3(Vector2D v1, Vector2D v2, Vector2D v3)
{
	return{ v1.X + v2.X + v3.X, v1.Z + v2.Z + v3.Z };
}

//MeshSkins
enum SkinNum
{
	CheckPointMesh, CrossMesh, FlareMesh, GarageLargeMesh, GarageSmallMesh, GroundMesh,
	InterStellarMesh, IsleCornerMesh, IsleCrossMesh, IsleStraightMesh, IsleTeeMesh,
	LampMesh, Race2Mesh, SkyBoxMesh, TankLarge1Mesh, TankLarge2Mesh, TankSmall1Mesh, TankSmall2Mesh,
	Tribune1Mesh, Tribune2Mesh, Tribune3Mesh, WalkWayMesh, WallMesh, DummyPathFindingMesh
};

//MeshSkins in String format 
const string NameOfSkin[NumberOfThings]{ "CheckPointMesh", "CrossMesh", "FlareMesh", "GarageLargeMesh", "GarageSmallMesh", "GroundMesh",
"InterStellarMesh", "IsleCornerMesh", "IsleCrossMesh", "IsleStraightMesh", "IsleTeeMesh",
"LampMesh", "Race2Mesh", "SkyBoxMesh", "TankLarge1Mesh", "TankLarge2Mesh", "TankSmall1Mesh", "TankSmall2Mesh",
"Tribune1Mesh", "Tribune2Mesh", "Tribune3Mesh", "WalkWayMesh", "WallMesh", "DummyPathFindingMesh" };

//gets the number of objects in maps.txt to resize the vector that will hold them
int GetNumberOfObjects()
{
	//reads in objects from files
	ifstream FileIn(MapFileName);

	//if file doesn't exist create file with default objects from work sheet
	if (!FileIn)
	{
		cout << "[ERROR]: Can't open input file, File May be missing... \n ";
		cout << "<Creating File>";
		ofstream outfile(MapFileName);
		//(Mesh, x, y, z, rotation )
		outfile << to_string(SkyBoxMesh) << " 0.0 -960.0 0.0 0.0 " << endl;
		outfile << to_string(GroundMesh) << " 0.0 0.0 0.0 0.0 " << endl;
		outfile << to_string(CheckPointMesh) << " 0.0 0.0 0.0 0.0 " << endl;
		outfile << to_string(IsleStraightMesh) << " -10.0 0.0 40.0 0.0 " << endl;
		outfile << to_string(IsleStraightMesh) << " 10.0 0.0 40.0 0.0 " << endl;
		outfile << to_string(WallMesh) << " -10.5 0.0 46 0.0 " << endl;
		outfile << to_string(WallMesh) << " 9.5 0.0 46.0 0.0 " << endl;
		outfile << to_string(IsleStraightMesh) << " 10.0 0.0 53.0 0.0 " << endl;
		outfile << to_string(IsleStraightMesh) << " -10.0 0.0 53.0 0.0 " << endl;
		outfile << to_string(CheckPointMesh) << " 0.0 0.0 100.0 0.0 ";
		FileIn.close();
	}

	//Reads Objects in from file and assigns each line as a position in the given vector.
	else { FileIn.close(); }
	string line;
	int Count = 0;
	FileIn.open(MapFileName);
	while (!FileIn.eof())
	{
		getline(FileIn, line);
		Count++;
	}
	FileIn.close();
	return Count;
}

//gets the number of Checkpoints in maps.txt to resize the vector that will hold them
int GetNumberOfCheckPoints()
{
	ifstream FileIn(MapFileName);
	string line;
	int Count = 0;
	while (!FileIn.eof())
	{
		getline(FileIn, line);
		if (line[0] == '0') //char checkpointsmesh
		{
			Count++;
		}
	}
	return Count;
}

//get number of DummyPathFinders to resize the vector that will hold them
int GetNumberOfDummyPathFinders()
{
	char Check = CheckPointMesh;
	ifstream FileIn(MapFileName);
	string line;
	int Count = 0;
	while (!FileIn.eof())
	{
		getline(FileIn, line);
		if (line[0] == '2' && line[1] == '3') //23
		{
			Count++;
		}
	}
	return Count;
}

//Gets all the objects in maps.txt and assigns them to a vector
void VectorGet(vector <string>& ObjVector)
{
	ifstream FileIn(MapFileName);
	string line;
	int counter = 0;
	while (!FileIn.eof())
	{
		getline(FileIn, line);
		ObjVector[counter] = line;
		cout << "Loading-> " << counter << ": " << ObjVector[counter] << endl;
		counter++;
	}
	return;
}

//Object class holds all the objects from maps.txt 
class Object
{
private:

	//circle Collision values
	float CheckPointRadius = 9.86159f;
	float FlareRadius = 0.5f;
	float GarageSmallRadius = 5.10302f;
	float LampRadius = 4.57125f;
	float Race2Radius = 0.5f;
	float TankLarge1Radius = (3.12677f + 5.11026f) / 2.0f;
	float TankLarge2Radius = (3.13098f + 5.10605f) / 2.0f;
	float TankSmall1Radius = (3.14098f + 5.09605f) / 2.0f;
	float TankSmall2Radius = (3.11473f + 5.1223f) / 2.0f;
	float Tribune1Radius = (21.8479f + 20.8358f) / 8.0f;

	//box collision values
	float GarageLargeXMin = -10.0384f;
	float GarageLargeXMax = 10.0384f;
	float GarageLargeZMin = -6.93205f;
	float GarageLargeZMax = 6.93205f;

	float InterStellarXMin = -8.0f;
	float InterStellarXMax = 8.0f;
	float InterStellarZMin = -36.0f;
	float InterStellarZMax = 39.6f;

	float IsleCornerXMin = -4.42294f;
	float IsleCornerXMax = 5.72269f;
	float IsleCornerZMin = -5.71911f;
	float IsleCornerZMax = 4.17878f;

	float IsleCrossXMin = -5.71908f;
	float IsleCrossXMax = 4.66959f;
	float IsleCrossZMin = -5.71908f;
	float IsleCrossZMax = 5.99127f;

	float IsleStraightXMin = -2.67529f;
	float IsleStraightXMax = 2.67529f;
	float IsleStraightZMin = -3.41748f;
	float IsleStraightZMax = 3.41748f;

	float IsleTeeXMin = -5.72448f;
	float IsleTeeXMax = 3.15858f;
	float IsleTeeZMin = -4.66931f;
	float IsleTeeZMax = 5.71911f;

	float Tribune2XMin = -24.914f;
	float Tribune2XMax = 24.914f;
	float Tribune2ZMin = -18.0925f;
	float Tribune2ZMax = 18.0925f;

	float Tribune3XMin = -29.2955f;
	float Tribune3XMax = 30.5274f;
	float Tribune3ZMin = -32.2349f;
	float Tribune3ZMax = 32.2349f;

	float WallXMin = -0.934082f;
	float WallXMax = 0.934082f;
	float WallZMin = -4.83559f;
	float WallZMax = 4.83559f;

public:

	IModel* Model;
	int t; //type
	float x;
	float y;
	float z;
	float Rotation;
	float Radius = 1.0f;
	float XMin;
	float XMax;
	float ZMin;
	float ZMax;
	float CheckPointLegPos = 9.4f;
	float CheckPointLegRadius = 0.7f;

	//sets boundingboxes
	void BoundriesSetter()
	{
		//circles
		if (t == CheckPointMesh) Radius = CheckPointRadius;
		else if (t == FlareMesh)Radius = FlareRadius;
		else if (t == GarageSmallMesh) Radius = GarageSmallRadius;
		else if (t == LampMesh) Radius = LampRadius;
		else if (t == Race2Mesh) Radius = Race2Radius;
		else if (t == TankLarge1Mesh) Radius = TankLarge1Radius;
		else if (t == TankLarge2Mesh) Radius = TankLarge2Radius;
		else if (t == TankSmall1Mesh) Radius = TankSmall1Radius;
		else if (t == TankSmall2Mesh) Radius = TankSmall2Radius;
		else if (t == Tribune1Mesh) Radius = Tribune1Radius;

		//boxes
		else if (t == GarageLargeMesh) {
			XMin = GarageLargeXMin + x;
			XMax = GarageLargeXMax + x;
			ZMin = GarageLargeZMin + z;
			ZMax = GarageLargeZMax + z;
		}

		else if (t == InterStellarMesh) {
			XMin = InterStellarXMin + x;
			XMax = InterStellarXMax + x;
			ZMin = InterStellarZMin + z;
			ZMax = InterStellarZMax + z;
		}

		else if (t == IsleCornerMesh) {
			XMin = IsleCornerXMin + x;
			XMax = IsleCornerXMax + x;
			ZMin = IsleCornerZMin + z;
			ZMax = IsleCornerZMax + z;
		}

		else if (t == IsleCrossMesh) {
			XMin = IsleCrossXMin + x;
			XMax = IsleCrossXMax + x;
			ZMin = IsleCrossZMin + z;
			ZMax = IsleCrossZMax + z;
		}

		else if (t == IsleStraightMesh) {
			XMin = IsleStraightXMin + x;
			XMax = IsleStraightXMax + x;
			ZMin = IsleStraightZMin + z;
			ZMax = IsleStraightZMax + z;
		}

		else if (t == IsleTeeMesh) {
			XMin = IsleTeeXMin + x;
			XMax = IsleTeeXMax + x;
			ZMin = IsleTeeZMin + z;
			ZMax = IsleTeeZMax + z;
		}

		else if (t == Tribune2Mesh) {
			XMin = Tribune2XMin + x;
			XMax = Tribune2XMax + x;
			ZMin = Tribune2ZMin + z;
			ZMax = Tribune2ZMax + z;
		}

		else if (t == Tribune3Mesh) {
			XMin = Tribune3XMin + x;
			XMax = Tribune3XMax + x;
			ZMin = Tribune3ZMin + z;
			ZMax = Tribune3ZMax + z;
		}

		else if (t == WallMesh) {
			XMin = WallXMin + x;
			XMax = WallXMax + x;
			ZMin = WallZMin + z;
			ZMax = WallZMax + z;
		}
	}

};

//Player Class handles player input/output
class HoverCar
{
public:
	IModel* Model;
	float Radius = 3.4619f;
	float FrontOffsetZ = 6.4619f / 2.0f;
	float FrontRadius = 1.5f;
	float BackOffsetZ = -(6.4619f / 2.0f);
	float BackRadius = 4.0f;
	float Acceleration = 0.0f;
	float Drag;
	float RotationSpeed;
	bool FloatUp = true;
	float FloatMin = 0.0f;
	float FloatMax = 1.0f;
	float FloatAmount = .01f;
	float StartX = 0.0f;
	float StartY = 0.0f;
	float StartZ = 0.0f;
};

//Colision detection for two spheres (the player, an object)
bool SphereToSphere(HoverCar Sphere, Object CheckPoint)
{
	if (
		sqrt(
			pow((Sphere.Model->GetX() - CheckPoint.x), 2)
			+ pow((Sphere.Model->GetZ() - CheckPoint.z), 2)
		)
		- Sphere.Radius - CheckPoint.Radius < 0
		) return true;

	else return false;
}

//Collision detection for Legs of checkpoints
bool SphereToCheckPointLegs(HoverCar Sphere, Object CheckPoint)
{
	if (
		sqrt(
			pow((Sphere.Model->GetX() - (CheckPoint.x + CheckPoint.CheckPointLegPos)), 2)
			+ pow((Sphere.Model->GetZ() - CheckPoint.z), 2)
		)
		- Sphere.Radius - CheckPoint.CheckPointLegRadius < 0
		) return true;

	else if (
		sqrt(
			pow((Sphere.Model->GetX() - (CheckPoint.x - CheckPoint.CheckPointLegPos)), 2)
			+ pow((Sphere.Model->GetZ() - CheckPoint.z), 2)
		)
		- Sphere.Radius - CheckPoint.CheckPointLegRadius < 0
		) return true;

	else return false;
}

//colision detection for sphere to box (the player, an object)
bool SphereToBox(HoverCar Sphere, Object Box)
{
	if (
		Sphere.Model->GetX() > (Box.XMin) - Sphere.Radius &&
		Sphere.Model->GetX() < (Box.XMax) + Sphere.Radius &&
		Sphere.Model->GetZ() > (Box.ZMin) - Sphere.Radius &&
		Sphere.Model->GetZ() < (Box.ZMax) + Sphere.Radius
		) return true;

	else return false;
}

bool PlayerToNPC(HoverCar Sphere, HoverCar NPC)
{
	if (
		sqrt(
			pow((Sphere.Model->GetX() - NPC.Model->GetX()), 2)
			+ pow((Sphere.Model->GetZ() - NPC.Model->GetZ()), 2)
		)
		- Sphere.Radius - NPC.Radius < 0
		)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed(1000, 500);

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("Media");
	//myEngine->AddMediaFolder("D:\\ProgramData\\TL-Engine\\Media");

	/**** Set up your scene here ****/

	//Font
	IFont* myFont = myEngine->LoadFont("Times New Roman", 30);

	//backdrop
	myEngine->CreateSprite("ui_backdrop.png", (myEngine->GetWidth() / 2) - 350, myEngine->GetHeight() - 60, 0);

	//Constants
	const int GameWidth = myEngine->GetWidth();
	const int GameHeight = myEngine->GetHeight();
	const int GameCenterWidth = GameWidth / 2;
	const int GameCenterHeight = GameHeight / 2;

	const int TextDialogY = GameHeight - 30;
	const int TextDialogX = GameCenterWidth;

	const int TextStateX = GameCenterWidth;
	const int TextStateY = GameHeight - 55;

	const int TextSpeedX = GameCenterWidth + 250;
	const int TextSpeedY = GameHeight - 30;

	const int TextBoostX = GameCenterWidth - 250;
	const int TextBoostY = GameHeight - 40;

	const int TextHealthX = GameWidth - 100;
	const int TextHealthY = 0;

	const int LapHeightPos = 0;
	const int NumOfMeshes = 25;
	const int NumberOfLaps = 3;
	const enum GameStates { Loading, Paused, Playing, RaceOver };

	/////////////
	//variables//
	/////////////

	/****game states****/
	int GameState = Loading;
	int CheckPointState = 0;
	int PathFinderState = 0;
	bool StartGame = false;
	int CountDownLimit = 3; //Count down before game starts after hitting space
	int LapState = 1;

	/*****Keys********/
	//MoveMent
	EKeyCode KeyAccelerate = Key_W;
	EKeyCode KeyDecelerate = Key_S;
	EKeyCode KeyTurnRight = Key_D;
	EKeyCode KeyTurnLeft = Key_A;
	EKeyCode KeyBoost = Key_Space;

	//game
	EKeyCode KeyQuit = Key_Escape;
	EKeyCode KeyPause = Key_P;
	EKeyCode KeyDevloper = Key_M;
	EKeyCode KeyStartGame = Key_Space;

	//camera
	EKeyCode KeyCamFowards = Key_Up;
	EKeyCode KeyCamBackwards = Key_Down;
	EKeyCode KeyCamLeft = Key_Left;
	EKeyCode KeyCamRight = Key_Right;
	EKeyCode KeyCamReset = Key_1;
	EKeyCode KeyCamFirstPerson = Key_2;

	/*****Number of Things*****/
	int NumberOfObjects = GetNumberOfObjects();
	int NumberOfCheckPoints = GetNumberOfCheckPoints();
	int NumberOfDummyPathFinders = GetNumberOfDummyPathFinders();


	/***camera Variables***/
	float CamX = 0.0f;
	float CamY = 0.0f;
	float CamZ = 0.0f;
	float CamMoveY = 10.0f;
	float CamMoveZ = -30.0f;
	float CamRotateLocalX = 20.0f;
	float CamFpY = -4.0f;
	float CamFpZ = 30.0f;
	float CamSpeed = 0.0f;
	float CamMultiplier = 30.0f;
	float InitalMouseY = 0.0f;
	float MouseYMax = 90.0f;
	float MouseYMin = -90.0f;
	bool FirstPerson = false;

	/*Clock*/
	float Clock = 0.0f;
	myEngine->Timer();
	int ClockXPos = 0;
	int ClockYPos = 0;

	/****HoverCar, Player****/

	//Boosters engaged
	int BoostWarningAmount = 1; //seconds
	int BoostCoolDownLimit = 5; //seconds
	int BoostTimeLimit = 3; //seconds
	int BoostTimer = 0;
	int BoostCoolDownTimer = 0;
	float HoverCarBoost = 10.0f; //Amount to boost by
	bool BoostAllowed = true;
	bool StartBoostTimer = false;
	bool StartBoostCoolDown = false;
	bool BoostWarning = false;


	//Car Leaning
	int RotationCount = 0;
	int RotationLimit = 50;
	float RotationAmount = .50f;
	int FrontRotationCount = 0;
	int FrontRotationLimit = 50;
	float FrontRotationAmount = .1f;

	//CarSpeeds
	int SpeedMultiplier = 100;
	float HoverCarDrag = -0.5f;
	float HoverCarAcceleration = 0.3f;
	float RotationSpeed = 100.0f;
	float BoostDecelMultiplier = 0.1f;
	float BoostAccelMultipier = 2.005f;
	int SpeedReadOut = 0;

	//CarHealth
	int HoverCarHealth = 100;
	int HoverCarMaxHealth = 100;
	bool DamageTaken = false;

	//////////
	//Meshes// (If adding new mesh update NumOfMeshes and add line to bottom of these meshes)
	//////////
	IMesh* ObjSkin[NumOfMeshes];
	ObjSkin[CheckPointMesh] = myEngine->LoadMesh("Checkpoint.x"); //0
	ObjSkin[CrossMesh] = myEngine->LoadMesh("Cross.x"); //1
	ObjSkin[FlareMesh] = myEngine->LoadMesh("Flare.x"); //2
	ObjSkin[GarageLargeMesh] = myEngine->LoadMesh("GarageLarge.x"); //3
	ObjSkin[GarageSmallMesh] = myEngine->LoadMesh("GarageSmall.x"); //4
	ObjSkin[GroundMesh] = myEngine->LoadMesh("Ground.x"); //5
	ObjSkin[InterStellarMesh] = myEngine->LoadMesh("Interstellar.x");
	ObjSkin[IsleCornerMesh] = myEngine->LoadMesh("IsleCorner.x"); //6
	ObjSkin[IsleCrossMesh] = myEngine->LoadMesh("IsleCross.x"); //7
	ObjSkin[IsleStraightMesh] = myEngine->LoadMesh("IsleStraight.x"); //8
	ObjSkin[IsleTeeMesh] = myEngine->LoadMesh("IsleTee.x"); //9
	ObjSkin[LampMesh] = myEngine->LoadMesh("Lamp.x"); //10
	ObjSkin[Race2Mesh] = myEngine->LoadMesh("race2.x"); //11
	ObjSkin[SkyBoxMesh] = myEngine->LoadMesh("Skybox 07.x"); //12
	ObjSkin[TankLarge1Mesh] = myEngine->LoadMesh("TankLarge1.x"); //13
	ObjSkin[TankLarge2Mesh] = myEngine->LoadMesh("TankLarge2.x"); //14
	ObjSkin[TankSmall1Mesh] = myEngine->LoadMesh("TankSmall1.x"); //15
	ObjSkin[TankSmall2Mesh] = myEngine->LoadMesh("TankSmall2.x"); //16
	ObjSkin[Tribune1Mesh] = myEngine->LoadMesh("Tribune1.x"); //17
	ObjSkin[Tribune2Mesh] = myEngine->LoadMesh("Tribune2.x"); //18
	ObjSkin[Tribune3Mesh] = myEngine->LoadMesh("Tribune3.x"); //19
	ObjSkin[WalkWayMesh] = myEngine->LoadMesh("Walkway.x"); //20
	ObjSkin[WallMesh] = myEngine->LoadMesh("Wall.x"); //21
	ObjSkin[DummyPathFindingMesh] = myEngine->LoadMesh("Dummy.x"); //22

	/////////////////////
	//Creating Objects//
	///////////////////

	/****Player object****/
	HoverCar Player;
	Player.StartX = -3.0f;
	Player.StartY = 0.0f;
	Player.StartZ = -50.0f;
	IMesh* DummyMesh = myEngine->LoadMesh("Dummy.x"); 	//create Dummy
	IModel* DummyPlayer = DummyMesh->CreateModel(Player.StartX, Player.StartY, Player.StartZ); //Make the into varaibles
	Player.Model = ObjSkin[Race2Mesh]->CreateModel(0.0f); //Create Player in world and attach Player to dummy
	Player.Model->AttachToParent(DummyPlayer);
	Vector2D Momentum{ 0.0f, 0.0f };
	Vector2D Thrust{ 0.0f, 0.0f };
	Vector2D Drag{ 0.0f, 0.0f };
	float Matrix[4][4];

	/****NPC****/
	HoverCar NonPlayer;
	NonPlayer.StartX = 10.0f;
	NonPlayer.StartZ = -50.0f;
	NonPlayer.Model = ObjSkin[Race2Mesh]->CreateModel(NonPlayer.StartX, NonPlayer.StartY, NonPlayer.StartZ);
	NonPlayer.Acceleration = 20.0f;
	NonPlayer.Model->SetSkin("npcskin.jpg");

	/****Camera****/
	ICamera* MyCamera = myEngine->CreateCamera(kManual, CamX, CamY, CamZ);
	MyCamera->AttachToParent(DummyPlayer);
	MyCamera->MoveY(CamMoveY);
	MyCamera->MoveZ(CamMoveZ);
	MyCamera->RotateLocalX(CamRotateLocalX);

	/****Objects from file****/
	vector <string> ListOfObjects(NumberOfObjects);
	VectorGet(ListOfObjects);

	/****CheckPoints****/
	vector <int> CheckPointPosList(NumberOfCheckPoints);

	/****Dummy Path Finders****/
	vector <int> DummyPathFinderList(NumberOfDummyPathFinders);

	/****IModels****/
	vector <IModel*> LoadObjects;
	LoadObjects.resize(NumberOfObjects);

	/****MapItems from file****/
	vector <Object> MapItems(NumberOfObjects);

	//creates objects using meshes from the vector list
	int CheckPointCounter = 0;
	int DummyPathFinderCounter = 0;
	for (int e = 0; e < ListOfObjects.size(); e++)
	{
		string t, x, y, z, r; // type, x, y, z, Rotation
		string line = ListOfObjects[e];
		string Holder = "";
		int RowCount = 0;

		//Gets co ordinates from file
		for (int i = 0; i < line.length(); i++)
		{
			Holder = Holder + line[i];
			if (line.length() == 0) //ignores blank lines
			{

			}

			//after a Space, commit value before space to a Row in the vector. This means it is able to handle numbers bigger than 1 char
			else if (line[i] == ' ')
			{
				if (RowCount == 0) MapItems[e].t = stoi(Holder); //Type of mesh
				else if (RowCount == 1) MapItems[e].x = stof(Holder); //x co or
				else if (RowCount == 2) MapItems[e].y = stof(Holder); //y
				else if (RowCount == 3) MapItems[e].z = stof(Holder); //z
				else if (RowCount == 4) MapItems[e].Rotation = stof(Holder); //Rotation of object
				Holder = "";
				RowCount++;
			}
		}

		//commits it and creates it
		MapItems[e].BoundriesSetter(); //sets its bounding box/sphere depending on what its type is
		MapItems[e].Model = ObjSkin[MapItems[e].t]->CreateModel(MapItems[e].x, MapItems[e].y, MapItems[e].z);
		MapItems[e].Model->RotateLocalY(MapItems[e].Rotation);

		/*Special Cases*/
		//checkpoints
		if (MapItems[e].t == CheckPointMesh)
		{
			CheckPointPosList[CheckPointCounter] = e;
			cout << endl << "[" << e << "] Checkpoint: " << CheckPointCounter;
			CheckPointCounter++;
		}

		//DummyPathFinders
		if (MapItems[e].t == DummyPathFindingMesh)
		{
			DummyPathFinderList[DummyPathFinderCounter] = e;
			cout << endl << "[" << e << "] PathFinder: " << DummyPathFinderCounter;
			DummyPathFinderCounter++;
		}
	}


	while (myEngine->IsRunning())
		// The main game loop, repeat until engine is stopped
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

		//stops mouse wondering while paused
		if (GameState != Playing)
		{
			myEngine->GetMouseMovementX();
			myEngine->GetMouseMovementY();
		}

		//Exit game
		if (myEngine->KeyHit(KeyQuit))	myEngine->Stop();

		//variables that need updated with frametime
		float frameTime = myEngine->Timer();
		Player.RotationSpeed = frameTime * RotationSpeed;
		CamSpeed = frameTime * CamMultiplier;
		Player.Drag = HoverCarDrag * frameTime;
		Player.Acceleration = HoverCarAcceleration * frameTime;


		//Loading State
		if (GameState == Loading)
		{
			//print GameState
			myFont->Draw("Loading", TextDialogX, TextStateY, kBlack, kCentre);

			//While game not started, ask the player to press the spacebar to start.
			if (!StartGame)
			{
				myFont->Draw("Press Space to start", TextDialogX, TextDialogY, kBlack, kCentre);
			}

			//Player Starts the game
			if (myEngine->KeyHit(KeyStartGame))
			{
				StartGame = true;
			}

			//when Game Starts, count down.
			if (StartGame && Clock < CountDownLimit)
			{
				//count down from  and then say go
				int IntClock = Clock;
				myFont->Draw(to_string(CountDownLimit - IntClock), TextDialogX, TextDialogY, kBlack, kCentre);
				Clock = Clock + frameTime;
			}

			//Change Dialog to GO when timer is up
			if (Clock > CountDownLimit)
			{
				myFont->Draw("Go", TextDialogX, TextDialogY, kBlack, kCentre);
				Clock = Clock + frameTime;
				if (Clock > CountDownLimit + 1)
				{
					GameState = Playing;
					myEngine->StartMouseCapture(); // Captures mouse movement
					Clock = 0.0f;
				}
			}
		}

		//Paused State
		else if (GameState == Paused)
		{
			//print GameState
			myFont->Draw("Paused", TextDialogX, TextStateY, kBlack, kCentre);

			//draw clock 
			int IntClock = Clock;
			myFont->Draw("Time: " + to_string(IntClock), ClockXPos, ClockYPos);

			//UnPause Game
			if (myEngine->KeyHit(KeyPause))
			{
				GameState = Playing;
				myEngine->StartMouseCapture(); // Captures mouse movement
			}
		}

		//Game is playing
		else if (GameState == Playing) {

			//print GameState
			myFont->Draw("Playing", TextStateX, TextStateY, kBlack, kCentre);

			//State Transitions

			//Pause Game
			if (myEngine->KeyHit(KeyPause))
			{
				GameState = Paused;
			}

			//end game
			else if (CheckPointState == NumberOfCheckPoints)
			{
				GameState = RaceOver;
			}

			//Timer
			int IntClock = Clock;
			myFont->Draw("Time: " + to_string(IntClock), 0, 0);
			Clock = Clock + frameTime;

			//////////////
			//Hover Car//
			////////////


			//Make the HoverCar Hover while in 3rd person (1st person hovering is annoying)
			if (!FirstPerson)
			{
				if (Player.FloatUp) Player.Model->MoveY(Player.FloatAmount);
				else if (!Player.FloatUp) Player.Model->MoveY(-Player.FloatAmount);
				if (Player.Model->GetY() > Player.FloatMax) Player.FloatUp = false;
				else if (Player.Model->GetY() < Player.FloatMin) Player.FloatUp = true;
			}

			//***********Moving The Car**************//

			float PreviousX = DummyPlayer->GetX();
			float PreviousZ = DummyPlayer->GetZ();

			//get facing vector
			DummyPlayer->GetMatrix(&Matrix[0][0]); //get matrix
			Vector2D FacingVector = { Matrix[2][0], Matrix[2][2] };

			//car leans backwards if already learning forwards

			//accelerate
			if (myEngine->KeyHeld(KeyAccelerate))
			{
				Thrust = { Scalar(Player.Acceleration, FacingVector) };

				//lean car forwards
				if (FrontRotationCount < FrontRotationLimit)
				{
					Player.Model->RotateLocalX(-FrontRotationAmount);
					FrontRotationCount++;
				}
			}

			//decelerate
			else if (myEngine->KeyHeld(KeyDecelerate))
			{
				Thrust = { Scalar(-Player.Acceleration * 0.7f, FacingVector) };
			}

			//set thrust to 0
			else
			{
				Thrust = { 0.0f,0.0f };
				if (FrontRotationCount <= FrontRotationLimit && FrontRotationCount > 0)
				{
					Player.Model->RotateLocalX(FrontRotationAmount);
					FrontRotationCount--;
				}
			}

			//Using boost
			if (myEngine->KeyHeld(KeyBoost) && BoostAllowed)
			{
				//starts timer
				if (!StartBoostTimer)
				{
					BoostTimer = IntClock;
					StartBoostTimer = true;
				}

				//gives thrust
				Thrust = { Scalar(BoostAccelMultipier, Thrust) };

				//checks time limit
				if (StartBoostTimer && IntClock > BoostTimer + BoostTimeLimit)
				{
					//decelereates the car
					Momentum = { Scalar(BoostDecelMultiplier, Momentum) };
					StartBoostTimer = false; //stops timer
					BoostAllowed = false; //boost not allowed
				}

				//display boost warning
				if (StartBoostTimer && IntClock + BoostWarningAmount > BoostTimer + BoostTimeLimit)
				{
					BoostWarning = true;
				}

				else
				{
					BoostWarning = false;
				}
			}

			//if boost not allowed
			else if (!BoostAllowed)
			{
				//start boostcooldown timer
				if (!StartBoostCoolDown)
				{
					StartBoostCoolDown = true;
					BoostCoolDownTimer = IntClock;
				}

				//Checks time limit
				if (IntClock > BoostCoolDownTimer + BoostCoolDownLimit)
				{
					StartBoostCoolDown = false; //stops timmer
					BoostAllowed = true; // boost is allowed again
				}
			}
			else
			{
				StartBoostTimer = false;
				BoostWarning = false;
			}

			//drag
			Drag = Scalar(Player.Drag, Momentum);

			//Calculate overall momentum
			Momentum = Sum3(Momentum, Thrust, Drag);

			//Checks collision with non-player car
			if (PlayerToNPC(Player, NonPlayer))
			{
				DummyPlayer->SetPosition(PreviousX, 0.0f, PreviousZ);
				Momentum.X = -Momentum.X;
				Momentum.Z = -Momentum.Z;
			}

			//Colision Detection, Runs through every object in the vector 
			else
			{
				for (int i = 0; i < NumberOfObjects; i++)
				{
					int Check = MapItems[i].t; //Gets what object is being checked.

					//Circles (Bounce off them)
					if (Check == FlareMesh || Check == GarageSmallMesh || Check == LampMesh || Check == Race2Mesh || Check == TankLarge1Mesh || Check == TankLarge2Mesh || Check == TankSmall1Mesh || Check == TankSmall2Mesh || Check == Tribune1Mesh)
					{
						if (SphereToSphere(Player, MapItems[i]))
						{
							DamageTaken = true;
							DummyPlayer->SetPosition(PreviousX, 0.0f, PreviousZ);
							Momentum.X = -Momentum.X;
							Momentum.Z = -Momentum.Z;
							i = NumberOfObjects; //exits detection
						}
					}

					//CheckPoint Detection, Go through them
					else if (Check == CheckPointMesh)
					{
						//checks which checkpoint player has gone though
						for (int j = 0; j < NumberOfCheckPoints; j++)
						{
							if (CheckPointState == j) {
								//if checkpoint gone though is equal to checkpoint state, update state.
								if (SphereToSphere(Player, MapItems[CheckPointPosList[j]]))
								{
									CheckPointState = CheckPointState + 1;
									//When Checkpoint state is larger than number of checkpoints, increase amount of laps completed
									if (CheckPointState == NumberOfCheckPoints && LapState < NumberOfLaps)
									{
										CheckPointState = 0;
										LapState++;
									}
								}
							}
						}
						//detects checkpoint legs
						if (SphereToCheckPointLegs(Player, MapItems[i]))
						{
							DamageTaken = true;
							DummyPlayer->SetPosition(PreviousX, 0.0f, PreviousZ);
							Momentum.X = -Momentum.X;
							Momentum.Z = -Momentum.Z;
							i = NumberOfObjects; //exits detection loop
						}
					}

					//Box Collisions (bounce off them)
					else if (Check == GarageLargeMesh || Check == InterStellarMesh || Check == IsleCornerMesh || Check == IsleCrossMesh || Check == IsleStraightMesh || Check == IsleTeeMesh || Check == Tribune2Mesh || Check == Tribune3Mesh || Check == WallMesh)
					{
						if (SphereToBox(Player, MapItems[i]))
						{
							DamageTaken = true;
							DummyPlayer->SetPosition(PreviousX, 0.0f, PreviousZ);
							Momentum.X = -Momentum.X;
							Momentum.Z = -Momentum.Z;
							i = NumberOfObjects; //exits detection
						}
					}

					//Dummy Path Finder
					else if (Check == DummyPathFindingMesh)
					{
						for (int j = 0; j < NumberOfDummyPathFinders; j++)
						{
							if (PathFinderState == j)
							{
								if (SphereToSphere(NonPlayer, MapItems[DummyPathFinderList[j]]))
								{
									PathFinderState++;
									if (PathFinderState == NumberOfDummyPathFinders)
									{
										PathFinderState = 0;
									}
									//Implement collision detection between the car and the struts of the checkpoints as sphere - to - sphere
								}
							}
						}
					}
				}
			}

			//move hovercar(dummy)
			DummyPlayer->Move(Momentum.X, 0.0f, Momentum.Z);
			SpeedReadOut = SpeedMultiplier * sqrt(pow(Momentum.X, 2) + pow(Momentum.Z, 2));

			//rotate car
			if (myEngine->KeyHeld(KeyTurnLeft))
			{
				DummyPlayer->RotateLocalY(-Player.RotationSpeed);
				if (RotationCount > -RotationLimit)
				{
					Player.Model->RotateLocalZ(RotationAmount);
					RotationCount--;
				}
			}

			else if (myEngine->KeyHeld(KeyTurnRight))
			{
				DummyPlayer->RotateLocalY(Player.RotationSpeed);
				if (RotationCount < RotationLimit)
				{
					Player.Model->RotateLocalZ(-RotationAmount);
					RotationCount++;
				}
			}

			else
			{
				if (RotationCount >= -RotationLimit && RotationCount < 0)
				{
					Player.Model->RotateLocalZ(-RotationAmount);
					RotationCount++;
				}

				else if (RotationCount <= RotationLimit && RotationCount > 0)
				{
					Player.Model->RotateLocalZ(RotationAmount);
					RotationCount--;
				}
			}

			//Damage Control
			if (DamageTaken)
			{
				DamageTaken = false;
				HoverCarHealth--;
			}

			//If hovercar has no health, end game
			if (HoverCarHealth <= 0)
			{
				GameState = RaceOver;
			}

			///////////////////
			//Camera Controls//
			/////////////////// 

			//Mouse moves the camera
			//Look up and down (MouseY)
			float YRotator = myEngine->GetMouseMovementY();
			InitalMouseY = InitalMouseY + YRotator;
			if (InitalMouseY > MouseYMin&& InitalMouseY < MouseYMax) MyCamera->RotateLocalX(YRotator);
			else InitalMouseY = InitalMouseY - YRotator;

			//Look ARound (MouseX)
			MyCamera->RotateY(myEngine->GetMouseMovementX());

			//Arrow keys move camera
			if (myEngine->KeyHeld(KeyCamFowards))   MyCamera->MoveLocalZ(CamSpeed);
			if (myEngine->KeyHeld(KeyCamBackwards))	MyCamera->MoveLocalZ(-CamSpeed);
			if (myEngine->KeyHeld(KeyCamRight))		MyCamera->MoveLocalX(CamSpeed);
			if (myEngine->KeyHeld(KeyCamLeft))		MyCamera->MoveLocalX(-CamSpeed);

			//reset camera
			if (myEngine->KeyHit(KeyCamReset))
			{
				MyCamera->DetachFromParent();
				MyCamera->ResetOrientation();
				MyCamera->SetPosition(CamX, CamY, CamZ);
				MyCamera->MoveY(CamMoveY);
				MyCamera->MoveZ(CamMoveZ);
				MyCamera->RotateLocalX(CamRotateLocalX);
				MyCamera->AttachToParent(DummyPlayer);
				InitalMouseY = 0.0f;
				FirstPerson = false;
			}

			//first person Camera
			if (myEngine->KeyHit(KeyCamFirstPerson))
			{
				MyCamera->DetachFromParent();
				MyCamera->ResetOrientation();
				MyCamera->SetPosition(CamX, CamY + CamFpY, CamZ + CamFpZ);
				MyCamera->MoveY(CamMoveY);
				MyCamera->MoveZ(CamMoveZ);
				MyCamera->RotateLocalX(CamRotateLocalX);
				InitalMouseY = 0.0f;
				MyCamera->AttachToParent(Player.Model);

				FirstPerson = true;
				Player.Model->SetY(0.0f);
			}

			if (myEngine->KeyHit(Key_3))
			{
				MyCamera->DetachFromParent();
				MyCamera->ResetOrientation();
				MyCamera->SetPosition(CamX, CamY + CamFpY, CamZ + CamFpZ);
				MyCamera->MoveY(CamMoveY);
				MyCamera->MoveZ(CamMoveZ);
				MyCamera->RotateLocalX(CamRotateLocalX);
				InitalMouseY = 0.0f;
				MyCamera->AttachToParent(NonPlayer.Model);
				FirstPerson = true;
				Player.Model->SetY(0.0f);
			}


			//////////
			////NPC///
			//////////

			//Looking at dummy waypoints
			NonPlayer.Model->MoveLocalZ(frameTime * NonPlayer.Acceleration);
			NonPlayer.Model->LookAt(MapItems[DummyPathFinderList[PathFinderState]].Model);


			////////////
			//drawings//
			//////////// 


			if (BoostWarning)
			{
				myFont->Draw("Overheating!", TextBoostX, TextBoostY, kBlack, kCentre);
			}

			else if (StartBoostTimer)
			{
				myFont->Draw("BOOST", TextBoostX, TextBoostY, kBlack, kCentre);
			}

			//drawing Checkpoint States
			if (CheckPointState < NumberOfCheckPoints)
			{
				myFont->Draw("CheckPoint " + to_string(CheckPointState) + " of " + to_string(NumberOfCheckPoints) + " complete", TextDialogX, TextDialogY, kBlack, kCentre);
			}

			//draw when crossing finishline

			//number of laps
			myFont->Draw("Lap " + to_string(LapState) + " / " + to_string(NumberOfLaps), TextDialogX, LapHeightPos, kBlack, kCentre);

			//health
			myFont->Draw("Health " + to_string(HoverCarHealth) + " / " + to_string(HoverCarMaxHealth), TextHealthX, TextHealthY, kBlack, kCentre);

			//Draw speed readout
			myFont->Draw("MPH: " + to_string(SpeedReadOut), TextSpeedX, TextSpeedY, kBlack, kCentre);

			//Developer
			if (myEngine->KeyHeld(KeyDevloper))
			{
				myFont->Draw("FrameTime: " + to_string(frameTime), 0, 25 * 4, kBlack);
				myFont->Draw("X: " + to_string(DummyPlayer->GetX()), 0, 25., kBlack);
				myFont->Draw("Y: " + to_string(DummyPlayer->GetY()), 0, 25 * 2, kBlack);
				myFont->Draw("Z: " + to_string(DummyPlayer->GetZ()), 0, 25 * 3, kBlack);
				myFont->Draw("FPS " + to_string(1.0f / frameTime), 0, 25 * 5, kBlack);
				myFont->Draw("pX: " + to_string(Player.Model->GetX()), 0, 25 * 6, kBlack);
				myFont->Draw("pY: " + to_string(Player.Model->GetY()), 0, 25 * 7, kBlack);
				myFont->Draw("pZ: " + to_string(Player.Model->GetZ()), 0, 25 * 8, kBlack);
				myFont->Draw("Front Sphere r: " + to_string(Player.FrontRadius), 0, 25 * 9, kBlack);
				myFont->Draw("Front Sphere z: " + to_string(Player.Model->GetZ() + Player.FrontOffsetZ), 0, 25 * 10, kBlack);
				myFont->Draw("Back Sphere r: " + to_string(Player.BackRadius), 0, 25 * 11, kBlack);
				myFont->Draw("Back Sphere z: " + to_string(Player.Model->GetZ() + Player.BackOffsetZ), 0, 25 * 12, kBlack);
				myFont->Draw("NpcX: " + to_string(NonPlayer.Model->GetX()), 0, 25 * 13, kBlack);
				myFont->Draw("NpcY: " + to_string(NonPlayer.Model->GetY()), 0, 25 * 14, kBlack);
				myFont->Draw("NpcpZ: " + to_string(NonPlayer.Model->GetZ()), 0, 25 * 15, kBlack);
			}
		}

		else if (GameState == RaceOver)
		{
			//print GameState
			myFont->Draw("Playing", TextStateX, TextStateY, kBlack, kCentre);
			//print dialog, Race complete
			myFont->Draw("Race complete", TextDialogX, TextDialogY, kBlack, kCentre);
			int IntClock = Clock;
			myFont->Draw("Congratulations you finished the race in " + to_string(IntClock) + " Seconds!", GameCenterWidth, GameCenterHeight, kBlack, kCentre);
			DummyPlayer->RotateY(CamSpeed);
			Player.Model->RotateY(-CamSpeed);
		}
	}
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

// Assignment 3.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace tle;

const int NumberOfThings = 24;
//Create Map Shiz
enum SkinNum {
	CheckPointMesh, CrossMesh,FlareMesh, GarageLargeMesh, GarageSmallMesh, GroundMesh,
	InterStellarMesh,IsleCornerMesh,IsleCrossMesh,IsleStraightMesh,IsleTeeMesh,
	LampMesh,Race2Mesh,SkyBoxMesh,TankLarge1Mesh,TankLarge2Mesh,TankSmall1Mesh,TankSmall2Mesh,
	Tribune1Mesh,Tribune2Mesh,Tribune3Mesh,WalkWayMesh, WallMesh, DummyMesh
};
const string NameOfSkin[NumberOfThings]{ "CheckPointMesh", "CrossMesh", "FlareMesh", "GarageLargeMesh", "GarageSmallMesh", "GroundMesh",
"InterStellarMesh", "IsleCornerMesh", "IsleCrossMesh", "IsleStraightMesh", "IsleTeeMesh",
"LampMesh", "Race2Mesh", "SkyBoxMesh", "TankLarge1Mesh", "TankLarge2Mesh", "TankSmall1Mesh", "TankSmall2Mesh",
"Tribune1Mesh", "Tribune2Mesh", "Tribune3Mesh", "WalkWayMesh", "WallMesh", "DummyMesh" };
const enum Coordinates {ObjName, CoX , CoY , CoZ, CoR, CoorLength };
class ObjectMaker 
{
public:

	IModel*Model;
	float x;
	float y;
	float z;
	float Rotation = 0.0f;
	
};
int NumberOfObject()
{
	ifstream FileIn("map.txt");
	if (!FileIn)
			{
				cout << "[ERROR]: Can't open input file, File May be missing... \n ";
				cout << "<Creating File>";
				ofstream outfile("map.txt");
				//(Mesh x y z rotation ) Space at the end is important
				outfile << to_string(SkyBoxMesh) << " 0.0 -960.0 0.0 0.0 " << endl;	//skybox
				outfile << to_string(GroundMesh) << " 0.0 0.0 0.0 0.0 " << endl; //ground																		 
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
	else { FileIn.close(); }
		string line;
		int TestCount = 0;
		FileIn.open("map.txt");
		while (!FileIn.eof())
		{
			getline(FileIn, line);
			TestCount++;
		}
		FileIn.close();
		return TestCount;
}
void VectorGet(vector <string> & TEST)
{
	ifstream FileIn("map.txt");
	if (!FileIn)
			{
				cout << "[ERROR]: Can't open input file, File May be missing... \n ";
				cout << "<Creating File>";
				ofstream outfile("map.txt");
				outfile << "1 0 0 -50 0";		
			}
	string line;
	int counter = 0;
	while (!FileIn.eof())
	{
		getline(FileIn, line);
		TEST[counter] = line ;
		counter++;
	}
	for (int i = 0; i < TEST.size(); i++)
	{
		cout << "num " << i << ": "<< TEST[i] << endl;
	}

	return;
}
void Write(int Mesh, float x, float y, float z, float rotation)
{
	ofstream myfile;
	myfile.open("Map.txt", myfile.app);
	myfile << endl << to_string(Mesh) + " " + to_string(x) + " " + to_string(y) + " " + to_string(z) + " " + to_string(rotation) + " ";
	myfile.close();
}




void main()
{

	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed(1000,500);

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("Media");
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");

	/**** Set up your scene here ****/

	//timer, The total Frame Time
	float Clock = 0.0f;
	myEngine->Timer();

	//Font
	IFont* myFont = myEngine->LoadFont("Times New Roman", 30);

	//Constants
	const float kGameSpeed = 1.0f;

	//camera
	ICamera*MyCamera = myEngine->CreateCamera(kManual, 0.0f, 0.0f, 0.0f);

	//Meshes 
	IMesh*ObjSkin[25];
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
	ObjSkin[DummyMesh] = myEngine->LoadMesh("Flare2.x"); //22
 
	//Load Object Maker
	ObjectMaker Player;

	//Dummy
	IMesh*DummyMash = myEngine->LoadMesh("Dummy.x");
	IModel*DummyPlayer = DummyMash->CreateModel(0.0f,0.0f,0.0f);

	//HoverCar Player;
	Player.Model = ObjSkin[0]->CreateModel(0.0f,0.0f,0.0f);
	Player.Model->AttachToParent(DummyPlayer);

	//Attach Camera To Hover-Car
	MyCamera->AttachToParent(DummyPlayer);
	MyCamera->MoveY(10.0f);
	MyCamera->MoveZ(-30.0f);
	MyCamera->RotateLocalX(20.0f);

	//backdrop
	myEngine->CreateSprite("ui_backdrop.jpg", (myEngine->GetWidth() / 2) - 350.0f, myEngine->GetHeight() - 60.0f, 0.0f);

	//keys
	///////////

	//Z
	EKeyCode AccelerateKey = Key_W;
	EKeyCode DecelerateKey = Key_S;
	EKeyCode MoveRightKey = Key_D;
	EKeyCode MoveLeftKey = Key_A;

	//x
	EKeyCode TurnRightKey = Key_E;
	EKeyCode TurnLeftKey = Key_Q;

	//y
	EKeyCode MoveUpKey = Key_R;
	EKeyCode MoveDownKey = Key_F;

	//Objects
	EKeyCode CycleRightKey = Key_X;
	EKeyCode CycleLeftKey = Key_Z;
	EKeyCode PlaceObjectKey = Key_0;

	//game
	EKeyCode QuitKey = Key_Escape;
	EKeyCode PauseKey = Key_P;

	//camera
	EKeyCode KeyCamFowards = Key_Up;
	EKeyCode KeyCamBackwards = Key_Down;
	EKeyCode KeyCamLeft = Key_Left;
	EKeyCode KeyCamRight = Key_Right;

	//variables
	float DialogPos = myEngine->GetHeight() - 30.0f;
	float StateTextPos = myEngine->GetHeight() - 60.0f;
	float MoveMent = 1.0f * kGameSpeed;

	int Skin = 0;
	float LoadRot = 0.0f;
	vector <string> List (NumberOfObject());
	VectorGet(List);
	vector <IModel*> TEST;
	TEST.resize(NumberOfObject());

	//creates objects
	for (int e = 0; e < List.size(); e++)
	{
		string t;
		string x;
		string y;
		string z;
		string r;

		string line = List[e];
		string Holder = "";
		int RowCount = 0;
		//sorts shit
		for (int i = 0; i < line.length(); i++)
		{
			Holder = Holder + line[i];
			if (line.length() == 0)
			{

			}
			else if (line[i] == ' ')
			{
				if (RowCount == 0) t = Holder;
				else if (RowCount == 1) x = Holder;
				else if (RowCount == 2) y = Holder;
				else if (RowCount == 3) z = Holder;
				else if (RowCount == 4) r = Holder;		
				Holder = "";
				RowCount++;
			}
		}

		//commits it

			TEST[e] = ObjSkin[stoi(t)]->CreateModel(stoi(x), stoi(y), stoi(z));
			TEST[e]->RotateLocalY(stoi(r));

	}

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

		//Timer
		float frameTime = myEngine->Timer() * kGameSpeed;

		//Developer
			myFont->Draw("FrameTime: " + to_string(frameTime), 0.0f, 0.0f, kBlack);
			myFont->Draw("X: " + to_string(Player.Model->GetX()), 0.0f, 25.0f, kBlack);
			myFont->Draw("Y: " + to_string(Player.Model->GetY()), 0.0f, 25.0f*2.0f, kBlack);
			myFont->Draw("Z: " + to_string(Player.Model->GetZ()), 0.0f, 25.0f*3.0f, kBlack);
			myFont->Draw("Rotation: " + to_string(Player.Rotation), 0.0f, 25.0f*4.0f, kBlack);
			myFont->Draw("FPS " + to_string(1.0f/frameTime), 0.0f, 25.0f*5.0f, kBlack);
			myFont->Draw("X: " + to_string(DummyPlayer->GetX()), 0.0f, 25.0f*6.0f, kBlack);
			myFont->Draw("Y: " + to_string(DummyPlayer->GetY()), 0.0f, 25.0f*7.0f, kBlack);
			myFont->Draw("Z: " + to_string(DummyPlayer->GetZ()), 0.0f, 25.0f*8.0f, kBlack);
			myFont->Draw("Skin: " + NameOfSkin[Skin], myEngine->GetWidth()/2.0f, 0.0f, kBlack,kCentre);
		
			//Exit game
		if (myEngine->KeyHit(QuitKey))
		{
			myEngine->Stop();
		}

		//Object movement
		if (myEngine->KeyHit(AccelerateKey))
		{
			DummyPlayer->MoveLocalZ(MoveMent);
		}
		if (myEngine->KeyHit(DecelerateKey))
		{
			DummyPlayer->MoveLocalZ(-MoveMent);
		}
		if (myEngine->KeyHit(MoveRightKey))
		{
			DummyPlayer->MoveLocalX(MoveMent);
			//DummyPlayer->RotateLocalY(0.150f);
		}
		if (myEngine->KeyHit(MoveLeftKey))
		{
			DummyPlayer->MoveLocalX(-MoveMent);
			//DummyPlayer->RotateLocalY(-0.150f);
		}
		if (myEngine->KeyHit(Key_E))
		{
			DummyPlayer->RotateY(90.0f);
			//DummyPlayer->MoveLocalX(0.150f);
			Player.Rotation = Player.Rotation + 90.0f;
		}
		if (myEngine->KeyHit(Key_Q))
		{
			DummyPlayer->RotateY(-90.0f);
			//DummyPlayer->MoveLocalX(-0.150f);
			Player.Rotation = Player.Rotation - 90.0f;
		}

		if (myEngine->KeyHit(MoveUpKey))
		{
			DummyPlayer->MoveY(MoveMent);
		}
		if (myEngine->KeyHit(MoveDownKey))
		{
			DummyPlayer->MoveY(-MoveMent);
		}

		//skin cycle
		if (myEngine->KeyHit(CycleRightKey))
		{
			Skin++;
			ObjSkin[Skin - 1]->RemoveModel(Player.Model);
			if (Skin > NumberOfThings-1)
			{
				Skin = 0;
			}
			Player.Model = ObjSkin[Skin]->CreateModel();
			Player.Model->ResetOrientation();
			Player.Model->RotateLocalY(LoadRot);
			Player.Model->AttachToParent(DummyPlayer);

		}

		if (myEngine->KeyHit(CycleLeftKey))
		{
			Skin--;
			ObjSkin[Skin + 1]->RemoveModel(Player.Model);
			if (Skin < 0)
			{
				Skin = NumberOfThings-1;
			}

			Player.Model = ObjSkin[Skin]->CreateModel();
			Player.Model->ResetOrientation();
			Player.Model->RotateLocalY(LoadRot);
			Player.Model->AttachToParent(DummyPlayer);

		}

		if (myEngine->KeyHit(PlaceObjectKey))
		{
			Player.x = DummyPlayer->GetX();
			Player.y = DummyPlayer->GetY();
			Player.z = DummyPlayer->GetZ();

			Player.Model->DetachFromParent();
			Player.Model->SetX(Player.x);
			Player.Model->SetY(Player.y);
			Player.Model->SetZ(Player.z);
			Player.Model->ResetOrientation();
			Player.Model->RotateLocalY(Player.Rotation);

			Player.Model = ObjSkin[Skin]->CreateModel();
			Player.Model->ResetOrientation();
			Player.Model->RotateLocalY(LoadRot);
			Player.Model->AttachToParent(DummyPlayer);
			//Player.Model->ResetOrientation();
			//Player.Model->RotateY(Player.Rotation);

			Write(Skin, Player.x, Player.y, Player.z, Player.Rotation);
		}

		////////////////////
		//Camera Controlls//
		////////////////////

		if (myEngine->KeyHeld(KeyCamFowards))
		{
			MyCamera->MoveLocalZ(MoveMent);
			//MyCamera->LookAt(Player.Model);
		}
		if (myEngine->KeyHeld(KeyCamBackwards))
		{
			MyCamera->MoveLocalZ(-MoveMent);
			//MyCamera->LookAt(Player.Model);
		}
		if (myEngine->KeyHit(KeyCamRight))
		{
			Player.Model->RotateLocalY(90.0f);
			Player.Rotation = Player.Rotation + 90.0f;
			LoadRot = LoadRot + 90.0f;
		}
		if (myEngine->KeyHit(KeyCamLeft))
		{
			Player.Model->RotateLocalY(-90.0f);
			Player.Rotation = Player.Rotation - 90.0f;
			LoadRot = LoadRot - 90.0f;
		}


		if (myEngine->KeyHit(Key_1))
		{
			MoveMent = MoveMent / 10.0f;
		}		
		if (myEngine->KeyHit(Key_2))
		{
			MoveMent = MoveMent * 10.0f;
		}		

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

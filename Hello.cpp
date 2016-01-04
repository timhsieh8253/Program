/*==============================================================
character movement testing using Fly2

- Load a scene
- Generate a terrain object
- Load a character
- Control a character to move
- Change poses

(C)2012-2015 Chuan-Chang Wang, All Rights Reserved
Created : 0802, 2012

Last Updated : 1004, 2015, Kevin C. Wang
===============================================================*/
#include "FlyWin32.h"
#include <numeric>
#include "LYUBU.h"
#include "DONZO.h"
#include "ROBBER.h"
#include "FOOTMAN.h"
#include "SORCERER.h"
#include "WARLORD.h"
//Tim2016
#define RandomWalk 1
#define FollowActor 2
#define StartAttacl 3

float result[3];
VIEWPORTid vID;                 // the major viewport
SCENEid sID;                    // the 3D scene
OBJECTid cID, tID;              // the main camera and the terrain for terrain following
LYUBU Lyubu;
DONZO Donzo;
ROBBER Robber;
//Tim2016
FOOTMAN Footman;
SORCERER Sorcerer;
WARLORD WarLord;

int attack_on_delay = 0;//for attack delay
bool action_lock = 0;//



ROOMid terrainRoomID = FAILED_ID;
TEXTid textID = FAILED_ID;

// some globals
int frame = 0;
int oldX, oldY, oldXM, oldYM, oldXMM, oldYMM;
int cur_angle = 0;
// hotkey callbacks
void QuitGame(BYTE, BOOL4);
void Movement(BYTE, BOOL4);

//Tim Attack
void Keyboardfunc(BYTE, BOOL4);

// timer callbacks
void GameAI(int);
void RenderIt(int);

// mouse callbacks
void InitPivot(int, int);
void PivotCam(int, int);
void InitMove(int, int);
void MoveCam(int, int);
void InitZoom(int, int);
void ZoomCam(int, int);
//LyuBu function
//void LyuBu_init(BOOL4 &beOK);
void LyuBu_turn();


float vector_norm(float* A){

	return sqrt(pow(A[0], 2) + pow(A[1], 2) + pow(A[2], 2));

}
void cal_ud(float* new_f, float* new_d, float* act_pos, float* cam_pos){
	float x12, y12, z12, z21;

	x12 = act_pos[0] - cam_pos[0];
	y12 = act_pos[1] - cam_pos[1];
	z12 = act_pos[2] - cam_pos[2];
	z21 = -z12;

	new_f[0] = act_pos[0] - cam_pos[0];
	new_f[1] = act_pos[1] - cam_pos[1];
	new_f[2] = z12;

	new_d[0] = z21 * x12;
	new_d[1] = z21 * y12;
	new_d[2] = x12*x12 + y12*y12;

}
//minimal
double radious;
bool character_camera_angel(){
	FnCamera camera;
	FnCharacter actor;
	float act_pos[3];
	float cam_pos[3], cam_f[3], cam_d[3], hit_d[3];
	FnObject terrain;
	terrain.ID(tID);

	// get camera information
	camera.ID(cID);
	camera.GetPosition(cam_pos);
	camera.GetDirection(cam_f, cam_d);

	// play character pose
	actor.ID(Lyubu.id);
	actor.GetPosition(act_pos);
	hit_d[0] = cam_pos[0] - act_pos[0];
	hit_d[1] = cam_pos[1] - act_pos[1];
	hit_d[2] = cam_pos[2] - act_pos[2];

	result[0] = result[1] = result[2] = 0;
	double org_distance = hit_d[0] * hit_d[0] + hit_d[1] * hit_d[1] + hit_d[2] * hit_d[2];
	if (terrain.HitTest(act_pos, hit_d, result, NULL, NULL, NULL, NULL)){

		if (cam_pos[2]<1600 &&
			result[0] && result[1] && result[2] &&
			((result[0] - act_pos[0])*(result[0] - act_pos[0]) + (result[1] - act_pos[1])*(result[1] - act_pos[1]) + (result[2] - act_pos[2])*(result[2] - act_pos[2])) <
			((act_pos[0] - cam_pos[0])*(act_pos[0] - cam_pos[0]) + (act_pos[1] - cam_pos[1])*(act_pos[1] - cam_pos[1]) + (act_pos[2] - cam_pos[2])*(act_pos[2] - cam_pos[2])))
		{
			cam_pos[2] += 5;
			double cur_distance = org_distance - (hit_d[2] * hit_d[2]) + (act_pos[2] - cam_pos[2])*(act_pos[2] - cam_pos[2]);
			double scale = radious / cur_distance;

			scale = 1;
			float new_f[3] = { act_pos[0] - cam_pos[0], act_pos[1] - cam_pos[1], act_pos[2] - cam_pos[2] };
			cam_pos[0] = act_pos[0] - new_f[0] * scale;
			cam_pos[1] = act_pos[1] - new_f[1] * scale;
			cam_pos[2] = act_pos[2] - new_f[2] * scale;
			float new_d[3] = { -new_f[2] * new_f[0], -new_f[2] * new_f[1], new_f[0] * new_f[0] + new_f[1] * new_f[1] };
			camera.SetPosition(cam_pos);
			camera.SetDirection(new_f, new_d);
			//result[2] = scale;
			return TRUE;
		}
		else{
			// no obstacle
			terrain.HitTest(act_pos, hit_d, result, NULL, NULL, NULL, NULL);
			if (cam_pos[2] > 200){
				cam_pos[2] -= 5;
				if (cam_pos[2] < 200)
					cam_pos[2] = 200;
				double cur_distance = org_distance - (hit_d[2] * hit_d[2]) + (act_pos[2] - cam_pos[2])*(act_pos[2] - cam_pos[2]);
				double scale = radious / cur_distance;

				scale = 1;
				float new_f[3] = { act_pos[0] - cam_pos[0], act_pos[1] - cam_pos[1], act_pos[2] - cam_pos[2] };
				cam_pos[0] = act_pos[0] - new_f[0] * scale;
				cam_pos[1] = act_pos[1] - new_f[1] * scale;
				cam_pos[2] = act_pos[2] - new_f[2] * scale;
				float new_d[3] = { -new_f[2] * new_f[0], -new_f[2] * new_f[1], new_f[0] * new_f[0] + new_f[1] * new_f[1] };

				hit_d[0] = cam_pos[0] - act_pos[0];
				hit_d[1] = cam_pos[1] - act_pos[1];
				hit_d[2] = cam_pos[2] - act_pos[2];

				result[0] = result[1] = result[2] = 0;
				terrain.HitTest(act_pos, hit_d, result, NULL, NULL, NULL, NULL);
				if (!result[0] && !result[1] && !result[2])
				{
					camera.SetPosition(cam_pos);
					camera.SetDirection(new_f, new_d);
				}
				//result[2] = scale;
			}
			return FALSE;
		}

	}
	else{
		return FALSE;
	}
}


/*------------------
the main program
C.Wang 1010, 2014
-------------------*/
void FyMain(int argc, char **argv)
{
	// create a new world
	BOOL4 beOK = FyStartFlyWin32("NTU@2015 Homework #03 - Use Fly2", 0, 0, 1024, 768, FALSE);

	// setup the data searching paths
	FySetShaderPath("Data\\NTU6\\Shaders");
	FySetModelPath("Data\\NTU6\\Scenes");
	FySetTexturePath("Data\\NTU6\\Scenes\\Textures");
	FySetScenePath("Data\\NTU6\\Scenes");

	// create a viewport
	vID = FyCreateViewport(0, 0, 1024, 768);
	FnViewport vp;
	vp.ID(vID);

	// create a 3D scene
	sID = FyCreateScene(10);
	FnScene scene;
	scene.ID(sID);

	// load the scene
	scene.Load("gameScene02");
	scene.SetAmbientLights(1.0f, 1.0f, 1.0f, 0.6f, 0.6f, 0.6f);

	// load the terrain
	tID = scene.CreateObject(OBJECT);
	FnObject terrain;
	terrain.ID(tID);
	BOOL beOK1 = terrain.Load("terrain");
	terrain.Show(FALSE);

	// set terrain environment
	terrainRoomID = scene.CreateRoom(SIMPLE_ROOM, 10);
	FnRoom room;
	room.ID(terrainRoomID);
	room.AddObject(tID);

	// load the character
	FySetModelPath("Data\\NTU6\\Characters");
	FySetTexturePath("Data\\NTU6\\Characters");
	FySetCharacterPath("Data\\NTU6\\Characters");

	//lo character init
	Lyubu.Initiate(sID, terrainRoomID, beOK);
	Donzo.Initiate(sID, terrainRoomID, beOK);
	Robber.Initiate(sID, terrainRoomID, beOK);
	Footman.Initiate(sID, terrainRoomID, beOK);
	Sorcerer.Initiate(sID, terrainRoomID, beOK);
	WarLord.Initiate(sID, terrainRoomID, beOK);

	// translate the camera
	cID = scene.CreateObject(CAMERA);
	FnCamera camera;
	camera.ID(cID);
	camera.SetNearPlane(5.0f);
	camera.SetFarPlane(100000.0f);

	// set camera initial position and orientation
	//pos[0] = 3869.0f; pos[1] = -3508.0f; pos[2] = 150.0f;
	float act_pos[3], pos[3], fDir[3], uDir[3];
	FnCharacter actor;
	actor.ID(Lyubu.id);
	actor.GetPosition(act_pos);
	actor.GetDirection(fDir, uDir);

	pos[0] = 2969.0f; pos[1] = -3708.0f; pos[2] = 100.0f;
	cal_ud(fDir, uDir, act_pos, pos);

	camera.SetDirection(fDir, uDir);
	camera.SetPosition(pos);
	radious = (act_pos[0] - pos[0])*(act_pos[0] - pos[0]) + (act_pos[1] - pos[1])*(act_pos[1] - pos[1]) + (act_pos[2] - pos[2])*(act_pos[2] - pos[2]);

	float mainLightPos[3] = { -4579.0, -714.0, 15530.0 };
	float mainLightFDir[3] = { 0.276, 0.0, -0.961 };
	float mainLightUDir[3] = { 0.961, 0.026, 0.276 };

	FnLight lgt;
	lgt.ID(scene.CreateObject(LIGHT));
	lgt.Translate(mainLightPos[0], mainLightPos[1], mainLightPos[2], REPLACE);
	lgt.SetDirection(mainLightFDir, mainLightUDir);
	lgt.SetLightType(PARALLEL_LIGHT);
	lgt.SetColor(1.0f, 1.0f, 1.0f);
	lgt.SetName("MainLight");
	lgt.SetIntensity(0.4f);

	// create a text object for displaying messages on screen
	textID = FyCreateText("Trebuchet MS", 18, FALSE, FALSE);

	// set Hotkeys
	FyDefineHotKey(FY_ESCAPE, QuitGame, FALSE);  // escape for quiting the game
	FyDefineHotKey(FY_UP, Movement, FALSE);      // Up for moving forward
	FyDefineHotKey(FY_DOWN, Movement, FALSE);    // Down for moving backward
	FyDefineHotKey(FY_RIGHT, Movement, FALSE);   // Right for turning right
	FyDefineHotKey(FY_LEFT, Movement, FALSE);    // Left for turning left

	//Tim Attack
	FyDefineHotKey(FY_A, Keyboardfunc, FALSE);
	FyDefineHotKey(FY_S, Keyboardfunc, FALSE);
	FyDefineHotKey(FY_L, Keyboardfunc, FALSE);	// lo for testing die

	// define some mouse functions
	FyBindMouseFunction(LEFT_MOUSE, InitPivot, PivotCam, NULL, NULL);
	FyBindMouseFunction(MIDDLE_MOUSE, InitZoom, ZoomCam, NULL, NULL);
	FyBindMouseFunction(RIGHT_MOUSE, InitMove, MoveCam, NULL, NULL);

	// bind timers, frame rate = 30 fps
	FyBindTimer(0, 30.0f, GameAI, TRUE);
	FyBindTimer(1, 30.0f, RenderIt, TRUE);

	//while (character_camera_angel());
	// invoke the system
	FyInvokeFly(TRUE);

}


/*-------------------------------------------------------------
30fps timer callback in fixed frame rate for major game loop
--------------------------------------------------------------*/
void GameAI(int skip)
{
	FnCamera camera;
	FnCharacter actor, act_Robber, act_DonZo;
	float act_pos[3];
	float cam_pos[3], cam_f[3], cam_d[3];
	FnObject terrain;
	terrain.ID(tID);


	// get camera information
	camera.ID(cID);
	camera.GetPosition(cam_pos);
	camera.GetDirection(cam_f, cam_d);

	// play character pose
	actor.ID(Lyubu.id);
	actor.Play(LOOP, (float)skip, FALSE, TRUE);
	actor.GetPosition(act_pos);
	//Tim2016
	Footman.play(attack_on_delay, skip, action_lock);
	Sorcerer.play(attack_on_delay, skip, action_lock);
	WarLord.play(attack_on_delay, skip, action_lock);
	//lo play Robber pose
	Robber.play(attack_on_delay, skip, action_lock);

	//lo play DonZo
	Donzo.play(attack_on_delay, skip, action_lock);

	float dif_pos[3] = { cam_pos[0] - act_pos[0], cam_pos[1] - act_pos[1], cam_pos[2] - act_pos[2] };

	// Homework #01 part 1
	// ....
	float dis = 10.0f;
	float movement[3];
	float new_f[3], new_d[3];

	if (!Lyubu.is_attack){
		// up and down
		if ((FyCheckHotKeyStatus(FY_UP) || FyCheckHotKeyStatus(FY_DOWN)) && !FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_RIGHT)){
			actor.MoveForward(dis, TRUE, FALSE, 0.0f, TRUE);
			actor.GetPosition(act_pos);
			cam_pos[0] = act_pos[0] + dif_pos[0];
			cam_pos[1] = act_pos[1] + dif_pos[1];
			cam_pos[2] = act_pos[2] + dif_pos[2];
			camera.SetPosition(cam_pos);
		}

		// right forward
		else if (FyCheckHotKeyStatus(FY_RIGHT) && FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_DOWN)){
			//actor.GetPosition(act_pos);
			//camera.GetPosition(cam_pos);
			//act_pos[0] = act_pos[0] + (-dif_pos[0] - dif_pos[1]) / sqrt(2*(dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1]))*5;
			//act_pos[1] = act_pos[1] + (-dif_pos[1] + dif_pos[0]) / sqrt(2*(dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1]))*5;
			//actor.SetPosition(act_pos);
			actor.MoveForward(dis / 2, TRUE, FALSE, 0.0f, TRUE);
			actor.GetPosition(act_pos);
			cam_pos[0] = act_pos[0] + dif_pos[0];
			cam_pos[1] = act_pos[1] + dif_pos[1];
			cam_pos[2] = act_pos[2] + dif_pos[2];
			camera.SetPosition(cam_pos);
		}
		// right backward
		else if (FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_LEFT) && FyCheckHotKeyStatus(FY_DOWN)){
			//actor.GetPosition(act_pos);
			//camera.GetPosition(cam_pos);
			//act_pos[0] = act_pos[0] + (-dif_pos[0] + dif_pos[1]) / sqrt(2 * (dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1])) * 5;
			//act_pos[1] = act_pos[1] + (dif_pos[1] + dif_pos[0]) / sqrt(2 * (dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1])) * 5;
			//actor.SetPosition(act_pos);
			actor.MoveForward(dis / 2, TRUE, FALSE, 0.0f, TRUE);
			actor.GetPosition(act_pos);
			cam_pos[0] = act_pos[0] + dif_pos[0];
			cam_pos[1] = act_pos[1] + dif_pos[1];
			cam_pos[2] = act_pos[2] + dif_pos[2];
			camera.SetPosition(cam_pos);
		}
		// left forward
		else if (!FyCheckHotKeyStatus(FY_RIGHT) && FyCheckHotKeyStatus(FY_UP) && FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_DOWN)){

			//actor.GetPosition(act_pos);
			//camera.GetPosition(cam_pos);

			//act_pos[0] = act_pos[0] + (dif_pos[0] - dif_pos[1]) / sqrt(2 * (dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1])) * 5;
			//act_pos[1] = act_pos[1] + (-dif_pos[1] - dif_pos[0]) / sqrt(2 * (dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1])) * 5;
			//actor.SetPosition(act_pos);
			actor.MoveForward(dis / 2, TRUE, FALSE, 0.0f, TRUE);
			actor.GetPosition(act_pos);
			cam_pos[0] = act_pos[0] + dif_pos[0];
			cam_pos[1] = act_pos[1] + dif_pos[1];
			cam_pos[2] = act_pos[2] + dif_pos[2];
			camera.SetPosition(cam_pos);
		}
		// left backward
		else if (!FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_UP) && FyCheckHotKeyStatus(FY_LEFT) && FyCheckHotKeyStatus(FY_DOWN)){
			//actor.GetPosition(act_pos);
			//camera.GetPosition(cam_pos);
			//act_pos[0] = act_pos[0] + (dif_pos[0] + dif_pos[1]) / sqrt(2 * (dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1])) * 5;
			//act_pos[1] = act_pos[1] + (dif_pos[1] - dif_pos[0]) / sqrt(2 * (dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1])) * 5;
			//actor.SetPosition(act_pos);
			actor.MoveForward(dis / 2, TRUE, FALSE, 0.0f, TRUE);
			actor.GetPosition(act_pos);
			cam_pos[0] = act_pos[0] + dif_pos[0];
			cam_pos[1] = act_pos[1] + dif_pos[1];
			cam_pos[2] = act_pos[2] + dif_pos[2];
			camera.SetPosition(cam_pos);
		}
		// only left
		else if (!FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_UP) && FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_DOWN)){
			//actor.TurnRight(-2.0f);
			movement[0] = dif_pos[1] / sqrt(dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1]);
			movement[1] = -dif_pos[0] / sqrt(dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1]);
			act_pos[0] += movement[0] * 5;
			act_pos[1] += movement[1] * 5;
			actor.SetPosition(act_pos);

			actor.GetPosition(act_pos);
			new_f[0] = cam_pos[1] - act_pos[1];
			new_f[1] = -(cam_pos[0] - act_pos[0]);
			new_f[2] = 0;
			new_d[0] = new_d[1] = 0;
			new_d[2] = 1;
			actor.SetDirection(new_f, new_d);

			actor.GetPosition(act_pos);
			camera.GetPosition(cam_pos);
			cal_ud(new_f, new_d, act_pos, cam_pos);

			camera.SetDirection(new_f, new_d);
		}
		else if (FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_DOWN)){

			movement[0] = -dif_pos[1] / sqrt(dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1]);
			movement[1] = dif_pos[0] / sqrt(dif_pos[0] * dif_pos[0] + dif_pos[1] * dif_pos[1]);
			act_pos[0] += movement[0] * 5;
			act_pos[1] += movement[1] * 5;
			actor.SetPosition(act_pos);

			actor.GetPosition(act_pos);
			new_f[0] = -(cam_pos[1] - act_pos[1]);
			new_f[1] = cam_pos[0] - act_pos[0];
			new_f[2] = 0;
			new_d[0] = new_d[1] = 0;
			new_d[2] = 1;
			actor.SetDirection(new_f, new_d);

			actor.GetPosition(act_pos);
			camera.GetPosition(cam_pos);
			cal_ud(new_f, new_d, act_pos, cam_pos);

			camera.SetDirection(new_f, new_d);
		}
		// press many bottom
		else if (FyCheckHotKeyStatus(FY_RIGHT) || FyCheckHotKeyStatus(FY_UP) || FyCheckHotKeyStatus(FY_LEFT) || FyCheckHotKeyStatus(FY_DOWN))
		{
			actor.MoveForward(5.0f, TRUE, FALSE, 0.0f, TRUE);
			actor.GetPosition(act_pos);
			cam_pos[0] = act_pos[0] + dif_pos[0];
			cam_pos[1] = act_pos[1] + dif_pos[1];
			cam_pos[2] = act_pos[2] + dif_pos[2];
			camera.SetPosition(cam_pos);
		}
	}
	camera.GetPosition(cam_pos);
	actor.GetPosition(act_pos);
	//camera.GetDirection(new_f,new_d);
	new_f[0] = -(act_pos[0] - cam_pos[0]);
	new_f[1] = -(act_pos[1] - cam_pos[1]);
	new_f[2] = -(act_pos[2] - cam_pos[2]);
	int iHIT = 1;
	character_camera_angel();
	Robber.isattack(0);
	Donzo.isattack(0);


	if (attack_on_delay > 0)
		attack_on_delay--;
	else
	{
		if (Lyubu.is_attack == 1)
		{

			if (!FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN)){
				Lyubu.curPoseID = Lyubu.idleID;
			}
			else{
				Lyubu.curPoseID = Lyubu.runID;
			}
			// need f and d 
			float act_d[3] = { 0, 0, 1 };
			Lyubu.is_attack = 0;
			actor.SetDirection(Lyubu.GetOldFaceDir(), act_d);
			LyuBu_turn();
			actor.SetCurrentAction(0, NULL, Lyubu.curPoseID, 5.0f);
			actor.Play(START, 0.0f, FALSE, TRUE);
		}

	}
	//camera.SetDirection(new_f, cam_d);
	/*result[0] = result[1] = result[2] = 0;
	if (terrain.HitTest(act_pos, new_f, result, NULL, NULL, NULL, NULL)){
	if (
	((result[0] - act_pos[0])*(result[0] - act_pos[0]) + (result[1] - act_pos[1])*(result[1] - act_pos[1]) + (result[2] - act_pos[2])*(result[2] - act_pos[2]))  <
	((act_pos[0] - cam_pos[0])*(act_pos[0] - cam_pos[0]) + (act_pos[1] - cam_pos[1])*(act_pos[1] - cam_pos[1]) + (act_pos[2] - cam_pos[2])*(act_pos[2] - cam_pos[2])))
	cam_pos[2] += 1;
	else{}

	camera.SetPosition(cam_pos);
	}
	else{
	result[0] = 0;
	}*/

}



/*----------------------
perform the rendering
C.Wang 0720, 2006
-----------------------*/
void RenderIt(int skip)
{
	FnViewport vp;

	// render the whole scene
	vp.ID(vID);
	vp.Render3D(cID, TRUE, TRUE);

	// get camera's data
	FnCamera camera;
	camera.ID(cID);

	float pos[3], fDir[3], uDir[3];
	camera.GetPosition(pos);
	camera.GetDirection(fDir, uDir);

	// show frame rate
	static char string[128];
	if (frame == 0) {
		FyTimerReset(0);
	}

	if (frame / 10 * 10 == frame) {
		float curTime;

		curTime = FyTimerCheckTime(0);
		sprintf(string, "Fps: %6.2f", frame / curTime);
	}

	frame += skip;
	if (frame >= 1000) {
		frame = 0;
	}

	FnText text;
	text.ID(textID);

	text.Begin(vID);
	text.Write(string, 20, 20, 255, 0, 0);

	char posS[256], fDirS[256], uDirS[256];
	char resulttttt[256];
	sprintf(posS, "pos: %8.3f %8.3f %8.3f", pos[0], pos[1], pos[2]);
	sprintf(fDirS, "facing: %8.3f %8.3f %8.3f", fDir[0], fDir[1], fDir[2]);
	sprintf(uDirS, "up: %8.3f %8.3f %8.3f", uDir[0], uDir[1], uDir[2]);
	sprintf
		(resulttttt, " %8.3f %8.3f %8.3f %d %d %d %d %d %d", result[0], result[1], result[2], cur_angle, Robber.HP, Robber.is_attack_frame, Donzo.HP, attack_on_delay, Lyubu.is_attack);

	text.Write(posS, 20, 35, 255, 255, 0);
	text.Write(fDirS, 20, 50, 255, 255, 0);
	text.Write(uDirS, 20, 65, 255, 255, 0);
	text.Write(resulttttt, 20, 80, 255, 255, 0);

	text.End();

	// swap buffer
	FySwapBuffers();
}


/*------------------
Keyboard control by Tim
------------------*/
void Keyboardfunc(BYTE code, BOOL4 value)
{
	FnCharacter actor, act_Robber, act_DonZo;
	//test
	FnCharacter act_sor;
	float act_pos[3], act_d[3], act_f[3];
	float Robber_pos[3], Robber_f[3], Robber_d[3];
	float DonZo_pos[3], DonZo_f[3], DonZo_d[3];
	actor.ID(Lyubu.id);
	act_Robber.ID(Robber.id);
	act_sor.ID(Sorcerer.id);


	actor.GetPosition(act_pos);
	actor.GetDirection(act_f, act_d);
	//Tim get Robber Position

	act_Robber.GetPosition(Robber_pos);
	act_Robber.GetDirection(Robber_f, Robber_d);
	//Tim count the distance between Robber and actor
	float rob_act_distance = sqrt(pow(Robber_pos[0] - act_pos[0], 2) + pow(Robber_pos[1] - act_pos[1], 2));

	act_DonZo.ID(Donzo.id);
	act_DonZo.GetPosition(DonZo_pos);
	act_DonZo.GetDirection(DonZo_f, DonZo_d);
	float DonZo_act_distance = sqrt(pow(DonZo_pos[0] - act_pos[0], 2) + pow(DonZo_pos[1] - act_pos[1], 2));

	if (value && attack_on_delay == 0)
	{
		Lyubu.is_attack = 1;
		if (code == FY_A)
		{
			//test Sorcerer
			Sorcerer.curPoseID = Sorcerer.test_action;
			act_sor.SetCurrentAction(0, NULL, Sorcerer.curPoseID, 5.0f);
			act_sor.Play(START, 0.0f, FALSE, TRUE);

			Lyubu.curPoseID = Lyubu.normal_attack1ID;
			actor.SetCurrentAction(0, NULL, Lyubu.curPoseID, 5.0f);
			actor.Play(START, 0.0f, FALSE, TRUE);
			//Tim2016 
			Lyubu.SetOldFaceDir(act_f);
			//Lyubu.old_f[0] = act_f[0];
			//Lyubu.old_f[1] = act_f[1];
			//Lyubu.old_f[2] = act_f[2];
			//Lai			
			attack_on_delay = 24;

			if (DonZo_act_distance < 100 && Donzo.HP >0)
			{
				//Tim vector between actor and Robber
				float DonZo_new_f[3] = { act_pos[0] - DonZo_pos[0], act_pos[1] - DonZo_pos[1], act_pos[2] - DonZo_pos[2] };
				float act_new_f[3] = { -act_pos[0] + DonZo_pos[0], -act_pos[1] + DonZo_pos[1], -act_pos[2] + DonZo_pos[2] };

				Donzo.curPoseID = Donzo.light_damagedID;

				act_DonZo.SetDirection(DonZo_new_f, DonZo_d);
				actor.SetDirection(act_new_f, act_d);


			}
			else if (rob_act_distance < 100 && Robber.HP >0)
			{
				//Tim vector between actor and Robber
				float rob_new_f[3] = { act_pos[0] - Robber_pos[0], act_pos[1] - Robber_pos[1], act_pos[2] - Robber_pos[2] };
				float act_new_f[3] = { -act_pos[0] + Robber_pos[0], -act_pos[1] + Robber_pos[1], -act_pos[2] + Robber_pos[2] };
				Robber.curPoseID = Robber.damaged1ID;

				act_Robber.SetDirection(rob_new_f, Robber_d);
				actor.SetDirection(act_new_f, act_d);

			}
		}
		else if (code == FY_S)
		{

			Lyubu.curPoseID = Lyubu.heavy_attack1ID;
			actor.SetCurrentAction(0, NULL, Lyubu.curPoseID, 5.0f);
			actor.Play(START, 0.0f, FALSE, TRUE);
			//Tim
			Lyubu.SetOldFaceDir(act_f);
			//Lyubu.old_f[0] = act_f[0];
			//Lyubu.old_f[1] = act_f[1];
			//Lyubu.old_f[2] = act_f[2];

			//Lai
			if (attack_on_delay == 0)
				attack_on_delay = 72;

			if (DonZo_act_distance < 100 && Donzo.HP >0)
			{
				//Tim vector between actor and Robber
				float DonZo_new_f[3] = { act_pos[0] - DonZo_pos[0], act_pos[1] - DonZo_pos[1], act_pos[2] - DonZo_pos[2] };
				float act_new_f[3] = { -act_pos[0] + DonZo_pos[0], -act_pos[1] + DonZo_pos[1], -act_pos[2] + DonZo_pos[2] };
				Donzo.curPoseID = Donzo.heavy_damagedID;


				act_DonZo.SetDirection(DonZo_new_f, DonZo_d);
				actor.SetDirection(act_new_f, act_d);


			}
			else if (rob_act_distance < 100 && Robber.HP >0)
			{
				//Tim vector between actor and Robber
				float rob_new_f[3] = { act_pos[0] - Robber_pos[0], act_pos[1] - Robber_pos[1], act_pos[2] - Robber_pos[2] };
				float act_new_f[3] = { -act_pos[0] + Robber_pos[0], -act_pos[1] + Robber_pos[1], -act_pos[2] + Robber_pos[2] };
				Robber.curPoseID = Robber.damaged2ID;

				act_Robber.SetDirection(rob_new_f, Robber_d);
				actor.SetDirection(act_new_f, act_d);

			}
		}
		else if (code == FY_L)
		{
			Robber.curPoseID = Robber.dieID;
			act_Robber.SetCurrentAction(0, NULL, Robber.curPoseID, 5.0f);
			act_Robber.Play(START, 0.0f, FALSE, TRUE);
		}
	}





}

/*------------------
movement control
-------------------*/

void LyuBu_turn(){
	FnCharacter actor;
	actor.ID(Lyubu.id);
	float angle[9] = { 0, 45, 90, 135, 180, -135, -90, -45 };
	if (!Lyubu.is_attack){
		//foward
		if (!FyCheckHotKeyStatus(FY_LEFT) && FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			cur_angle = 0;
		}
		//right foward
		else if (!FyCheckHotKeyStatus(FY_LEFT) && FyCheckHotKeyStatus(FY_UP) && FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			actor.TurnRight(45.0f);
			cur_angle = 1;
		}
		//right
		else if (!FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			actor.TurnRight(90.0f);
			cur_angle = 2;
		}
		//right backward
		else if (!FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && FyCheckHotKeyStatus(FY_RIGHT) && FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			actor.TurnRight(135.0f);
			cur_angle = 3;
		}
		//down
		else if (!FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			actor.TurnRight(180.0f);
			cur_angle = 4;
		}
		//left down
		else if (FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			actor.TurnRight(-135.0f);
			cur_angle = 5;
		}
		//left
		else if (FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			actor.TurnRight(-90.0f);
			cur_angle = 6;
		}
		//left forward
		else if (FyCheckHotKeyStatus(FY_LEFT) && FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			actor.TurnRight(-45.0f);
			cur_angle = 7;
		}
		else if (!FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN)){
			actor.TurnRight(-angle[cur_angle]);
			cur_angle = 0;
		}
	}
}

void Movement(BYTE code, BOOL4 value)
{
	// Homework #01 part 2
	// ....
	FnCharacter actor;
	actor.ID(Lyubu.id);
	float angle[9] = { 0, 45, 90, 135, 180, -135, -90, -45 };

	if (Lyubu.is_attack)
		return;

	if (value)
	{
		if (code == FY_UP || code == FY_DOWN || code == FY_LEFT || code == FY_RIGHT){
			if (Lyubu.curPoseID == Lyubu.idleID)
			{
				Lyubu.curPoseID = Lyubu.runID;
				actor.SetCurrentAction(0, NULL, Lyubu.curPoseID, 5.0f);
				actor.Play(START, 0.0f, FALSE, TRUE);
			}
		}
	}
	else if (!FyCheckHotKeyStatus(FY_LEFT) && !FyCheckHotKeyStatus(FY_UP) && !FyCheckHotKeyStatus(FY_RIGHT) && !FyCheckHotKeyStatus(FY_DOWN))
	{
		actor.TurnRight(-angle[cur_angle]);
		Lyubu.curPoseID = Lyubu.idleID;
		actor.SetCurrentAction(0, NULL, Lyubu.curPoseID, 5.0f);
		actor.Play(START, 0.0f, FALSE, TRUE);
		cur_angle = 0;
	}
	LyuBu_turn();
}


/*------------------
quit the demo
C.Wang 0327, 2005
-------------------*/
void QuitGame(BYTE code, BOOL4 value)
{
	if (code == FY_ESCAPE) {
		if (value) {
			FyQuitFlyWin32();
		}
	}
}



/*-----------------------------------
initialize the pivot of the camera
C.Wang 0329, 2005
------------------------------------*/
void InitPivot(int x, int y)
{
	oldX = x;
	oldY = y;
	frame = 0;
}


/*------------------
pivot the camera
C.Wang 0329, 2005
-------------------*/
void PivotCam(int x, int y)
{
	FnObject model;

	if (x != oldX) {
		model.ID(cID);
		model.Rotate(Z_AXIS, (float)(x - oldX) / 10, GLOBAL);
		oldX = x;
	}

	if (y != oldY) {
		model.ID(cID);
		model.Rotate(X_AXIS, (float)(y - oldY) / 10, GLOBAL);
		oldY = y;
	}
}


/*----------------------------------
initialize the move of the camera
C.Wang 0329, 2005
-----------------------------------*/
void InitMove(int x, int y)
{
	oldXM = x;
	oldYM = y;
	frame = 0;
}


/*------------------
move the camera
C.Wang 0329, 2005
-------------------*/
void MoveCam(int x, int y)
{
	if (x != oldXM) {
		FnObject model;

		model.ID(cID);
		model.Translate((float)(x - oldXM)*2.0f, 0.0f, 0.0f, LOCAL);
		oldXM = x;
	}
	if (y != oldYM) {
		FnObject model;

		model.ID(cID);
		model.Translate(0.0f, (float)(oldYM - y)*2.0f, 0.0f, LOCAL);
		oldYM = y;
	}
}


/*----------------------------------
initialize the zoom of the camera
C.Wang 0329, 2005
-----------------------------------*/
void InitZoom(int x, int y)
{
	oldXMM = x;
	oldYMM = y;
	frame = 0;
}


/*------------------
zoom the camera
C.Wang 0329, 2005
-------------------*/
void ZoomCam(int x, int y)
{
	if (x != oldXMM || y != oldYMM) {
		FnObject model;

		model.ID(cID);
		model.Translate(0.0f, 0.0f, (float)(x - oldXMM)*10.0f, LOCAL);
		oldXMM = x;
		oldYMM = y;
	}
}
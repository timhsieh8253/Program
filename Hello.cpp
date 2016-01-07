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
#include "dialog.h"
#include "FyMedia.h"


float result[3];
VIEWPORTid vID;                 // the major viewport
SCENEid sID;                    // the 3D scene
OBJECTid cID, tID;              // the main camera and the terrain for terrain following
LYUBU Lyubu;
DONZO Donzo;
ROBBER Robber[128];
FOOTMAN footman;

int attack_on_delay = 0;//for attack delay
bool action_lock = 0;//

//for effect
GAMEFX_SYSTEMid gFXID = FAILED_ID;
OBJECTid dummyID = FAILED_ID; // object for display FX


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
BOOL4 beOK;

//Lai
int count_robber = 0;
char live=0;
int next_wave = 30;
int frame_clock = 300; // a clock for 300 frames
void call_Robber(float[],int);
void Robber_play(float[],int);


//dialog
MEDIAid mmID;

int event_num = 0;
int movie_lock = 0;
int frame_cal = 0;
int play_media = 0;
dialog dia;
void dialong_init();
void Space_func(BYTE, BOOL4);
void do_event(int skip);
void movie0();
void movie1(int skip);
void movie2(int skip);
int movie3(int skip);
int movie3(int skip){
	FnCamera camera;
	FnCharacter actor;
	float pos[3], fdir[3], udir[3];

	actor.ID(Lyubu.id);
	actor.GetPosition(pos);
	if (frame_cal == 1){
		Lyubu.curPoseID = Lyubu.runID;
		actor.SetCurrentAction(NULL, 0, Lyubu.curPoseID);
		actor.Play(START, 0.0f, FALSE, TRUE);
	}
	if (pos[0] > 3806.497 && pos[1] > -3456.355){
		fdir[0] = 1; fdir[1] = 1; fdir[2] = 0;
		udir[0] = 0; udir[1] = 0; udir[2] = 1;
		actor.SetDirection(fdir, udir);
		Lyubu.curPoseID = Lyubu.idleID;
		actor.SetCurrentAction(NULL, 0, Lyubu.curPoseID);
		actor.Play(START, 0.0f, FALSE, TRUE);
		return 1;
	}
	else
		actor.MoveForward(3.0f, TRUE, FALSE, 0.0f, TRUE);
	actor.Play(LOOP, (float)skip, FALSE, TRUE);

	camera.ID(cID);
	camera.GetPosition(pos);
	camera.GetDirection(fdir,udir);
	if (pos[0] <= 3095.083 && pos[1] <= -3798.389){
		pos[0] += (3095.083 - 2958.218) / 30;	pos[1] += (-3798.389 + 3934.650) / 30;
		fdir[0] -= (0.962 - 0.874) / 30; fdir[1] += (0.420 - 0.127) / 30; fdir[2] += (-0.245 + 0.242)/30;
		udir[0] +=-0.02/30 ; udir[1] += 0.074/30; udir[2] += 0;
		 
	}
	else{
		pos[0] = 3095.083; pos[1] = -3798.389; pos[2] = 200;
		fdir[0] = 0.874; fdir[1] = 0.420; fdir[2] = -0.245;
		udir[0] = 0.220; udir[1] = 0.106; udir[2] = 0.970;
	}

	camera.SetPosition(pos);
	camera.SetDirection(fdir, udir);
	return 0;
}
void movie2(int skip){
	FnCharacter actor;
	FnViewport vp;
	float pos[4],p2D[2];
	actor.ID(Lyubu.id);
	actor.GetPosition(pos);
	
	vp.ID(vID);
	vp.ComputeScreenPosition(cID, p2D, pos, PHYSICAL_SCREEN, FALSE);
	dia.special_render(p2D);
	vp.Render3D(cID, TRUE, TRUE);
	vp.RenderSprites(dia.Lyubuid, FALSE, TRUE);
	
}
void movie0(){
	//initial camera and actor pos
	FnCamera camera;
	FnCharacter actor;
	float pos[3] = { 2958.218, -3934.650, 200 };
	float fdir[3] = { 0.962, 0.127, -0.242 };
	float udir[3] = { 0.240, 0.032, 0.970 };

	float a_pos[3] = { 3691.727, -4225.118, 0.897 };
	float a_fdir[3] = { 57.385, 384.3824, 0 };
	float a_udir[3] = { 0,0,1 };

	camera.ID(cID);
	actor.ID(Lyubu.id);
	camera.SetPosition(pos);
	camera.SetDirection(fdir, udir);
	actor.SetPosition(a_pos);
	actor.SetDirection(a_fdir, a_udir);
	Lyubu.curPoseID = Lyubu.runID;
	actor.SetCurrentAction(NULL, 0, Lyubu.curPoseID);
	actor.Play(START, 0.0f, FALSE, TRUE);
}
void movie1(int skip){
	FnCharacter actor;
	float pos[3] ,fdir[3] ,udir[3];
	actor.ID(Lyubu.id);
	actor.GetPosition(pos);
	if (pos[0] > 3749.112 && pos[1] > -3840.7356){
		Lyubu.curPoseID = Lyubu.idleID;
		actor.SetCurrentAction(NULL, 0, Lyubu.curPoseID);
		actor.Play(START, 0.0f, FALSE, TRUE);
	}
	else
		actor.MoveForward(3.0f, TRUE, FALSE, 0.0f, TRUE);
	actor.Play(LOOP, (float)skip, FALSE, TRUE);
}

//for special event
void do_event(int skip){
	FnCharacter actor;
	FnCharacter foot;
	actor.ID(Lyubu.id);
	foot.ID(footman.id);

	FyBeginMedia("Data\\NTU6\\Media", 2);

	if(event_num == 1 && dia.content_now == 1){
		movie0();	
	}
	else if (event_num == 1 && dia.content_now == 2){
		frame_cal++;
		movie_lock = 1;
		movie1(skip);
		if (frame_cal > 70)
			dia.next_content();
	}
	else if (event_num == 1 && dia.content_now == 3){
		movie1(skip);
		movie_lock = 0;
		frame_cal = 0;
	}
	else if (event_num == 1 && dia.content_now == 4){
		//!!
		frame_cal++;
		movie1(skip);
		movie2(skip);
		if (frame_cal > 60){
			frame_cal = 0;
			dia.next_content();
		}
	}
	else if (event_num == 1 && dia.content_now == 5){
		//move camera and actor ,cancel render!!
		frame_cal++;
		if (movie3(skip)){
			dia.next_content();
			frame_cal = 0;
		}
	}
	else if (event_num == 1 && dia.content_now == 11){
		if (FyCheckHotKeyStatus(FY_S) && frame_cal == 0){
			Lyubu.curPoseID = Lyubu.heavy_attack2ID;
			actor.SetCurrentAction(NULL, 0, Lyubu.curPoseID);
			actor.Play(START, 0.0f, FALSE, TRUE);
			frame_cal++;
		}
		else if (frame_cal == 58){
			Lyubu.curPoseID = Lyubu.idleID;
			actor.SetCurrentAction(NULL, 0, Lyubu.curPoseID);
			actor.Play(START, 0.0f, FALSE, TRUE);
			dia.next_content();
			frame_cal = 0;

			footman.curPoseID = footman.dying_AID;
			foot.SetCurrentAction(NULL, 0, footman.curPoseID);
			actor.Play(START, 0.0f, FALSE, TRUE);
		}
		else if(frame_cal > 0){
			actor.Play(LOOP, (float)skip, FALSE, TRUE);
			frame_cal++;
		}
	}
	else if (event_num == 1 && dia.content_now == 12){
		frame_cal++;
		foot.Play(ONCE, (float)skip, FALSE, TRUE);
		if (frame_cal == 65){
			frame_cal = 0;
			movie_lock = 0;
		}
	}
	else if (event_num == 1 && dia.content_now == 16){
		if (!play_media){
			mmID = FyCreateMediaPlayer("pokemonGET.mp3", 0, 0, 800, 600);
			FnMedia mP;
			mP.Object(mmID);
			mP.Play(ONCE);
			play_media++;
		}
		movie_lock = 0;
	}
	else
		movie_lock = 0;
}

//dialog_init
void dialog_init(){
	//dialog init
	FnScene scene;
	// add a 2D scene for sprites
	dia.dialogid = FyCreateScene();
	scene.ID(dia.dialogid);
	scene.SetSpriteWorldSize(1024, 768);   // same size as the viewport

	// create a sprite as the text background
	dia.dialog_backGID = scene.CreateObject(SPRITE);
	// create the sprite text object to display the caption
	dia.contentID = scene.CreateObject(SPRITE);


	//dialog pic init
	dia.picid = FyCreateScene();
	scene.ID(dia.picid);
	scene.SetSpriteWorldSize(1024, 768);
	dia.pic_backGID = scene.CreateObject(SPRITE);

	//full init
	dia.fullid = FyCreateScene();
	scene.ID(dia.fullid);
	dia.fullcontentID = scene.CreateObject(SPRITE);
	scene.SetSpriteWorldSize(1024, 768);
	dia.full_backGID = scene.CreateObject(SPRITE);

	//Lyubu init
	dia.Lyubuid = FyCreateScene();
	scene.ID(dia.Lyubuid);
	scene.SetSpriteWorldSize(1024, 768);
	dia.Lyubu_backGID = scene.CreateObject(SPRITE);
	dia.LyubucontentID = scene.CreateObject(SPRITE);
	
	
}



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
	beOK = FyStartFlyWin32("NTU@2015 Homework #03 - Use Fly2", 0, 0, 1024, 768, FALSE);

	// setup the data searching paths
	FySetShaderPath("Data\\NTU6\\Shaders");
	FySetModelPath("Data\\NTU6\\Scenes");
	FySetTexturePath("Data\\NTU6\\Scenes\\Textures");
	FySetScenePath("Data\\NTU6\\Scenes");
	FySetGameFXPath("Data\\NTU6\\FX");


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
	float init_pos[3] = { 3790.0f, -3158.0f, 1000.0f };
	Donzo.Initiate(sID, terrainRoomID, beOK,init_pos);
	footman.Initiate(sID, terrainRoomID, beOK);


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
	
	//dialog part
	dialog_init();
	event_num = 1;
	dia.start_dialog(event_num);
	FyDefineHotKey(FY_SPACE, Space_func, FALSE);  // escape for quiting the game
	
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
	if (event_num){
		do_event(skip);
		return;
	}
	else
		FySetTexturePath("Data\\NTU6\\Characters");	
	//Lai
	if (frame_clock < 1) frame_clock = 300;
	else frame_clock--;


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

	//Lai
	if (next_wave > 0)
	{
		if (next_wave != 0) next_wave--;
		if (next_wave == 0)
		{
			count_robber = 0;
			call_Robber(act_pos, 10);
		}
	}
	//Lai
	Robber_play(act_pos, skip);


	
	//lo play DonZo
	Donzo.play(attack_on_delay,skip);

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
	

	Donzo.isattack(0);


	if (attack_on_delay > 0)
		attack_on_delay--;
	else
	{   
		if (Lyubu.is_attack==1)
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
	// play game FX

	if (gFXID != FAILED_ID) {
		FnGameFXSystem gxS(gFXID);
		BOOL4 beOK = gxS.Play((float)skip, ONCE);
		if (!beOK) {
			FnScene scene(sID);
			scene.DeleteGameFXSystem(gFXID);
			gFXID = FAILED_ID;
		}
	}
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
	dia.render_dialog(vp,0);
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
	//
	sprintf(posS, "pos: %d %d %d", Robber[0].GetAttackClock(), Robber[0].GetLeaveWithL(), Robber[0].GetAttackClock());
	sprintf(fDirS, "facing: %8.3f %8.3f %8.3f", fDir[0], fDir[1], fDir[2]);

	sprintf(uDirS, "up: %8.3f %8.3f %8.3f", uDir[0], uDir[1], uDir[2]);

	sprintf
		(resulttttt, " %8.3f %8.3f %8.3f %d %d %d %d %d %d", result[0], result[1], result[2], cur_angle, Donzo.HP, Robber[0].HP, live, next_wave, Robber[0].GetCleanClock());

	text.Write(posS, 20, 35, 255, 255, 0);
	text.Write(fDirS, 20, 50, 255, 255, 0);

	text.Write(uDirS, 20, 65, 255, 255, 0);

	text.Write(resulttttt, 20, 80, 255, 255, 0);
	
	text.End();

	// swap buffer
	FySwapBuffers();
}
void Space_func(BYTE code, BOOL4 value){
	if (value && event_num && !movie_lock){
		if (!dia.next_content())
			event_num = 0;
		else{
			movie_lock = 1;
			play_media = 0;
		}
	}

}

/*------------------
Keyboard control by Tim
------------------*/
void Keyboardfunc(BYTE code, BOOL4 value)
{
	FnCharacter actor, act_Robber, act_DonZo;
	float act_pos[3], act_d[3], act_f[3];
	float Robber_pos[3], Robber_f[3], Robber_d[3];
	float DonZo_pos[3], DonZo_f[3], DonZo_d[3];
	actor.ID(Lyubu.id);
	act_Robber.ID(Robber[0].id);


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
			

			Lyubu.curPoseID = Lyubu.normal_attack2ID;
			actor.SetCurrentAction(0, NULL, Lyubu.curPoseID, 5.0f);
			actor.Play(START, 0.0f, FALSE, TRUE);
			Lyubu.GetOldFaceDir()[0] = act_f[0];
			Lyubu.GetOldFaceDir()[1] = act_f[1];
			Lyubu.GetOldFaceDir()[2] = act_f[2];
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
			else //if (rob_act_distance < 100 && Robber[0].HP >0) //Lai
			{
				//select the less HP one
				int tar;
				bool tar_flag = FALSE;
				for (int i = 0; i < count_robber && !tar_flag; i++)
				{
					if (Robber[i].GetDisWithL() <= 130 && Robber[i].HP > 0) 
					{
						tar = i;  tar_flag = TRUE;
					}
				}
				if (tar_flag) // if anyone can be attacked
				{
					for (int i = 0; i < count_robber; i++)
					{
						if (Robber[i].GetDisWithL()>130 || Robber[i].HP == 0) continue;
						if (Robber[i].HP < Robber[tar].HP) tar = i;
					}
				
					//Tim vector between actor and Robber
					float rob_new_f[3] = { act_pos[0] - Robber[tar].pos[0], act_pos[1] - Robber[tar].pos[1], act_pos[2] - Robber[tar].pos[2] };
					float act_new_f[3] = { -act_pos[0] + Robber[tar].pos[0], -act_pos[1] + Robber[tar].pos[1], -act_pos[2] + Robber[tar].pos[2] };
					Robber[tar].curPoseID = Robber[tar].damaged1ID;
					Robber[tar].attacked_target = TRUE;//Lai 0105
					act_Robber.SetDirection(rob_new_f, Robber_d);
					actor.SetDirection(act_new_f, act_d);

				}
			}
		}
		else if (code == FY_S)
		{
			Lyubu.curPoseID = Lyubu.heavy_attack2ID;
			actor.SetCurrentAction(0, NULL, Lyubu.curPoseID, 5.0f);
			actor.Play(START, 0.0f, FALSE, TRUE);
			Lyubu.GetOldFaceDir()[0] = act_f[0];
			Lyubu.GetOldFaceDir()[1] = act_f[1];
			Lyubu.GetOldFaceDir()[2] = act_f[2];

			//Lai
			if (attack_on_delay == 0)
				attack_on_delay = 58;

			if (DonZo_act_distance < 100 && Donzo.HP >0)
			{
				//Tim vector between actor and Robber
				float DonZo_new_f[3] = { act_pos[0] - DonZo_pos[0], act_pos[1] - DonZo_pos[1], act_pos[2] - DonZo_pos[2] };
				float act_new_f[3] = { -act_pos[0] + DonZo_pos[0], -act_pos[1] + DonZo_pos[1], -act_pos[2] + DonZo_pos[2] };
				Donzo.curPoseID = Donzo.heavy_damagedID;

	
				act_DonZo.SetDirection(DonZo_new_f, DonZo_d);
				actor.SetDirection(act_new_f, act_d);


			}
			else //if(rob_act_distance < 120 && Robber[0].HP >0)
			{
				int tar = 0;
				for (int i = 0; i < count_robber; i++)
				{
					if (Robber[i].GetDisWithL()>200 || Robber[i].HP==0) continue;
					if (Robber[i].HP < Robber[tar].HP) tar = i;
					Robber[i].attacked_target = TRUE;//Lai 0105
					Robber[i].curPoseID = Robber[i].damaged2ID;
					
				}
				if (Robber[tar].HP>0)
				{
					//Tim vector between actor and Robber
					float rob_new_f[3] = { act_pos[0] - Robber[tar].pos[0], act_pos[1] - Robber[tar].pos[1], act_pos[2] - Robber[tar].pos[2] };
					float act_new_f[3] = { -act_pos[0] + Robber[tar].pos[0], -act_pos[1] + Robber[tar].pos[1], -act_pos[2] + Robber[tar].pos[2] };

					act_Robber.SetDirection(rob_new_f, Robber_d);
					actor.SetDirection(act_new_f, act_d);
				}
			}
		}
		else if (code == FY_L)
		{
			if (attack_on_delay == 0)
				attack_on_delay = 30;
			for (int i = 0; i < count_robber; i++)
			{
				if (Robber[i].HP>0) Robber[i].HP = 1;
				Robber[i].attacked_target = TRUE;//Lai 0105
				Robber[i].curPoseID = Robber[i].damaged2ID;
			}

			/*
			Robber[0].curPoseID = Robber[0].dieID;
			act_Robber.SetCurrentAction(0, NULL, Robber[0].curPoseID, 5.0f);
			act_Robber.Play(START, 0.0f, FALSE, TRUE);
			*/
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

//Lai
void call_Robber(float loc_pos[], int num)
{
	float Robber_pos[3];
	count_robber=num ;
	
	for (int i = 0; i < num; i++)
	{
		Robber_pos[0] = loc_pos[0] + (rand() % 400)*1.0f-200.0f;
		Robber_pos[1] = loc_pos[1] + (rand() % 400)*1.0f-200.0f;
		Robber_pos[2] = loc_pos[2];
		Robber[i].Initiate(sID, terrainRoomID, beOK, Robber_pos);
		
	}
	
}

//Lai
void Robber_play(float act_pos[],int skip)
{
	
	int num = count_robber;
	bool anyone_live=FALSE;
	float new_f[3], new_d[3] = { 0, 0, 1 };
	int dis[3] = {300,85,60}; // too far/ mid/ too close
	live = 0;
	for (int i = 0; i < num; i++)
		//lo play Robber pose
	{	

		if (Robber[i].attacked_target && attack_on_delay>0)
			Robber[i].isattack(attack_on_delay);
		Robber[i].play(attack_on_delay, skip);

		if (Robber[i].HP < 1) { Robber[i].actor_clean(beOK); 
		continue; }
		else anyone_live = TRUE;
		live++;
		int run_flag = 1;
		Robber[i].SetDisWithL(Robber[i].dis(act_pos));

		if (!Robber[i].attacked_target || Robber[i].GetLeaveWithL() < 0)
		{
			//for run
			if (Robber[i].GetLeaveWithL() >= 0)
			{
				if (Robber[i].GetStopFlag() != 0 && frame_clock % 10 == 0)
				{
					int sf = Robber[i].GetStopFlag();
					Robber[i].SetStopFlag(--sf);
				}

				if (Robber[i].GetDisWithL() >= dis[0])
				{
					Robber[i].SetLeaveWithL(2);
					new_f[0] = -(Robber[i].pos[0] - act_pos[0]);
					new_f[1] = -(Robber[i].pos[1] - act_pos[1]);
					new_f[2] = Robber[i].pos[2] - act_pos[2];

					Robber[i].actor.SetDirection(new_f, new_d);
					Robber[i].SetPosition(30);
				}
				else if (dis[0] > Robber[i].GetDisWithL() && Robber[i].GetDisWithL() > dis[1])
				{
					for (int j = 0; j < num && run_flag == 1 && Robber[i].GetStopFlag() == 0; j++)
					{
						if (j == i || (Robber[j].HP < 1)) continue;

						float dis_i_j = Robber[i].dis(Robber[j].pos);

						if (dis_i_j <= 30) // too close, stop
						{
							if (Robber[j].dis(act_pos) < Robber[i].GetDisWithL())
							{

								new_f[0] = (Robber[i].pos[0] - act_pos[0]);
								new_f[1] = -(Robber[i].pos[1] - act_pos[1]);
								new_f[2] = Robber[i].pos[2] - Robber[j].pos[2];
								if (pow(new_f[0], 2)>pow(new_f[1], 2))
								{
									if (new_f[0] * new_f[1] > 0) new_f[1] = new_f[1] * 100;
									else					   new_f[1] = new_f[1] * -100;
									new_f[1] = new_f[1] * Robber[i].GetFindWay();
								}
								else  {
									if (new_f[0] * new_f[1] > 0) new_f[0] = new_f[0] * 100;
									else					   new_f[0] = new_f[0] * -100;
									new_f[0] = new_f[0] * Robber[i].GetFindWay();
								}// control the dir... always right/left setted by Robber[i].find_way;

								Robber[i].actor.SetDirection(new_f, new_d);

								if (Robber[j].dis(act_pos) > dis[1] * 1.1)
									Robber[j].SetPosition(30 - dis_i_j);
								else
									Robber[i].SetPosition(-5);

								Robber[i].SetStopFlag(rand() % 5 + 1);
								run_flag = 0; //identify a robber j a time
								Robber[i].SetLeaveWithL(0);
							}
						}

					}//for (int j = 0; j < num; j++ ...

					if (Robber[i].GetStopFlag() == 0 || dis[1] > Robber[i].dis(act_pos)) // Robber[i].stop_flag>0 : someone between Robber[i] and lyubu
					{

						new_f[0] = -(Robber[i].pos[0] - act_pos[0]);
						new_f[1] = -(Robber[i].pos[1] - act_pos[1]);
						new_f[2] = Robber[i].pos[2] - act_pos[2];

						Robber[i].actor.SetDirection(new_f, new_d);
					}
					if (run_flag == 1 && Robber[i].GetDisWithL() > dis[1])
						Robber[i].SetLeaveWithL(1);

					Robber[i].SetPosition(run_flag*(rand() % 10) / (Robber[i].GetStopFlag() + 1));//real speed=run_flag*0~10*1.0

				}//else if (500>Robber[i].dis(act_pos) && Robber[i].di....

				else if (dis[1] >= Robber[i].GetDisWithL()  && Robber[i].GetDisWithL() > dis[2])
				{
					Robber[i].SetLeaveWithL(0);
					if (Robber[i].GetStopFlag() != 0)
						Robber[i].SetStopFlag (rand() % 10);

					new_f[0] = -(Robber[i].pos[0] - act_pos[0]);
					new_f[1] = -(Robber[i].pos[1] - act_pos[1]);
					new_f[2] = Robber[i].pos[2] - act_pos[2];
					Robber[i].actor.SetDirection(new_f, new_d);
					Robber[i].SetPosition(0);
				}


			}// for run Robber[i].leave_with_L >= 0;

			if (dis[2] > Robber[i].GetDisWithL()) // too close
			{
				//Robber[i].leave_with_L = 0;
				new_f[0] = -(Robber[i].pos[0] - act_pos[0]);
				new_f[1] = -(Robber[i].pos[1] - act_pos[1]);
				new_f[2] = Robber[i].pos[2] - act_pos[2];
				Robber[i].actor.SetDirection(new_f, new_d);

				Robber[i].SetPosition(run_flag*-1.0*(rand() % 10));
			}



			// attack
			if ((frame_clock % 2 == 0 && !Robber[i].action_lock) || Robber[i].GetLeaveWithL() < 0)
			if ((dis[1] >= Robber[i].GetDisWithL() && rand() % 10 < 1) || Robber[i].GetLeaveWithL() < 0)
			{

				Robber[i].attackplayer(rand() % 3);


			}

		}//		if (!Robber[i].attacked_target || Robber[i].leave_with_L < 0)

	} //for int i

	if (!anyone_live && next_wave==0) // all die
	{		
		next_wave = 150;
	}
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
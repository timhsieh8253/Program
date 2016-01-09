#include "LYUBU.h"
#include "FlyWin32.h"


LYUBU::LYUBU()
{
	//
}


LYUBU::~LYUBU()
{
}

void LYUBU::Initiate(SCENEid sID, ROOMid terrainRoomID, BOOL4 &beOK)
{
	//store scene ID for FX
	sid = sID;
	
	FnScene scene;
	scene.ID(sID);
	id = scene.LoadCharacter("Lyubu2");
	//blood
	bloodBarObj = scene.CreateObject(MODEL);     // blood bar object id
	FnObject model(bloodBarObj);
	float size[2], color[3];
	size[0] = 200.0f;
	size[1] = 10.0f;
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	bloodBar= model.Billboard(NULL, size, NULL, 0, color);    // the billboard
	

	// put the character on terrain
	float fDir[3], uDir[3];
	FnCharacter actor;
	actor.ID(id);
	//pos[0] = 3569.0f; pos[1] = -3208.0f; pos[2] = 1000.0f;
	//pos[0] = 4013.461f; pos[1] = -3938.850f; pos[2] = 1000.0f;
	pos[0] = 3691.727f; pos[1] = -4225.118f; pos[2] = 1000.0f;
	fDir[0] = 1.0f; fDir[1] = 1.0f; fDir[2] = 0.0f;
	uDir[0] = 0.0f; uDir[1] = 0.0f; uDir[2] = 1.0f;
	actor.SetDirection(fDir, uDir);

	actor.SetTerrainRoom(terrainRoomID, 10.0f);
	beOK = actor.PutOnTerrain(pos);

	// blood init
	Lyubu_blood = FyCreateScene();
	scene.ID(Lyubu_blood);
	scene.SetSpriteWorldSize(1024, 768);
	Lyubu_backGID = scene.CreateObject(SPRITE);
	FnSprite sp;
	sp.ID(Lyubu_backGID);
	sp.SetSize(500, 20);
	sp.SetPosition(150, 690, 0);
	float rgb[4];
	rgb[0] = 1.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = 1.0f;
	sp.SetColor(rgb);
	blood_size = 500;
	//head init
	Lyubu_head = FyCreateScene();
	scene.ID(Lyubu_head);
	scene.SetSpriteWorldSize(1024, 768);
	headID = scene.CreateObject(SPRITE);
	sp.ID(headID);
	//FySetTexturePath("Data\\NTU6");
	sp.SetImage("Lyu3", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
	sp.SetSize(100, 100);
	sp.SetPosition(30, 650, 0);
	//blood
	// get the base object of Lyubu
	//OBJECTid baseID = scene.CreateObject(SPRITE);
	// make the blood bar's parent is the base and raise up the blood bar higher than the head of lyubu
	//model.SetParent(baseID);
	//model.SetPosition(0,0,0);

	// Get two character actions pre-defined at Lyubu2
	idleID = actor.GetBodyAction(NULL, "Idle");
	runID = actor.GetBodyAction(NULL, "Run");
	dieID = actor.GetBodyAction(NULL, "Die");
	guardID = actor.GetBodyAction(NULL, "guard");
	fightidleID = actor.GetBodyAction(NULL, "FightIdle");

	//attack
	normal_attack1ID = actor.GetBodyAction(NULL, "NormalAttack1");
	normal_attack2ID = actor.GetBodyAction(NULL, "NormalAttack2");
	normal_attack3ID = actor.GetBodyAction(NULL, "NormalAttack3");
	normal_attack4ID = actor.GetBodyAction(NULL, "NormalAttack4");
	heavy_attack1ID = actor.GetBodyAction(NULL, "HeavyAttack1");
	heavy_attack2ID = actor.GetBodyAction(NULL, "HeavyAttack2");
	heavy_attack3ID = actor.GetBodyAction(NULL, "HeavyAttack3");
	ultimate_attackID = actor.GetBodyAction(NULL, "UltimateAttack");
	//damage
	heavy_damagedID = actor.GetBodyAction(NULL, "HeavyDamaged");
	right_damagedID = actor.GetBodyAction(NULL, "RightDamaged");
	left_damagedID = actor.GetBodyAction(NULL, "LeftDamaged");

	// set the character to idle action
	curPoseID = idleID;
	actor.SetCurrentAction(NULL, 0, curPoseID);
	actor.Play(START, 0.0f, FALSE, TRUE);

	//set HP
	HP = 10000;
	maxHP = 10000;
	is_attack = 0;
	old_f[0] = 0; old_f[1] = 0; old_f[2] = 0;
}


void LYUBU::play(int attack_on_delay, int skip){
	FnCharacter actor;
	actor.ID(id);
	// tai FX
	/*if (is_attack_frame == 20)
	{
		FySetGameFXPath("Data\\NTU6\\FX");
		FnScene scene(sid);

		// remove the old one if necessary
		if (gFXID != NULL) {
			scene.DeleteGameFXSystem(gFXID);
		}

		// create a new game FX system
		gFXID = scene.CreateGameFXSystem();

		// case 1 : we create/move a dummy object on the hit position
		FnGameFXSystem gxS(gFXID);

		if (dummyID == FAILED_ID) {
			dummyID = scene.CreateObject(MODEL);
		}

		FnObject dummy(dummyID);
		float FX_pos[3] = { pos[0], pos[1], 100.0f };
		dummy.SetPosition(FX_pos);

		// play the FX on it
		BOOL4 beOK = gxS.Load("HurtDir", TRUE);
		if (beOK) {
			gxS.SetParentObjectForAll(dummyID);
		}
	}
*/

	if (((curPoseID != runID && curPoseID != idleID  && curPoseID != dieID) || action_lock) )
	{
		if ( is_attack_frame != 0) 	 is_attack_frame --;

		if (!action_lock)
		{
			action_lock = TRUE;
			actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
			actor.Play(ONCE, (float)skip, FALSE, TRUE);//0105
		}
		else if (action_lock)
			actor.Play(ONCE, (float)skip, FALSE, TRUE);

		if (HP>0 && attack_on_delay == 0 && is_attack_frame==0)
		{
			curPoseID = runID;
			actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
			actor.Play(START, (float)skip, FALSE, TRUE);
			action_lock = FALSE;
		}
	}

	else if (curPoseID != dieID)
	{
		actor.Play(LOOP, (float)skip, FALSE, TRUE);
	}
	else
		actor.Play(ONCE, (float)skip, FALSE, TRUE);
}

float* LYUBU::GetPosition()
{
	return pos;
}
float* LYUBU::GetOldFaceDir()
{
	return old_f;
}
void LYUBU::SetOldFaceDir(float* f)
{
	old_f[0] = f[0];
	old_f[1] = f[1];
	old_f[2] = f[2];
}
void LYUBU::SetPosition(float* p)
{
	pos[0] = p[0];
	pos[1] = p[1];
	pos[2] = p[2];
}
void LYUBU::SetBlood(int curHP)
{ 
	FnSprite sp;
	sp.ID(Lyubu_backGID);
	sp.SetSize(((float)curHP / (float)maxHP)*(float)blood_size, 20);
	sp.SetPosition(150, 690, 0);
	float rgb[4];
	rgb[0] = 1.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = 1.0f;
	sp.SetColor(rgb);
	
}

void LYUBU::SetFX()
{
	FnScene scene;
	scene.ID(sid);
	// remove the old one if necessary
	FySetGameFXPath("Data\\NTU6\\FX");

	if (gFXID != NULL) {
		scene.DeleteGameFXSystem(gFXID);
	}

	// create a new game FX system
	gFXID = scene.CreateGameFXSystem();

	// case 1 : we create/move a dummy object on the hit position
	FnGameFXSystem gxS(gFXID);

	if (dummyID == FAILED_ID) {
		dummyID = scene.CreateObject(MODEL);
	}

	FnObject dummy(dummyID);
	float FX_pos[3] = { pos[0], pos[1], pos[2] };
	dummy.SetPosition(FX_pos);

	// play the FX on it
	BOOL4 beOK = gxS.Load("11", TRUE);
	if (beOK) {
		gxS.SetParentObjectForAll(dummyID);
	}


}
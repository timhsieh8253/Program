#include "DONZO.h"
#include "FlyWin32.h"

DONZO::DONZO()
{
}


DONZO::~DONZO()
{
}
void DONZO::Initiate(SCENEid sID, ROOMid terrainRoomID, BOOL4 &beOK){
	FnScene scene;
	scene.ID(sID);
	//Robber
	id = scene.LoadCharacter("Donzo2");
	//blood
	bloodBarObj = scene.CreateObject(MODEL);     // blood bar object id
	FnObject model(bloodBarObj);
	float size[2], color[3];
	size[0] = 20.0f;
	size[1] = 2.0f;
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	bloodBar = model.Billboard(NULL, size, NULL, 0, color);    // the billboard

	//lo put the Robber on terrain
	float fDir[3], uDir[3];
	FnCharacter actor;
	actor.ID(id);
	pos[0] = 3790.0f; pos[1] = -3158.0f; pos[2] = 1000.0f;
	fDir[0] = -1.0f; fDir[1] = -1.0f; fDir[2] = 0.0f;
	uDir[0] = 0.0f; uDir[1] = 0.0f;uDir[2] = 1.0f;
	actor.SetDirection(fDir, uDir);

	actor.SetTerrainRoom(terrainRoomID, 10.0f);
	beOK = actor.PutOnTerrain(pos);
	//blood
	// get the base object of Lyubu
	OBJECTid baseID = actor.GetBaseObject();
	// make the blood bar's parent is the base and raise up the blood bar higher than the head of lyubu
	model.SetParent(baseID);
	model.Translate(0.0f, 0.0f,100.0f, REPLACE);

	//lo DonZo PART
	idleID = actor.GetBodyAction(NULL, "Idle");
	runID = actor.GetBodyAction(NULL, "Run");

	light_attack1ID = actor.GetBodyAction(NULL, "AttackL1");
	light_attack2ID = actor.GetBodyAction(NULL, "AttackL2");
	heavy_attack1ID = actor.GetBodyAction(NULL, "AttackH");
	heavy_attack2ID = actor.GetBodyAction(NULL, "HeavyAttack");
	defenceID = actor.GetBodyAction(NULL, "Defence");
	light_damagedID = actor.GetBodyAction(NULL, "DamageL");
	heavy_damagedID = actor.GetBodyAction(NULL, "DamageH");
	dieID = actor.GetBodyAction(NULL, "Die");
	curPoseID = idleID;
	actor.SetCurrentAction(NULL, 0,curPoseID);
	actor.Play(START, 0.0f, FALSE, TRUE);
	HP = 288;
	maxHP = 288;
	is_attack_frame = 0;
	state = 0;
}
void DONZO::isattack(int index){
	
	FnCharacter actor;
	actor.ID(id);

	if (curPoseID != heavy_damagedID && curPoseID != light_damagedID){
		if (is_attack_frame > 0)
			is_attack_frame -= 2;
		return;
	}
	if (is_attack_frame == 0 && curPoseID == light_damagedID){
		is_attack_frame = 2;
	}
	else if (is_attack_frame == 0 && curPoseID == heavy_damagedID){
		is_attack_frame = 3;
	}
	if (is_attack_frame > 0){
		is_attack_frame--;
		if (curPoseID == light_damagedID)
		{
			HP -= 1;
			SetBlood(HP);
		}
		else if (curPoseID == heavy_damagedID)
		{
			HP -= 2;
			SetBlood(HP);
		}
	}


	if (curPoseID != dieID && HP <= 0){
		curPoseID = dieID;
		actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
		actor.Play(START, 0.0f, FALSE, TRUE);
	}
}
void DONZO::play(int attack_on_delay, int skip, bool action_lock){
	FnCharacter actor;
	actor.ID(id);

	//Lai
	if (curPoseID != idleID && attack_on_delay < 40 && curPoseID != dieID)
	{

		if (!action_lock)
		{
			action_lock = TRUE;
			actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
		}

		actor.Play(ONCE, (float)skip, FALSE, TRUE);

		if (HP>0 && attack_on_delay == 0)
		{
			curPoseID = idleID;
			actor.SetCurrentAction(0, NULL,curPoseID, 5.0f);
			action_lock = FALSE;
		}
	}

	else if (curPoseID !=dieID)
	{
		actor.Play(LOOP, (float)skip, FALSE, TRUE);
	}
	else
		actor.Play(ONCE, (float)skip, FALSE, TRUE);
}
float* DONZO::GetPosition()
{
	return pos;
}
float* DONZO::GetOldFaceDir()
{
	return old_f;
}
void DONZO::SetOldFaceDir(float* f)
{
	old_f[0] = f[0];
	old_f[1] = f[1];
	old_f[2] = f[2];
}
void DONZO::SetPosition(float* p)
{
	pos[0] = p[0];
	pos[1] = p[1];
	pos[2] = p[2];
}
int DONZO::GetState()
{
	return state;
}
void DONZO::SetState(int s)
{
	state = s;
}
void DONZO::SetBlood(int curHP)
{
	float size[2];
	size[0] = 20.0f*curHP / maxHP;
	size[1] = 2.0f;

	FnBillboard bb(bloodBar);
	bb.SetPositionSize(NULL, size);
}
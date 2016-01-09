#include "SORCERER.h"
#include "FlyWin32.h"

SORCERER::SORCERER()
{
}


SORCERER::~SORCERER()
{
}
void SORCERER::Initiate(SCENEid sID, ROOMid terrainRoomID, BOOL4 &beOK){
	FnScene scene;
	scene.ID(sID);
	//Robber
	id = scene.LoadCharacter("Sorcerer01");
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
	pos[0] = 2497; pos[1] = -2083; pos[2] = 1000.0f;
	fDir[0] = -1.0f; fDir[1] = -1.0f; fDir[2] = 0.0f;
	uDir[0] = 0.0f; uDir[1] = 0.0f; uDir[2] = 1.0f;
	actor.SetDirection(fDir, uDir);

	actor.SetTerrainRoom(terrainRoomID, 10.0f);
	actor.TurnRight(-40.0f);
	beOK = actor.PutOnTerrain(pos);
	//blood
	// get the base object 
	OBJECTid baseID = actor.GetBaseObject();
	// make the blood bar's parent is the base and raise up the blood bar higher than the head of lyubu
	model.SetParent(baseID);
	model.Translate(0.0f, 0.0f, 230.0f, REPLACE);


	idleID = actor.GetBodyAction(NULL, "Idle");
	runID = actor.GetBodyAction(NULL, "Run");
	test_action = actor.GetBodyPoseNumber("Jump_runing");
		
	
	curPoseID = idleID;
	actor.SetCurrentAction(NULL, 0, curPoseID);
	actor.Play(START, 0.0f, FALSE, TRUE);
	HP = 144;
	maxHP = 144;
	is_attack_frame = 0;
	state = 0;
}

void SORCERER::play(int attack_on_delay, int skip, bool action_lock){
	FnCharacter actor;
	actor.ID(id);

	//Lai
	/*
	if (curPoseID != combatidleID && attack_on_delay < 50 && curPoseID != dieID)
	{

	if (!action_lock)
	{
	action_lock = TRUE;
	actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
	}

	actor.Play(ONCE, (float)skip, FALSE, TRUE);

	if (HP>0 && attack_on_delay == 0)
	{
	curPoseID = combatidleID;
	actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
	action_lock = FALSE;
	}
	}

	else if (curPoseID != dieID)
	{
	actor.Play(LOOP, (float)skip, FALSE, TRUE);
	}
	else*/
	actor.Play(LOOP, (float)skip, FALSE, TRUE);
}
float* SORCERER::GetPosition()
{
	return pos;
}
float* SORCERER::GetOldFaceDir()
{
	return old_f;
}
void SORCERER::SetOldFaceDir(float* f)
{
	old_f[0] = f[0];
	old_f[1] = f[1];
	old_f[2] = f[2];
}
void SORCERER::SetPosition(float* p)
{
	pos[0] = p[0];
	pos[1] = p[1];
	pos[2] = p[2];
}
int SORCERER::GetState()
{
	return state;
}
void SORCERER::SetState(int s)
{
	state = s;
}
void SORCERER::SetBlood(int curHP)
{
	float size[2];
	size[0] = 20.0f*curHP / maxHP;
	size[1] = 2.0f;

	FnBillboard bb(bloodBar);
	bb.SetPositionSize(NULL, size);
}
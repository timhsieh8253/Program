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
	FnScene scene;
	scene.ID(sID);
	id = scene.LoadCharacter("Lyubu2");
	//blood
	bloodBarObj = scene.CreateObject(MODEL);     // blood bar object id
	FnObject model(bloodBarObj);
	float size[2], color[3];
	size[0] = 20.0f;
	size[1] = 2.0f;
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	bloodBar= model.Billboard(NULL, size, NULL, 0, color);    // the billboard
	

	// put the character on terrain
	float fDir[3], uDir[3];
	FnCharacter actor;
	actor.ID(id);
	pos[0] = 3569.0f; pos[1] = -3208.0f; pos[2] = 1000.0f;
	fDir[0] = 1.0f; fDir[1] = 1.0f; fDir[2] = 0.0f;
	uDir[0] = 0.0f; uDir[1] = 0.0f; uDir[2] = 1.0f;
	actor.SetDirection(fDir, uDir);

	actor.SetTerrainRoom(terrainRoomID, 10.0f);
	beOK = actor.PutOnTerrain(pos);

	//blood
	// get the base object of Lyubu
	OBJECTid baseID = actor.GetBaseObject();
	// make the blood bar's parent is the base and raise up the blood bar higher than the head of lyubu
	model.SetParent(baseID);
	model.Translate(0.0f, 0.0f, 90.0f, REPLACE);

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
	float size[2];
	size[0] = 20.0f*curHP / maxHP;
	size[1] = 2.0f;

	FnBillboard bb(bloodBar);
	bb.SetPositionSize(NULL, size);
}

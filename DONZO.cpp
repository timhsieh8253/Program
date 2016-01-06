#include "DONZO.h"
#include "FlyWin32.h"

DONZO::DONZO()
{
}


DONZO::~DONZO()
{
}
void DONZO::Initiate(SCENEid sID, ROOMid terrainRoomID, BOOL4 &beOK, float init_pos[]){
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
	actor.ID(id);
	pos[0] = init_pos[0]; pos[1] = init_pos[1]; pos[2] = init_pos[2];
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

	stop_flag = 0;
	leave_with_L = 2;//2:>500 1:500~100 0: <100
	attack_clock = 0;
	action_lock = FALSE;
	attacked_target = FALSE;

	find_way = rand() % 2;
	if (find_way == 0) find_way = -1;
}
void DONZO::isattack(int index){
	
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
void DONZO::attackplayer(int atk_lv)
{
	if (attack_clock == 0)
	{

		leave_with_L = -1;

		if (atk_lv == 0)
		{
			attack_clock = 34;
			curPoseID = light_attack1ID;
		}
		else if (atk_lv == 1)
		{
			attack_clock = 24;
			curPoseID = light_attack2ID;
		}
		else if (atk_lv == 2)
		{
			attack_clock = 29;
			curPoseID = heavy_attack1ID;
			actor.MoveForward(2.0f, TRUE, FALSE, 0.0f, TRUE);

		}
	}
	else if (attack_clock > 0)
	{
		attack_clock--;
		if (attack_clock == 0)
		{

			leave_with_L = 0;
		}
	}

}
void DONZO::play(int attack_on_delay, int skip){
	if (((curPoseID != runID && curPoseID != idleID  && curPoseID != dieID) || action_lock) && attack_on_delay < 50)
	{

		if (!action_lock)
		{
			action_lock = TRUE;
			actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
			actor.Play(ONCE, (float)skip, FALSE, TRUE);//0105
		}
		if (action_lock)
			actor.Play(ONCE, (float)skip, FALSE, TRUE);

		if (HP>0 && attack_on_delay == 0 && attack_clock == 0)
		{
			if (leave_with_L > 0)
				curPoseID = runID;
			else
				curPoseID = idleID;

			actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
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
void DONZO::SetPosition(float fwd)
{
	actor.MoveForward(fwd*1.0f, TRUE, FALSE, 0.0f, TRUE);

	if (leave_with_L > 0 && curPoseID != runID)
	{
		curPoseID = runID;
		actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
		actor.Play(START, 0.0f, FALSE, TRUE);
	}
	else if (leave_with_L == 0 && curPoseID != idleID)
	{
		curPoseID = idleID;
		actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
		actor.Play(START, 0.0f, FALSE, TRUE);
	}
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
int DONZO::GetAttackClock()
{
	return attack_clock;
}
void DONZO::SetAttackClock(int ac)
{
	attack_clock = ac;
}
int DONZO::GetDamagedType()
{
	return damaged_type;
}
void  DONZO::SetDamagedType(int dt)
{
	damaged_type = dt;
}
int DONZO::GetStopFlag()
{
	return stop_flag;
}
void  DONZO::SetStopFlag(int sf)
{
	stop_flag = sf;
}
int  DONZO::GetLeaveWithL()
{
	return leave_with_L;
}
void  DONZO::SetLeaveWithL(int lw)
{
	leave_with_L = lw;
}
int  DONZO::GetFindWay()
{
	return find_way;
}
void  DONZO::SetFindWay(int fw)
{
	find_way = fw;
}
int  DONZO::GetCleanClock()
{
	return clean_clock;
}
void  DONZO::SetCleanClock(int cc)
{
	clean_clock = cc;
}
float  DONZO::GetDisWithL()
{
	return diswithL;
}
void DONZO::SetDisWithL(float dw)
{
	diswithL = dw;
}
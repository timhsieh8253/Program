#include "ROBBER.h"
#include "FlyWin32.h"

ROBBER::ROBBER()
{	//Lai
	stop_flag = 0;
	leave_with_L = 2;//2:>500 1:500~100 0: <100
	attack_clock = 0;
	action_lock = FALSE;
	attacked_target = FALSE;

	find_way = rand() % 2; 
	if (find_way == 0) find_way = -1;

}


ROBBER::~ROBBER()
{
}
void ROBBER::Initiate(SCENEid sID, ROOMid terrainRoomID, BOOL4 &beOK, float init_pos[]){
	FnScene scene;
	scene.ID(sID);
	//Robber
	id = scene.LoadCharacter("Robber02");
	//lo put the Robber on terrain
	float  fDir[3], uDir[3];
	
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
	//blood

	actor.ID(id);
	pos[0] = init_pos[0]; pos[1] = init_pos[1]; pos[2] = init_pos[2];
	fDir[0] = -1.0f; fDir[1] = -1.0f;fDir[2] = 0.0f;
	uDir[0] = 0.0f; uDir[1] = 0.0f; uDir[2] = 1.0f;
	actor.SetDirection(fDir, uDir);
	
	actor.SetTerrainRoom(terrainRoomID, 10.0f);
	beOK = actor.PutOnTerrain(pos);

	//blood
	// get the base object of Lyubu
	OBJECTid baseID = actor.GetBaseObject();
	// make the blood bar's parent is the base and raise up the blood bar higher than the head of lyubu
	model.SetParent(baseID);
	model.Translate(0.0f, 0.0f, 70.0f, REPLACE);
	//blood

	//lo DonZo PART
	idleID = actor.GetBodyAction(NULL, "Idle");
	runID = actor.GetBodyAction(NULL, "Run");

	combatidleID = actor.GetBodyAction(NULL, "ComBatIdle");
	//runID = actor.GetBodyAction(NULL, "Run");
	rshiftID = actor.GetBodyAction(NULL, "MoveRight");
	lshiftID = actor.GetBodyAction(NULL, "MoveLeft");
	light_attack1ID= actor.GetBodyAction(NULL, "NormalAttack1");
	light_attack2ID = actor.GetBodyAction(NULL, "NormalAttack2");
	heavy_attackID = actor.GetBodyAction(NULL, "HeavyAttack1");
	damaged1ID = actor.GetBodyAction(NULL, "Damage1");//15 f
	damaged2ID = actor.GetBodyAction(NULL, "Damage2");//25 f
	dieID = actor.GetBodyAction(NULL, "Dead");
	curPoseID = runID;
	actor.SetCurrentAction(NULL, 0, curPoseID);
	actor.Play(START, 0.0f, FALSE, TRUE);
	HP =144;
	maxHP = 144;
	is_attack_frame = 0;
}
void ROBBER::isattack(int attack_on_delay){


	if (is_attack_frame == 0 && curPoseID == damaged1ID){
		is_attack_frame = 24;
		damaged_type = 1;
	}
	else if (is_attack_frame == 0 && curPoseID == damaged2ID){
		is_attack_frame = 36;
		damaged_type = 2;
	}
	
	if (is_attack_frame > 0){
		is_attack_frame--;
		if (damaged_type == 1)
		{
			HP -= 1;
		}
		else if (damaged_type == 2)
		{
			HP -= 2;
			
		}
		SetBlood(HP);
		
		if (is_attack_frame <1)
			attacked_target = FALSE;
	}


	if (curPoseID != dieID && HP <= 0){
		is_attack_frame == 0;//Lai
		attacked_target = FALSE;//Lai
		clean_clock = 90;
		curPoseID = dieID;
		actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
		
	}
}
void ROBBER::play(int attack_on_delay, int skip){
//	FnCharacter actor;
//	actor.ID(id);

	//Lai
	if (((curPoseID != runID && curPoseID != combatidleID  && curPoseID != dieID) || action_lock)&& attack_on_delay < 50)
	{

		if (!action_lock)
		{
			action_lock = TRUE;
			actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
			actor.Play(ONCE, (float)skip, FALSE, TRUE);//0105
		}
		if (action_lock)
			actor.Play(ONCE, (float)skip, FALSE, TRUE);
		
		if (HP>0 && attack_on_delay == 0 && attack_clock==0)
		{
			if (leave_with_L > 0)
				curPoseID = runID;
			else
				curPoseID = combatidleID;
			
			actor.SetCurrentAction(0, NULL,curPoseID, 5.0f);
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
//Lai
void ROBBER::attackplayer(int atk_lv)
{ /*
	light_attack1ID = actor.GetBodyAction(NULL, "NormalAttack1"); 35f
	light_attack2ID = actor.GetBodyAction(NULL, "NormalAttack2"); 25f
	heavy_attackID = actor.GetBodyAction(NULL, "HeavyAttack1");  30f
	*/
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
			curPoseID = heavy_attackID;
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

void ROBBER::SetPosition(float fwd)
{	
	actor.MoveForward(fwd*1.0f, TRUE, FALSE, 0.0f, TRUE);

	if (leave_with_L > 0 && curPoseID != runID)
	{
		curPoseID = runID;
		actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
		actor.Play(START, 0.0f, FALSE, TRUE);
	}
	else if (leave_with_L == 0 && curPoseID != combatidleID)
	{
		curPoseID =  combatidleID;
		actor.SetCurrentAction(0, NULL, curPoseID, 5.0f);
		actor.Play(START, 0.0f, FALSE, TRUE);
	}

	//actor.SetPosition(pos);
}

float ROBBER::dis(float Tpos[])//dis with Target
{
	actor.GetPosition(pos);
	return sqrt(pow(Tpos[0] - pos[0],2) + pow(Tpos[1] - pos[1],2));

}
void ROBBER::actor_clean(BOOL4&beOK)
{	
	if (clean_clock > 0) clean_clock--;
	else actor.DropToTrashCan(beOK);

}
float* ROBBER::GetPosition()
{
	return pos;
}
float* ROBBER::GetOldFaceDir()
{
	return old_f;
}
void ROBBER::SetOldFaceDir(float* f)
{
	old_f[0] = f[0];
	old_f[1] = f[1];
	old_f[2] = f[2];
}
int ROBBER::GetState()
{
	return state;
}
void ROBBER::SetState(int s)
{
	state = s;
}
void ROBBER::SetBlood(int curHP)
{
	float size[2];
	size[0] = 20.0f*curHP / maxHP;
	size[1] = 2.0f;

	FnBillboard bb(bloodBar);
	bb.SetPositionSize(NULL, size);
}
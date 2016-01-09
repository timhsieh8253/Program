#pragma once
#include "FlyWin32.h"

class LYUBU
{
public:
	LYUBU();
	~LYUBU();
	void Initiate(SCENEid, ROOMid,BOOL4&);
	float* GetPosition();
	float* GetOldFaceDir();
	void SetOldFaceDir(float*);
	void SetPosition(float*);
	void SetBlood(int);
	void SetFX();

	void play(int, int);//******************

	CHARACTERid id;
	//attack
	ACTIONid normal_attack1ID, normal_attack2ID, normal_attack3ID, normal_attack4ID;
	ACTIONid heavy_attack1ID, heavy_attack2ID, heavy_attack3ID;
	ACTIONid ultimate_attackID;
	//Damage
	ACTIONid heavy_damagedID, right_damagedID, left_damagedID;
	//others
	ACTIONid idleID, runID, curPoseID, dieID, guardID, fightidleID;
	//Blood
	OBJECTid bloodBarObj;
	GEOMETRYid bloodBar;

	// FX
	SCENEid sid;
	GAMEFX_SYSTEMid gFXID = FAILED_ID;
	OBJECTid dummyID = FAILED_ID; // object for display FX

	
	int HP;
	int maxHP;
	int is_attack;
	int is_attack_frame;//********
	int blood_size;

	SCENEid Lyubu_blood, Lyubu_head;
	OBJECTid Lyubu_backGID,headID;
private:
	float pos[3];
	//LyuBu old face direction
	float old_f[3]; 

	bool action_lock;

};


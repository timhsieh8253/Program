#pragma once
#include "FlyWin32.h"

class ROBBER
{
public:
	ROBBER();
	~ROBBER();

	void Initiate(SCENEid, ROOMid, BOOL4&,float[]);
	void isattack(int); //be attacked
	void attackplayer(int);
	void play(int, int);
	//**
	int GetState();
	void SetState(int);
	float* GetPosition();
	float* GetOldFaceDir();
	void SetOldFaceDir(float*);

	void SetBlood(int);
	//**

	void SetPosition(float);
	void actor_clean(BOOL4&);
	float dis(float[]);
	CHARACTERid id;
	//attack
	ACTIONid light_attack1ID, light_attack2ID, heavy_attackID;
	//Damage
	ACTIONid damaged1ID, damaged2ID;
	//Defense
	ACTIONid rshiftID, lshiftID;
	//others
	ACTIONid combatidleID,idleID, runID, curPoseID, dieID, defenceID;

	//Blood
	OBJECTid bloodBarObj;
	GEOMETRYid bloodBar;


	FnCharacter actor;

	int HP;
	int maxHP;

	int is_attack;
	int is_attack_frame;

	//LyuBu old face direction
	float old_f[3];
	int state;

	int attack_clock;
	bool attacked_target;
	int damaged_type;
	float pos[3];
	int stop_flag;
	int leave_with_L;
	int find_way;
	int clean_clock;
	float diswithL;
	bool action_lock;

	GAMEFX_SYSTEMid gFXID = FAILED_ID;
	OBJECTid dummyID = FAILED_ID; // object for display FX
};


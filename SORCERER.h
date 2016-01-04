#pragma once
#include "FlyWin32.h"

class SORCERER
{
public:
	SORCERER();
	~SORCERER();

	void Initiate(SCENEid, ROOMid, BOOL4&);
	void isattack(int);
	void play(int, int, bool);
	int GetState();
	void SetState(int);
	float* GetPosition();
	float* GetOldFaceDir();
	void SetOldFaceDir(float*);
	void SetPosition(float*);
	void SetBlood(int);
	CHARACTERid id;
	//attack
	ACTIONid light_attack1ID, light_attack2ID, heavy_attackID;
	//Damage
	ACTIONid damaged1ID, damaged2ID;
	//Defense
	ACTIONid rshiftID, lshiftID;
	//others
	ACTIONid combatidleID, idleID, runID, curPoseID, dieID, defenceID;
	ACTIONid test_action;
	//Blood
	OBJECTid bloodBarObj;
	GEOMETRYid bloodBar;

	int HP;
	int maxHP;
	int is_attack;
	int is_attack_frame;
	//LyuBu old face direction
private:
	int state;
	float old_f[3];
	float pos[3];
};


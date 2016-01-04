#pragma once
#include "FlyWin32.h"

class DONZO
{
public:
	DONZO();
	~DONZO();

	void Initiate(SCENEid, ROOMid, BOOL4&);
	void isattack(int);
	void play(int,int,bool);
	int GetState();
	void SetState(int);
	float* GetPosition();
	float* GetOldFaceDir();
	void SetOldFaceDir(float*);
	void SetPosition(float*);
	void SetBlood(int);
	CHARACTERid id;
	//attack
	ACTIONid light_attack1ID, light_attack2ID, heavy_attack1ID, heavy_attack2ID;
	//Damage
	ACTIONid light_damagedID, heavy_damagedID;
	//others
	ACTIONid idleID, runID, curPoseID, dieID, defenceID;
	//Blood
	OBJECTid bloodBarObj;
	GEOMETRYid bloodBar;


	int HP;
	int maxHP;
	//int is_attack;
	int is_attack_frame;
	//LyuBu old face direction
private:
	float old_f[3];
	float pos[3];
	int state;
};


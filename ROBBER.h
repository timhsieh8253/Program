#pragma once
#include "FlyWin32.h"

class ROBBER
{
public:
	ROBBER();
	~ROBBER();

	void Initiate(SCENEid, ROOMid, BOOL4&,float[]);
	void isattack(int); //be attacked
	int attackplayer(int);
	void play(int, int);

	int GetState();
	void SetState(int);
	float* GetPosition();
	float* GetOldFaceDir();
	void SetOldFaceDir(float*);
	void SetBlood(int);
	int GetAttackClock();
	void SetAttackClock(int);
	int GetDamagedType();
	void SetDamagedType(int);
	int GetStopFlag();
	void SetStopFlag(int);
	int GetLeaveWithL();
	void SetLeaveWithL(int);
	int GetFindWay();
	void SetFindWay(int);
	int GetCleanClock();
	void SetCleanClock(int);
	float GetDisWithL();
	void SetDisWithL(float);
	

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
	bool attacked_target;
	bool action_lock;
	float pos[3];

	// FX
	SCENEid sid;
	GAMEFX_SYSTEMid gFXID = FAILED_ID;
	OBJECTid dummyID = FAILED_ID; // object for display FX
	//LyuBu old face direction
private:
	float old_f[3];
	
	float diswithL;
	int state;

	int attack_clock;
	int damaged_type;
	
	int stop_flag;
	int leave_with_L;
	int find_way;
	int clean_clock;
	
	int hit_time[5];//*******************
	int hit_level;//******************
};


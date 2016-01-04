#pragma once
#include "FlyWin32.h"

class FOOTMAN
{
public:
	FOOTMAN();
	~FOOTMAN();

	void Initiate(SCENEid, ROOMid, BOOL4&);
	//void isattack(int);
	void play(int, int, bool);
	int GetState();
	void SetState(int);
	float* GetPosition();
	float* GetOldFaceDir();
	void SetOldFaceDir(float*);
	void SetPosition(float*);
	void SetBlood(int);
	CHARACTERid id;
	//others
	ACTIONid  idleID, runID,dying_AID,curPoseID,swingID;
	//Blood
	OBJECTid bloodBarObj;
	GEOMETRYid bloodBar;

	int HP;
	int maxHP;
	int is_attack_frame;
	//LyuBu old face direction
private:
	int state;
	float old_f[3];
	float pos[3];
};


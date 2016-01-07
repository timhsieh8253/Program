#include <string>
#include "FlyWin32.h"
using namespace std;

//dialog 0: content number--
//dialog 1: content number--

class dialog
{
public:
	dialog();
	~dialog();
	void start_dialog(int num);	
	int next_content();
	void render_dialog(FnViewport vp,int lock);
	void end_content();
	void set_pic(int num,FnSprite &sp2);
	void special_render(float* pos);
	
	int content_now,content_end;
	int event_num;
	int* speaker;
	float fade_in ,fade_out;
	string *content;
	SCENEid dialogid, picid, fullid, Lyubuid;
	OBJECTid dialog_backGID, pic_backGID, full_backGID, Lyubu_backGID;
	OBJECTid contentID,fullcontentID, LyubucontentID;

};

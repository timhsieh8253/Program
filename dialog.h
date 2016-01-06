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
	void render_dialog(FnViewport vp);
	void end_content();
	void set_pic(int num);
	
	int content_now,content_end;
	int event_num;
	int* speaker;
	string *content;
	SCENEid dialogid, picid;
	OBJECTid dialog_backGID, pic_backGID;
	OBJECTid contentID;
};

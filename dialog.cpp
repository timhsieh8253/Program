#include "dialog.h"
#include "FlyWin32.h"
using namespace std;

dialog::dialog()
{
	content_now = 0;
	content_end = 0;
	content = NULL;
	dialog_backGID = FAILED_ID;
}

dialog::~dialog()
{
	//aaaaa
	if (content)
		delete content;
}

void dialog::render_dialog(FnViewport vp){
	vp.RenderSprites(dialogid, FALSE, TRUE);
	vp.RenderSprites(picid, FALSE, TRUE);
}

void dialog::start_dialog(int num){
	event_num = num;
	content_now = 0;
	content_end = 0;
	if(num == 1)
		content_end = 2;
	next_content();
}

void dialog::end_content(){
	FnSprite sp;
	FnSpriteText text0;
	float rgb[4];	
	sp.ID(dialog_backGID);
	sp.SetSize(800, 200);

	text0.ID(contentID);
	text0.SetArea(800, 200);
	text0.SetParent(dialog_backGID);
	rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = 0.0;
	sp.SetColor(rgb);			
	text0.UseFont("新細明體", 25, TRUE, FALSE);			
	// show the caption on the sprite text at (10, 10) position in white color
	text0.Begin();
	text0.End();   // be sure to call this function when you finish the writing
	sp.ID(pic_backGID);
	sp.SetSize(0,0);
}
//num 0: Lyubu
//num 1: else
void dialog::set_pic(int num){
	FnSprite sp;
	sp.ID(pic_backGID);
	FySetTexturePath("Data\\NTU6");
	if(num == 0){
		sp.SetImage("ll", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(182, 144);
		sp.SetPosition(810 , 10, 0);
	}
	else if(num == 1){
		sp.SetImage("lll", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(182, 144);
		sp.SetPosition(10 , 10, 0);
	}
}

int dialog::next_content(){
	if (content)
		delete content;
	if(content_now > content_end){
		end_content();
		return 0;
	}
	
	FnSprite sp;
	FnSpriteText text0;
	float rgb[4];	
	sp.ID(dialog_backGID);
	sp.SetSize(800, 200);

	text0.ID(contentID);
	text0.SetArea(800, 200);
	text0.SetParent(dialog_backGID);
	
	if(event_num == 1){
		if(content_now == 0){
			rgb[0] = 0.0f; rgb[1] = 1.0f; rgb[2] = 0.0f; rgb[3] = 0.5f;
			sp.SetColor(rgb);			
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "Test您好:", 255, 255, 255, 255);
			text0.Write(50, 60, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();   // be sure to call this function when you finish the writing
			sp.SetPosition(10 ,10 ,1);
			set_pic(0);
		}
		else if(content_now == 1){
			rgb[0] = 0.0f; rgb[1] = 1.0f; rgb[2] = 0.0f; rgb[3] = 0.5f;
			sp.SetColor(rgb);			
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "Test您好:", 255, 255, 255, 255);
			text0.Write(50, 60, "第二個第二個第二個第二個第二個第二個", 255, 255, 255, 255);
			text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			sp.SetPosition(10 ,10 ,1);			
		}
		else if(content_now == 2){
			rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; rgb[3] = 0.5f;
			sp.SetColor(rgb);			
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "Test您好2:", 255, 255, 255, 255);
			text0.Write(50, 60, "這是另一個人在說話啦哈哈哈", 255, 255, 255, 255);
			text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			sp.SetPosition(210 ,10 ,1);	
			set_pic(1);
		}
	}
	/*if (set_num == 0){
		content = new string[2];
		content[0] = "Test1 第一行";
		content[1] = "Test1 第二行";
		content_end = 2;
	}
	else if (set_num == 1){
		content = new string[1];
		content[0] = "Test1 第一行";
		content_end = 1;
	}*/
	content_now ++;

	return 1;
}

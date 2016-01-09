#include "dialog.h"
#include "FlyWin32.h"
using namespace std;

dialog::dialog()
{
	content_now = 0;
	content_end = 0;
	content = NULL;
	dialog_backGID = FAILED_ID;
	fade_in = 0;
	fade_out = 1;
}

dialog::~dialog()
{
	//aaaaa
	if (content)
		delete content;
}
void dialog::special_render(float* pos){
	if(event_num == 1 && content_now == 4){
		FnSprite sp;
		FnSpriteText text0;
		float rgb[4];
		sp.ID(dialog_backGID);
		
		
		text0.ID(contentID);
		text0.SetArea(800, 200);
		text0.SetParent(dialog_backGID);
		text0.UseFont("新細明體", 50, TRUE, FALSE);
		text0.Begin();
		text0.Write(20, 20, "!!", 255, 255, 0, 255);
		text0.End();
		sp.SetPosition(pos[0]+10 ,pos[1]+100 ,0);
		
		sp.SetSize(800, 200);
		rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = 0.0f;
		sp.SetColor(rgb);
		
	}
}
void dialog::special_render2(float* pos){
	FnSprite sp;
	FnSpriteText text0;
	float rgb[4];
	sp.ID(dialog_backGID);	
	
	text0.ID(contentID);
	text0.SetArea(800, 200);
	text0.SetParent(dialog_backGID);
	text0.UseFont("新細明體", 50, TRUE, FALSE);
	text0.Begin();
	text0.Write(20, 20, "!!", 255, 255, 0, 255);
	text0.End();
	sp.SetPosition(pos[0]+10 ,pos[1]+100 ,0);
	
	sp.SetSize(800, 200);
	rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = 0.0f;
	sp.SetColor(rgb);
}
void dialog::render_dialog(FnViewport vp,int lock){
	if(!lock){
		//if ((event_num == 1 && (content_now == 0 || content_now == 1)) ||
		//	(event_num == 3 && (content_now == 0 || content_now == 1))	){
			//vp.RenderSprites(dialogid, FALSE, TRUE);
			//vp.RenderSprites(picid, FALSE, TRUE);
			vp.RenderSprites(fullid, FALSE, TRUE);
		//}		
		//else{
			vp.RenderSprites(dialogid, FALSE, TRUE);
			vp.RenderSprites(picid, FALSE, TRUE);
		//}
	}
	if(fade_out != 1.0f || fade_in!= 0.0f)
		next_content();
}

void dialog::start_dialog(int num){
	event_num = num;
	content_now = 0;
	content_end = 0;
	if(num == 1)
		content_end = 21;
	else if(num == 2)
		content_end = 6;
	else if(num == 3)
		content_end = 12;
	else if(num == 4)
		content_end = 5;
	else if(num == 5)
		content_end = 0;
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
//num 1: skeleton
//2 - quest, 3- lyu2, 4-letter, 5-rob, 6-rob2, 7-don2
void dialog::set_pic(int num, FnSprite &sp2){
	FnSprite sp;	
	float rgb[4];
	sp.ID(pic_backGID);
	FySetTexturePath("Data\\NTU6");
	if(num == 0){
		sp.SetImage("Lyu3", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(810 , 10, 0);
		rgb[0] = 1.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);			
		sp2.SetPosition(10 ,10 ,0);
	}
	else if(num == 1){
		sp.SetImage("s", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(10 , 10, 0);
		rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);
		sp2.SetPosition(210 ,10 ,0);	
	}
	else if(num == 2){
		sp.SetSize(0,0);
		rgb[0] = 0.5f; rgb[1] = 0.5f; rgb[2] = 0.5f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);
		sp2.SetPosition(110 ,10 ,0);
	}
	else if(num == 3){
		sp.SetImage("Lyu2", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(810 , 10, 0);
		rgb[0] = 0.0f; rgb[1] = 1.0f; rgb[2] = 0.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);			
		sp2.SetPosition(10 ,10 ,0);
	}
	else if(num == 4){
		sp.SetImage("letter", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(10 , 10, 0);
		rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);
		sp2.SetPosition(210 ,10 ,0);
	}
	else if(num == 5){
		sp.SetImage("Rob", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(10 , 10, 0);
		rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);
		sp2.SetPosition(210 ,10 ,0);
	}
	else if(num == 6){
		sp.SetImage("Rob2", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(10 , 10, 0);
		rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);
		sp2.SetPosition(210 ,10 ,0);
	}
	else if(num == 7){
		sp.SetImage("Don2", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(10 , 10, 0);
		rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);
		sp2.SetPosition(210 ,10 ,0);
	}
	else if(num == 8){
		sp.SetImage("s2", 0, NULL, 0, NULL, NULL, MANAGED_MEMORY, FALSE, FALSE);
		sp.SetSize(200, 200);
		sp.SetPosition(10 , 10, 0);
		rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 1.0f; rgb[3] = 0.5f;
		sp2.SetColor(rgb);
		sp2.SetPosition(210 ,10 ,0);
	}
}

int dialog::next_content(){
	if (content)
		delete content;
	if(content_now > content_end){
		end_content();
		return 0;
	}

	if(event_num == 1){
		if(content_now == 0){
			FnSprite sp;
			FnSpriteText text0;

			sp.ID(full_backGID);
			sp.SetSize(1024, 768);
			float rgb[4];
			rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = 1.0f;
			sp.SetColor(rgb);
			sp.SetPosition(0,0,1);
			text0.ID(fullcontentID);
			text0.SetArea(1024, 768);
			text0.SetParent(full_backGID);
			text0.UseFont("新細明體", 50, TRUE, FALSE);			
			text0.Begin();
			text0.Write(300, 384, "按空白鍵以開始", 255, 255, 255, 255);
			text0.End();   // be sure to call this function when you finish the writing
			
		}
		else if(content_now == 1){
			FnSprite sp;
			FnSpriteText text0;

			sp.ID(full_backGID);
			sp.SetSize(1024, 768);
			float rgb[4];
			rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = fade_out;
			sp.SetColor(rgb);
			sp.SetPosition(0,0,1);
			text0.ID(fullcontentID);
			text0.SetArea(1024, 768);
			text0.SetParent(full_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.End();   // be sure to call this function when you finish the writing
			//start fadeout
			fade_out = fade_out - 0.05;
			if(fade_out < 0.0f){
				fade_out = 1.0f;
				content_now = 1;
			}
			else
				content_now = 0;
		}
		else if(content_now == 2){	
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "啦啦啦~呂布遊長安~~~", 255, 255, 255, 255);
			text0.End();   // be sure to call this function when you finish the writing

			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 3 || content_now == 4 ){
			end_content();
		}
		else if(content_now == 5){		
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "路上怎麼會有一個死人骨頭?!?!", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();	
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);			
		}
		else if(content_now == 6){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "骷髏:", 255, 255, 255, 255);
			text0.Write(50, 60, "嘿嘿嘿嘿.......", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(1, sp);
		}
		else if(content_now == 7){		
			FnSprite sp;
			FnSpriteText text0;

			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);		
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "你...你是誰??你想幹嘛?", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();

			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 8){	
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "骷髏:", 255, 255, 255, 255);
			text0.Write(50, 60, "這位英雄，我是誰不重要。", 255, 255, 255, 255);
			text0.Write(50, 90, "我看你從頭頂衝出兩根雞毛", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(1, sp);
		}
		else if(content_now == 9){	
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "骷髏:", 255, 255, 255, 255);
			text0.Write(50, 60, "一定是個百年難得一見的練舞奇才，", 255, 255, 255, 255);	
			text0.Write(50, 90, "我這裡有一本舞林秘笈，你不仿拿去參詳參詳", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(1, sp);
		}
		else if(content_now == 10){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			//text0.Write(20, 20, "骷髏:", 255, 255, 255, 255);
			text0.Write(50, 60, "按下S鍵施展學習並施展舞林秘笈", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
			
		}
		else if(content_now == 11){	
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "骷髏:", 255, 255, 255, 255);
			text0.Write(50, 60, "啊....你打我QQ", 255, 255, 255, 255);	
			text0.Write(50, 90, "好痛...我原本也很會跳舞的，", 255, 255, 255, 255);
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(1, sp);
		}
		else if(content_now == 12){	
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "骷髏:", 255, 255, 255, 255);
			text0.Write(50, 60, "直到膝蓋中了一箭...."	, 255, 255, 255, 255);						
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(1, sp);
		}
		else if(content_now == 13){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "..................."	, 255, 255, 255, 255);						
			text0.Write(50, 90, "............................."	, 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(3, sp);
		}
		else if(content_now == 14){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "疑? 骨頭堆裡面怎麼有封信?"	, 255, 255, 255, 255);						
			//text0.Write(50, 90, "............................."	, 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 15){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "呂布撿起了一封信", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
		}
		else if(content_now == 16){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "信:", 255, 255, 255, 255);
			text0.Write(50, 60, "世紀舞王大賽徵求各方勇士踴躍參加，", 255, 255, 255, 255);	
			text0.Write(50, 90, "參加者即有機會可獲得公主貂蟬青睞!", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(4, sp);
		}
		else if(content_now == 17){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "信:", 255, 255, 255, 255);
			text0.Write(50, 60, "憑此信參加，任信不認人", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(4, sp);
		}
		else if(content_now == 18){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "竟..竟然是我最愛的貂蟬", 255, 255, 255, 255);						
			text0.Write(50, 90, "這樣我誓死也要去參加!!", 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 19){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "小貂貂，我來了!!!!!!!!!!!!!!!", 255, 255, 255, 255);						
			//text0.Write(50, 90, "這樣我誓死也要去參加!!", 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 20){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "恭喜玩家呂布獲得任務：參加舞會", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
		}
		else if(content_now == 21){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "請玩家保護信件直到會場", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
		}
		
	}
	else if(event_num == 2){
		if(content_now == 0){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "強盜A:", 255, 255, 255, 255);
			text0.Write(50, 60, "站住!!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(5, sp);
		}
		else if(content_now == 1){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "你們是誰?", 255, 255, 255, 255);
			text0.Write(50, 90, "為何要阻止我前去會場?", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 2){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "強盜B:", 255, 255, 255, 255);
			text0.Write(50, 60, "哼!! 貂蟬是屬於我們的!", 255, 255, 255, 255);
			text0.Write(50, 90, "不交出參加信的話，就去死吧!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(6, sp);
		}
		else if(content_now == 3){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "強盜B:", 255, 255, 255, 255);
			text0.Write(50, 60, "還不速速交出參加信!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(5, sp);
		}
		else if(content_now == 4){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "一群小丑!!", 255, 255, 255, 255);
			text0.Write(50, 90, "還不看我好好教訓教訓你們!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "字字字字字字字字字字字字字字字字字字字字", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 5){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "強盜B:", 255, 255, 255, 255);
			text0.Write(50, 60, "兄弟們!!殺!!!!!", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(6, sp);
		}
		else if(content_now == 6){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "強盜A:", 255, 255, 255, 255);
			text0.Write(50, 60, "殺!!!!!", 255, 255, 255, 255);
			text0.End();
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(5, sp);
		}
	}
	else if(event_num == 3){
		if(content_now == 0){
			FnSprite sp;
			FnSpriteText text0;

			sp.ID(full_backGID);
			sp.SetSize(1024, 768);
			float rgb[4];
			rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = fade_in;
			sp.SetColor(rgb);
			sp.SetPosition(0,0,0);
			//start fadeout
			fade_in = fade_in + 0.05;
			if(fade_in > 1.0){
				fade_in = 0.0;
				content_now = 0;
			}
			else
				content_now = -1;
		}
		else if(content_now == 1){
			FnSprite sp;
			FnSpriteText text0;

			sp.ID(full_backGID);
			sp.SetSize(1024, 768);
			float rgb[4];
			rgb[0] = 0.0f; rgb[1] = 0.0f; rgb[2] = 0.0f; rgb[3] = fade_out;
			sp.SetColor(rgb);
			sp.SetPosition(0,0,0);
			//start fadeout
			fade_out = fade_out - 0.05;
			if(fade_out < 0.0){
				fade_out = 1.0;
				content_now = 1;
			}
			else
				content_now = 0;
		}
		else if(content_now == 2){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "呼，費盡千辛萬苦，", 255, 255, 255, 255);						
			text0.Write(50, 90, "終於到會場了，貂貂貂貂，我來了!", 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 3){
			//earthquake
			end_content();
		}
		else if(content_now == 4){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布:", 255, 255, 255, 255);
			text0.Write(50, 60, "......?", 255, 255, 255, 255);						
			//text0.Write(50, 90, "終於到會場了，貂貂貂貂，我來了!", 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 5){
			//Donzo appear
			end_content();
		}
		else if(content_now == 6){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "貂蟬(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "你終於來了，小布布，", 255, 255, 255, 255);	
			text0.Write(50, 90, "我一眼就看上你了，我就是你的貂蟬啊!", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(7, sp);
		}
		else if(content_now == 7){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布：", 255, 255, 255, 255);
			text0.Write(50, 60, "不...不要過來", 255, 255, 255, 255);	
			text0.Write(50, 90, "我.....我才不要這樣的貂蟬!!", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 8){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布：", 255, 255, 255, 255);
			text0.Write(50, 60, "在過來我揍死你!!", 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(0, sp);
		}
		else if(content_now == 9){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "貂蟬(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "啊，真是太切心了，", 255, 255, 255, 255);	
			text0.Write(50, 90, "難道由愛生恨就是這種感覺嗎!!", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(7, sp);
		}
		else if(content_now == 10){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "貂蟬(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "既然得不到你，", 255, 255, 255, 255);	
			text0.Write(50, 90, "那麼你就去死吧!!", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(7, sp);
		}
		else if(content_now == 11){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "任務觸發：消滅董卓", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
		}
		else if(content_now == 12){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "請保護呂布，免於董卓的荼毒", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
		}
	}
	else if(event_num == 4){
		if(content_now == 0){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "貂蟬(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "小布布，你竟然辣手摧花QAQ", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(7, sp);
		}
		else if(content_now == 1){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "貂蟬(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "哼! 你以為這樣就結束了嗎?", 255, 255, 255, 255);
			text0.Write(50, 90, "我原本不想用這招的...", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(7, sp);
		}
		else if(content_now == 2){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "貂蟬(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "殺了一個我，還有千千萬萬個我!!", 255, 255, 255, 255);
			text0.Write(50, 90, "就決定是你了!!董甲、董乙、董丙........", 255, 255, 255, 255);			
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(7, sp);
		}
		else if(content_now == 3){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "呂布：", 255, 255, 255, 255);
			text0.Write(50, 60, "這.....", 255, 255, 255, 255);	
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(3, sp);
		}
		else if(content_now == 4){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "最終任務：消滅千千萬萬個董卓", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
		}
		else if(content_now == 5){
			FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "請消滅999個董卓的分身", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(2, sp);
		}
	}
	else if(event_num == 5){
		if(content_now == 0){
		FnSprite sp;
			FnSpriteText text0;
			
			text0.ID(contentID);
			text0.SetArea(800, 200);
			text0.SetParent(dialog_backGID);
			text0.UseFont("新細明體", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "骷骷:", 255, 255, 255, 255);
			text0.Write(50, 60, "肖年~會場不在那邊喔!", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(8, sp);
		}
	}
	content_now++;

	return content_now;
}

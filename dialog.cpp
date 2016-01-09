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
		text0.UseFont("�s�ө���", 50, TRUE, FALSE);
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
	text0.UseFont("�s�ө���", 50, TRUE, FALSE);
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
	text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
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
			text0.UseFont("�s�ө���", 50, TRUE, FALSE);			
			text0.Begin();
			text0.Write(300, 384, "���ť���H�}�l", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "�հհ�~�f���C���w~~~", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "���W���|���@�Ӧ��H���Y?!?!", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�u�\:", 255, 255, 255, 255);
			text0.Write(50, 60, "�K�K�K�K.......", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "�A...�A�O��??�A�Q�F��?", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�u�\:", 255, 255, 255, 255);
			text0.Write(50, 60, "�o��^���A�ڬO�֤����n�C", 255, 255, 255, 255);
			text0.Write(50, 90, "�ڬݧA�q�Y���ĥX�������", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�u�\:", 255, 255, 255, 255);
			text0.Write(50, 60, "�@�w�O�Ӧʦ~���o�@�����m�R�_�~�A", 255, 255, 255, 255);	
			text0.Write(50, 90, "�ڳo�̦��@���R�L���D�A�A���鮳�h�Ѹ԰Ѹ�", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			//text0.Write(20, 20, "�u�\:", 255, 255, 255, 255);
			text0.Write(50, 60, "���US��I�i�ǲߨìI�i�R�L���D", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�u�\:", 255, 255, 255, 255);
			text0.Write(50, 60, "��....�A����QQ", 255, 255, 255, 255);	
			text0.Write(50, 90, "�n�h...�ڭ쥻�]�ܷ|���R���A", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�u�\:", 255, 255, 255, 255);
			text0.Write(50, 60, "���콥�\���F�@�b...."	, 255, 255, 255, 255);						
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "��? ���Y��̭���򦳫ʫH?"	, 255, 255, 255, 255);						
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "�f���߰_�F�@�ʫH", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�H:", 255, 255, 255, 255);
			text0.Write(50, 60, "�@���R���j�ɼx�D�U��i�h���D�ѥ[�A", 255, 255, 255, 255);	
			text0.Write(50, 90, "�ѥ[�̧Y�����|�i��o���D�I�ͫC��!", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�H:", 255, 255, 255, 255);
			text0.Write(50, 60, "�̦��H�ѥ[�A���H���{�H", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "��..���M�O�ڳ̷R���I��", 255, 255, 255, 255);						
			text0.Write(50, 90, "�o�˧ڻ}���]�n�h�ѥ[!!", 255, 255, 255, 255);	
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "�p�I�I�A�ڨӤF!!!!!!!!!!!!!!!", 255, 255, 255, 255);						
			//text0.Write(50, 90, "�o�˧ڻ}���]�n�h�ѥ[!!", 255, 255, 255, 255);	
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "���ߪ��a�f����o���ȡG�ѥ[�R�|", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "�Ъ��a�O�@�H�󪽨�|��", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�j�sA:", 255, 255, 255, 255);
			text0.Write(50, 60, "����!!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "�A�̬O��?", 255, 255, 255, 255);
			text0.Write(50, 90, "����n����ګe�h�|��?", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�j�sB:", 255, 255, 255, 255);
			text0.Write(50, 60, "��!! �I�ͬO�ݩ�ڭ̪�!", 255, 255, 255, 255);
			text0.Write(50, 90, "����X�ѥ[�H���ܡA�N�h���a!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�j�sB:", 255, 255, 255, 255);
			text0.Write(50, 60, "�٤��t�t��X�ѥ[�H!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "�@�s�p��!!", 255, 255, 255, 255);
			text0.Write(50, 90, "�٤��ݧڦn�n�аV�аV�A��!!", 255, 255, 255, 255);
			//text0.Write(50, 90, "�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r�r", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�j�sB:", 255, 255, 255, 255);
			text0.Write(50, 60, "�S�̭�!!��!!!!!", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�j�sA:", 255, 255, 255, 255);
			text0.Write(50, 60, "��!!!!!", 255, 255, 255, 255);
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "�I�A�O�ɤd���U�W�A", 255, 255, 255, 255);						
			text0.Write(50, 90, "�ש��|���F�A�I�I�I�I�A�ڨӤF!", 255, 255, 255, 255);	
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f��:", 255, 255, 255, 255);
			text0.Write(50, 60, "......?", 255, 255, 255, 255);						
			//text0.Write(50, 90, "�ש��|���F�A�I�I�I�I�A�ڨӤF!", 255, 255, 255, 255);	
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�I��(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "�A�ש�ӤF�A�p�����A", 255, 255, 255, 255);	
			text0.Write(50, 90, "�ڤ@���N�ݤW�A�F�A�ڴN�O�A���I�Ͱ�!", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f���G", 255, 255, 255, 255);
			text0.Write(50, 60, "��...���n�L��", 255, 255, 255, 255);	
			text0.Write(50, 90, "��.....�ڤ~���n�o�˪��I��!!", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f���G", 255, 255, 255, 255);
			text0.Write(50, 60, "�b�L�ӧڴ~���A!!", 255, 255, 255, 255);	
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�I��(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "�ڡA�u�O�Ӥ��ߤF�A", 255, 255, 255, 255);	
			text0.Write(50, 90, "���D�ѷR�ͫ�N�O�o�طPı��!!", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�I��(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "�J�M�o����A�A", 255, 255, 255, 255);	
			text0.Write(50, 90, "����A�N�h���a!!", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "����Ĳ�o�G��������", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "�ЫO�@�f���A�K�󸳨������r", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�I��(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "�p�����A�A���M����R��QAQ", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�I��(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "��! �A�H���o�˴N�����F��?", 255, 255, 255, 255);
			text0.Write(50, 90, "�ڭ쥻���Q�γo�۪�...", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�I��(DonZo):", 255, 255, 255, 255);
			text0.Write(50, 60, "���F�@�ӧڡA�٦��d�d�U�U�ӧ�!!", 255, 255, 255, 255);
			text0.Write(50, 90, "�N�M�w�O�A�F!!���ҡB���A�B����........", 255, 255, 255, 255);			
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�f���G", 255, 255, 255, 255);
			text0.Write(50, 60, "�o.....", 255, 255, 255, 255);	
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "�̲ץ��ȡG�����d�d�U�U�Ӹ���", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(50, 60, "�Ю���999�Ӹ���������", 255, 255, 255, 255);		
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
			text0.UseFont("�s�ө���", 25, TRUE, FALSE);			
			text0.Begin();
			text0.Write(20, 20, "�u�u:", 255, 255, 255, 255);
			text0.Write(50, 60, "�v�~~�|�����b�����!", 255, 255, 255, 255);		
			text0.End();		
			
			sp.ID(dialog_backGID);
			sp.SetSize(800, 200);
			set_pic(8, sp);
		}
	}
	content_now++;

	return content_now;
}

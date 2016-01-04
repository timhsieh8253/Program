#include "dialog.h"


dialog::dialog()
{
	content_now = 0;
	content_end = 0;
	content = NULL;
}

dialog::~dialog()
{
	if (content)
		delete content;
}


void dialog::set_content(int set_num){
	if (content)
		delete content;

	if (set_num == 0){
		content = new string[2];
		content[0] = "Test1 第一行";
		content[1] = "Test1 第二行";
		content_end = 2;
	}
	else if (set_num == 1){
		content = new string[1];
		content[0] = "Test1 第一行";
		content_end = 1;
	}
	content_now = 0;
}

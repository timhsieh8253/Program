#include <string>
#include "FlyWin32.h"
using namespace std;

//dialog 0: content 0 ~ 
//

class dialog
{
public:
	dialog();
	~dialog();
	void set_content(int set_num);	

	int content_now,content_end;
	string *content;
	SCENEid dialogid;
};

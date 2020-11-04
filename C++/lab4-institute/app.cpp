#include "stdafx.h"
#include "app.h"


App::App()
{
	funcs.push_back(&App::addStudents);
	funcs.push_back(&App::findStudents);
	funcs.push_back(&App::deleteStudents);
	funcs.push_back(&App::showStudents);
	funcs.push_back(&App::changeGroup);
	funcs.push_back(&App::changeKind);

}

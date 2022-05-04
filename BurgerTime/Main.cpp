#include "BurgerTimePCH.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BurgerTimeGame.h"


int main(int, char* []) {


	BurgerTimeGame burgerTimeGame;
	burgerTimeGame.Run();

	return 0;
}
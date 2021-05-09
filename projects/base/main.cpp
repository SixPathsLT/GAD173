#include "cmath"
#include "kf/kf_log.h"
#include "GameManager.h"
#include "ResourceManager.h"
using namespace std;

int main()
{

	//loads resources
	ResourceManager::init();
	Button::init();
	GameManager::inst().init();

	return 0;
}

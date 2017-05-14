#include "GenerateEnemyEvent.h"
#include "GameMaster.h"

namespace ZS {

	GenerateEnemyEvent::GenerateEnemyEvent(float _progress) {
		progress = _progress;
	}

	GenerateEnemyEvent::~GenerateEnemyEvent() {
	}

	void GenerateEnemyEvent::addEnemy(Enemy* enemy) {
		enemyVec.push_back(enemy);
	}

	void GenerateEnemyEvent::execute() {
		GameMaster::GetInstance()->getLevelManager()->createEnemy(, progress);
	}
}

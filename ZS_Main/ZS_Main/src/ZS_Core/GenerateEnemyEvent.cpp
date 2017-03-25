#include "GenerateEnemyEvent.h"
#include "GameMaster.h"

namespace ZS {

	GenerateEnemyEvent::GenerateEnemyEvent(Vec3 _pos) {
		pos = _pos;
	}

	GenerateEnemyEvent::~GenerateEnemyEvent() {
	}

	void GenerateEnemyEvent::addEnemy(Enemy* enemy) {
		enemyVec.push_back(enemy);
	}

	void GenerateEnemyEvent::execute() {
		GameMaster::GetInstance()->getLevelManager()->createEnemy(pos);
	}
}

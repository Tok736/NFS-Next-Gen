#include "../include/physics/physics.h"
#include "../include/graphics/graphic.h"
#include "logic/Game.h"
#include "physics/SQLite.h"
//road id [0,1]
//cars id [2..9]
//obstraction id [10..20]
//decor id [21..30]

//obstructions id:
// cone - 10
// mud - 11
// oil - 12
// pit - 13
// rock1 - 14
// rock2 - 15
// rock3 - 16
// water - 17
// wheel - 18


//decor id
// tree1 - 21
// tree2 - 22
// tree 3 -23


int main()
{
	SQLiteDataBase db;
	while (db.setUser("player", "12345") == USER_ALREADY_EXISTS){} //повторный ввод - для регистрации
	while (db.getAuthorizeUser("player", "12345") == USER_NOT_FOUND){} //повторный ввод - для авторизации
    //Game myGame;
    //myGame.playGame();
    return 0;
}

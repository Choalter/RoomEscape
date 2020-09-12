#include <bangtal.h>
using namespace bangtal;

//요구사항1. 2개 이상의 장면 -> ok

//요구사항2. 2개 이상의 장면이 문으로 연결되어 있음 -> ok

//요구사항3.숨겨진 문을 클릭하면 게임이 종료됨

int main()
{
	//장면을 생성한다.
	auto scene1 = Scene::create("무어의 방1", "Images/RoomEscape/배경-1.png");
	auto scene2 = Scene::create("무어의 방2", "Images/RoomEscape/배경-2.png");//ScenePtr = 장면 변수 선언
	auto scene3 = Scene::create("무어의 방3", "Images/RoomEscape/배경-1.png");

	//열쇠를 만든다.
	auto key = Object::create("Images/RoomEscape/열쇠.png", scene1, 600, 150);
	key->setScale(0.2f);

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		key->pick();
		showMessage("무어씨의 열쇠다.");
		return true;
		});

	auto flowerpot_moved = false;
	auto flowerpot = Object::create("Images/RoomEscape/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (action == MouseAction::MOUSE_DRAG_LEFT) {
			flowerpot->locate(scene1, 450, 150);
			flowerpot_moved = true;
		}
		else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
			flowerpot->locate(scene1, 650, 150);
			flowerpot_moved = true;
		}
		return true;
		});

	//문을 생성한다.
	//모두 object로 생성
	auto door1_open = false;
	auto door1 = Object::create("Images/RoomEscape/문-오른쪽-닫힘.png", scene1, 800, 270);

	//열쇠 획득 이후 문을 클릭하면 scene2로 이동한다.
	door1->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool {
		if (door1_open == true) {
			scene2->enter();
		}
		else if (key->isHanded()) {
			door1->setImage("Images/RoomEscape/문-오른쪽-열림.png");
			door1_open = true;
		}

		else {
			showMessage("열쇠가 필요하다!!!!");
		}
		return true;
		});

	auto door2 = Object::create("Images/RoomEscape/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto door3_open = false;
	auto door3_locked = true;

	auto door3 = Object::create("Images/RoomEscape/문-오른쪽-닫힘.png", scene2, 910, 270);
	door3->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool {
		if (door3_locked) {
			showMessage("문이 열리지 않는다...");
		}
		else if (door3_open) {
			scene3->enter();
		}
		else {
			door3->setImage("Images/RoomEscape/문-오른쪽-열림.png");
			door3_open = true;
		}
		return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		door3_locked = false;
		showMessage("철커덕!");
		return true;
		});

	auto scene1_password = Object::create("Images/RoomEscape/암호1.png", scene1, 50, 500, false);
	auto scene2_password = Object::create("Images/RoomEscape/암호1-애너그램.png", scene2, 600, 100, false);
	auto scene3_password = Object::create("Images/RoomEscape/암호2-애너그램.png", scene3, 600, 100, false);

	auto door3_keypad = Object::create("Images/RoomEscape/키패드.png", scene2, 885, 420);
	door3_keypad->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool {
		showKeypad("BANGTAL", door3);
		return true;
		});

	auto door4 = Object::create("Images/RoomEscape/문-오른쪽-열림.png", scene3, 800, 270);
	door4->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	auto door5_open = false, door5_locked = true;
	auto door5 = Object::create("Images/RoomEscape/문-왼쪽-닫힘.png", scene3, 320, 300, false);
	door5->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool {
		if (door5_locked) {
			showMessage("문이 열리질 않는다...");
		}
		else if (door5_open) {
			showMessage("드디어 탈출했다!!!");
			endGame();
		}
		else {
			door5->setImage("Images/RoomEscape/문-왼쪽-열림.png");
			door5_open = true;
		}
		return true;
		});

	door5->setOnKeypadCallback([&](ObjectPtr object)->bool {
		door5_locked = false;
		door5->show();
		showMessage("철커덕!");
		return true;
		});

	auto door5_keypad = Object::create("Images/RoomEscape/키패드.png", scene3, 600, 420, false);
		door5_keypad->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool {
			showKeypad("ROOMESCAPE", door5);
			return true;
			});

	auto scene2_lighted = true;
	auto scene2_button = Object::create("Images/RoomEscape/스위치.png", scene2, 880, 440);
	scene2_button->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)-> bool {
		if (scene2_lighted) {
			scene1->setLight(0.2f);
			scene2->setLight(0.2f);
			scene2_password->show();
			scene1_password->show();
			scene2_lighted = false;
		}
		else {
			scene1->setLight(1.0f);
			scene2->setLight(1.0f);
			scene2_password->hide();
			scene1_password->hide();
			scene2_lighted = true;
		}
		return true;
		});

	auto scene3_lighted = true;
	auto scene3_button = Object::create("Images/RoomEscape/스위치.png", scene3, 220, 500);
	scene3_button->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)-> bool {
		if (scene3_lighted) {
			scene3->setLight(0.2f);
			scene3_password->show();
			scene3_lighted = false;
			door5_keypad->show();
		}
		else {
			scene3->setLight(1.0f);
			scene3_password->hide();
			scene3_lighted = true;
			door5_keypad->hide();
		}
		return true;
		});


	//게임을 시작한다.
	startGame(scene1);

	return 0;
}
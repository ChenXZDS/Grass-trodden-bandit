#include <iostream>
using namespace std;

int player_x = 0;
int player_y = 0;
int bad_x = 70;
int bad_y = 0;
int bad_speed = 3;
int seed = 133; //随机数种子
int stop = 1;
int Over_Q = 0;
int GC_add = 0;
int GC_Q = 0;
int GC_x[64];
int GC_y[64];
int GC_I = 0;
short over_time = 3;
short over_T = 0;
short D = 2;
bool IsExit = false;
bool IsOver = false;
bool IsGoodOver = false;
bool IsPlayAgain = false;
bool IsInGC = false;
bool IsInOver = false;
bool CanOver = false;
string key;
string block_p;
string block_b;
string scene[64][64];
string camera[15][15];

void Move() { //玩家移动函数
	cin >> key;
	scene[player_y][player_x] = block_p;
	if (key[0] == 'w' || key[0] == 'W') {
		player_y += -1;
	}
	if (key[0] == 'a' || key[0] == 'A') {
		player_x += -1;
	}
	if (key[0] == 's' || key[0] == 'S') {
		player_y += 1;
	}
	if (key[0] == 'd' || key[0] == 'D') {
		player_x += 1;
	}
}

void Bad_Move() { //坏人移动函数
	if(stop % bad_speed == 0){
		scene[bad_y][bad_x] = block_b;
		if (bad_x > player_x) {
			bad_x += -1;
		}
		if (bad_y > player_y) {
			bad_y += -1;
		}
		if (bad_x < player_x) {
			bad_x += 1;
		}
		if (bad_y < player_y) {
			bad_y += 1;
		}
	}
	stop++ ;
}

void Game() { //游戏逻辑函数
	int x = bad_x - player_x;
	int y = bad_y - player_y;
	IsInGC = false;
	if (x < 2 && y < 2 && x > -2 && y > -2) { //游戏结束判定
		IsOver = true;
	}
	if (player_x < 7) { //位置更正
		player_x = 7;
	}
	if (player_y < 7) {
		player_y = 7;
	}
	if (player_x > 56) {
		player_x = 56;
	}
	if (player_y > 56) {
		player_y = 56;
	}
	if (bad_x < 7) {
		bad_x = 7;
	}
	if (bad_y < 7) {
		bad_y = 7;
	}
	if (bad_x > 56) {
		bad_x = 56;
	}
	if (bad_y > 56) {
		bad_y = 56;
	}
	block_p = scene[player_y][player_x]; //角色生成
	scene[player_y][player_x] = "你";
	if((stop - 1) % bad_speed == 0){
		block_b = scene[bad_y][bad_x];
		scene[bad_y][bad_x] = "坏";
	}
	for (int i = 0; i < 64; i++) {
		if (GC_x[i] == player_x && GC_y[i] == player_y) {
			IsInGC = true;
			GC_I = i;
		}
	}
	if (key[0] == 'q' || key[0] == 'Q') {
		IsExit = true;
	}
	if (GC_Q >= Over_Q) {
		CanOver = true;
		scene[56][56] = "洞";
	}
	if (CanOver && player_x == 56 && player_y == 56 && (key[0] == 'e' || key[0] == 'E')) {
		over_T++ ;
	}
	else {
		over_T = 0;
	}
	if (over_T >= over_time) {
		IsGoodOver = true;
	}
}

void Camera() { //摄像机函数
	for (int i = 0; i < 15; i++) {
		for (int o = 0; o < 15; o++) {
			camera[i][o] = scene[i + player_y - 7][o + player_x - 7];
		}
	}
}

void Draw() { //显示画面函数
	for (int i = 0; i < 15; i++) {
		for (int o = 0; o < 15; o++) {
			cout << camera[i][o];
		}
		cout << "\n";
	}
}

void Create() { //生成物品函数
	long temp = seed;
	for (int i = 0; i < 8; i++) {
		for (int o = 0; o < 8; o++) {
			temp = (temp * seed) >> 2; //随机数生成
			if (temp % 2 == 0) {
				scene[i * 6 + 10][o * 6 + 10] = "草";
				GC_x[GC_add] = 0;
				GC_y[GC_add] = 0;
				GC_add++;
			}
			else {
				scene[i * 6 + 10][o * 6 + 10] = "金";
				GC_x[GC_add] = o * 6 + 10;
				GC_y[GC_add] = i * 6 + 10;
				GC_add++ ;
				Over_Q++;
			}
		}
	}
}

void Load() { //初始化函数
	player_x = 0;
	player_y = 0;
	bad_x = 70;
	bad_y = 0;
	GC_Q = 0;
	GC_add = 0;
	Over_Q = 0;
	over_T = 0;
	key = "z";
	IsOver = false;
	IsExit = false;
	CanOver = false;
	IsGoodOver = false;
	for (int i = 0; i < 64; i++) { //场景初始
		for (int o = 0; o < 64; o++) {
			scene[i][o] = "墙";
		}
	}
	for (int i = 0; i < 50; i++) {
		for (int o = 0; o < 50; o++) {
			scene[i + 7][o + 7] = "土";
		}
	}
	Create();
	Over_Q /= 2;
	Game();
	Camera();
	cout << "金币数量: " << GC_Q << "\t" << "目标数量:" << Over_Q << endl;
	Draw();
}

void Setting() { //设置函数
	int check = 0;
	string menu[3] = { "难度", "地图种子", "完成"};
	IsExit = false;
	while (true) {
		cout << endl;
		cout << "设置" << endl << endl;
		cout << "(输入W或S选择，输入E确认)" << endl << endl;
		for (int i = 0; i < 3; i++) {
			if (check == i) {
				cout << "[@]";
			}
			else {
				cout << "[O]";
			}
			cout << menu[i] << endl << endl;
		}
		string temp;
		cin >> temp;
		if (temp[0] == 'w' || temp[0] == 'W') {
			check--;
		}
		if (temp[0] == 's' || temp[0] == 'S') {
			check++;
		}
		if (check < 0) {
			check = 0;
		}
		if (check > 2) {
			check = 2;
		}
		if (temp[0] == 'e' || temp[0] == 'E') {
			if (check == 0) {
				string T;
				cout << endl << "请选择难度：" << "(当前难度：" << D << ")" << endl << "[1]低" << endl << "[2]中" << endl << "[3]高" << endl << "[4]取消" << endl << "(输入数字选择)" << endl;
				cin >> T;
				if (T[0] == '1') {
					bad_speed = 4;
					over_time = 2;
					D = 1;
				}
				if (T[0] == '2') {
					bad_speed = 3;
					over_time = 3;
					D = 2;
				}
				if (T[0] == '3') {
					bad_speed = 2;
					over_time = 4;
					D = 3;
				}
			}
			if (check == 1) {
				int T;
				cout << "请输入0~999内的地图种子(实验性功能，会导致地图生成出错)：" << "(当前种子：" << seed << ")";
			again:
				cin >> T;
				if (T < 0 || T > 999) {
					cout << "请输入指定范围内的种子：";
					goto again;
				}
				seed = T;
			}
			if (check == 2) {
				break;
			}
		}
	}
}

void Start() { //开始界面函数
	int check = 0;
	string menu[4] = {"开始游戏", "设置", "操作说明", "退出"};
	IsExit = false;
	while (true) {
		cout << endl;
		cout << "踩草大盗" << endl << endl;
		cout << "(输入W或S选择，输入E确认)" << endl << endl;
		for (int i = 0; i < 4; i++) {
			if (check == i) {
				cout << "[@]";
			}
			else {
				cout << "[O]";
			}
			cout << menu[i] << endl << endl;
		}
		string temp;
		cin >> temp;
		if (temp[0] == 'w' || temp[0] == 'W') {
			check--;
		}
		if (temp[0] == 's' || temp[0] == 'S') {
			check++;
		}
		if (check < 0) {
			check = 0;
		}
		if (check > 3) {
			check = 3;
		}
		if (temp[0] == 'e' || temp[0] == 'E') {
			if (check == 0) {
				break;
			}
			if (check == 1) {
				Setting();
			}
			if (check == 2) {
				cout << endl << "输入WASD移动，\n输入E拾取金币或钻入地洞，\n输入Q退出\n同时小心坏人的追捕\n\n输入任意键完成\n";
				cin >> temp;
			}
			if (check == 3) {
				IsExit = true;
				break;
			}
		}
	}
}

void Good_Over() { //游戏过关函数
	IsPlayAgain = false;
	string temp;
	cout << endl << "成功达成目标！" << "(金币数量：" << GC_Q << ")" << endl << "再来一遍？(Y/N)";
	cin >> temp;
	if (temp[0] == 'y' || temp[0] == 'Y') {
		IsPlayAgain = true;
	}
}

void Bad_Over() { //游戏失败函数
	IsPlayAgain = false;
	string temp;
	cout << endl << "你被坏人抓住了！" << endl << "再来一遍？(Y/N)";
	cin >> temp;
	if (temp[0] == 'y' || temp[0] == 'Y') {
		IsPlayAgain = true;
	}
}

int main(){
	cout << "请先进行设置：" << endl;
	Setting();
	char temp;
again:
	Start();
	if (IsExit) {
		return 0;
	}
play_again:
	Load();
	while(true){ //无限循环
		if (IsExit) {
			break;
		}
		Move();
		Bad_Move();
		Game();
		if(CanOver){
			cout << "钻入地洞(" << over_T << "/" << over_time << ")" << endl;
		}
		if (IsInGC) {
			if (key[0] == 'e' || key[0] == 'E') {
				block_p = "土";
				GC_x[GC_I] = 0;
				GC_y[GC_I] = 0;
				GC_Q++;
			}
		}
		Camera();
		cout << "金币数量: " << GC_Q << "\t" << "目标数量:" << Over_Q << endl;
		Draw();
		if (IsOver) {
			Bad_Over();
			if (IsPlayAgain) {
				goto play_again;
			}
			break;
		}
		if (IsGoodOver) {
			Good_Over();
			if (IsPlayAgain) {
				goto play_again;
			}
			break;
		}
	}
	goto again;
}
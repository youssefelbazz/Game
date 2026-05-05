#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// ---- إعدادات ----
const int W = 480, H = 600;
const float LANE_X[] = { 120, 200, 280, 360 };

// ---- متغيرات اللعبة ----
int playerLane = 1;
float playerY = 500;
float speed = 3.0f;
int score = 0;
int lives = 3;
int spawnTimer = 0;
float lineY = 0;
int invincible = 0;
bool gameOver = false;

struct Enemy {
	float x, y;
	float r, g, b;
};
std::vector<Enemy> enemies;

float enemyColors[4][3] = {
	{0.86f, 0.19f, 0.19f},
	{0.19f, 0.47f, 0.86f},
	{0.86f, 0.58f, 0.11f},
	{0.58f, 0.19f, 0.78f}
};

// ---- رسم مستطيل ----
void drawRect(float x, float y, float w, float h, float r, float g, float b) {
	float left = x - w / 2.0f;
	float right = x + w / 2.0f;
	float top = y - h / 2.0f;
	float bottom = y + h / 2.0f;

	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(left, top);
	glVertex2f(right, top);
	glVertex2f(right, bottom);
	glVertex2f(left, bottom);
	glEnd();
}

// ---- رسم سيارة ----
void drawCar(float x, float y, float r, float g, float b) {
	// جسم السيارة
	drawRect(x, y, 40, 70, r, g, b);
	// زجاج
	drawRect(x, y - 5, 30, 22, 0.39f, 0.78f, 1.0f);
	// عجلات
	drawRect(x - 22, y - 25, 10, 15, 0.12f, 0.12f, 0.12f);
	drawRect(x + 22, y - 25, 10, 15, 0.12f, 0.12f, 0.12f);
	drawRect(x - 22, y + 25, 10, 15, 0.12f, 0.12f, 0.12f);
	drawRect(x + 22, y + 25, 10, 15, 0.12f, 0.12f, 0.12f);
}

// ---- رسم نص ----
void drawText(float x, float y, const std::string& text) {
	glColor3f(1, 1, 1);
	glRasterPos2f(x, y);
	for (char c : text)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// ---- Display ----
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.09f, 0.09f, 0.15f, 1.0f);

	// الطريق
	drawRect(250, H / 2.0f, 330, H, 0.35f, 0.35f, 0.35f);

	// حواف الطريق
	drawRect(93, H / 2.0f, 6, H, 1.0f, 1.0f, 0.0f);
	drawRect(407, H / 2.0f, 6, H, 1.0f, 1.0f, 0.0f);

	// خطوط الممرات
	for (int lane = 0; lane < 3; lane++) {
		float lx = 160.0f + lane * 80.0f;
		for (int i = 0; i < 9; i++) {
			float y1 = lineY + i * 80 - 80;
			drawRect(lx, y1 + 20, 4, 40, 0.86f, 0.86f, 0.86f);
		}
	}

	// رسم الأعداء
	for (auto& e : enemies)
		drawCar(e.x, e.y, e.r, e.g, e.b);

	// رسم اللاعب
	if (invincible == 0 || (invincible / 5) % 2 == 0)
		drawCar(LANE_X[playerLane], playerY, 0.11f, 0.78f, 0.58f);

	// HUD
	drawText(10, 20, "Score: " + std::to_string(score / 10));
	drawText(160, 20, "Lives: " + std::to_string(lives));
	drawText(300, 20, "Speed: " + std::to_string((int)speed));

	if (gameOver) {
		drawText(140, 280, "GAME  OVER");
		drawText(110, 320, "Press R to Restart");
	}

	glutSwapBuffers();
}

// ---- Update ----
void update(int value) {
	if (!gameOver) {
		score++;
		if (score % 300 == 0)
			speed = std::min(speed + 0.4f, 9.0f);

		lineY += speed;
		if (lineY > 80) lineY -= 80;

		// Spawn
		spawnTimer++;
		int spawnRate = std::max(30, (int)(90 - speed * 5));
		if (spawnTimer >= spawnRate) {
			spawnTimer = 0;
			int lane = rand() % 4;
			int ci = rand() % 4;
			enemies.push_back({
				LANE_X[lane], -50,
				enemyColors[ci][0],
				enemyColors[ci][1],
				enemyColors[ci][2]
				});
		}

		// تحريك الأعداء
		for (auto& e : enemies)
			e.y += speed * 1.4f;

		// حذف الأعداء اللي طلعوا
		enemies.erase(
			std::remove_if(enemies.begin(), enemies.end(),
				[](const Enemy& e) { return e.y > H + 80; }),
			enemies.end()
		);

		// Collision
		float px = LANE_X[playerLane];
		if (invincible > 0) {
			invincible--;
		}
		else {
			for (int i = 0; i < (int)enemies.size(); i++) {
				float dx = std::abs(px - enemies[i].x);
				float dy = std::abs(playerY - enemies[i].y);
				if (dx < 30 && dy < 55) {
					lives--;
					invincible = 90;
					enemies.erase(enemies.begin() + i);
					if (lives <= 0) gameOver = true;
					break;
				}
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(16, update, 0); // ~60 FPS
}

// ---- Keyboard ----
void keyboard(unsigned char key, int x, int y) {
	if (gameOver && (key == 'r' || key == 'R')) {
		enemies.clear();
		playerLane = 1;
		score = 0;
		lives = 3;
		speed = 3.0f;
		spawnTimer = 0;
		invincible = 0;
		gameOver = false;
	}
}

void specialKeys(int key, int x, int y) {
	if (gameOver) return;
	if (key == GLUT_KEY_LEFT && playerLane > 0) playerLane--;
	if (key == GLUT_KEY_RIGHT && playerLane < 3) playerLane++;
}

// ---- Main ----
int main(int argc, char** argv) {
	srand((unsigned)time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(W, H);
	glutCreateWindow("Car Racing - OpenGL");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, W, H, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(display);
	glutTimerFunc(16, update, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);

	glutMainLoop();
	return 0;
}
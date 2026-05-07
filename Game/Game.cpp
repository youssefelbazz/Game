#pragma region Old CodeCar
//#include <GL/glut.h>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//#include <string>
////////////////////////////////////////////////////////////////الكود القديم///////////////////// Car Racing Game - OpenGL
//// ---- إعدادات ----
//const int W = 480, H = 600;
//const float LANE_X[] = { 120, 200, 280, 360 };
//
//// ---- متغيرات اللعبة ----
//int playerLane = 1;
//float playerY = 500;
//float speed = 3.0f;
//int score = 0;
//int lives = 4;
//int spawnTimer = 0;
//float lineY = 0;
//int invincible = 0;
//bool gameOver = false;
//
//struct Enemy {
//	float x, y;
//	float r, g, b;
//};
//std::vector<Enemy> enemies;
//
//float enemyColors[4][3] = {
//	{0.86f, 0.19f, 0.19f},
//	{0.19f, 0.47f, 0.86f},
//	{0.86f, 0.58f, 0.11f},
//	{0.58f, 0.19f, 0.78f}
//};
//
//// ---- رسم مستطيل ----
//void drawRect(float x, float y, float w, float h, float r, float g, float b) {
//	float left = x - w / 2.0f;
//	float right = x + w / 2.0f;
//	float top = y - h / 2.0f;
//	float bottom = y + h / 2.0f;
//
//	glColor3f(r, g, b);
//	glBegin(GL_QUADS);
//	glVertex2f(left, top);
//	glVertex2f(right, top);
//	glVertex2f(right, bottom);
//	glVertex2f(left, bottom);
//	glEnd();
//}
//
//// ---- رسم سيارة ----
//void drawCar(float x, float y, float r, float g, float b) {
//	// جسم السيارة
//	drawRect(x, y, 40, 70, r, g, b);
//	// زجاج
//	drawRect(x, y - 5, 30, 22, 0.39f, 0.78f, 1.0f);
//	// عجلات
//	drawRect(x - 22, y - 25, 10, 15, 0.12f, 0.12f, 0.12f);
//	drawRect(x + 22, y - 25, 10, 15, 0.12f, 0.12f, 0.12f);
//	drawRect(x - 22, y + 25, 10, 15, 0.12f, 0.12f, 0.12f);
//	drawRect(x + 22, y + 25, 10, 15, 0.12f, 0.12f, 0.12f);
//}
//
//// ---- رسم نص ----
//void drawText(float x, float y, const std::string& text) {
//	glColor3f(1, 1, 1);
//	glRasterPos2f(x, y);
//	for (char c : text)
//		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//}
//
//// ---- Display ----
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glClearColor(0.09f, 0.09f, 0.15f, 1.0f);
//
//	// الطريق
//	drawRect(250, H / 2.0f, 330, H, 0.35f, 0.35f, 0.35f);
//
//	// حواف الطريق
//	drawRect(93, H / 2.0f, 6, H, 1.0f, 1.0f, 0.0f);
//	drawRect(407, H / 2.0f, 6, H, 1.0f, 1.0f, 0.0f);
//
//	// خطوط الممرات
//	for (int lane = 0; lane < 3; lane++) {
//		float lx = 160.0f + lane * 80.0f;
//		for (int i = 0; i < 9; i++) {
//			float y1 = lineY + i * 80 - 80;
//			drawRect(lx, y1 + 20, 4, 40, 0.86f, 0.86f, 0.86f);
//		}
//	}
//
//	// رسم الأعداء
//	for (auto& e : enemies)
//		drawCar(e.x, e.y, e.r, e.g, e.b);
//
//	// رسم اللاعب
//	if (invincible == 0 || (invincible / 5) % 2 == 0)
//		drawCar(LANE_X[playerLane], playerY, 0.11f, 0.78f, 0.58f);
//
//	// HUD
//	drawText(10, 20, "Score: " + std::to_string(score / 10));
//	drawText(160, 20, "Lives: " + std::to_string(lives));
//	drawText(300, 20, "Speed: " + std::to_string((int)speed));
//
//	if (gameOver) {
//		drawText(140, 280, "GAME  OVER");
//		drawText(110, 320, "Press R to Restart");
//	}
//
//	glutSwapBuffers();
//}
//
//// ---- Update ----
//void update(int value) {
//	if (!gameOver) {
//		score++;
//		if (score % 300 == 0)
//			speed = std::min(speed + 0.4f, 9.0f);
//
//		lineY += speed;
//		if (lineY > 80) lineY -= 80;
//
//		// Spawn
//		spawnTimer++;
//		int spawnRate = std::max(30, (int)(90 - speed * 5));
//		if (spawnTimer >= spawnRate) {
//			spawnTimer = 0;
//			int lane = rand() % 4;
//			int ci = rand() % 4;
//			enemies.push_back({
//				LANE_X[lane], -50,
//				enemyColors[ci][0],
//				enemyColors[ci][1],
//				enemyColors[ci][2]
//				});
//		}
//
//		// تحريك الأعداء
//		for (auto& e : enemies)
//			e.y += speed * 1.4f;
//
//		// حذف الأعداء اللي طلعوا
//		enemies.erase(
//			std::remove_if(enemies.begin(), enemies.end(),
//				[](const Enemy& e) { return e.y > H + 80; }),
//			enemies.end()
//		);
//
//		// Collision
//		float px = LANE_X[playerLane];
//		if (invincible > 0) {
//			invincible--;
//		}
//		else {
//			for (int i = 0; i < (int)enemies.size(); i++) {
//				float dx = std::abs(px - enemies[i].x);
//				float dy = std::abs(playerY - enemies[i].y);
//				if (dx < 30 && dy < 55) {
//					lives--;
//					invincible = 90;
//					enemies.erase(enemies.begin() + i);
//					if (lives <= 0) gameOver = true;
//					break;
//				}
//			}
//		}
//	}
//
//	glutPostRedisplay();
//	glutTimerFunc(16, update, 0); // ~60 FPS
//}
//
//// ---- Keyboard ----
//void keyboard(unsigned char key, int x, int y) {
//	if (gameOver && (key == 'r' || key == 'R')) {
//		enemies.clear();
//		playerLane = 1;
//		score = 0;
//		lives = 3;
//		speed = 3.0f;
//		spawnTimer = 0;
//		invincible = 0;
//		gameOver = false;
//	}
//}
//
//void specialKeys(int key, int x, int y) {
//	if (gameOver) return;
//	if (key == GLUT_KEY_LEFT && playerLane > 0) playerLane--;
//	if (key == GLUT_KEY_RIGHT && playerLane < 3) playerLane++;
//}
//
//// ---- Main ----
//int main(int argc, char** argv) {
//	srand((unsigned)time(0));
//
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(W, H);
//	glutCreateWindow("Car Racing - OpenGL");
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, W, H, 0, -1, 1);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glutDisplayFunc(display);
//	glutTimerFunc(16, update, 0);
//	glutKeyboardFunc(keyboard);
//	glutSpecialFunc(specialKeys);
//
//	glutMainLoop();
//	return 0;
//}  
#pragma endregion

#pragma region NewCodeCar

//#include <GL/glut.h>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//#include <string>
//#include <cmath>   // عشان sin() في تأثير الومضان
//
//// ================================================================
////  إعدادات النافذة والطريق
//// ================================================================
//const int W = 480, H = 600;                          // عرض وطول النافذة
//const float LANE_X[] = { 120, 200, 280, 360 };       // مراكز الـ 4 ممرات على محور X
//const int   TOTAL_LANES = 4;                          // عدد الممرات
//
//// ================================================================
////  متغيرات اللعبة
//// ================================================================
//int   playerLane = 1;      // رقم الممر الحالي للاعب (0 → 3)
//float playerY = 500;    // موضع اللاعب على محور Y (ثابت)
//float speed = 3.0f;   // سرعة اللعبة (بتزيد مع الوقت)
//int   score = 0;      // النقاط (بتتزاد كل frame)
//int   lives = 3;      // عدد الحيوات
//int   spawnTimer = 0;      // عداد لحساب امتى يطلع عدو جديد
//float lineY = 0;      // موضع خطوط الطريق المتحركة
//int   invincible = 0;      // عداد فترة الـ invincibility بعد الاصطدام
//bool  gameOver = false;  // هل اللعبة انتهت؟
//int   highScore = 0;      // أعلى نقطة وصلها اللاعب
//
//// ================================================================
////  هيكل العدو
//// ================================================================
//struct Enemy {
//    float x, y;       // موضع العدو
//    float r, g, b;    // لون العدو
//    float width = 40, height = 70;  // حجم العدو
//};
//std::vector<Enemy> enemies;   // قائمة الأعداء الموجودين على الشاشة
//
//// ================================================================
////  ألوان الأعداء (4 ألوان مختلفة)
//// ================================================================
//float enemyColors[4][3] = {
//    {0.86f, 0.19f, 0.19f},   // أحمر
//    {0.19f, 0.47f, 0.86f},   // أزرق
//    {0.86f, 0.58f, 0.11f},   // برتقالي
//    {0.58f, 0.19f, 0.78f}    // بنفسجي
//};
//
//// ================================================================
////  رسم مستطيل ملون بـ OpenGL
////  x,y = المركز | w,h = العرض والطول | r,g,b = اللون
//// ================================================================
//void drawRect(float x, float y, float w, float h,
//    float r, float g, float b, float alpha = 1.0f) {
//    // حساب حواف المستطيل من المركز
//    float left = x - w / 2.0f;
//    float right = x + w / 2.0f;
//    float top = y - h / 2.0f;
//    float bottom = y + h / 2.0f;
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glColor4f(r, g, b, alpha);   // تحديد اللون مع الشفافية
//
//    // رسم المستطيل كـ Quad (4 نقاط)
//    glBegin(GL_QUADS);
//    glVertex2f(left, top);       // فوق شمال
//    glVertex2f(right, top);       // فوق يمين
//    glVertex2f(right, bottom);    // تحت يمين
//    glVertex2f(left, bottom);    // تحت شمال
//    glEnd();
//
//    // رسم حواف المستطيل عشان يبقى أوضح
//    glColor4f(0, 0, 0, 0.3f);
//    glLineWidth(1.5f);
//    glBegin(GL_LINE_LOOP);
//    glVertex2f(left, top);
//    glVertex2f(right, top);
//    glVertex2f(right, bottom);
//    glVertex2f(left, bottom);
//    glEnd();
//}
//
//// ================================================================
////  رسم دائرة (للعجلات)
////  cx,cy = المركز | radius = نصف القطر | segments = عدد الأضلاع
//// ================================================================
//void drawCircle(float cx, float cy, float radius,
//    float r, float g, float b, int segments = 16) {
//    glColor3f(r, g, b);
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(cx, cy);   // المركز
//    for (int i = 0; i <= segments; i++) {
//        // حساب نقاط الدائرة باستخدام sin و cos
//        float angle = 2.0f * 3.14159f * i / segments;
//        glVertex2f(cx + radius * cos(angle),
//            cy + radius * sin(angle));
//    }
//    glEnd();
//}
//
//// ================================================================
////  رسم السيارة
////  x,y = المركز | r,g,b = لون الجسم | flip = عكس الاتجاه للأعداء
//// ================================================================
//void drawCar(float x, float y, float r, float g, float b, bool flip = false) {
//    float dir = flip ? -1.0f : 1.0f;   // اتجاه السيارة
//
//    // --- جسم السيارة الرئيسي ---
//    drawRect(x, y, 40, 70, r, g, b);
//
//    // --- سقف السيارة (أغمق شوية) ---
//    drawRect(x, y - 5 * dir, 26, 25, r * 0.7f, g * 0.7f, b * 0.7f);
//
//    // --- زجاج أمامي ---
//    drawRect(x, y - 12 * dir, 22, 12, 0.6f, 0.85f, 1.0f, 0.85f);
//
//    // --- زجاج خلفي ---
//    drawRect(x, y + 8 * dir, 22, 10, 0.6f, 0.85f, 1.0f, 0.6f);
//
//    // --- العجلات (دوايل) ---
//    drawCircle(x - 22, y - 20 * dir, 7, 0.15f, 0.15f, 0.15f);
//    drawCircle(x + 22, y - 20 * dir, 7, 0.15f, 0.15f, 0.15f);
//    drawCircle(x - 22, y + 20 * dir, 7, 0.15f, 0.15f, 0.15f);
//    drawCircle(x + 22, y + 20 * dir, 7, 0.15f, 0.15f, 0.15f);
//
//    // --- جنط العجلات (دوايل أصغر فاتحة) ---
//    drawCircle(x - 22, y - 20 * dir, 3.5f, 0.7f, 0.7f, 0.7f);
//    drawCircle(x + 22, y - 20 * dir, 3.5f, 0.7f, 0.7f, 0.7f);
//    drawCircle(x - 22, y + 20 * dir, 3.5f, 0.7f, 0.7f, 0.7f);
//    drawCircle(x + 22, y + 20 * dir, 3.5f, 0.7f, 0.7f, 0.7f);
//
//    // --- أضواء أمامية (صفراء) ---
//    drawRect(x - 12, y - 33 * dir, 10, 5, 1.0f, 1.0f, 0.3f);
//    drawRect(x + 12, y - 33 * dir, 10, 5, 1.0f, 1.0f, 0.3f);
//
//    // --- أضواء خلفية (حمراء) ---
//    drawRect(x - 12, y + 33 * dir, 10, 5, 1.0f, 0.2f, 0.2f);
//    drawRect(x + 12, y + 33 * dir, 10, 5, 1.0f, 0.2f, 0.2f);
//}
//
//// ================================================================
////  رسم نص على الشاشة
//// ================================================================
//void drawText(float x, float y, const std::string& text,
//    float r = 1, float g = 1, float b = 1) {
//    glColor3f(r, g, b);
//    glRasterPos2f(x, y);
//    for (char c : text)
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//}
//
//// ================================================================
////  رسم شريط الـ HUD (النقاط والحيوات)
//// ================================================================
//void drawHUD() {
//    // خلفية شبه شفافة للـ HUD
//    drawRect(240, 18, 480, 36, 0.0f, 0.0f, 0.0f, 0.5f);
//
//    // النقاط
//    drawText(10, 23, "Score: " + std::to_string(score / 10), 1.0f, 1.0f, 0.3f);
//
//    // أعلى نقطة
//    drawText(150, 23, "Best: " + std::to_string(highScore / 10), 0.3f, 1.0f, 0.8f);
//
//    // الحيوات (قلوب)
//    std::string heartsStr = "Lives: ";
//    for (int i = 0; i < lives; i++) heartsStr += "<3 ";
//    drawText(300, 23, heartsStr, 1.0f, 0.3f, 0.3f);
//
//    // السرعة
//    drawText(390, 23, "Spd:" + std::to_string((int)speed), 0.8f, 0.8f, 0.8f);
//}
//
//// ================================================================
////  شاشة Game Over
//// ================================================================
//void drawGameOver() {
//    // خلفية داكنة شفافة
//    drawRect(240, 300, 480, 600, 0.0f, 0.0f, 0.0f, 0.65f);
//
//    drawText(160, 260, "GAME  OVER", 1.0f, 0.2f, 0.2f);
//    drawText(100, 300, "Score: " + std::to_string(score / 10), 1.0f, 1.0f, 0.3f);
//    drawText(100, 330, "Best:  " + std::to_string(highScore / 10), 0.3f, 1.0f, 0.8f);
//    drawText(110, 370, "Press R to Restart", 0.8f, 0.8f, 0.8f);
//}
//
//// ================================================================
////  دالة الرسم الرئيسية (بتتشاغل كل frame)
//// ================================================================
//void display() {
//    glClearColor(0.09f, 0.09f, 0.15f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // --- رسم العشب على الجانبين ---
//    drawRect(45, H / 2.0f, 90, H, 0.13f, 0.35f, 0.13f);
//    drawRect(435, H / 2.0f, 90, H, 0.13f, 0.35f, 0.13f);
//
//    // --- رسم الطريق الرمادي ---
//    drawRect(250, H / 2.0f, 330, H, 0.30f, 0.30f, 0.30f);
//
//    // --- حواف الطريق الصفراء ---
//    drawRect(93, H / 2.0f, 6, H, 1.0f, 1.0f, 0.0f);
//    drawRect(407, H / 2.0f, 6, H, 1.0f, 1.0f, 0.0f);
//
//    // --- خطوط الممرات المتحركة ---
//    for (int lane = 0; lane < 3; lane++) {
//        float lx = 160.0f + lane * 80.0f;
//        for (int i = 0; i < 9; i++) {
//            float y1 = lineY + i * 80 - 80;
//            // خط أبيض متقطع
//            drawRect(lx, y1 + 20, 3, 35, 0.9f, 0.9f, 0.9f, 0.7f);
//        }
//    }
//
//    // --- رسم الأعداء (مقلوبين عشان واجهتهم للأسفل) ---
//    for (auto& e : enemies)
//        drawCar(e.x, e.y, e.r, e.g, e.b, true);
//
//    // --- رسم اللاعب مع تأثير الومضان لما يتضرب ---
//    if (invincible == 0 || (invincible / 5) % 2 == 0)
//        drawCar(LANE_X[playerLane], playerY, 0.11f, 0.78f, 0.58f);
//
//    // --- رسم الـ HUD ---
//    drawHUD();
//
//    // --- شاشة Game Over ---
//    if (gameOver)
//        drawGameOver();
//
//    glutSwapBuffers();   // عرض الـ frame الجديد
//}
//
//// ================================================================
////  دالة التحديث (بتتشاغل كل 16ms ≈ 60 FPS)
//// ================================================================
//void update(int value) {
//    if (!gameOver) {
//
//        // زيادة النقاط كل frame
//        score++;
//
//        // تحديث أعلى نقطة
//        if (score > highScore) highScore = score;
//
//        // زيادة السرعة كل 300 frame
//        if (score % 300 == 0)
//            speed = std::min(speed + 0.4f, 9.0f);
//
//        // تحريك خطوط الطريق للأسفل (وهم الحركة)
//        lineY += speed;
//        if (lineY > 80) lineY -= 80;
//
//        // ---- Spawn أعداء جدد ----
//        spawnTimer++;
//        // كلما زادت السرعة، كلما قل وقت الـ spawn
//        int spawnRate = std::max(30, (int)(90 - speed * 5));
//        if (spawnTimer >= spawnRate) {
//            spawnTimer = 0;
//            int lane = rand() % TOTAL_LANES;   // ممر عشوائي
//            int ci = rand() % 4;             // لون عشوائي
//            enemies.push_back({
//                LANE_X[lane], -50,             // يبدأ من فوق الشاشة
//                enemyColors[ci][0],
//                enemyColors[ci][1],
//                enemyColors[ci][2]
//                });
//        }
//
//        // ---- تحريك الأعداء للأسفل ----
//        for (auto& e : enemies)
//            e.y += speed * 1.4f;
//
//        // ---- حذف الأعداء اللي عدوا تحت الشاشة ----
//        enemies.erase(
//            std::remove_if(enemies.begin(), enemies.end(),
//                [](const Enemy& e) { return e.y > H + 80; }),
//            enemies.end()
//        );
//
//        // ---- كشف التصادم ----
//        float px = LANE_X[playerLane];
//        if (invincible > 0) {
//            invincible--;   // تنقيص عداد الـ invincibility
//        }
//        else {
//            for (int i = 0; i < (int)enemies.size(); i++) {
//                float dx = std::abs(px - enemies[i].x);
//                float dy = std::abs(playerY - enemies[i].y);
//                // لو المسافة أقل من نص عرض + نص طول السيارتين
//                if (dx < 30 && dy < 55) {
//                    lives--;
//                    invincible = 90;               // 90 frame invincible
//                    enemies.erase(enemies.begin() + i);
//                    if (lives <= 0) gameOver = true;
//                    break;
//                }
//            }
//        }
//    }
//
//    glutPostRedisplay();              // طلب رسم frame جديد
//    glutTimerFunc(16, update, 0);     // استدعاء نفسها بعد 16ms
//}
//
//// ================================================================
////  دالة الكيبورد (حروف عادية)
//// ================================================================
//void keyboard(unsigned char key, int x, int y) {
//    // إعادة اللعبة لما يضغط R
//    if (gameOver && (key == 'r' || key == 'R')) {
//        enemies.clear();
//        playerLane = 1;
//        score = 0;
//        lives = 3;
//        speed = 3.0f;
//        spawnTimer = 0;
//        invincible = 0;
//        gameOver = false;
//    }
//    // إغلاق اللعبة بـ ESC
//    if (key == 27) exit(0);
//}
//
//// ================================================================
////  دالة الأسهم (Left / Right للتنقل بين الممرات)
//// ================================================================
//void specialKeys(int key, int x, int y) {
//    if (gameOver) return;
//    if (key == GLUT_KEY_LEFT && playerLane > 0) playerLane--;
//    if (key == GLUT_KEY_RIGHT && playerLane < 3) playerLane++;
//}
//
//// ================================================================
////  Main
//// ================================================================
//int main(int argc, char** argv) {
//    srand((unsigned)time(0));   // عشوائية مختلفة كل مرة
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // Double buffering
//    glutInitWindowSize(W, H);
//    glutInitWindowPosition(400, 100);              // موضع النافذة على الشاشة
//    glutCreateWindow("Car Racing - OpenGL");
//
//    // إعداد إحداثيات OpenGL 2D
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, W, H, 0, -1, 1);   // (0,0) في الركن العلوي الشمالي
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    // ربط الدوال بـ GLUT
//    glutDisplayFunc(display);        // دالة الرسم
//    glutTimerFunc(16, update, 0);    // دالة التحديث
//    glutKeyboardFunc(keyboard);      // كيبورد عادي
//    glutSpecialFunc(specialKeys);    // أسهم الكيبورد
//
//    glutMainLoop();   // بدء الـ game loop
//    return 0;
//}
//



#pragma endregion

#pragma region Brick Breake
//#include <GL/glut.h>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//#include <string>
//#include <cmath>
//
//// ================================================================
////  إعدادات النافذة
//// ================================================================
//const int W = 700, H = 800;
//
//// ================================================================
////  إعدادات اللعبة
//// ================================================================
//const int BRICK_ROWS = 6;    // عدد صفوف الطوب
//const int BRICK_COLS = 10;   // عدد أعمدة الطوب
//const float BRICK_W = 60.0f;
//const float BRICK_H = 25.0f;
//const float BRICK_PAD = 5.0f; // مسافة بين الطوب
//
//// ================================================================
////  متغيرات اللعبة
//// ================================================================
//float paddleX = W / 2.0f;    // موضع المضرب
//float paddleW = 100.0f;      // عرض المضرب
//float paddleH = 15.0f;       // طول المضرب
//float paddleY = H - 50.0f;   // موضع المضرب على Y
//
//float ballX = W / 2.0f;    // موضع الكورة X
//float ballY = H - 100.0f;  // موضع الكورة Y
//float ballR = 10.0f;       // نصف قطر الكورة
//float ballVX = 4.0f;        // سرعة الكورة X
//float ballVY = -4.0f;       // سرعة الكورة Y (للأعلى)
//bool  ballLaunched = false;   // هل الكورة انطلقت؟
//
//int   score = 0;
//int   lives = 3;
//int   level = 1;
//bool  gameOver = false;
//bool  won = false;
//
//// ================================================================
////  هيكل الطوبة
//// ================================================================
//struct Brick {
//    float x, y;       // موضع الطوبة
//    bool  alive;      // هل لسه موجودة؟
//    float r, g, b;    // لونها
//    int   hits;       // كام ضربة محتاجة عشان تتكسر
//};
//std::vector<Brick> bricks;
//
//// ================================================================
////  ألوان الصفوف
//// ================================================================
//float rowColors[6][3] = {
//    {0.9f, 0.2f, 0.2f},   // أحمر
//    {0.9f, 0.5f, 0.1f},   // برتقالي
//    {0.9f, 0.9f, 0.1f},   // أصفر
//    {0.2f, 0.8f, 0.2f},   // أخضر
//    {0.2f, 0.5f, 0.9f},   // أزرق
//    {0.7f, 0.2f, 0.9f}    // بنفسجي
//};
//
//// ================================================================
////  إنشاء الطوب
//// ================================================================
//void initBricks() {
//    bricks.clear();
//    float startX = (W - (BRICK_COLS * (BRICK_W + BRICK_PAD))) / 2.0f + BRICK_W / 2.0f;
//    float startY = 80.0f;
//
//    for (int row = 0; row < BRICK_ROWS; row++) {
//        for (int col = 0; col < BRICK_COLS; col++) {
//            Brick b;
//            b.x = startX + col * (BRICK_W + BRICK_PAD);
//            b.y = startY + row * (BRICK_H + BRICK_PAD);
//            b.alive = true;
//            b.r = rowColors[row][0];
//            b.g = rowColors[row][1];
//            b.b = rowColors[row][2];
//            // الصفوف الأولى محتاجة ضربتين
//            b.hits = (row < 2) ? 2 : 1;
//            bricks.push_back(b);
//        }
//    }
//}
//
//// ================================================================
////  إعادة تعيين الكورة
//// ================================================================
//void resetBall() {
//    ballX = paddleX;
//    ballY = paddleY - ballR - 5;
//    ballVX = 4.0f + level * 0.5f;
//    ballVY = -(4.0f + level * 0.5f);
//    ballLaunched = false;
//}
//
//// ================================================================
////  رسم مستطيل
//// ================================================================
//void drawRect(float x, float y, float w, float h,
//    float r, float g, float b, float alpha = 1.0f) {
//    float left = x - w / 2.0f;
//    float right = x + w / 2.0f;
//    float top = y - h / 2.0f;
//    float bottom = y + h / 2.0f;
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glColor4f(r, g, b, alpha);
//    glBegin(GL_QUADS);
//    glVertex2f(left, top);
//    glVertex2f(right, top);
//    glVertex2f(right, bottom);
//    glVertex2f(left, bottom);
//    glEnd();
//
//    // حواف
//    glColor4f(1, 1, 1, 0.2f);
//    glLineWidth(1.0f);
//    glBegin(GL_LINE_LOOP);
//    glVertex2f(left, top);
//    glVertex2f(right, top);
//    glVertex2f(right, bottom);
//    glVertex2f(left, bottom);
//    glEnd();
//}
//
//// ================================================================
////  رسم دائرة (الكورة)
//// ================================================================
//void drawCircle(float cx, float cy, float radius,
//    float r, float g, float b, int segments = 32) {
//    glColor3f(r, g, b);
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(cx, cy);
//    for (int i = 0; i <= segments; i++) {
//        float angle = 2.0f * 3.14159f * i / segments;
//        glVertex2f(cx + radius * cosf(angle),
//            cy + radius * sinf(angle));
//    }
//    glEnd();
//
//    // حافة الكورة
//    glColor3f(1, 1, 1);
//    glLineWidth(1.5f);
//    glBegin(GL_LINE_LOOP);
//    for (int i = 0; i <= segments; i++) {
//        float angle = 2.0f * 3.14159f * i / segments;
//        glVertex2f(cx + radius * cosf(angle),
//            cy + radius * sinf(angle));
//    }
//    glEnd();
//}
//
//// ================================================================
////  رسم نص
//// ================================================================
//void drawText(float x, float y, const std::string& text,
//    float r = 1, float g = 1, float b = 1) {
//    glColor3f(r, g, b);
//    glRasterPos2f(x, y);
//    for (char c : text)
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//}
//
//// ================================================================
////  دالة الرسم الرئيسية
//// ================================================================
//void display() {
//    glClearColor(0.08f, 0.08f, 0.15f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // ---- رسم الطوب ----
//    for (auto& b : bricks) {
//        if (!b.alive) continue;
//        // لو محتاج ضربتين → أغمق شوية
//        float mul = (b.hits == 2) ? 1.0f : 0.7f;
//        drawRect(b.x, b.y, BRICK_W, BRICK_H,
//            b.r * mul, b.g * mul, b.b * mul);
//        // لو محتاج ضربتين → ارسم علامة
//        if (b.hits == 2)
//            drawText(b.x - 4, b.y + 6, "2", 1, 1, 1);
//    }
//
//    // ---- رسم المضرب ----
//    drawRect(paddleX, paddleY, paddleW, paddleH,
//        0.3f, 0.7f, 1.0f);
//
//    // ---- رسم الكورة ----
//    drawCircle(ballX, ballY, ballR, 1.0f, 0.9f, 0.3f);
//
//    // ---- HUD ----
//    drawRect(W / 2.0f, 15, W, 30, 0, 0, 0, 0.5f);
//    drawText(10, 20, "Score: " + std::to_string(score),
//        1.0f, 1.0f, 0.3f);
//    drawText(W / 2 - 40, 20, "Level: " + std::to_string(level),
//        0.3f, 1.0f, 0.8f);
//    std::string livesStr = "Lives: ";
//    for (int i = 0; i < lives; i++) livesStr += "<3 ";
//    drawText(W - 160, 20, livesStr, 1.0f, 0.3f, 0.3f);
//
//    // ---- رسالة الإطلاق ----
//    if (!ballLaunched && !gameOver && !won)
//        drawText(W / 2 - 100, H - 80, "Press SPACE to launch!", 0.8f, 0.8f, 0.8f);
//
//    // ---- Game Over ----
//    if (gameOver) {
//        drawRect(W / 2.0f, H / 2.0f, 400, 200, 0, 0, 0, 0.75f);
//        drawText(W / 2 - 70, H / 2 - 30, "GAME OVER", 1.0f, 0.2f, 0.2f);
//        drawText(W / 2 - 80, H / 2 + 10, "Score: " + std::to_string(score), 1, 1, 0.3f);
//        drawText(W / 2 - 100, H / 2 + 50, "Press R to Restart", 0.8f, 0.8f, 0.8f);
//    }
//
//    // ---- You Win ----
//    if (won) {
//        drawRect(W / 2.0f, H / 2.0f, 400, 200, 0, 0, 0, 0.75f);
//        drawText(W / 2 - 60, H / 2 - 30, "YOU WIN!", 0.2f, 1.0f, 0.4f);
//        drawText(W / 2 - 80, H / 2 + 10, "Score: " + std::to_string(score), 1, 1, 0.3f);
//        drawText(W / 2 - 100, H / 2 + 50, "Press R to Restart", 0.8f, 0.8f, 0.8f);
//    }
//
//    glutSwapBuffers();
//}
//
//// ================================================================
////  دالة التحديث
//// ================================================================
//void update(int value) {
//    if (!gameOver && !won) {
//
//        // ---- لو الكورة لسه مش انطلقت تتبع المضرب ----
//        if (!ballLaunched) {
//            ballX = paddleX;
//            ballY = paddleY - ballR - 5;
//        }
//        else {
//
//            // ---- تحريك الكورة ----
//            ballX += ballVX;
//            ballY += ballVY;
//
//            // ---- ارتداد من الجدران ----
//            if (ballX - ballR < 0) {
//                ballX = ballR;
//                ballVX = fabsf(ballVX);   // اتجاه يمين
//            }
//            if (ballX + ballR > W) {
//                ballX = W - ballR;
//                ballVX = -fabsf(ballVX);  // اتجاه شمال
//            }
//            if (ballY - ballR < 30) {     // سقف (بعد الـ HUD)
//                ballY = 30 + ballR;
//                ballVY = fabsf(ballVY);   // اتجاه أسفل
//            }
//
//            // ---- الكورة وقعت تحت ----
//            if (ballY + ballR > H) {
//                lives--;
//                if (lives <= 0)
//                    gameOver = true;
//                else
//                    resetBall();
//            }
//
//            // ---- ارتداد من المضرب ----
//            if (ballY + ballR >= paddleY - paddleH / 2.0f &&
//                ballY + ballR <= paddleY + paddleH / 2.0f &&
//                ballX >= paddleX - paddleW / 2.0f &&
//                ballX <= paddleX + paddleW / 2.0f &&
//                ballVY > 0)
//            {
//                // زاوية الارتداد حسب مكان الضربة على المضرب
//                float hitPos = (ballX - paddleX) / (paddleW / 2.0f);
//                ballVX = hitPos * 6.0f;
//                ballVY = -fabsf(ballVY);
//                ballY = paddleY - paddleH / 2.0f - ballR;
//            }
//
//            // ---- ارتداد من الطوب ----
//            for (auto& b : bricks) {
//                if (!b.alive) continue;
//
//                float left = b.x - BRICK_W / 2.0f;
//                float right = b.x + BRICK_W / 2.0f;
//                float top = b.y - BRICK_H / 2.0f;
//                float bottom = b.y + BRICK_H / 2.0f;
//
//                // هل الكورة لاصقة بالطوبة؟
//                if (ballX + ballR > left && ballX - ballR < right &&
//                    ballY + ballR > top && ballY - ballR < bottom) {
//
//                    b.hits--;
//                    if (b.hits <= 0) {
//                        b.alive = false;
//                        score += 10 * level;
//                    }
//
//                    // تحديد اتجاه الارتداد
//                    float overlapLeft = ballX + ballR - left;
//                    float overlapRight = right - (ballX - ballR);
//                    float overlapTop = ballY + ballR - top;
//                    float overlapBottom = bottom - (ballY - ballR);
//
//                    float minOverlap = fminf(fminf(overlapLeft, overlapRight),
//                        fminf(overlapTop, overlapBottom));
//
//                    if (minOverlap == overlapTop || minOverlap == overlapBottom)
//                        ballVY = -ballVY;
//                    else
//                        ballVX = -ballVX;
//
//                    break;
//                }
//            }
//
//            // ---- هل كل الطوب اتكسر؟ ----
//            bool allDead = true;
//            for (auto& b : bricks)
//                if (b.alive) { allDead = false; break; }
//
//            if (allDead) {
//                level++;
//                initBricks();
//                resetBall();
//                paddleW = fmaxf(paddleW - 10.0f, 50.0f); // المضرب بيصغر كل level
//            }
//        }
//    }
//
//    glutPostRedisplay();
//    glutTimerFunc(16, update, 0);
//}
//
//// ================================================================
////  حركة الماوس للمضرب
//// ================================================================
//void mouseMove(int x, int y) {
//    paddleX = (float)x;
//    // تأكد إن المضرب ميخرجش برا الشاشة
//    if (paddleX - paddleW / 2.0f < 0)   paddleX = paddleW / 2.0f;
//    if (paddleX + paddleW / 2.0f > W)   paddleX = W - paddleW / 2.0f;
//}
//
//// ================================================================
////  Keyboard
//// ================================================================
//void keyboard(unsigned char key, int x, int y) {
//    // إطلاق الكورة
//    if (key == ' ' && !ballLaunched && !gameOver && !won)
//        ballLaunched = true;
//
//    // إعادة اللعبة
//    if ((key == 'r' || key == 'R') && (gameOver || won)) {
//        score = 0;
//        lives = 3;
//        level = 1;
//        gameOver = false;
//        won = false;
//        paddleW = 100.0f;
//        paddleX = W / 2.0f;
//        initBricks();
//        resetBall();
//    }
//
//    if (key == 27) exit(0);  // ESC للخروج
//}
//
//// ================================================================
////  Main
//// ================================================================
//int main(int argc, char** argv) {
//    srand((unsigned)time(0));
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(W, H);
//    glutInitWindowPosition(300, 50);
//    glutCreateWindow("Brick Breaker - OpenGL");
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, W, H, 0, -1, 1);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    initBricks();
//    resetBall();
//
//    glutDisplayFunc(display);
//    glutTimerFunc(16, update, 0);
//    glutKeyboardFunc(keyboard);
//    glutPassiveMotionFunc(mouseMove);  // تحريك المضرب بالماوس
//    glutMotionFunc(mouseMove);
//
//    glutMainLoop();
//    return 0;
//}

#pragma endregion









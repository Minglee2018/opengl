#include <main.h>
#include <GlobalDeclarations.h>

void house1();
void house(float x, float y, float z); 
void stand(float x, float y, float z);
void apart(float, float, float);
float  h = 5, h1 = 6, d1 = 4, g = 1, g1 = 2;


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH) - 100, glutGet(GLUT_SCREEN_HEIGHT) - 100);
	glutInitWindowPosition(50, 50);

	//Create the window
	glutCreateWindow("Tanks!");
	initRendering();

	//Set handler functions
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleKeyUp);
	glutMotionFunc(handleActiveMouse);
	glutPassiveMotionFunc(handlePassiveMouse);
	glutReshapeFunc(handleResize);
	glutIgnoreKeyRepeat(true);
	if (isFullscreen) {
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	glutMouseFunc(playerFire);
	glutIgnoreKeyRepeat(1);

	playerTank = new Tank(0.0f, 0.0f, 0.0f);
	playerTank->setHealth(playerHealth);
	playerTank->setShieldStrength(10);

	srand(time(0));

	for (int i = 0; i < numObstacles; i++) {
		int x = 0;
		int z = 0;
		int r = 0;
		while (distanceBetween(0, 0, x, z) < 10) {
			x = rand() % (2 * mapSize) - mapSize;
			z = rand() % (2 * mapSize) - mapSize;
			r = rand() % 5 + 2;
		}
		createObstacle(float(x), float(z), float(r));
	}

	for (int i = 0; i < numTanks; i++) {
		int x = 0;
		int z = 0;
		while (distanceBetween(0, 0, x, z) < 20) {
			x = rand() % (2 * mapSize) - mapSize;
			z = rand() % (2 * mapSize) - mapSize;
		}
		createTank(float(x), float(z));
		if (!tanks[i]->canMoveTo(tanks[i]->givePosX(), tanks[i]->givePosZ())) {
			delete tanks[i];
			tanks.erase(tanks.begin() + i);
			i--;
		}
	}

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}

//Initializes 3D rendering
void initRendering() {

	glClearColor(fogColour[0], fogColour[1], fogColour[2], fogColour[3]);

	// set the fog attributes
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 200.0f);
	glFogfv(GL_FOG_COLOR, fogColour);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.1f);

	// enable the fog
	glEnable(GL_FOG);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Wireframe
	if (isFullscreen) {
		glutFullScreen();
		glutWarpPointer(770, 450);
	}
}

void update(int value){

	
	checkInput();
	
	bool bulletNotDead = true;
	
	for (int i = 0; i < bullets.size(); i++){
		bullets[i]->move();
		bulletNotDead = true;
		for (int j = 0; j < tanks.size() && bulletNotDead; j++) {
			if (tanks[j]->isHitBy(bullets[i])){
				tanks[j]->damage(1);
				bullets[i]->flagAsDead();
				bulletNotDead = false;
			}
		}
		if (bulletNotDead && playerTank->isHitBy(bullets[i])){
			if (playerTank->hasShieldLeft()) {
				playerTank->activateShield();
			}
			else if (!invincibility){
				playerTank->damage(1);
				screenShakeMagnitude += 1.0f;
			}
			bullets[i]->flagAsDead();
		}
	}
	
	for (int i = 0; i < bullets.size(); i++){
		if (bullets[i]->isDead()){
			delete bullets[i];
			bullets.erase(bullets.begin()+i);
		}		
	}
	
	slowMotionCounter++;
	if (slowMotionCounter >= slowMotionMagnitude){
		for (int i = 0; i < tanks.size(); i++) {
			tanks[i]->move();
			tanks[i]->runAI();
			slowMotionCounter = 0;
		}
	}
	
	for (int i = 0; i < tanks.size(); i++) {
		if (tanks[i]->isDead()){
			delete tanks[i];
			tanks.erase(tanks.begin()+i);
			numTanks--;
		}
	}
	if (playerTank->isDead() && (!invincibility)){
		exit(0);
	}
	if (numTanks <= 0) {
		exit(0);
	}
	playerTank->move();
	
	if (radarVisionActivated) {
		if (radarVisionMagnitude > 1.0f) {
			radarVisionActivated = false;
			radarVisionMagnitude *= 0.95f;
		}
		else {
			radarVisionMagnitude += 0.01f;
		}

	}
	else {
		radarVisionMagnitude *= 0.95f;
	}
	
	if (slowMotionActivated) {
		if (float(slowMotionMagnitude) > slowMotionDuration) {
			slowMotionActivated = false;
			slowMotionMagnitude = slowMotionDuration;
		}
		else {
			slowMotionMagnitude += 0.5f;
		}
		
	}
	else if (slowMotionMagnitude <= 0){
		slowMotionMagnitude = 0;
	}
	else {
		slowMotionMagnitude -= 0.03f;
	}

	bulletSpeed = bulletSpeedOriginal*(50.0f-slowMotionMagnitude)/50.0f;
	 
	fogColour[0] = (1.0f-radarVisionMagnitude)*originalfogColour[0];
	fogColour[1] = (1.0f-radarVisionMagnitude)*originalfogColour[1];
	fogColour[2] = (1.0f-radarVisionMagnitude)*originalfogColour[2];
	
	lagDistance *= 0.95f;
	screenShakeMagnitude *= 0.95f;
	zoomMagnitude *= 0.95f;
	
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

//Draws the 3D scene
void display() {

	glFogfv(GL_FOG_COLOR,  fogColour);   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(-200.0f, 0.0f, -200.0f);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(-200.0f, 0.0f, 200.0f);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(200.0f, 0.0f, 200.0f);
	glColor3f(0.8f, 0.6f, 0.4f);
	glVertex3f(200.0f, 0.0f, -200.0f);
	glEnd();
	glFlush();
	glPushMatrix();

		float x = 0.1f * (rand()% 10);
		float y = 0.1f * (rand()% 10);
		float z = 0.1f * (rand()% 10);
	
		glRotatef(screenShakeMagnitude,x,y,z);
		glTranslatef(0.0f, -1.5f, -6.0f);
		glRotatef(10, 1.0f, 0.0f, 0.0f);
		glRotatef(-playerTank->giveRotation(), 0.0f, 1.0f, 0.0f);
		glRotatef(lagDistance, 0.0f, 1.0f, 0.0f);
		glRotatef(-playerTank->giveTurretRotation(), 0.0f, 1.0f, 0.0f);	

		glTranslatef(-playerTank->givePosX(), 0.0f, -playerTank->givePosZ());
	
		//Add ambient light
		GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		
		//Add positioned light
		GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
		GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
		
		//Add directed light
		GLfloat lightColor1[] = {0.2f, 0.2f, 1.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
		//Coming from the direction (-1, 0.5, 0.5)
		GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

		house1();
		makeReferenceCubes(1.5f, 0.1f);
		for (int i = 0; i < bullets.size(); i++){
			bullets[i]->drawSelf();
		}
		for (int i = 0; i < tanks.size(); i++){
			tanks[i]->drawSelf();
		}
		for (int i = 0; i < obstacles.size(); i++){
			obstacles[i]->drawSelf();
		}
		makeGrid(mapSize);
		
		
		glPushMatrix();
		glTranslatef(playerTank->givePosX(), 1.0f, playerTank->givePosZ());
		glRotatef(playerTank->giveRotation() + playerTank->giveTurretRotation(), 0.0f, 1.0f, 0.0f);
		glColor4f(0.0f, 0.0f, 0.0f, 0.2f);	
	
		float seperation = 3.0f;
	
			for (int i = 1; i <= 10; i++) {
				float bulletTravel = (-seperation*i)/bulletSpeed;
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -seperation*i);
					glRotatef(-playerTank->giveRotation() - playerTank->giveTurretRotation(), 0.0f, 1.0f, 0.0f);
					glTranslatef(-playerTank->giveSpeedX()*bulletTravel, 0.0f, -playerTank->giveSpeedZ()*bulletTravel);
					glutSolidSphere(0.05f, 4, 4);
				glPopMatrix();
			}
	
	
		glPopMatrix();
	
		playerTank->drawSelf();
	
		
	glPopMatrix();
	
	glDisable(GL_LIGHTING);
	drawHealthBars();
	glEnable(GL_LIGHTING);
	
		
	glutSwapBuffers();
}

void renderBitmapString(float x, float y, float z, void *font, char *string) {  
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void setOrthographicProjection() {
	
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, 1440, 0, 900);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -900, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void handlePassiveMouse(int x, int y){
	playerTank->rotateTurret(0.1f*(lastMouseX - x));
	lagDistance += 0.1f*(lastMouseX - x);
	lastMouseX = x;
	if (x <= 2 || x >= 1438){
		glutWarpPointer(770, 450);
		if (leftMouseDown){
			playerFire(GLUT_LEFT_BUTTON, GLUT_DOWN, 0, 0);
		}
		lastMouseX = 770;
	}
}

void handleActiveMouse(int x, int y){
	handlePassiveMouse(x,y);
}

void checkInput(){
	if(keyDown[27]){
		exit(0);
	}
	if (keyDown['w']){
		playerTank->accelerate(true);
	}
	if (keyDown['s']){
		playerTank->accelerate(false);
	}
	if (keyDown['a']){
		playerTank->rotate(true);
	}
	if (keyDown['d']){
		playerTank->rotate(false);
	}
	if (keyDown['i']){
		playerTank->boost();
		screenShakeMagnitude +=0.02f;
	}
	if (keyDown['e']){
		zoomMagnitude += 0.02f;
	}
	if (keyDown['k']){
		int direction = playerTank->centerTurret();
		if (direction > 0){
			lagDistance += 2.5f;
		}
		else if (direction < 0){
			lagDistance -= 2.5f;
		}
	}
	if (keyDown['u']) {
		radarVisionActivated = true;
	}
	if (keyDown['o']) {
		slowMotionActivated = true;
	}
	if (keyDown['j']){
		if (playerTank->giveRotationSpeed() > 0.5f){
			playerTank->rotateTurret(1.0f);
		}
		else if (playerTank->giveRotationSpeed() < -0.5f){
			playerTank->rotateTurret(-1.0f);
		}
		playerTank->rotateTurret(1.5f);
		lagDistance += 2.5;
	}
	if (keyDown['l']){
		if (playerTank->giveRotationSpeed() > 0.5f){
			playerTank->rotateTurret(1.0f);
		}
		else if (playerTank->giveRotationSpeed() < -0.5f){
			playerTank->rotateTurret(-1.0f);
		}
		playerTank->rotateTurret(-1.5f);
		lagDistance -= 2.5;
	}
	if (keyDown[' '] || leftMouseDown){
		if (playerTank->fire()){
			screenShakeMagnitude += 0.1f;
		}
	}
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {    //The current mouse coordinates
	keyDown[key] = true;
}

void handleKeyUp(unsigned char key, int x, int y){
	keyDown[key] = false;
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
	screenWidth = w;
	screenHeight = h;
}

void playerFire(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			leftMouseDown = true;
		}
		else {
			leftMouseDown =false;
		}

	}
}

void createTank(float x, float y){
	tanks.push_back(new Tank(x, y, 0.0f));
}

void createObstacle(float x, float z, float r){
	obstacles.push_back(new Obstacle(x, z, r));
}

void drawHealthBars(){
	glPushMatrix();
		glTranslatef(0.0f, 1.1f, -3.0f);
		glColor4f(1.0f, 0.3f, 0.3f, 0.2f);
		glPushMatrix();
			glScalef(2*playerTank->giveHealth(), 1.0f, 1.0f);
			glutSolidCube(0.1f);
		glPopMatrix();
	
		glTranslatef(0.0f, -0.1f, 0.0f);
		glColor4f(0.2f, 0.2f, 1.0f, 0.3f);
		glPushMatrix();
			glScalef(2.0f*playerTank->giveShieldStrength(), 1.0f, 1.0f);
			glutSolidCube(0.1f);
		glPopMatrix();	
	glPopMatrix();
}


void house1(){
	house(120, 0.1f, 50);
	house(120, 0.1f, 90);
	house(160, 0.1f, 90);
	house(80, 0.1f, 90);
	house(160, 0.1f, 50);
	house(80, 0.1f, 50);
	house(-130, 0.1f, 120);
	house(-130, 0.1f, 160);
	house(-90, 0.1f, 120);
	house(-60, 0.1f, 120);
	house(-90, 0.1f, 160);
	stand(-10, 6, 130);
	stand(30, 6, 130);
	house(-60, 0.1f, 160);
	apart(150, 0, -150);
	apart(80, 0, -90);
	apart(150, 0, -90);
	apart(150, 0, -30);
	apart(-150, 0, -30);
	apart(-150, 0, -110);
	apart(-150, 0, -180);
}

void stand(float x, float y, float z)
{
	glColor3f(1, 0.8f, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x, y - h1, z + d1);
	glVertex3f(x + h, y - h1, z + d1);
	glVertex3f(x + h, y, z);
	glEnd();
	glColor3f(1, 0.5, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + h, y, z);
	glVertex3f(x + h, y - h1, z - d1);
	glVertex3f(x, y - h1, z - d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);

	glBegin(GL_POLYGON);
	glVertex3f(x, y - h1, z + d1);
	glVertex3f(x, y - h1 - 2, z + d1);
	glVertex3f(x + 1, y - h1 - 2, z + d1);
	glVertex3f(x + 1, y - h1, z + d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);
	glBegin(GL_POLYGON);
	glVertex3f(x + h, y - h1, z + d1);
	glVertex3f(x + h, y - h1 - 2, z + d1);
	glVertex3f(x + h - 1, y - h1 - 2, z + d1);
	glVertex3f(x + h - 1, y - h1, z + d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);

	glBegin(GL_POLYGON);
	glVertex3f(x, y - h1, z - d1);
	glVertex3f(x, y - h1 - 2, z - d1);
	glVertex3f(x + 1, y - h1 - 2, z - d1);
	glVertex3f(x + 1, y - h1, z - d1);
	glEnd();

	glColor3f(0.6f, 0.12f, 0.4f);

	glBegin(GL_POLYGON);
	glVertex3f(x + h, y - h1, z - d1);
	glVertex3f(x + h, y - h1 - 2, z - d1);
	glVertex3f(x + h - 1, y - h1 - 2, z - d1);
	glVertex3f(x + h - 1, y - h1, z - d1);
	glEnd();
}


void house(float x, float y, float z)
{
	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y), float(z));
	glVertex3f(float(x), float(y), float(z + 30));
	glVertex3f(float(x), float(y + 15), float(z + 30));
	glVertex3f(float(x), float(y + 15), float(z));
	glEnd();

	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 15), float(y), float(z));
	glVertex3f(float(x - 15), float(y + 15), float(z));
	glVertex3f(float(x - 15), float(y + 15), float(z + 30));
	glVertex3f(float(x - 15), float(y), float(z + 30));
	glEnd();

	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y), float(z + 30));
	glVertex3f(float(x - 15), float(y), float(z + 30));
	glVertex3f(float(x - 15), float(y + 15), float(z + 30));
	glVertex3f(float(x), float(y + 15), float(z + 30));
	glEnd();

	glColor3f(0.01f, 0.05f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 15), float(y), float(z));
	glVertex3f(float(x - 15), float(y + 15), float(z));
	glVertex3f(float(x), float(y + 15), float(z));
	glVertex3f(float(x), float(y), float(z));
	glEnd();


	glColor3f(0.01f, 0.05f, 1.5f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 15), float(y), float(z));
	glVertex3f(float(x), float(y), float(z));
	glVertex3f(float(x), float(y), float(z + 30));
	glVertex3f(float(x - 15), float(y), float(z + 30));
	glEnd();

	glColor3f(0.51f, 0.015f, 0.008f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x + 1.69 * 3), float(y + 3.5 * 3), float(z));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z + 30));
	glVertex3f(float(x + 1.69 * 3), float(y + 3.5 * 3), float(z + 30));
	glEnd();

	glColor3f(0.51f, 0.015f, 0.008f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x - 6.69 * 3), float(y + 3.5 * 3), float(z));
	glVertex3f(float(x - 6.69 * 3), float(y + 3.5 * 3), float(z + 30));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z + 30));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z));
	glEnd();


	glColor3f(0.1f, 0.015f, 0.13f);
	glBegin(GL_POLYGON);
	glVertex3f(x, y + 15, z);
	glVertex3f(float(x), float(y + 15), float(z));
	glVertex3f(float(x - 15), float(y + 5), float(z));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z));
	glEnd();

	glColor3f(0.1f, 0.015f, 0.13f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y + 15), float(z + 30));
	glVertex3f(float(x - 15), float(y + 15), float(z + 30));
	glVertex3f(float(x - 2.5 * 3), float(y + 7.5 * 3), float(z + 30));
	glEnd();
}

void apart(float x, float y, float z)
{
	int i;
	int j;
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex3f(GLfloat(x), GLfloat(y), GLfloat(z + 0.5));
	glVertex3f(GLfloat(x + 45), GLfloat(y), GLfloat(z + 0.5));
	glVertex3f(GLfloat(x + 45), GLfloat(y + 100), GLfloat(z + 0.5));
	glVertex3f(GLfloat(x), GLfloat(y + 100), GLfloat(z + 0.5));
	glEnd();  glColor3f(0.8f, 0.8f, 0.8f);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(float(x + 2), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 88), float(z));
			glVertex3f(float(x + 2), float(y + 88), float(z));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x + 2), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 98), float(z));
			glVertex3f(float(x + 10), float(y + 88), float(z));
			glVertex3f(float(x + 2), float(y + 88), float(z));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y), float(z + 45 - 0.5));
	glVertex3f(float(x + 45), float(y), float(z + 45 - 0.5));
	glVertex3f(float(x + 45), float(y + 100), float(z + 45 - 0.5));
	glVertex3f(float(x), float(y + 100), float(z + 45 - 0.5));
	glEnd();  	glColor3f(0.8f, 0.8f, 0.8f);

	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_POLYGON);
			glVertex3f(float(x + 2), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 88), float(z + 45));
			glVertex3f(float(x + 2), float(y + 88), float(z + 45));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);

	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(float(11 * i), 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x + 2), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 98), float(z + 45));
			glVertex3f(float(x + 10), float(y + 88), float(z + 45));
			glVertex3f(float(x + 2), float(y + 88), float(z + 45));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x + 0.5), float(y), float(z));
	glVertex3f(float(x + 0.5), float(y), float(z + 45));
	glVertex3f(float(x + 0.5), float(y + 100), float(z + 45));
	glVertex3f(float(x + 0.5), float(y + 100), float(z));
	glEnd();
	glColor3f(0.8f, 0.8f, 0.8f);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_POLYGON);
			glVertex3f(float(x), float(y + 98), float(z + 2));
			glVertex3f(float(x), float(y + 98), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}glColor3f(0, 0, 0);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x), float(y + 98), float(z + 2));
			glVertex3f(float(x), float(y + 98), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 10));
			glVertex3f(float(x), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x + 45 - 0.5), float(y), float(z - 0.5));
	glVertex3f(float(x + 45 - 0.5), float(y), float(z + 45 - 0.5));
	glVertex3f(float(x + 45 - 0.5), float(y + 100), float(z + 45 - 0.5));
	glVertex3f(float(x + 45 - 0.5), float(y + 100), float(z - 0.5));
	glEnd(); glColor3f(0.8f, 0.8f, 0.8f);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_POLYGON);
			glVertex3f(float(x + 45), float(y + 98), float(z + 2));
			glVertex3f(float(x + 45), float(y + 98), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}
	glColor3f(0, 0, 0);
	for (j = 0; j < 8; j++)
	{

		glPushMatrix();
		glTranslatef(0, float(-12 * j), 0);
		for (i = 0; i < 4; i++)
		{
			glPushMatrix();
			glTranslatef(0, 0, float(11 * i));
			glBegin(GL_LINE_LOOP);
			glVertex3f(float(x + 45), float(y + 98), float(z + 2));
			glVertex3f(float(x + 45), float(y + 98), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 10));
			glVertex3f(float(x + 45), float(y + 88), float(z + 2));
			glEnd();
			glPopMatrix();
		}glPopMatrix();
	}

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y), float(z - 0.5));
	glVertex3f(float(x + 45), float(y), float(z - 0.5));
	glVertex3f(float(x + 45), float(y), float(z + 45 - 0.5));
	glVertex3f(float(x), float(y), float(z + 45 - 0.5));
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(float(x), float(y + 100), float(z));
	glVertex3f(float(x + 45), float(y + 100), float(z));
	glVertex3f(float(x), float(y + 100), float(z + 45));
	glVertex3f(float(x), float(y + 100), float(z + 45));
	glEnd();
}

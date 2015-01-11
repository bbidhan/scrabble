#include "game.h"
#include <fstream>
#include <cstring>
#include <cmath>

extern emenu currMenu;
extern game *myGame;
extern bool game_set;

bool underscorepressed = false;

struct byX{
    bool operator()(position const & a, position const & b) const{
        return a.x < b.x;
    }
};
struct byY{
    bool operator()(position const & a, position const & b) const{
        return a.y < b.y;
    }
};

class cuboid
{
    private:
        GLfloat length, height, width;
        GLuint texture;
        GLfloat red, green, blue;
    public:
        cuboid() {}
        cuboid(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLuint = 0);
        void draw();
        void draw(GLuint);
};

cuboid :: cuboid(GLfloat l, GLfloat h, GLfloat w, GLfloat r, GLfloat g, GLfloat b, GLuint tex)
{
    length = l;
    height = h;
    width = w;
    red = r;
    green = g;
    blue = b;
    texture = tex;
}

void cuboid :: draw()
{
    GLfloat vertices[] = {
    0.0, 0.0, 0.0, //0
    length, 0.0, 0.0, //1
    length, height, 0.0, //2
    0.0, height, 0.0, //3
    0.0, 0.0, -width, //4
    length, 0.0, -width, //5
    length, height, -width, //6
    0.0, height, -width, //7
    };
    GLuint front[] = {0,1,2,3};
    GLuint right[] = {1,5,6,2};
    GLuint bottom[] = {0,1,5,4};
    GLuint back[] = {4,5,6,7};
    GLuint left[] = {0,4,7,3};
    GLuint top[] = {3,2,6,7};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
        glNormal3d(0, 0, 1);
        for(int count = 0; count<4; count++)
            glArrayElement(front[count]);
        glNormal3d(1, 0, 0);
        for(int count = 0; count<4; count++)
            glArrayElement(right[count]);
        glNormal3d(0, -1, 0);
        for(int count = 0; count<4; count++)
            glArrayElement(bottom[count]);
        glNormal3d(0, 0, -1);
        for(int count = 0; count<4; count++)
            glArrayElement(back[count]);
        glNormal3d(-1, 0, 0);
        for(int count = 0; count<4; count++)
            glArrayElement(left[count]);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        for(int count = 0; count<4; count++)
        {
            if (count<=1) glTexCoord2f(count, 0.0);
            else glTexCoord2f(3.0-count, 1.0);
            glArrayElement(top[count]);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void cuboid :: draw(GLuint newtexture)
{
    texture = newtexture;
    draw();
}

class rack
{
    private:
        GLfloat lengthf, heightf, widthf; //dimensions for the front cuboid
        GLfloat lengthb, heightb, widthb; //dimesions for the back cuboid
        GLfloat red, green, blue;
    public:
        rack() {}
        rack(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
        void draw();
};

rack :: rack(GLfloat lf, GLfloat hf, GLfloat wf, GLfloat lb, GLfloat hb, GLfloat wb, GLfloat r, GLfloat g, GLfloat b)
{
    lengthf = lf;
    heightf = hf;
    widthf = wf;
    lengthb = lb;
    heightb = hb;
    widthb = wb;
    red = r;
    green = g;
    blue = b;
}

void rack :: draw(void)
{
    /*GLfloat white_light[] = { 0.0, 1.0, 0.2, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);*/
    cuboid front(lengthf, heightf, widthf, red, green, blue);
    cuboid back(lengthb, heightb, widthb, red, green, blue);
    front.draw();
    glTranslatef(0.0, 0.0, -widthf);
    back.draw();
}

class selector
{
    protected:
        GLfloat length, breadth;
        GLfloat red, green, blue;
    public:
        selector(){}
        selector(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
        void draw();
};

selector :: selector(GLfloat ln, GLfloat br, GLfloat r, GLfloat g, GLfloat b)
{
    length = ln;
    breadth = br;
    red = r;
    green = g;
    blue = b;
}

void selector :: draw()
{
    glLineWidth(10.0);
    glColor3f(red, green, blue);
    glBegin(GL_LINE_LOOP);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(length, 0.0, 0.0);
        glVertex3f(length, 0.0, -breadth);
        glVertex3f(0.0, 0.0, -breadth);
    glEnd();
}

class currentplayer_indicator : public selector
{
    public:
        currentplayer_indicator(): selector() {}
        currentplayer_indicator(GLfloat ln, GLfloat br, GLfloat r, GLfloat g, GLfloat b): selector(ln, br, r, g, b){}
        void draw();
};

void currentplayer_indicator :: draw()
{
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
        glVertex2f(0.0, 0.0);
        glVertex2f(length, 0.0);
        glVertex2f(length, breadth);
        glVertex2f(0.0, breadth);
    glEnd();
}

class font
{
    private:
        GLfloat length, breadth;
        GLuint *num_texture, *char_texture;
    public:
        font(){}
        font(GLfloat, GLfloat, GLuint*, GLuint*);
        void operator<<(int);
        void operator<<(string);
        void operator<<(char);
};

font :: font(GLfloat l, GLfloat b, GLuint *num, GLuint *charc)
{
    length = l;
    breadth = b;
    num_texture = num;
    char_texture = charc;
}

void font :: operator<<(int num)
{
    int num_length;
    if (num==0) num_length = 1;
    else num_length = log10(num) + 1;
    glColor3f(1.0, 1.0, 1.0);
    int count = num_length;
    while (count!=0)
    {
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, num_texture[num/int(pow(10,--count))]);
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex2f(length, 0.0);
        glTexCoord2d(1.0, 1.0);
        glVertex2f(length, breadth);
        glTexCoord2d(0.0, 1.0);
        glVertex2f(0.0, breadth);
        num = num%int(pow(10, count));
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glTranslatef(length, 0.0, 0.0);
    }
    glTranslatef(-num_length*length, 0.0, 0.0);
}

void font :: operator<<(string word)
{
    char name[10];
    strcpy(name, word.c_str());
    int str_length = strlen(name);
    int count = 0;
    glColor3f(1.0, 1.0, 1.0);
    while (name[count] != '\0')
    {
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, char_texture[name[count] - 64]);
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex2f(length, 0.0);
        glTexCoord2d(1.0, 1.0);
        glVertex2f(length, breadth);
        glTexCoord2d(0.0, 1.0);
        glVertex2f(0.0, breadth);
        count++;
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glTranslatef(length, 0.0, 0.0);
    }
    glTranslatef(-str_length*length, 0.0, 0.0);
}

void font :: operator<<(char letter)
{
    if (letter == '\n') glTranslatef(0.0, -length*1.5, 0.0);
}

font print;

game::game() {
    players.reserve(2);
    currPlayerId=0;
    pass =0;
    totGames=0;
}

void game::endGame(){
    ofstream outfile("asd.txt",std::ios_base::app);
    for(int i=0;i<totalPlayers();i++){
        getPlayer(i).endGame();
        for(int j=0;j<getPlayer(i).patts.size();j++){
            outfile<<endl<<getPlayer(i).patts[j].lastPattern<<" ";
            outfile<<getPlayer(i).patts[j].totlastScorePatt;
        }
    }
    outfile.close();
}

void game::run(const char *player_one, const char *player_two){

    harveyBot = new harvey("HARVEY",false);

    if ((player_one == NULL)&&(player_two == NULL))
    {
        harvey* harveyBot2 = new harvey("ASTER",false);
        addAIPlayer(harveyBot);
        addAIPlayer(harveyBot2);
    }
    else if (player_two == NULL)
    {
        addPlayer(player_one);
        addAIPlayer(harveyBot);
    }
    else
    {
        addPlayer(player_one);
        addPlayer(player_two);
    }

    currentPlayer = &this->currPlayer();      //POINTER 'VARIABLE'

    x = 7;
    y = 7;
    error = true;

}

int game::totalPlayers() {
    return players.size();
}
bag& game::getBag() {
    return myBag;
}
board& game::getBoard() {
    return myBoard;
}
harvey& game::currPlayer() {
    return players[currPlayerId];
}
harvey& game::getPlayer(int id) {
    return players[id];
}
harvey& game::winner() {
    int scr =0;
    int id =0;
    for(int i=0;i<totalPlayers();i++){
        if(getPlayer(i).getTotalScore()>scr){
            scr = getPlayer(i).getTotalScore();
            id=i;
        }
    }
    return getPlayer(id);
}
harvey& game::nextPlayer() {
    if(currPlayerId==players.size()-1) {
        currPlayerId=0;
    } else {
        currPlayerId++;
    }
    myBoard.incPlaycount();
    //playCount++;
    return currPlayer();
}
void game::removePlayer(int id) {
    players.erase(players.begin()+id);
}
void game::addPlayer(string name) {
    harvey* pl= new harvey(name,true);
    for(int i = 0; i<7; i++) {
        pl->pullLetterFromBag(myBag);
    }
    players.push_back(*pl);
}
void game::addAIPlayer(harvey *bot) {
    for(int i = 0; i<7; i++) {
        bot->pullLetterFromBag(myBag);
    }
    players.push_back(*bot);
}

void game::output(void)
{
    static int counter = 0;
    counter++;
    static GLuint board_texture;
    static GLuint tile_texture[27];
    static GLuint num_texture[10];
    if (counter == 1)
    {
        board_texture =
        SOIL_load_OGL_texture
        (
            "board.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
        tile_texture[0] =
        SOIL_load_OGL_texture
        (
            "_.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
        char letter[2];
        for (int count = 1; count<=26; count++)
        {
            letter[0] = count + 64;
            letter[1] = '\0';
            tile_texture[count] =
            SOIL_load_OGL_texture
            (
                strcat(letter, ".png"), //1 for 'A'
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
        }
        for (int count = 0; count<=9; count++)
        {
            letter[0] = count + 48;
            letter[1] = '\0';
            num_texture[count] =
            SOIL_load_OGL_texture
            (
                strcat(letter, ".png"), //0 for '0'
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
        }
        glLoadIdentity();
        gluPerspective(45.0, 1280.0/768.0, 5.0, 100.0);
        gluLookAt(0.0, 7.5, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glMatrixMode(GL_MODELVIEW);
        print = font(0.3, 0.3, num_texture, tile_texture);
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 64.0 };
        GLfloat light_position[] = { 0.0, 2.0, 0.0, 0.0 };
        GLfloat white_light[] = { 0.0, 0.5, 0.0, 1.0 };
        GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    static cuboid scr_board (board_dimension, board_thickness, board_dimension, 0.0, 0.0, 0.0, board_texture);
    static cuboid tile(unit, tile_thickness, unit, 0.210, 0.180, 0.140);
    static rack scr_rack(9*unit, rack_height, tile_thickness, 9*unit, rack_height + unit, 0.4, 0.0, 0.5, 0.0);
    static selector cursor(unit, unit, 0.0, 0.0, 0.2);
    static currentplayer_indicator marker(0.3, 0.3, 0.0, 0.5, 0.5);
    //Drawing Part of the function
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-board_dimension/2, -board_thickness/2, 2.5); //Translate the board towards left and down.
    glRotatef(15.0, 1.0, 0.0, 0.0); //Rotate the board about x-axis
    scr_board.draw();
    glTranslatef(0.0, board_thickness/2, 0.0); //Transfer the origin to the lowermost left corner of board
    glTranslatef(0.0, 0.0, -14*unit); //Transfer the origin to the uppermost left corner of board
    if(pass==totalPlayers()) {
            endGame();
            currMenu = ewinner;
            glutPostRedisplay();
        }
        if(currentPlayer->isAI) {
            if(currentPlayer->aiProcess(myBoard,myBag,true,0) == 0) {
                pass++;
            } else {
                pass = 0;
            }
            if(currentPlayer->totalLetters()==0) {
                endGame();
                currMenu = ewinner;
                glutPostRedisplay();
            }
            currentPlayer = &nextPlayer();
        }
     for (int i = 0; i<buffer.size(); i++)
    {
        glTranslatef(buffer[i].getX()*unit, 0.0, buffer[i].getY()*unit);
        tile.draw(tile_texture[buffer[i].getLetter().getName() - 64]);
        glTranslatef(-buffer[i].getX()*unit, 0.0, -buffer[i].getY()*unit);
    }
    for (int i = 0; i<=14; i++)
    {
        for (int j = 0; j<=14; j++)
        {
            if (myBoard.isSet(i,j))
            {
                glTranslatef(i*unit, 0.0, j*unit);
                tile.draw(tile_texture[myBoard.getPosition(i,j).getLetter().getName() - 64]);
                glTranslatef(-i*unit, 0.0, -j*unit);
            }
        }
    }
    glTranslatef(0.0, 0.0, 14*unit); //To the lowermost left corner of the board
    glTranslatef(3*unit, -board_thickness, 2.0); //Rack to the desired position
    glRotatef(-30.0, 1.0, 0.0, 0.0);
    scr_rack.draw();
    glTranslatef(0.0, rack_height, 0.0);
    glRotatef(90.0, 1.0, 0.0 ,0.0);
    for(int i = 0;i< currentPlayer->totalLetters();i++)
    {
            tile.draw(tile_texture[currentPlayer->getLetters(i).getName() - 64]);
            glTranslatef(unit, 0.0, 0.0);
    }
       glLoadIdentity();
        glTranslatef(-(7.5+4)*unit, 3.0, -7.5*unit);
        for(int j = 0; j < totalPlayers(); j++, glLoadIdentity(),
        glTranslatef((7.5+2)*unit, 3.0, -7.5*unit)) {
            glTranslatef(-0.5, 0.0, 0.0);
            if(currentPlayer->getName()==getPlayer(j).getName()) {
                marker.draw();
            }
            glTranslatef(0.5, 0.0, 0.0);
            print << getPlayer(j).getName();
            print << '\n';
            print << getPlayer(j).getLastScore(); print << '\n';
            print << getPlayer(j).getTotalScore(); print << '\n';
            for(int i = 0; i<getPlayer(j).totalLastWords(); i++) {
               print << getPlayer(j).getLastWord(i); print << '\n';
            }
        }
        glLoadIdentity();
        glTranslatef(-board_dimension/2, -board_thickness/2, 2.5); //Translate the board towards left and down.
        glRotatef(15.0, 1.0, 0.0, 0.0); //Rotate the board about x-axis
        glTranslatef(0.0, board_thickness/2, 0.0); //Transfer the origin to the lowermost left corner of board
        glTranslatef(0.0, 0.0, -14*unit); //Transfer the origin to the uppermost left corner of board
        glTranslatef(x*unit, 0.2, y*unit);
        if (myBoard.isSet(x,y)) glTranslatef(0.0, tile_thickness, 0.0);
        cursor.draw();
        glFlush();
        glutPostRedisplay();
}

void game::normal_input(unsigned char KB_code)
{
        if (underscorepressed)
        {
            for(int i = 0;i<currentPlayer->totalLetters();i++){
                    if(currentPlayer->getLetters(i).getASCII()==KB_UNDERSCORE){
                        currentPlayer->getLetters(i).convertBlankTo(char(KB_code-32));
                        underscorepressed = false;
                        break;
                    }
                }
        }
        underscorepressed = false;
        if (KB_code==KB_ESCAPE){
                currMenu = emain_menu;
                glutPostRedisplay();
            }
        else if(((KB_code>=97 && KB_code<= 122 )||KB_code==KB_UNDERSCORE) && !myBoard.getCurrentLetter().exists()){
                for(int i = 0; i<currentPlayer->totalLetters(); i++) {
                    if(currentPlayer->getLetters(i).getASCII()==KB_code-32) {
                        myBoard.setCurrentLetter(currentPlayer->getLetters(i));
                        currentPlayer->eraseLetter(i);
                        buffer.push_back(myBoard.getCurrentPos());
                        error = myBoard.isValidBuffer(buffer);
                        if(!error)myBoard.updateBoard(buffer,wordBuffer);
                        break;
                    }
                }
        }
        else if(KB_code==KB_BACKSPACE && buffer.size()>0){
                int i =buffer[buffer.size()-1].x;
                int j =buffer[buffer.size()-1].y;
                currentPlayer->drawLetterFromBuffer(buffer);
                error = myBoard.isValidBuffer(buffer);
                if(!error)myBoard.updateBoard(buffer,wordBuffer);
        }
        else if(KB_code==96) {
                underscorepressed = true;
                }

        else if(KB_code==KB_ENTER && buffer.size()>0){
            error = myBoard.isValidBuffer(buffer);
                if(!error)myBoard.updateBoard(buffer,wordBuffer);
                //HAS VALID WORDS
                currentPlayer->clearLastRun();
                if(myBoard.totalLastWords()>0 && !error) {
                    //DICTIONARY CHECK HERE
                    for(int i = 0; i<myBoard.totalLastWords(); i++) {
                        if(harveyBot->head->search_word(myBoard.getLastWordLower(i))==0) {
                            error = true;
                        }
                        currentPlayer->addWord(myBoard.getLastWord(i));
                    }
                    if(!error) {
                        currentPlayer->setLastScore(myBoard.getLastScore());
                        currentPlayer->finalizeWords();
                        for(int i = 0; i<buffer.size(); i++) {
                            myBoard.getPosition(buffer[i]).setLetter(buffer[i].getLetter());
                            myBoard.getPosition(buffer[i]).setAdder(1);
                            myBoard.getPosition(buffer[i]).setMultiplier(1);
                            if(myBag.lettersLeft()>0) {
                                currentPlayer->pullLetterFromBag(myBag);
                            }
                        }
                        currentPlayer->setTotalScore();
                        buffer.clear();
                        wordBuffer.clear();
                        myBoard.clearLastRun();
                        if(currentPlayer->totalLetters()==0) {
                            //break;
                        }
                        currentPlayer = &nextPlayer();
                        pass = 0;
                        //removePlayer(0);
                    }
                }
        }

        myBoard.setCurrentX(x);
        myBoard.setCurrentY(y);
        myBoard.setCurrentLetter(myBoard.getPosition(myBoard.getCurrentPos()).getLetter());
        for(int i = 0;i<buffer.size();i++){
            if(myBoard.getCurrentX()==buffer[i].x && myBoard.getCurrentY()==buffer[i].y){
               myBoard.setCurrentLetter(buffer[i].getLetter());
            }
        }
       glutPostRedisplay();
}

void game::special_input(int KB_code)
{
    switch (KB_code){
                case KB_LEFT:
                           if (x >= 1) x--;  KB_code=0;
                break;

                case KB_RIGHT:
                           if (x <= 13) x++;  KB_code=0;
                break;

                case KB_UP:
                            if (y >= 1) y--;  KB_code=0;
                break;

                case KB_DOWN:
                             if (y <= 13) y++;  KB_code=0;
                break;

                case GLUT_KEY_F2:
                currentPlayer->drawAllLettersFromBuffer(buffer);
                currentPlayer = &nextPlayer();
                pass++;
                glutPostRedisplay();
                break;

            }
        myBoard.setCurrentX(x);
        myBoard.setCurrentY(y);
        myBoard.setCurrentLetter(myBoard.getPosition(myBoard.getCurrentPos()).getLetter());
        for(int i = 0;i<buffer.size();i++){
            if(myBoard.getCurrentX()==buffer[i].x && myBoard.getCurrentY()==buffer[i].y){
               myBoard.setCurrentLetter(buffer[i].getLetter());
            }
        }
        glutPostRedisplay();
}

game::~game()
{
    //dtor
}

void menu:: output(void)
{
    GLfloat screen_width = (1280/500.0)*0.8;
    GLfloat screen_height = (768/500.0)*1.3;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-screen_width/2, -screen_height/2, 0.0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex2f(screen_width, 0.0);
        glTexCoord2d(1.0, 1.0);
        glVertex2f(screen_width, screen_height);
        glTexCoord2d(0.0, 1.0);
        glVertex2f(0.0, screen_height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glTranslatef(screen_width/2, screen_height/2, 0.0);
    glFlush();
}

void menu::normal_input(unsigned char key)
{
    if (key==KB_ENTER) currMenu = forward;
    if (key==KB_ESCAPE) currMenu = backward;
    glutPostRedisplay();
}

void selective_menu:: output(void)
{
    GLfloat screen_width = (1280/500.0)*0.8;
    GLfloat screen_height = (768/500.0)*1.3;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-screen_width/2, -screen_height/2, 0.0);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texture[level-1]);
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex2f(screen_width, 0.0);
        glTexCoord2d(1.0, 1.0);
        glVertex2f(screen_width, screen_height);
        glTexCoord2d(0.0, 1.0);
        glVertex2f(0.0, screen_height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glTranslatef(screen_width/2, screen_height/2, 0.0);
    glFlush();
}

void selective_menu::normal_input(unsigned char key)
{
    if (key==KB_ENTER)
    {
        currMenu = forwardarray[level-1];
        level = 1;
    }
    if (key==KB_ESCAPE) currMenu = backward;
    glutPostRedisplay();
}

void selective_menu::special_input(int key)
{
    switch (key){
                case KB_UP:
                    if (level > 1) level--;
                    break;
                case KB_DOWN:
                    if (level < options) level++;
                    break;
            }
    glutPostRedisplay();
}

void result :: output(void)
{
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(0.0, 1280.0, 0.0, 768.0);
    menu::output();
    print << myGame->winner().getName();
    print << myGame->winner().getTotalScore();
}

void result :: normal_input(unsigned char key)
{
    if (key==KB_ENTER)
    {
        delete myGame;
        game_set = false;
        currMenu = emain_menu;
        glutPostRedisplay();
    }
}

void mode_menu :: normal_input(unsigned char key)
{
    if (key==KB_ENTER)
    {
        myGame = new game;
        game_set = true;
        if (humans == 1)
                myGame->run("PLAYERONE");
        if (humans == 2)
            myGame->run("PLAYERONE", "PLAYERTWO");
    }
    menu::normal_input(key);
}


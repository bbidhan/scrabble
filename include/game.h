#ifndef GAME_H
#define GAME_H


#include "GL\glut.h"
#include "SOIL.h"

#include <iostream>
#include <stdlib.h>

#include "letter.h"
#include "position.h"
#include "bufferPosition.h"
#include "bag.h"
#include "player.h"
#include "node.h"
#include "harvey.h"
#include "aster.h"
#include "board.h"
#include "drawengine.h"

#define KB_UP GLUT_KEY_UP
#define KB_DOWN GLUT_KEY_DOWN
#define KB_LEFT GLUT_KEY_LEFT
#define KB_RIGHT GLUT_KEY_RIGHT
#define KB_ESCAPE 27
#define KB_ENTER 13
#define KB_BACKSPACE 8
#define KB_UNDERSCORE 95

#define unit 0.7
#define board_dimension unit*15
#define board_thickness 0.3
#define tile_thickness 0.3
#define rack_height 0.4

class game{
public:
    game();
    void run(const char* = NULL, const char* = NULL);
    harvey* harveyBot;
    int cnt;
    //vector<aster>& getPlayers();
    int totalPlayers();
    bag& getBag();
    board& getBoard();
    harvey& currPlayer();
    harvey& getPlayer(int id);
    harvey& nextPlayer();
    void addPlayer(string name);
    void removePlayer(int id);
    void addAIPlayer(harvey *bot);
    void endGame();
    harvey& winner();
    virtual ~game();
    int totGames;
    void output(void);
    void normal_input(unsigned char);
    void special_input(int);
    void draw_background(void);
    protected:
private:
    harvey *currentPlayer;
    int x ;
    int y ;
    bool error;
    vector<position> buffer;
    vector<position> wordBuffer;
    int gameCount;
    int pass;
    vector<harvey> players;
    int currPlayerId;
    bag myBag;
    board myBoard;
};

enum emenu{emain_menu, erules, ecredits, eexit, egame_mode, eplayer_one, eplayer_two, egame, ewinner};

class menu
{
    protected:
        GLuint texture;
        emenu forward;
        emenu backward;
    public:
        menu() {}
        menu(const char *filename, emenu fr, emenu bk)
        {
            texture =
            SOIL_load_OGL_texture
            (
                filename,
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );
            forward = fr;
            backward = bk;
        }
        void output(void);
        void normal_input(unsigned char);
};

class selective_menu
{
    protected:
        GLuint options;
        GLuint level;
        GLuint *texture;
        emenu *forwardarray;
        emenu backward;
    public:
        selective_menu(){}
        selective_menu(emenu *fr, emenu bk, int opt, GLuint *tex)
        {
            options = opt;
            texture = tex;
            level = 1;
            forwardarray = fr;
            backward = bk;
        }
        void output(void);
        void normal_input(unsigned char);
        void special_input(int);
};

class result : public menu
{
    public:
        result(): menu() {}
        result(const char *filename, emenu fr, emenu bk): menu(filename, fr, bk) {}
        void output(void);
        void normal_input(unsigned char);
};

class mode_menu : public menu
{
    protected:
        int humans;
    public:
        mode_menu():menu() {}
        mode_menu(const char *filename, emenu fr, emenu bk, int h): menu(filename, fr, bk) { humans = h;}
        void normal_input(unsigned char);
};

#endif // GAME_H


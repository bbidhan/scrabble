#include "GL\glut.h"
#include "SOIL.h"
#include <cstring>

#include "game.h"

game *myGame = NULL;

bool game_set = false;

emenu currMenu = emain_menu;

menu credits, rules;
selective_menu main_menu, game_mode;
mode_menu  player_one, player_two;
result winner;

void display(void)
{
    switch(currMenu)
    {
        case emain_menu:
            if (game_set)
            {
                delete myGame;
                game_set = false;
            }
            main_menu.output();
            break;
        case erules:
            rules.output();
            break;
        case ecredits:
            credits.output();
            break;
        case eexit:
            exit(0);
            break;
        case egame_mode:
            game_mode.output();
            break;
        case eplayer_one:
            player_one.output();
            break;
        case eplayer_two:
            player_two.output();
            break;
        case egame:
            if (!game_set)
            {
                myGame = new game;
                game_set = true;
                myGame->run();
            }
            myGame->output();
            break;
        case ewinner:
            winner.output();
            break;
        default:
            exit(0);
    }
}

void handlenormalKeypress(unsigned char key,int a,int b)
{
    switch(currMenu)
    {
        case emain_menu:
            main_menu.normal_input(key);
            break;
        case erules:
            rules.normal_input(key);
            break;
        case ecredits:
            credits.normal_input(key);
            break;
        case egame_mode:
            game_mode.normal_input(key);
            break;
        case eplayer_one:
            player_one.normal_input(key);
            break;
        case eplayer_two:
            player_two.normal_input(key);
            break;
        case egame:
            myGame->normal_input(key);
            break;
        case ewinner:
            winner.normal_input(key);
            break;
        default:
            exit(0);
    }
}

void handlespecialKeypress(int key,int a,int b)
{
    switch(currMenu)
    {
        case emain_menu:
            main_menu.special_input(key);
            break;
        case erules:
            break;
        case ecredits:
            break;
        case egame_mode:
            game_mode.special_input(key);
            break;
        case eplayer_one:
            break;
        case eplayer_two:
            break;
        case egame:
            myGame->special_input(key);
            break;
        case ewinner:
            break;
        default:
            exit(0);
    }
}


void init(void)
{
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_NEAREST);
    glViewport(0, 0, 1280.0, 768.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1280.0, 0.0, 768.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 384);
    glutCreateWindow("Scrabble");
    init();
    GLuint main_menu_selector[] =
    {
        SOIL_load_OGL_texture
        (
            "main_menu_0.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        ),
        SOIL_load_OGL_texture
        (
            "main_menu_1.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        ),
        SOIL_load_OGL_texture
        (
            "main_menu_2.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        ),
        SOIL_load_OGL_texture
        (
            "main_menu_3.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        )
    };
    emenu main_menu_forward[] = {egame_mode, erules, ecredits, eexit};
    main_menu = selective_menu(main_menu_forward, eexit, 4, main_menu_selector);
    GLuint game_mode_selector[] =
    {
        SOIL_load_OGL_texture
        (
            "game_mode_0.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        ),
        SOIL_load_OGL_texture
        (
            "game_mode_1.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        ),
        SOIL_load_OGL_texture
        (
            "game_mode_2.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        )
    };
    emenu game_mode_forward[] = {eplayer_two, eplayer_one, egame};
    game_mode = selective_menu(game_mode_forward, emain_menu, 3, game_mode_selector);
    rules = menu("rules.png", erules, emain_menu);
    credits = menu("credits.png", ecredits, emain_menu);
    player_one = mode_menu("player_one.png", egame, egame_mode, 1);
    player_two = mode_menu("player_two.png", egame, egame_mode, 2);
    winner = result("winner.png", emain_menu, ewinner);
    glutDisplayFunc(display);
    glutKeyboardFunc(handlenormalKeypress);
    glutSpecialFunc(handlespecialKeypress);
    glutMainLoop();
    return 0;
}


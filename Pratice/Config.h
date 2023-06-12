/*****************************************************************//**
 * File: Config.h
 * Author: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Create Date: 2023-06-09
 * Editor: TENG-FENG YOU (vic.feng1234@gmail.com)
 * Update Date: 2023-06-09
 * Description: This file is a setting file. 
 *********************************************************************/
#pragma once

// Number
constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 800;
constexpr int TRIGGER_NUM = 2;


// block
constexpr const char *BLOCK_IMAGE_PATH = "./assects/tiles0.png";
constexpr const char *TERRAIN_FEATURE_IMAGE_PATH = "./assects/terrain_features.png";

// Monster
constexpr const char *RAT_IMAGE = "./assects/Monster/rat.png";
constexpr const char *SNAKE_IMAGE = "./assects/Monster/snake.png";
constexpr const char *GNOLL_IMAGE = "./assects/Monster/gnoll.png";
constexpr const char *CRAB_IMAGE = "./assects/Monster/crab.png";

// Player
constexpr const char *PLAYER_IMAGE = "./assects/Player/warrior.png";
constexpr const char *PLAYER_STATUS_IMAGE = "./assects/interfaces/status_pane.png";

// Font
constexpr const char *FONT_PATH = "./assects/fonts/pixel_font.ttf";

// Trigger
constexpr const char* TRAP_IMAGE_PATH = "./assects/terrain_features.png";

// Music
// Background
constexpr const char *BACKGROUND_PATH = "./assects/music/caves_1.ogg";
constexpr const char* ED_PATH = "./assects/music/ed.ogg";
constexpr const char* OP_PATH = "./assects/music/op.ogg";
// Action
constexpr const char* STAB_SOUNDS_PATH = "./assects/sounds/hit_stab.mp3";

// Save / Load
constexpr const char* SAVE_PATH = "./assects/save/save.txt";

// Buff
constexpr const char* BUFF_IMAGE_PATH = "./assects/interfaces/buffs.png";

// Item
constexpr const char* ITEMS_IMAGE_PATH = "./assects/items/items.png";

// win/lose/pre image
constexpr const char* ED_IMAGE_PATH = "./assects/interfaces/dead.png";
constexpr const char* START_IMAGE_PATH = "./assects/interfaces/start.png";

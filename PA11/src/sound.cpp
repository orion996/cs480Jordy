//
// Created by mari on 12/9/18.
//

#include "sound.h"
Mix_Chunk * Sound:: soundEffect;
Mix_Chunk * Sound:: soundEffect2;
Mix_Chunk * Sound:: soundEffect3;
Mix_Music * Sound:: bgMusic;

Sound::Sound(){

}

Sound::~Sound(){
    Mix_FreeMusic(Sound::bgMusic);
    Mix_FreeChunk(Sound::soundEffect);
    Mix_FreeChunk(Sound::soundEffect2);
    Mix_FreeChunk(Sound::soundEffect3);
}


void Sound:: audio(/*const char* &file*/){
   Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    Sound::soundEffect = Mix_LoadWAV(HIT_SOUND);
    Sound::soundEffect2 = Mix_LoadWAV(GUN_SOUND);
   Mix_AllocateChannels(16);


}

void Sound::background(){

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    Sound::bgMusic = Mix_LoadMUS(BG_MUSIC);
    Mix_AllocateChannels(16);
    Mix_PlayMusic(Sound::bgMusic,-1);

}
#include "includes/audio.h"
#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static Music audioMainMusic;

static Sound audioStepsSound[AUDIO_STEP_NUMBER];


/**
 * Load the audio file for the human footsteps.
 */
static void InitSteps()
{
    int i;
    char * local_steps[] = {AUDIO_STEP_1, AUDIO_STEP_2, AUDIO_STEP_3, AUDIO_STEP_4, 
                    AUDIO_STEP_5, AUDIO_STEP_6, AUDIO_STEP_7, AUDIO_STEP_8};
    for (i = 0; i < AUDIO_STEP_NUMBER; i++)
    {
        Sound s = LoadSound(local_steps[i]);
        audioStepsSound[i] = s;
    }
}

/**
 * Free the audio file the human footsteps.
 */
static void FreeAudioStepsSound()
{
    int i;
    for (i = 0; i < AUDIO_STEP_NUMBER; i++)
    {
        UnloadSound(audioStepsSound[i]);
    }
    
}

/**
 * Init the audio with a channel, start a generator and loads sounds
 */
static void InitAudio()
{
    InitAudioDevice();

    InitSteps();
}

/**
 * Load the main music.
 */
static void LoadAudioMainMusic()
{
    if(!IsAudioDeviceReady())
        InitAudio();

    audioMainMusic = LoadMusicStream(AUDIO_MAIN_MUSIC);
}

void PlayAudioMainMusic()
{
    LoadAudioMainMusic();

    if(IsMusicPlaying(audioMainMusic))
        return;
    
    SetMusicVolume(audioMainMusic, 0.05);
    PlayMusicStream(audioMainMusic);
}

void ResumeAudioMainMusic()
{
    if(!IsMusicPlaying(audioMainMusic))
        ResumeMusicStream(audioMainMusic);

    return;
}

void PauseAudioMainMusic()
{
    if(!IsMusicPlaying(audioMainMusic))
        return;

    PauseMusicStream(audioMainMusic);
}

void StopAudioMainMusic()
{
    StopMusicStream(audioMainMusic);
}

void FreeAudioMainMusic()
{
    StopSoundMulti();
    FreeAudioStepsSound();
    UnloadMusicStream(audioMainMusic);
    CloseAudioDevice();
}

void UpdateAudio()
{
    UpdateMusicStream(audioMainMusic);
}

void PlaySoundRandomStep()
{
    if(!IsAudioDeviceReady())
        InitAudio();

    int r = (rand() % AUDIO_STEP_NUMBER);
    PlaySoundMulti(audioStepsSound[r]);
}

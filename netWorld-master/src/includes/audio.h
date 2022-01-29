/**
 * @file audio.h
 *
 * @brief Header file of the audio module
 *
 * This module contains function to play music and random sounds
 *
 * This header file can be used by any NetWorld game
 *
 */


#ifndef AUDIO_H
#define AUDIO_H

#define AUDIO_PATH "resources/sounds/"


#define AUDIO_MAIN_MUSIC AUDIO_PATH "main.mp3"

#define AUDIO_STEP_NUMBER 8
#define AUDIO_STEP_1 AUDIO_PATH "step1.mp3"
#define AUDIO_STEP_2 AUDIO_PATH "step2.mp3"
#define AUDIO_STEP_3 AUDIO_PATH "step3.mp3"
#define AUDIO_STEP_4 AUDIO_PATH "step4.mp3"
#define AUDIO_STEP_5 AUDIO_PATH "step5.mp3"
#define AUDIO_STEP_6 AUDIO_PATH "step6.mp3"
#define AUDIO_STEP_7 AUDIO_PATH "step7.mp3"
#define AUDIO_STEP_8 AUDIO_PATH "step8.mp3"

/**
 * Initialise and play the main music of the game.
 */
void PlayAudioMainMusic();

/**
 * Playing the main music after the main music was paused.
 */
void ResumeAudioMainMusic();

/**
 * Pause the main music.
 */
void PauseAudioMainMusic();

/**
 * Stop the main music.
 */
void StopAudioMainMusic();

/**
 * Free and close audio channel of the main music.
 */
void FreeAudioMainMusic();

/**
 * Update the main music during the execution of the game.
 */
void UpdateAudio();

/**
 * Play a human footsteps song.
 */
void PlaySoundRandomStep();
#endif

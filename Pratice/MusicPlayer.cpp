#include "MusicPlayer.h"

sf::Music MusicPlayer::edMusic;
sf::Music MusicPlayer::backGroundMusic;
sf::Music MusicPlayer::stabMusic;
sf::Music MusicPlayer::opMusic;

MusicPlayer::MusicPlayer()
{
	edMusic.openFromFile(ED_PATH);
	backGroundMusic.openFromFile(BACKGROUND_PATH);
	opMusic.openFromFile(OP_PATH);

}

MusicPlayer::~MusicPlayer()
{
	edMusic.stop();
	backGroundMusic.stop();
	opMusic.stop();

}

void MusicPlayer::play(MUSIC_TYPE type)
{
	switch (type) {
	case MUSIC_TYPE::BACKGROUND:
		backGroundMusic.play();
		break;
	case MUSIC_TYPE::ED:
		edMusic.play();
		break;
	case MUSIC_TYPE::OP:
		opMusic.play();
		break;
	}
}

void MusicPlayer::stop(MUSIC_TYPE type)
{
	switch (type) {
	case MUSIC_TYPE::BACKGROUND:
		backGroundMusic.stop();
		break;
	case MUSIC_TYPE::ED:
		edMusic.stop();
		break;
	case MUSIC_TYPE::OP:
		opMusic.stop();
		break;
	}
}

void MusicPlayer::pause(MUSIC_TYPE type)
{
	switch (type) {
	case MUSIC_TYPE::BACKGROUND:
		backGroundMusic.pause();
		break;
	case MUSIC_TYPE::ED:
		edMusic.pause();
		break;
	case MUSIC_TYPE::OP:
		opMusic.pause();
		break;
	}
}

void MusicPlayer::setVolume(float volume)
{
	backGroundMusic.setVolume(volume);
	edMusic.setVolume(volume);
}

void MusicPlayer::setLoop(MUSIC_TYPE type, bool isLooping)
{
	switch (type) {
	case MUSIC_TYPE::BACKGROUND:
		backGroundMusic.setLoop(isLooping);
		break;
	case MUSIC_TYPE::ED:
		edMusic.setLoop(isLooping);
		break;
	case MUSIC_TYPE::OP:
		opMusic.setLoop(isLooping);
		break;
	}
}

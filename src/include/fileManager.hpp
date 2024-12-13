#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>

#include "level.hpp"

//For managing file loading and writing
//has methods for file reading and writing for levels, points, textures and sounds
namespace FileManager {

    //Saves the new scores to a file
    //params: name of the file, a list of the scores and nicknames
    //returns: if the writing was successful
    bool SaveScore(const std::string& filename,
                std::vector<std::pair<std::string, int>> scores);

    //loads the scorelist from a file
    //params: anme of the file
    //returns: a list of nicknames and scores
    std::vector<std::pair<std::string, int>> LoadScore(const std::string& filename);

    //For creating level editor for future use
    /*bool SaveLevel(const std::string& filename, const std::vector<Entity*>&
    * entities);*/

    //Loads a level from file, creates entities
    //params: name of the file, current game
    //pointer of the new level
    std::unique_ptr<Level> LoadLevel(const std::string& filename, Game& game);

    //Loads images, creates textures and puts then to a dictionary
    //params: path of the images folder
    void LoadTextures(const std::string path);

    //searches a texture from the dictionary
    //params: name of the texture
    //returns: a pointer to the texture
    std::unique_ptr<sf::Texture>& GetTexture(const std::string name);

    //Loads sound effects
    //params: path of the sound effect folder
    void LoadSFX(const std::string path);

    //Plays a sound
    //params: name of the sound
    void PlaySound(const std::string name);

    //Loads music
    //params: path to the music folder
    void LoadMusic(const std::string path);

    //Plays music
    //params: name of the song
    void PlayMusic(const std::string name);

    //destroys the dictionaries for textures, music and sound effects
    void DestroySFML();

};  // namespace FileManager

#endif
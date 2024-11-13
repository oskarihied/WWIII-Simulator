#include "fileManager.hpp"
#include <fstream>
#include <sstream>

bool FileManager::SaveScore(const std::string& filename, std::vector<std::pair<std::string,int>> scores){
    std::ofstream file(filename);

    if (!file.is_open()){
        return false;
    }

    for(auto it : scores){
        file << it.first << ";" << it.second << "\n";
    }

    file.close();
    return true;
}

std::vector<std::pair<std::string,int>> FileManager::LoadScore(const std::string& filename){
    std::vector<std::pair<std::string,int>> scores;
    std::ifstream file(filename);

    if(!file.is_open()){
        return scores;
    }

    std::string line;
    while(std::getline(file, line)){
        std::istringstream stream(line);
        std::string name;
        int score;
        std::getline(stream,name,';');
        stream >> score;
        scores.push_back(std::make_pair(name,score));
    }

    file.close();
    return scores;
}
/*
bool FileManager::SaveLevel(const std::string& filename, const std::vector<Entity*>& entities){

}
std::vector<Box*> FileManager::LoadLevel(const std::string& filename);*/

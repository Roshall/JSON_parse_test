#include "position_parse.h"
#include <fstream>
#include <string>

PositionParse::PositionParse(std::string &s){
    this->ParseFromString(s);
}

bool PositionParse::IsBegin() const{
    if(this->y_v>this->begin)
        return true;
    else
        return false;
}
bool PositionParse::IsEnd() const{
    if(this->y_v<this->end)
        return true;
    else
        return false;
}

bool PositionParse::ParseFromFile(const std::string &path){
    // read a JSON file
    std::ifstream input_(path);
    input_ >> this->__json;
    this->x_v = std::stod(this->__json["x"].get<std::string>());
    this->y_v = std::stod(this->__json["y"].get<std::string>());
    this->timestamp_v = std::stod(this->__json["timestamp"].get<std::string>());
    return true;
}

bool PositionParse::ParseFromString(const std::string &origin){
    // read a JSON string
    this->__json = nlohmann::json::parse(origin);
    this->x_v = std::stod(this->__json["x"].get<std::string>());
    this->y_v = std::stod(this->__json["y"].get<std::string>());
    this->timestamp_v = std::stold(this->__json["timestamp"].get<std::string>());
    return true;
}

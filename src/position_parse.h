#pragma once

#include <string>
#include <vector>
#include <stdlib.h>
#include <nlohmann/json.hpp>

class PositionParse{
    public:
    PositionParse() = default;
    PositionParse(std::string &);
    ~PositionParse() = default;
    PositionParse & operator=(const PositionParse&) = delete;
    PositionParse(const PositionParse &)=delete;

    bool ParseFromFile(const std::string &path);
    bool ParseFromString(const std::string &origin);
    
    inline const double GetX() const{
        return this->x_v;
    }
    inline const double GetY() const{
        return this->y_v;
    }
    inline const double GetTS() const{
        return this->timestamp_v;
    }

    bool IsBegin() const; //判断是否是起始位置
    bool IsEnd() const;
    

    private:
    double x_v;
    double y_v;
    double timestamp_v;
    nlohmann::json __json;
    double begin=656.272;
    double end=169.277;


};
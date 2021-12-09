#include "position_parse.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

int main(){
    PositionParse test_parse;
    std::string path="/Users/bicycle/Documents/woker/json_test/data/position.jsonc";
    std::cout<<"++++++++++++++"<<" Test Parse From File: "<<"++++++++++++++"<<std::endl;
    test_parse.ParseFromFile(path);
    printf("%.6f\n", test_parse.GetX());
    printf("%.6f\n", test_parse.GetY());
    printf("%lld\n", test_parse.GetTS());

    std::cout<<"++++++++++++++"<<" Test Parse From String: "<<"++++++++++++++"<<std::endl;
    std::string origin = R"({
        "engine_id": "1",
        "data_type": "1",
        "tag_id": "0032",
        "tag_id_dec": "50",
        "x": "44.09889",
        "y": "10.80403",
        "z": "1.00000",
        "timestamp": "1535361775271",
        "sn": "16",
        "bettery": "3.91",
        "anchors": [
            {
                "anchor_id": "8478"
            },
            {
                "anchor_id": "8492"
            },
            {
                "anchor_id": "8572"
            },
            {
                "anchor_id": "85C8"
            },
            {
                "anchor_id": "8748"
            },
            {
                "anchor_id": "878A"
            }
        ],
        "events": [
            {
                "event_type": "LOCK"
            },
            {
                "event_type": "MOVE"
            }
        ],
        "heart_rates": {
            "heart_rate_val": "90",
            "heart_rate_quality": "2"
        },
        "move_level": {
            "level_val": "1",
            "move_timestamp": "1535361775271"
        },
        "hard_hat_alarm": {
            "alarm_type": "1",
            "alarm_timestamp": "1535361775271"
        },
        "blood_pressure": {
            "systolic_val": "1",
            "diastolic_val": "1",
            "timestamp": "1535361775271"
        },
        "blood_oxygen": {
            "oxygen_val": "1",
            "timestamp": "1535361775271"
        },
        "temperature": {
            "temp_val": "1",
            "timestamp": "1535361775271"
        }
    })";
    test_parse.ParseFromString(origin);
    printf("%.6f\n", test_parse.GetX());
    printf("%.6f\n", test_parse.GetY());
    printf("%lld\n", test_parse.GetTS());
    return 0;
}
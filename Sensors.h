#include <iostream>
#include <string>
#include <vector>
#include "Objects.h"

using namespace std;

enum class ObjectType {
    UNKNOWN,
    VEHICLE,
    BIKE,
    PEDESTRIAN,
    TRAFFIC_LIGHT,
    TRAFFIC_SIGN
};

struct SensorReading {
    ObjectType type = ObjectType::UNKNOWN;
    float distance;
    Position position{0,0};
    string objectId;
    float confidence;

    /* std::optional<float> speed;
    std::optional<Direction> direction;
    std::optional<std::string> signText;
    std::optional<std::string> trafficLightColor;*/
};



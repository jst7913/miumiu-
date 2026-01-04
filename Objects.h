#include <iostream>
#include <string>

using namespace std;

enum class Colour { RED, GREEN, YELLOW };
enum class Direction { NORTH, EAST, SOUTH, WEST };
enum class Speed {
    STOPPED,        // 0 cells/tick
    HALF_SPEED,     // 1 cell/tick
    FULL_SPEED      // 2 cells/tick
};



class GridWorld {
    int matrix[40][40];
public:
    //GridWorld() 

    ~GridWorld () {
        cout << "[Destructor] Grid World destroyed." << endl;
    }
};

//---Objects-----

class Position {
    int x;
    int y;
public:
    Position(int x, int y) : x(x), y(y) {}

    ~Position() {}
};


class WorldObject {
protected:
    string id;
    char glyph;
    Position pos;

public:
    WorldObject(const string& id, char glyph, int x, int y) : id(id), glyph(glyph), pos(x, y){}

    ~WorldObject() {}

    string getID() const { return id; }
    char getGlyph() const { return glyph; }
    Position getPosition() const { return pos; }

    virtual void tick() {}   
};

//----- StaticOBJs -----
class StaticObject : public WorldObject {
public:
    StaticObject(const string& id, char glyph, int x, int y) : WorldObject(id, glyph, x, y) {}

    ~StaticObject() {}
};

class StationaryVehicle : public StaticObject {
    static int counter;

public:
    StationaryVehicle(int x, int y) : StaticObject( "PARKED:" + std::to_string(++counter), 'P', x, y) { // ftiaksto analoga to ti zhtaei sth poreia
        std::cout << "[+PARKED: " << id << "]: Parked at (" << x << ", " << y << ")\n";
    }

    ~StationaryVehicle() {
        std::cout << "[-PARKED: " << id << "]: I'm being towed away !\n";
    }
};
int StationaryVehicle::counter = 0;


class TrafficSign : public StaticObject {
    static int counter;
    string text;

public:
    TrafficSign(int x, int y, const string& text) : StaticObject("SIGN:" + std::to_string(++counter), 'S', x, y), text(text) {
        //std::cout << "[+" << id << "] Sign created: " << text << " at ("  << x << ", " << y << ")\n";
    }

    bool isStop() const {
        return text == "STOP";
    }
};
int TrafficSign::counter = 0;



class TrafficLight : public StaticObject {
private:
    static int counter;
    Colour color;
    int ticks;

public:
    TrafficLight(int x, int y) : StaticObject("LIGHT:" + std::to_string(++counter), 'L', x, y), color(Colour::RED), ticks(0) {
        std::cout << "[+LIGHT: " << id << "] Initialized at (" << x << ", " << y << ") to RED\n";
    }

    ~TrafficLight() {
        std::cout << "[-" << id << "] Turning off\n";
    }

    void tick() override {
        ticks++;

        switch (color) {
        case Colour::RED:
            if (ticks == 4) { color = Colour::GREEN; ticks = 0; }
            break;
        case Colour::GREEN:
            if (ticks == 8) { color = Colour::YELLOW; ticks = 0; }
            break;
        case Colour::YELLOW:
            if (ticks == 2) { color = Colour::RED; ticks = 0; }
            break;
        }
    }

    Colour getColor() const { return color; }
};
int TrafficLight::counter = 0;


//----- MovingOBJs -----
class MovingObject : public WorldObject {
protected:
    Direction dir;
    Speed speed;

public:
    MovingObject(const std::string& id, char glyph, int x, int y, Direction dir) : WorldObject(id, glyph, x, y), dir(dir), speed(Speed::STOPPED) {}

    ~MovingObject() {}

    virtual void tick() = 0;
};







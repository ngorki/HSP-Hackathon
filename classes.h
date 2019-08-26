struct role{
    char *name;
    float hp;
    float atk;
    float def;
    int charged;
};

struct role classes[3] = {
    {"Assassin", 600, 40, 20, 2},
    {"Bruiser", 800, 30, 30, 3},
    {"Tank", 1000, 20, 40, 3}
};

struct subclass{
    char *subclassName;
    float classValue;
};

struct subclass subs[3][2] = {
    {{"Ninja Assassin", .5}, {"Vampire Assassin", 0.20}},
    {{"Bruiser Growth", .02},{"Bruiser Time Bomb", .20}},
    {{"Tank Missile", .05},{"Tank Camo", 0}}
};

struct role player1;
struct role player2;

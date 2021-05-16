# Infiltration

**Infiltration** is a stealth-like game me and a coupple of my friends
did as an end-of-term project for a programming course. The goal of the
game is to eliminate all of your enemies on the map in a sneaky manner --
that meaning, without getting caught.

And now, after some time has passed, I'm using this project as a base
for another task -- autodocumenting using __Doxygen__.

### Game manual (kind of) #

![Game screenshot](../screenshot.png)

#### How to play: #
- Use _directional keys_ to move around.
- Press _X_ while you're close to the enemy to kill him.
- Use _Left Ctrl_ to toggle between default and sprint modes.

### Code blocks #

Here are some code snippets from the main file
just so you know that I can include them here, too.

~~~{.cpp}
void MapGenerator::constructTree(std::vector<int> &tiles, std::vector<bool> &paths, int pos)
{
    // creating a vector of... functions!
    std::vector<int (MapGenerator::*)(std::vector<int> &tiles, std::vector<bool> &paths, int pos)> routes;

    routes.push_back(&MapGenerator::constructUp);
    routes.push_back(&MapGenerator::constructDown);
    routes.push_back(&MapGenerator::constructRight);
    routes.push_back(&MapGenerator::constructLeft);

    // shuffling it
    std::shuffle(routes.begin(), routes.end(), gen);

    // and that's how we add routes in a random sequence
    int newpos;
    for(int i = 0; i < 4; i++) {
        if(-1 != (newpos = (this->*(routes[i]))(tiles, paths, pos))) {
            constructTree(tiles, paths, newpos);
        }
    }
}
~~~

### Sources #
[Main repo](https://github.com/ArsenChick/infiltration)
#include "MouseEvent.h"
#include <vector>
#include <utility>

using namespace std;

static const vector<pair<MouseEventType, string>> events =
{
    make_pair(MouseEventType::DOWN, "Down"),
    make_pair(MouseEventType::UP, "Up"),
    make_pair(MouseEventType::MOVE, "Move")
};

string to_string(const MouseEventType &eventType)
{
    for(const auto &event : events)
        if(event.first == eventType)
            return event.second;

    return "";
}

MouseEventType to_mouseEvent(const std::string &eventName)
{
    for(const auto &event : events)
        if(event.second == eventName)
            return event.first;

    return MouseEventType::MOVE;
}

list<string> mouseActions()
{
    list<string> names;

    for(const auto &event : events)
        names.push_back(event.second);

    return names;
}

#pragma once

#include <cstdint>
#include <string_view>

class WindowClass
{
public:
    void Draw(std::string label);
    void AddTaskInList();
    void renderTodoList();
    void removeCompleted();
    void DrawToDoList();
};

void render(WindowClass& window_obj);
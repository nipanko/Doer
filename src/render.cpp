#include <iostream>
#include <imgui.h>
#include <implot.h>
#include "render.h"
#include <vector>

// Buffer for user input
static char inputBuffer[256] = "";

struct Task
{
    std::string description;
    bool completed = false;
};

std::vector<Task> tasks;

// Function to add a task to the list
void WindowClass::AddTaskInList()
{
    if (ImGui::Button("Add Task"))
    {
        ImGui::OpenPopup("AddTaskPopup");
    }

    // Add Task Popup
    if (ImGui::BeginPopupModal("AddTaskPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Task Description", inputBuffer, IM_ARRAYSIZE(inputBuffer),
            ImGuiInputTextFlags_EnterReturnsTrue);

        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            if (inputBuffer[0] != '\0')
            {
                tasks.push_back({ std::string(inputBuffer) });
                memset(inputBuffer, 0, sizeof(inputBuffer));
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }
}

// Function to render the To-Do List
void WindowClass::renderTodoList()
{
    ImGui::Text("TASK LIST");
    ImGui::Separator();
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        ImGui::Checkbox(tasks[i].description.c_str(), &tasks[i].completed);
        ImGui::SameLine();
        ImGui::Text(tasks[i].description.c_str());
    }
}

void WindowClass::removeCompleted()
{
    if(ImGui::Button("Remove Completed"))
    {
        for (auto it = tasks.begin(); it != tasks.end();)
        {
            if (it->completed)
            {
                it = tasks.erase(it); // Remove task and advance iterator
            }
            else
            {
                ++it; // Move to the next task
            }
        }
    }

}



void WindowClass::Draw(std::string label)
{
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
    constexpr static auto window_size = ImVec2(1280.0F, 720.0F);
    constexpr static auto window_pos = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowPos(window_pos);

    ImGui::Begin(label.data(), nullptr, window_flags);

    AddTaskInList();
    removeCompleted();
    ImGui::Separator();
    renderTodoList();

    ImGui::End();
}

void render(WindowClass& window_obj)
{
    window_obj.Draw("DOERS");
}

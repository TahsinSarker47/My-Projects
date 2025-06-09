#ifndef TASKTRACKER_HPP
#define TASKTRACKER_HPP

#include "Task.hpp"
#include <vector>
#include <string>

class TaskTracker {
public:
    explicit TaskTracker(const std::string& fname = "tasks.json");
    bool addTask(const std::string& description);
    bool updateTask(int id, const std::string& newDescription);
    bool deleteTask(int id);
    bool markTaskStatus(int id, const std::string& status);
    void listTasks(const std::string& filterStatus = "") const;

private:
    std::vector<Task> tasks;
    std::string filename;
    void loadTasks();
    bool saveTasks() const;
    void parseJsonArray(const std::string& jsonContent);
    void parseJsonObjects(const std::string& content);
    size_t findMatchingBrace(const std::string& content, size_t start) const;
    Task parseJsonObject(const std::string& objContent) const;
    int extractIntValue(const std::string& content, const std::string& key) const;
    std::string extractStringValue(const std::string& content, const std::string& key) const;
    int getNextId() const;
    static std::string trim(const std::string& str);
    static bool isWhitespace(const std::string& str);
};

#endif
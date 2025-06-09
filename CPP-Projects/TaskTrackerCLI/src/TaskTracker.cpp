#include "TaskTracker.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cctype>

TaskTracker::TaskTracker(const std::string& fname) : filename(fname) {
    loadTasks();
}

bool TaskTracker::addTask(const std::string& description) {
    if (description.empty() || isWhitespace(description)) {
        std::cout << "Error: Task description cannot be empty" << std::endl;
        return false;
    }
    int newId = getNextId();
    Task newTask(newId, trim(description));
    tasks.push_back(newTask);
    if (saveTasks()) {
        std::cout << "Task added successfully (ID: " << newId << ")" << std::endl;
        return true;
    } else {
        tasks.pop_back();
        return false;
    }
}

bool TaskTracker::updateTask(int id, const std::string& newDescription) {
    if (newDescription.empty() || isWhitespace(newDescription)) {
        std::cout << "Error: Task description cannot be empty" << std::endl;
        return false;
    }
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [id](const Task& task) { return task.id == id; });
    if (it == tasks.end()) {
        std::cout << "Error: Task with ID " << id << " not found" << std::endl;
        return false; 
    }
    it->updateDescription(trim(newDescription));
    if (saveTasks()) {
        std::cout << "Task " << id << " updated successfully" << std::endl;
        return true;
    }
    return false;
}

bool TaskTracker::deleteTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.id == id; });
    if (it == tasks.end()) {
        std::cout << "Error: Task with ID " << id << " not found" << std::endl;
        return false;
    }
    Task removedTask = *it;
    tasks.erase(it);
    if (saveTasks()) {
        std::cout << "Task " << id << " deleted successfully" << std::endl;
        return true;
    } else {
        tasks.push_back(removedTask);
        return false;
    }
}

bool TaskTracker::markTaskStatus(int id, const std::string& status) {
    if (status != "todo" && status != "in-progress" && status != "done") {
        std::cout << "Error: Invalid status. Must be one of: todo, in-progress, done" << std::endl;
        return false;
    }
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.id == id; });
    if (it == tasks.end()) {
        std::cout << "Error: Task with ID " << id << " not found" << std::endl;
        return false;
    }
    std::string oldStatus = it->status;
    it->updateStatus(status);

    if (saveTasks()) {
        std::cout << "Task " << id << " marked as " << status << std::endl;
    } else {
        it->updateStatus(oldStatus);
        return false;
    }
    return true;
}

void TaskTracker::listTasks(const std::string& filterStatus) const {
    std::vector<Task> filteredTasks;
    if (filterStatus.empty()) {
        filteredTasks = tasks;
    } else {
        if (filterStatus != "todo" && filterStatus != "in-progress" && filterStatus != "done") {
            std::cout << "Error: Invalid status filter. Must be one of: todo, in-rpogress, done" << std::endl;
            return;
        }
        std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(filteredTasks), [&filterStatus](const Task& task) { return task.status == filterStatus; });
    }
    if (filteredTasks.empty()) {
        if (filterStatus.empty()) {
            std::cout << "No tasks found. Add a task using: ./task-cli add \"Your task description\"" << std::endl;
        } else {
            std::cout << "No tasks found with status '" << filterStatus << "'" << std::endl;
        }
        return;
    }
    std::string header = filterStatus.empty() ? "All tasks" : "Tasks with status '" + filterStatus + "'";
    std::cout << "\n" << header << ":" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::sort(filteredTasks.begin(), filteredTasks.end(), [](const Task& a, const Task& b) { return a.id < b.id; });
    for (const auto& task : filteredTasks) {
        task.display();
    }
}

void TaskTracker::loadTasks() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::ofstream createFile(filename);
        if (createFile.is_open()) {
            createFile << "[]";
            createFile.close();
        }
        return;
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    try {
        parseJsonArray(content);
    } catch (const std::exception& e) {
        std::cout << "Warnign: Error parsing JSON file. Starting with empty task list." << std::endl;
        tasks.clear();
    }
}

bool TaskTracker::saveTasks() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file for writing" << std::endl;
        return false;
    }
    file << "[\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        file << tasks[i].toJson();
        if (i < tasks.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "]";
    file.close();
    return true;
}

void TaskTracker::parseJsonArray(const std::string& jsonContent) {
    tasks.clear();
    std::string content = trim(jsonContent);
    if (content == "[]" || content.empty()) {
        return;
    }
    size_t start = content.find('[');
    size_t end = content.rfind(']');
    if (start == std::string::npos || end == std::string::npos) {
        throw std::runtime_error("Invalid JSON array format");
    }
    std::string arrayContent = content.substr(start + 1, end - start - 1);
    arrayContent = trim(arrayContent);
    if (arrayContent.empty()) {
        return;
    }
    parseJsonObjects(arrayContent);
}

void TaskTracker::parseJsonObjects(const std::string& content) {
    size_t pos = 0;
    while (pos < content.length()) {
        size_t objStart = content.find('{', pos);
        if (objStart == std::string::npos) break;
        
        size_t objEnd = findMatchingBrace(content, objStart);
        if (objEnd == std::string::npos) break;

        std::string objContent = content.substr(objStart, objEnd - 
        objStart + 1);
        Task task = parseJsonObject(objContent);
        tasks.push_back(task);
        pos = objEnd + 1;
    }
}

size_t TaskTracker::findMatchingBrace(const std::string& content, size_t start) const {
    int braceCount = 0;
    for (size_t i = start; i < content.length(); ++i) {
        if (content[i] == '{') braceCount++;
        else if (content[i] == '}') {
            braceCount--;
            if (braceCount == 0) return i;
        }
    }
    return std::string::npos;
}

Task TaskTracker::parseJsonObject(const std::string& objContent) const {
    Task task;
    task.id = extractIntValue(objContent, "id");
    task.description = extractStringValue(objContent, "description");
    task.status = extractStringValue(objContent, "createdAt");
    task.createdAt = extractStringValue(objContent, "createdAt");
    task.updatedAt = extractStringValue(objContent, "updatedAt");

    return task;
}

int TaskTracker::extractIntValue(const std::string& content, const std::string& key) const {
    std::string pattern = "\"" + key + "\":";
    size_t pos = content.find(pattern);
    if (pos == std::string::npos) return 0;
    pos += pattern.length();
    while (pos < content.length() && std::isspace(content[pos])) pos++;
    size_t numStart = pos;
    while (pos < content.length() && std::isdigit(content[pos])) pos++;
    if (pos > numStart) {
        return std::stoi(content.substr(numStart, pos - numStart));
    }
    return 0;
}

std::string TaskTracker::extractStringValue(const std::string& content, const std::string& key) const {
    std::string pattern = "\"" + key + "\":";
    size_t pos = content.find(pattern);
    if (pos == std::string::npos) return "";
    pos += pattern.length();
    while (pos < content.length() && std::isspace(content[pos])) pos++;
    if (pos >= content.length() || content[pos] != '"') return "";
    size_t valueStart = pos;
    while (pos < content.length() && content[pos] != '"') {
        if (content[pos] == '\\') pos++;
        pos++;
    }
    return content.substr(valueStart, pos - valueStart);
}

int TaskTracker::getNextId() const {
    if (tasks.empty()) return 1;
    auto maxIt = std::max_element(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) { return a.id < b.id; });
    return maxIt->id + 1;
}

std::string TaskTracker::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

bool TaskTracker::isWhitespace(const std::string& str) {
    return str.find_last_not_of(" \t\n\r") == std::string::npos;
}
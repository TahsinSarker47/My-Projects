#include "Task.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <chrono>

Task::Task() : id(0), description(""), status("todo") {
    std::string timestamp = getCurrentTimestamp();
    createdAt = timestamp;
    updatedAt = timestamp;
} 

Task::Task(int id, const std::string& desc, const std::string& stat) : id(id), description(desc), status(stat) {
    std::string timestamp = getCurrentTimestamp();
    createdAt = timestamp;
    updatedAt = timestamp;
}

void Task::updateDescription(const std::string& newDesc) {
    description = newDesc;
    updatedAt = getCurrentTimestamp();
}

void Task::updateStatus(const std::string& newStatus) {
    status = newStatus;
    updatedAt = getCurrentTimestamp();
}

std::string Task::toJson() const {
    std::ostringstream json;
    json << "   {\n";
    json << "     \"id\": " << id << ",\n";
    json << "     \"description\": \"" << escapeJsonString(description) << "\",\n";
    json << "     \"status\": \"" << status << "\",\n";
    json << "     \"createdAt\": \"" << createdAt << "\",\n";
    json << "     \"updatedAt\": \"" << updatedAt << "\"\n";
    return json.str();
}

void Task::display() const {
    std::string statusDisplay;
    if (status == "todo") {
        statusDisplay = "⚪ TODO";
    } else if (status == "in-progress") {
        statusDisplay = "🟡 IN-PROGRESS";
    } else if (status == "done") {
        statusDisplay = "✅ DONE";
    } else {
        statusDisplay = status;
    }
    std::cout << "ID: " << id << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Status: " << formatTimestamp(createdAt) << std::endl;
    std::cout << "Updated: " << formatTimestamp(updatedAt) << std::endl;
    std::cout << std::string(60, '-') << std::endl;
}

std::string Task::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count() << 'Z';
    return oss.str();
}

std::string Task::formatTimestamp(const std::string& timestamp) {
    if (timestamp.length() >= 19) {
        std::string formatted = timestamp.substr(0, 19);
        std::replace(formatted.begin(), formatted.end(), 'T', ' ');
        return formatted;
    }
    return timestamp;
}

std::string Task::escapeJsonString(const std::string& str) {
    std::string escaped;
    for (char c : str) {
        switch (c) {
            case '"': escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\b': escaped += "\\b"; break;
            case '\f': escaped += "\\f"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default: escaped += c; break;
        }
    }
    return escaped;
}
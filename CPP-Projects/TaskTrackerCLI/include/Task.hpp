#ifndef TASK_HPP
#define TASK_HPP

#include <string>


class Task {
public:
    Task();
    explicit Task(int id, const std::string& desc, const std::string& stat = "todo");
    int id;
    std::string description;
    std::string createdAt;
    std::string updatedAt;
    std::string status;
    void updateDescription(const std::string& newDesc);
    void updateStatus(const std::string& newStatus);
    std::string toJson() const;
    void display() const;
private:
    static std::string getCurrentTimestamp();
    static std::string formatTimestamp(const std::string& timestamp);
    static std::string escapeJsonString(const std::string& str);
        
};

#endif
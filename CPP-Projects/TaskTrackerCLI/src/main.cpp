#include "TaskTracker.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

void printUsage() {
    std::cout << R"(
Task Tracker CLI - Manage your tasks from the command line

Usage:
    ./task-cli add "Task description"
    ./task-cli list
    ./task-cli list [todo|in-progress|done]
    ./task-cli update <id> "New description"
    ./task-cli delete <id>
    ./task-cli mark-in-progress <id>
    ./task-cli mark-done <id>

Examples:
    ./task-cli add "Buy groceries"
    ./task-cli list done
    ./task-cli update 1 "Buy grocceries and cook dinner"
    ./task-cli mark-in-progress 1
    ./task-cli delete 1
    
Features:
    - Automatic task ID generation
    - JSON file persistance (tasks.json)
    - Timestamp tracking for creation and updates
    - Status filtering and Unicode status indicators
    - Input validation and error hanling
)"  << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }
    TaskTracker tracker;
    std::string command = argv[1];
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    try {
        if (command == "add") {
            if (argc < 3) {
                std::cout << "Error: Please provide a task description\n";
                std::cout << "Usage: ./task-cli add \"Task description\"\n";
                return 1;
            }
            std::string description;
            for (int i = 2; i < argc; ++i) {
                if (i > 2) description += " ";
                description += argv[i];
            }
            tracker.addTask(description);
        } else if (command == "list") {
            if (argc == 2) {
                tracker.listTasks();
            } else if (argc == 3) {
                std::string status = argv[2];
                std::transform(status.begin(), status.end(), status.begin(), ::tolower);
                tracker.listTasks(status);
            } else {
                std::cout << "Error: Too many arguments for list command\n";
                std::cout << "Usage: ./task-cli list [todo|in-progress|done]\n";
                return 1;
            }
        } else if (command == "update") {
            if (argc < 4) {
                std::cout << "Error: Please provide task ID and new description\n";
                std::cout << "Usage: ./task-cli update <id> \"New description\"\n";
                return 1;
            }
            try {
                int taskId = std::stoi(argv[2]);
                std::string newDescription;
                for (int i = 3; i < argc; ++i) {
                    if (i > 3) newDescription += " ";
                    newDescription += argv[i];
                }
                tracker.updateTask(taskId, newDescription);
            } catch (const std::invalid_argument&) {
                std::cout << "Error: Task ID must be a number\n";
                return 1;
            }
        } else if (command == "delete") {
            if (argc != 3) {
                std::cout << "Error: Please provide a task ID\n";
                std::cout << "Usage: ./task-cli delete <id>\n";
                return 1;
            }
            try {
                int taskId = std::stoi(argv[2]);
                tracker.deleteTask(taskId);
            } catch (const std::invalid_argument&) {
                std::cout << "Error: Task ID must be a number\n";
                return 1;
            }
        } else if (command == "mar-in-progress") {
            if (argc != 3) {
                std::cout << "Error: Please provide a task ID\n";
                std::cout << "Usage: ./task-cli mark-in-progress <id>\n";
                return 1;
            }
            try {
                int taskId = std::stoi(argv[2]);
                tracker.markTaskStatus(taskId, "in-progress");
            } catch (const std::invalid_argument&) {
                std::cout << "Error: Task ID must be a number\n";
                return 1;
            }
        } else if (command == "mark-done") {
            if (argc != 3) {
                std::cout << "Error: Please provide a task ID\n";
                std::cout << "Usage: ./task-cli mark-done <id>\n";
                return 1;
            }
            try {
                int taskId = std::stoi(argv[2]);
                tracker.markTaskStatus(taskId, "done");
            } catch (const std::invalid_argument&) {
                std::cout << "Error: Task ID must be a number\n";
                return 1;
            }
        } else {
            std::cout << "Error: Unknown command '" << command << "'\n";
            printUsage();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
#include "Waypoint.h"
#include "PathManager.h"

PathManager* PathManager::m_instance = nullptr;

PathManager * PathManager::GetInstance() {
    if(!m_instance) {
        m_instance = new PathManager;
    }

    return m_instance;
}

int PathManager::NumPaths() {
    return m_paths.size();
}

bool PathManager::LoadPathsText(string text) {
    json loadedJson;

    try {
        loadedJson = json::parse(text);
    } catch (const exception& e) {
        Logger::logError("Could not parse paths file:" + string(e.what()));
        return false;
    }

    return LoadPaths(loadedJson);
}

bool PathManager::LoadPaths(json loadedJson) {
    m_paths = vector<Path>();

    try {
        json pathJson;
        for (auto path : loadedJson["paths"]) {
            string name = path["name"];
            vector<Waypoint> waypoints;
            for (auto point : path["points"]) {
                Vector2d point1 = Vector2d(point["x"], point["y"]);
                double speed = point["speed"];
                Waypoint waypoint(point1, speed); //TODO: Implement state command logic
                waypoints.push_back(waypoint);
            }
            Path newPath(name, waypoints);
            m_paths.push_back(newPath);
        }
    } catch (const exception& e) {
        Logger::logError("Error reading json path! " + string(e.what()));
        return false;
    }

    return true;
}

bool PathManager::LoadPathsFile(string filePath) {
    ifstream pathsFile;
    try {
        pathsFile.open(filePath);
        if(!pathsFile.is_open()) {
            Logger::logError("Could not open paths file at " + filePath);
            return false;
        }
    } catch (const exception& e) {
        Logger::logError("Could not open paths file at " + filePath + " : " + string(e.what()));
        return false;
    }

    json loadedJson;
    try {
        pathsFile >> loadedJson;
    } catch (const exception& e) {
        Logger::logError("Could not parse paths file:" + string(e.what()));
        pathsFile.close();
        return false;
    }

    pathsFile.close();
    return LoadPaths(loadedJson);
}

vector<Path> PathManager::GetPaths() {
    return m_paths;
}

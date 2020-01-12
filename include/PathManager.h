#pragma once

#include "Path.h"
#include <memory>
#include <fstream>

class PathManager {
public:
    static PathManager* GetInstance();

    bool LoadPathsText(string text);
    bool LoadPaths(json pathJson);
    bool LoadPathsFile(string filePath);

    int NumPaths();

    vector<Path> GetPaths();

private:
    PathManager() = default;
    vector<Path> m_paths;
    static PathManager* m_instance;
};



//
// Created by luca on 27/05/18.
//

#ifndef CG_PATH_TRACER_LOADER_H
#define CG_PATH_TRACER_LOADER_H


#include <string>

class Loader {

public:
    std::string path;

    Loader(const std::string& path);

    virtual void load() = 0;

};


#endif //CG_PATH_TRACER_LOADER_H

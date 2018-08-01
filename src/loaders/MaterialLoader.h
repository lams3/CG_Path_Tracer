//
// Created by luca on 28/07/18.
//

#ifndef CG_PATH_TRACER_MATERIALLOADER_H
#define CG_PATH_TRACER_MATERIALLOADER_H


#include "../core/Material.h"

class MaterialLoader {
	public:
	void load(const std::string& path, Material*& material);
};


#endif //CG_PATH_TRACER_MATERIALLOADER_H

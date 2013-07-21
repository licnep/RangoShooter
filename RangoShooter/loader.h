//
//  loader.h
//  nuova_prova_assimp
//
//  Created by Lorenzo Sciandra on 25/06/13.
//  Copyright (c) 2013 Lorenzo Sciandra. All rights reserved.
//

#ifndef nuova_prova_assimp_loader_h
#define nuova_prova_assimp_loader_h

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "assimp--2.0.863-sdk/include/assimp.h"
#include "assimp--2.0.863-sdk/include/aiPostProcess.h"
#include "assimp--2.0.863-sdk/include/aiScene.h"
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include "assimp.h"
#include "aiPostProcess.h"
#include "aiScene.h"
#endif

#include <IL/il.h>


//to map image filenames to textureIds
#include <string.h>
#include <map>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)
#define TRUE                1
#define FALSE               0

// trying to create something that will work properly

struct myScene {
    const struct aiScene* scene;
    struct aiVector3D scene_min, scene_max, scene_center;
};

//now the declaration of functions:

void get_bounding_box_for_node (const struct aiScene *,
                                const struct aiNode*,
                                struct aiVector3D*,
                                struct aiVector3D*,
                                struct aiMatrix4x4*);

void get_bounding_box (const struct aiScene *, struct aiVector3D*, struct aiVector3D*);

void color4_to_float4(const struct aiColor4D *, float );

void set_float4(float , float, float, float, float);

void apply_material(const struct aiMaterial *);

void Color4f(const struct aiColor4D *);

void recursive_render (const struct aiScene *, const struct aiNode*, float);

int LoadGLTextures(const aiScene*);

int loadasset (const char*, struct myScene*);

#endif

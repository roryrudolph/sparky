#ifndef TILELAYER_H_
#define TILELAYER_H_


#include "Renderer2D.h"
#include "BatchRenderer2D.h"
#include "Shader.h"
#include "Layer.h"

class TileLayer : public Layer
{
public:
	TileLayer(Shader *shader);
	~TileLayer();
};


#endif // TILELAYER_H_

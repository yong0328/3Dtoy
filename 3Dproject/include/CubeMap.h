#pragma once
#include "DrawObject.h"
#include "Base.h"
class CubeMap : public BaseObj
{
public:
	CubeMap();
	~CubeMap();
	CubeMap& operator=(const CubeMap&) = delete;
	CubeMap(const CubeMap&) = delete;
	void initCubeMap();
	unsigned int loadCubeMap();
	unsigned int CreateCubemapModel();
	virtual void Render() override;
private:
	unsigned int m_uCubeMapTexID;
	const std::vector<std::string> m_vCubemapPath = {
	"res/skybox/right.jpg",
	"res/skybox/left.jpg",
	"res/skybox/top.jpg",
	"res/skybox/bottom.jpg",
	"res/skybox/front.jpg",
	"res/skybox/back.jpg",
	};
};
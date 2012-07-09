#include "irrlicht/irrlicht.h"

using namespace irr;

scene::IMeshSceneNode* create_coqueiro1(scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
	video::IVideoDriver* driver = smgr->getVideoDriver();
	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/coqueiro1.3ds");
	scene::IMeshSceneNode* coqueiro = smgr->addMeshSceneNode(mesh,
															parent,
															-1, //id
															core::vector3df(x, y, z), //position
															core::vector3df(0, 0, 0), //rotation
															core::vector3df(0.2f, 0.2f, 0.2f), //scale
															false); //also Add If Mesh Pointer is Zero
	coqueiro->setMaterialTexture(0, driver->getTexture("media/3dmodels/coqueiro1.jpg"));
	coqueiro->setMaterialFlag(video::EMF_LIGHTING, false);
	return coqueiro;
}



scene::IMeshSceneNode* create_coqueiro3(scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
	video::IVideoDriver* driver = smgr->getVideoDriver();
	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/coqueiro3.3ds");
	scene::IMeshSceneNode* coqueiro = smgr->addMeshSceneNode(mesh,
															parent,
															-1, //id
															core::vector3df(x, y, z), //position
															core::vector3df(0, 0, 0), //rotation
															core::vector3df(0.05f, 0.05f, 0.05f), //scale
															false); //also Add If Mesh Pointer is Zero
//	coqueiro->setMaterialTexture(0, driver->getTexture("media/3dmodels/coqueiro1.jpg"));
	coqueiro->setMaterialFlag(video::EMF_LIGHTING, false);
	return coqueiro;
}



scene::IMeshSceneNode* create_papiro(scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
	video::IVideoDriver* driver = smgr->getVideoDriver();
	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/papiro1.3ds");
	scene::IMeshSceneNode* papiro = smgr->addMeshSceneNode(mesh,
															parent,
															-1, //id
															core::vector3df(x, y, z), //position
															core::vector3df(0, 0, 0), //rotation
															core::vector3df(0.1f, 0.1f, 0.1f), //scale
															false); //also Add If Mesh Pointer is Zero
	papiro->setMaterialTexture(0, driver->getTexture("media/3dmodels/papiro1.jpg"));
	papiro->setMaterialFlag(video::EMF_LIGHTING, false);
	return papiro;
}



scene::IMeshSceneNode* create_eagle(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/eagle.3DS");
	scene::IMeshSceneNode* eagle = smgr->addMeshSceneNode(mesh,
															parent,
															-1, 								//id
															core::vector3df(x, y, z), 			//position
															core::vector3df(0, -90, 0),			//rotation
															core::vector3df(0.1f, 0.1f, 0.1f),	//scale
															false); //also Add If Mesh Pointer is Zero
	eagle->setMaterialFlag(video::EMF_LIGHTING, false);
	eagle->setVisible(true);
	return eagle;
}




//void create_coqueiro2(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
//	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/coqueiro2.3ds");
//	scene::IMeshSceneNode* coqueiro = smgr->addMeshSceneNode(mesh,
//															parent,
//															-1, //id
//															core::vector3df(x, y, z), //position
//															core::vector3df(0, 0, 0), //rotation
//															core::vector3df(1.0f, 1.0f, 1.0f), //scale
//															false); //also Add If Mesh Pointer is Zero
////	coqueiro->setMaterialTexture(0, driver->getTexture("media/3dmodels/coqueiro1.jpg"));
//	coqueiro->setMaterialFlag(video::EMF_LIGHTING, false);
//}




//void create_tree(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
//	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/tree1.3ds");
//	scene::IMeshSceneNode* tree = smgr->addMeshSceneNode(mesh,
//															parent,
//															-1, 								//id
//															core::vector3df(x, y, z), 			//position
//															core::vector3df(0, 0, 0),			//rotation
//															core::vector3df(1.0f, 1.0f, 1.0f),	//scale
//															false); //also Add If Mesh Pointer is Zero
////	tree->setMaterialTexture(0, driver->getTexture("media/3dmodels/papiro1.jpg"));
//	tree->setMaterialFlag(video::EMF_LIGHTING, true);
//	tree->setVisible(true);
//}





//scene::IMeshSceneNode* create_bird(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
//	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/bird/HUMBIRD.3DS");
//	scene::IMeshSceneNode* tree = smgr->addMeshSceneNode(mesh,
//															parent,
//															-1, 								//id
//															core::vector3df(x, y, z), 			//position
//															core::vector3df(0, 0, 0),			//rotation
//															core::vector3df(1.0f, 1.0f, 1.0f),	//scale
//															false); //also Add If Mesh Pointer is Zero
////	tree->setMaterialTexture(0, driver->getTexture("media/3dmodels/papiro1.jpg"));
//	tree->setMaterialFlag(video::EMF_LIGHTING, false);
//	tree->setVisible(true);
//	return tree;
//}

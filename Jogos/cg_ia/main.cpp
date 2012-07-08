/** Example 012 Terrain Rendering

This tutorial will briefly show how to use the terrain renderer of Irrlicht. It
will also show the terrain renderer triangle selector to be able to do
collision detection with terrain.

Note that the Terrain Renderer in Irrlicht is based on Spintz'
GeoMipMapSceneNode, lots of thanks go to him. DeusXL provided a new elegant
simple solution for building larger area on small heightmaps -> terrain
smoothing.

In the beginning there is nothing special. We include the needed header files
and create an event listener to listen if the user presses a key: The 'W' key
switches to wireframe mode, the 'P' key to pointcloud mode, and the 'D' key
toggles between solid and detail mapped material.
*/
#include "irrlicht/irrlicht.h"
#include "irrlicht/driverChoice.h"
//#include "irrlicht/IMesh.h"

using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:

	MyEventReceiver(scene::ISceneNode* terrain, scene::ISceneNode* skybox, scene::ISceneNode* skydome) :
		Terrain(terrain), Skybox(skybox), Skydome(skydome), showBox(true)
	{
		Skybox->setVisible(true);
		Skydome->setVisible(false);
	}

	bool OnEvent(const SEvent& event)
	{
		// check if user presses the key 'W' or 'D'
		if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
		{
			switch (event.KeyInput.Key)
			{
			case irr::KEY_KEY_W: // switch wire frame mode
				Terrain->setMaterialFlag(video::EMF_WIREFRAME,
						!Terrain->getMaterial(0).Wireframe);
				Terrain->setMaterialFlag(video::EMF_POINTCLOUD, false);
				return true;
			case irr::KEY_KEY_P: // switch wire frame mode
				Terrain->setMaterialFlag(video::EMF_POINTCLOUD,
						!Terrain->getMaterial(0).PointCloud);
				Terrain->setMaterialFlag(video::EMF_WIREFRAME, false);
				return true;
			case irr::KEY_KEY_D: // toggle detail map
				Terrain->setMaterialType(
					Terrain->getMaterial(0).MaterialType == video::EMT_SOLID ?
					video::EMT_DETAIL_MAP : video::EMT_SOLID);
				return true;
			case irr::KEY_KEY_S: // toggle skies
				showBox=!showBox;
				Skybox->setVisible(showBox);
				Skydome->setVisible(!showBox);
				return true;
			default:
				break;
			}
		}

		return false;
	}

private:
	scene::ISceneNode* Terrain;
	scene::ISceneNode* Skybox;
	scene::ISceneNode* Skydome;
	bool showBox;
};



void create_HUD(video::IVideoDriver* driver, gui::IGUIEnvironment* env) {
	// add irrlicht logo
	env->addImage(driver->getTexture("media/irrlichtlogo2.png"),
		core::position2d<s32>(10,10));

	//set other font
	env->getSkin()->setFont(env->getFont("media/fontlucida.png"));

	// add some help text
	env->addStaticText(
		L"Press 'W' to change wireframe mode\nPress 'D' to toggle detail map\nPress 'S' to toggle skybox/skydome",
		core::rect<s32>(10,421,250,475), true, true, 0, -1, true);
}




scene::ICameraSceneNode* create_camera_and_light(video::IVideoDriver* driver, scene::ISceneManager* smgr) {
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0,100.0f,1.2f);
	camera->setPosition(core::vector3df(3583, 1000, 6240));
	camera->setTarget(core::vector3df(3583, 640, 0));
	camera->setFarValue(42000.0f);

	// add sun light
	scene::ISceneNode* node = smgr->addLightSceneNode(0, core::vector3df(2700*3,255*25,2600*2),
	                video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 800000.0f);

	// attach billboard to light
	node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(5000, 5000));
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	node->setMaterialTexture(0, driver->getTexture("media/particlewhite.bmp"));
	return camera;
}




void colide_with_terrain(scene::ISceneManager* smgr, scene::ITriangleSelector* selector, scene::ISceneNode* node) {
	/*
	To be able to do collision with the terrain, we create a triangle selector.
	If you want to know what triangle selectors do, just take a look into the
	collision tutorial. The terrain triangle selector works together with the
	terrain. To demonstrate this, we create a collision response animator
	and attach it to the camera, so that the camera will not be able to fly
	through the terrain.
	*/
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector, node, core::vector3df(60,100,60),
		core::vector3df(0,0,0),
		core::vector3df(0,50,0));
	node->addAnimator(anim);
	anim->drop();
}





scene::ITerrainSceneNode* create_island(video::IVideoDriver* driver, scene::ISceneManager* smgr) {
	/*
	Here comes the terrain renderer scene node: We add it just like any
	other scene node to the scene using
	ISceneManager::addTerrainSceneNode(). The only parameter we use is a
	file name to the heightmap we use. A heightmap is simply a gray scale
	texture. The terrain renderer loads it and creates the 3D terrain from
	it.

	To make the terrain look more big, we change the scale factor of
	it to (40, 4.4, 40). Because we don't have any dynamic lights in the
	scene, we switch off the lighting, and we set the file
	terrain-texture.jpg as texture for the terrain and detailmap3.jpg as
	second texture, called detail map. At last, we set the scale values for
	the texture: The first texture will be repeated only one time over the
	whole terrain, and the second one (detail map) 20 times.
	*/

	// add terrain scene node
	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
		"media/island.bmp",
		0,					// parent node
		-1,					// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(30.f, 10.f, 30.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
		);

	terrain->setMaterialFlag(video::EMF_LIGHTING, true);

	terrain->setMaterialTexture(0, driver->getTexture("media/grass.jpg"));
	terrain->setMaterialTexture(1, driver->getTexture("media/detailmap3.jpg"));

	terrain->setMaterialType(video::EMT_DETAIL_MAP);

	terrain->scaleTexture(1.0f, 20.0f);
	//terrain->setDebugDataVisible ( true );

	return terrain;
}



void create_water(video::IVideoDriver* driver, scene::ISceneManager* smgr) {

	// agua do lago onde a cachoeira cai
	scene::IAnimatedMesh* mesh = smgr->addHillPlaneMesh("lago_cachoeira",
									core::dimension2d<f32>(250,153),			//tileSize
									core::dimension2d<u32>(10,10), 0, 0, 	//tileCount, material, hillHeight
									core::dimension2d<f32>(0,0), 			//countHills
									core::dimension2d<f32>(1, 1)); 		//textureRepeatCount
	scene::ISceneNode* node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0),
														20.32432f,   //waveHeight
														1001.8732f, //waveSpeed
														3.0672638476f); //waveLength
	node->setPosition(core::vector3df(3460, 580, 4950));
//	node->setMaterialTexture(0, driver->getTexture("media/stones.jpg"));
	node->setMaterialTexture(0, driver->getTexture("media/rock-texture.jpg"));
	node->setMaterialTexture(1, driver->getTexture("media/water2.jpg"));
	node->setMaterialType(video::EMT_REFLECTION_2_LAYER);



	// agua do rio depois do lago
	mesh = smgr->addHillPlaneMesh("rio_depois_do_lago",
									core::dimension2d<f32>(60,150),			//tileSize
									core::dimension2d<u32>(10,10), 0, 0, 	//tileCount, material, hillHeight
									core::dimension2d<f32>(0,0), 			//countHills
									core::dimension2d<f32>(1, 1)); 		//textureRepeatCount
	node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0),
														1.0f,   //waveHeight
														200.0f, //waveSpeed
														30.0f); //waveLength
	node->setPosition(core::vector3df(3530, 580, 6450));
//	node->setMaterialTexture(0, driver->getTexture("media/stones.jpg"));
	node->setMaterialTexture(0, driver->getTexture("media/rock-texture.jpg"));
	node->setMaterialTexture(1, driver->getTexture("media/water2.jpg"));
	node->setMaterialType(video::EMT_REFLECTION_2_LAYER);



	// agua do rio antes da cachu
	mesh = smgr->addHillPlaneMesh("rio_antes_da_cachu",
									core::dimension2d<f32>(130,320),			//tileSize
									core::dimension2d<u32>(10,10), 0, 0, 	//tileCount, material, hillHeight
									core::dimension2d<f32>(0,0), 			//countHills
									core::dimension2d<f32>(1, 1)); 		//textureRepeatCount
	node = smgr->addWaterSurfaceSceneNode(mesh->getMesh(0),
														1.0f,   //waveHeight
														200.0f, //waveSpeed
														30.0f); //waveLength
	node->setPosition(core::vector3df(3600, 2210, 2120));
//	node->setMaterialTexture(0, driver->getTexture("media/stones.jpg"));
	node->setMaterialTexture(0, driver->getTexture("media/rock-texture.jpg"));
	node->setMaterialTexture(1, driver->getTexture("media/water2.jpg"));
	node->setMaterialType(video::EMT_REFLECTION_2_LAYER);

}





void create_river(video::IVideoDriver* driver, scene::ISceneManager* smgr) {
	scene::IParticleSystemSceneNode* ps;
	scene::IParticleEmitter* cachu;

	// rio antes da cachoeira
	ps = smgr->addParticleSystemSceneNode(false);
	cachu = ps->createBoxEmitter(
				core::aabbox3d<f32>(0, 0, 0, 1200, 1, 60), // emitter size
				core::vector3df(0.0f, 0.0f, 1.0f),   // initial direction
				1000,1200,                             // emit rate
				video::SColor(0,0,0,255),       // darkest color
				video::SColor(0,0,0,255),       // brightest color
				3100, 3100, 0,                         // min and max age, angle
				core::dimension2df(80.f,80.f),         // min size
				core::dimension2df(150.f,150.f));        // max size
	ps->setEmitter(cachu); // this grabs the emitter
	cachu->drop(); // so we can drop it here without deleting it
	ps->setPosition(core::vector3df(3000, 2200, 600));
//	ps->setScale(core::vector3df(1, 1, 18));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);



	// cachoeira
	ps = smgr->addParticleSystemSceneNode(false);
	cachu = ps->createBoxEmitter(
			core::aabbox3d<f32>(0, 0, 0, 1200, 1, 60), // emitter size
			core::vector3df(0.0f, 0.0f, 1.0f),   // initial direction
			1000,1200,                             // emit rate
			video::SColor(0,0,0,255),       // darkest color
			video::SColor(0,0,0,255),       // brightest color
			1300,1300,0,                         // min and max age, angle
			core::dimension2df(35.f,100.f),         // min size
			core::dimension2df(65.f,220.f));        // max size
	ps->setEmitter(cachu); // this grabs the emitter
	cachu->drop(); // so we can drop it here without deleting it
	// gravidade para as partículas
	scene::IParticleAffector* paf = ps->createGravityAffector(core::vector3df(0.0f,-2.0f, 0.2f));
	ps->addAffector(paf); // same goes for the affector
	paf->drop();
	ps->setPosition(core::vector3df(3000, 2200, 3700)); //5786
//	ps->setScale(core::vector3df(2,2,2));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);




	// lago depois do cachoeira
	ps = smgr->addParticleSystemSceneNode(false);
	cachu = ps->createBoxEmitter(
				core::aabbox3d<f32>(0, 0, 0, 2200, 1, 60), // emitter size
				core::vector3df(0.0f, 0.0f, 0.7f),   // initial direction
				1000,1200,                             // emit rate
				video::SColor(0,0,0,255),       // darkest color
				video::SColor(0,0,0,255),       // brightest color
				2300, 2300, 0,                         // min and max age, angle
				core::dimension2df(150.f,150.f),         // min size
				core::dimension2df(150.f,150.f));        // max size
	ps->setEmitter(cachu); // this grabs the emitter
	cachu->drop(); // so we can drop it here without deleting it
	ps->setPosition(core::vector3df(2500, 550, 4000));
//	ps->setScale(core::vector3df(1, 1, 18));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);




	// rio depois do lago
	ps = smgr->addParticleSystemSceneNode(false);
	cachu = ps->createBoxEmitter(
				core::aabbox3d<f32>(0, 0, 0, 550, 1, 60), // emitter size
				core::vector3df(0.0f, 0.0f, 1.2f),   // initial direction
				1000,1200,                             // emit rate
				video::SColor(0,0,0,255),       // darkest color
				video::SColor(0,0,0,255),       // brightest color
				1200, 1200, 0,                         // min and max age, angle
				core::dimension2df(80.f,80.f),         // min size
				core::dimension2df(120.f,120.f));        // max size
	ps->setEmitter(cachu); // this grabs the emitter
	cachu->drop(); // so we can drop it here without deleting it
	ps->setPosition(core::vector3df(3250, 580, 5650));
//	ps->setScale(core::vector3df(1, 1, 18));
	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, driver->getTexture("media/fire.bmp"));
	ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}




void create_coqueiro1(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/coqueiro1.3ds");
	scene::IMeshSceneNode* coqueiro = smgr->addMeshSceneNode(mesh,
															parent,
															-1, //id
															core::vector3df(x, y, z), //position
															core::vector3df(0, 0, 0), //rotation
															core::vector3df(0.2f, 0.8f, 0.2f), //scale
															false); //also Add If Mesh Pointer is Zero
	coqueiro->setMaterialTexture(0, driver->getTexture("media/3dmodels/coqueiro1.jpg"));
	coqueiro->setMaterialFlag(video::EMF_LIGHTING, false);
}



void create_coqueiro2(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/coqueiro2.3ds");
	scene::IMeshSceneNode* coqueiro = smgr->addMeshSceneNode(mesh,
															parent,
															-1, //id
															core::vector3df(x, y, z), //position
															core::vector3df(0, 0, 0), //rotation
															core::vector3df(1.0f, 1.0f, 1.0f), //scale
															false); //also Add If Mesh Pointer is Zero
//	coqueiro->setMaterialTexture(0, driver->getTexture("media/3dmodels/coqueiro1.jpg"));
	coqueiro->setMaterialFlag(video::EMF_LIGHTING, false);
}




void create_papiro(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
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
}




void create_tree(video::IVideoDriver* driver, scene::ISceneManager* smgr, int x, int y, int z, scene::ISceneNode* parent = 0) {
	scene::IMesh* mesh = smgr->getMesh("media/3dmodels/tree1.3ds");
	scene::IMeshSceneNode* tree = smgr->addMeshSceneNode(mesh,
															parent,
															-1, 								//id
															core::vector3df(x, y, z), 			//position
															core::vector3df(0, 0, 0),			//rotation
															core::vector3df(1.0f, 1.0f, 1.0f),	//scale
															false); //also Add If Mesh Pointer is Zero
//	tree->setMaterialTexture(0, driver->getTexture("media/3dmodels/papiro1.jpg"));
	tree->setMaterialFlag(video::EMF_LIGHTING, true);
	tree->setVisible(true);
}


/*
The start of the main function starts like in most other example. We ask the
user for the desired renderer and start it up. This time with the advanced
parameter handling.
*/
int main()
{
	bool shadows = true;

//	// ask user for driver
//	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
//	if (driverType==video::EDT_COUNT)
//		return 1;

	// create device with full flexibility over creation parameters
	// you can add more parameters if desired, check irr::SIrrlichtCreationParameters
	irr::SIrrlichtCreationParameters params;
//	params.DriverType=driverType;
	params.DriverType = video::EDT_OPENGL;
	params.WindowSize=core::dimension2d<u32>(640, 480);
	params.Stencilbuffer = shadows; // dynamic shadows
	IrrlichtDevice* device = createDeviceEx(params);

	if (device == 0)
		return 1; // could not create selected driver.


	/*
	First, we add standard stuff to the scene: A nice irrlicht engine
	logo, a small help text, a user controlled camera, and we disable
	the mouse cursor.
	*/

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();

	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	// create the HUD
	create_HUD(driver, env);

	// add camera and sun
	scene::ICameraSceneNode* camera = create_camera_and_light(driver, smgr);


	// disable mouse cursor
	device->getCursorControl()->setVisible(false);


	// add terrain scene node
	scene::ITerrainSceneNode* terrain = create_island(driver, smgr);


	// create triangle selector for the terrain
	scene::ITriangleSelector* selector = smgr->createTerrainTriangleSelector(terrain, 0);
	terrain->setTriangleSelector(selector);


	// add colision between camera and terrain
	colide_with_terrain(smgr, selector, camera);
	selector->drop();


	// rio de emissor de partículas
//	create_river(driver, smgr);


	// plantes
	create_coqueiro1(driver, smgr, 2500, 340, 6139);
	create_coqueiro2(driver, smgr, 5000, 340, 6139);
	create_papiro(driver, smgr, 5000, 630, 4500);
//	create_tree(driver, smgr, 2500, 340, 6139);


	// add water to lake
//	create_water(driver, smgr);



	/*
	To make the user be able to switch between normal and wireframe mode,
	we create an instance of the event reciever from above and let Irrlicht
	know about it. In addition, we add the skybox which we already used in
	lots of Irrlicht examples and a skydome, which is shown mutually
	exclusive with the skybox by pressing 'S'.
	*/

	// create skybox and skydome
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
		driver->getTexture("media/irrlicht2_up.jpg"),
		driver->getTexture("media/irrlicht2_dn.jpg"),
		driver->getTexture("media/irrlicht2_lf.jpg"),
		driver->getTexture("media/irrlicht2_rt.jpg"),
		driver->getTexture("media/irrlicht2_ft.jpg"),
		driver->getTexture("media/irrlicht2_bk.jpg"));
//		scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("media/skydome.jpg"),16,8,0.95f,2.0f);
	scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("media/blue_sea.jpg"),16,8,0.95f,2.0f);

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

	// create event receiver
	MyEventReceiver receiver(terrain, skybox, skydome);
	device->setEventReceiver(&receiver);


	/*
	That's it, draw everything.
	*/

	int lastFPS = -1;

	while(device->run())
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, 0 );

		smgr->drawAll();
		env->drawAll();

		driver->endScene();

		// display frames per second in window title
		int fps = driver->getFPS();
		if (lastFPS != fps)
		{
			core::stringw str = L"Ilha [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;
			// Also print terrain height of current camera position
			// We can use camera position because terrain is located at coordinate origin
			str += " x: ";
			str += camera->getAbsolutePosition().X;
			str += " y: ";
			str += camera->getAbsolutePosition().Y;
			str += " z: ";
			str += camera->getAbsolutePosition().Z;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}

	device->drop();

	return 0;
}

/*
Now you know how to use terrain in Irrlicht.
**/


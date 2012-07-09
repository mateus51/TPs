#include "irrlicht/irrlicht.h"
using namespace irr;

class Bird : public scene::ISceneNode {
public:

	Bird(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id) : scene::ISceneNode(parent, smgr, id) {
		Material.Wireframe = false;
		Material.Lighting = false;
		this->smgr = smgr;

		use_automatic_culling = false;

		// ponta da asa
		Vertices[0] = video::S3DVertex(0,20,10, -1,1,0, video::SColor(255,0,255,0), 0, 1);
		Vertices[1] = video::S3DVertex(20,20,10, 1,1,0, video::SColor(255,0,255,0), 0, 1);

		// corpo
		Vertices[2] = video::S3DVertex(10,0,0, 0,-1,0, video::SColor(255,0,255,0), 1, 0);
		Vertices[3] = video::S3DVertex(10,0,20, 0,-1,0, video::SColor(255,0,255,0), 1, 0);

		if (use_automatic_culling) {
			Box.reset(Vertices[0].Pos);
			for (s32 i=1; i<4; ++i)
				Box.addInternalPoint(Vertices[i].Pos);
		}
		else {
			setAutomaticCulling(scene::EAC_OFF);
		}
	}


	~Bird() { }


	virtual void OnRegisterSceneNode() {
		if (IsVisible)
			smgr->registerNodeForRendering(this);
		ISceneNode::OnRegisterSceneNode();
	}



	virtual void render() {
	//	u16 indices[] = {       0,2,3, 2,1,3, 1,0,3, 2,0,1      };
		u16 indices[] = {       0,2,3, 2,1,3      };
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawVertexPrimitiveList(&Vertices[0], 			// vertices
										   4, 					// vertexCount
										   &indices[0], 		// indexList for primitives
										   2, 					// primitives Counts
										   video::EVT_STANDARD, // video Type
										   scene::EPT_TRIANGLES,// primitive Type
										   video::EIT_16BIT); 	// index Type
	}



	virtual const core::aabbox3d<f32>& getBoundingBox() const {
		return Box;
	}


	virtual u32 getMaterialCount() const {
		return 1;
	}


	virtual video::SMaterial& getMaterial(u32 i) {
		return Material;
	}

private:

	scene::ISceneManager* smgr;
	core::aabbox3d<f32> Box; // the bounding box
	video::S3DVertex Vertices[4]; // vértices
	video::SMaterial Material; // materiel
	bool use_automatic_culling;
};

















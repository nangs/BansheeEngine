#pragma once

#include "BsOctreeSMPrerequisites.h"
#include "BsSceneManager.h"

namespace BansheeEngine
{
	class BS_SM_EXPORT OctreeSceneManager : public SceneManager
	{
	public:
		OctreeSceneManager() {}
		~OctreeSceneManager() {}

		const CM::Vector<HCamera>::type& getAllCameras() const { return mCachedCameras; }

		CM::Vector<HRenderable>::type getVisibleRenderables(const HCamera& camera) const;
	private:
		void notifyComponentAdded(const CM::HComponent& component);
		void notifyComponentRemoved(const CM::HComponent& component);

		CM::Vector<HCamera>::type mCachedCameras;
	};
}
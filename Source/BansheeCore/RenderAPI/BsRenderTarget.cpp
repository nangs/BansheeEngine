//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "RenderAPI/BsRenderTarget.h"
#include "RenderAPI/BsViewport.h"
#include "Error/BsException.h"
#include "RenderAPI/BsRenderAPI.h"
#include "CoreThread/BsCoreThread.h"

namespace bs
{
	RenderTarget::RenderTarget()
	{
		// We never sync from sim to core, so mark it clean to avoid overwriting core thread changes
		markCoreClean();
	}

	void RenderTarget::setPriority(INT32 priority)
	{
		std::function<void(SPtr<ct::RenderTarget>, INT32)> windowedFunc =
			[](SPtr<ct::RenderTarget> renderTarget, INT32 priority)
		{
			renderTarget->setPriority(priority);
		};

		gCoreThread().queueCommand(std::bind(windowedFunc, getCore(), priority));
	}

	SPtr<ct::RenderTarget> RenderTarget::getCore() const
	{
		return std::static_pointer_cast<ct::RenderTarget>(mCoreSpecific);
	}

	const RenderTargetProperties& RenderTarget::getProperties() const
	{
		THROW_IF_CORE_THREAD;

		return getPropertiesInternal();
	}

	void RenderTarget::getCustomAttribute(const String& name, void* pData) const
	{
		BS_EXCEPT(InvalidParametersException, "Attribute not found.");
	}

	namespace ct
	{
		RenderTarget::RenderTarget()
		{

		}

		void RenderTarget::setPriority(INT32 priority)
		{
			RenderTargetProperties& props = const_cast<RenderTargetProperties&>(getProperties());

			props.priority = priority;
		}

		const RenderTargetProperties& RenderTarget::getProperties() const
		{
			return getPropertiesInternal();
		}

		void RenderTarget::getCustomAttribute(const String& name, void* pData) const
		{
			BS_EXCEPT(InvalidParametersException, "Attribute not found.");
		}
	}
}        

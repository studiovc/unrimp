/*********************************************************\
 * Copyright (c) 2012-2018 The Unrimp Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Header guard                                          ]
//[-------------------------------------------------------]
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "RendererRuntime/Public/Export.h"

#include <Renderer/Public/Renderer.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace RendererRuntime
{
	class RenderableManager;
	class MaterialResourceManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace RendererRuntime
{


	//[-------------------------------------------------------]
	//[ Global definitions                                    ]
	//[-------------------------------------------------------]
	typedef uint32_t MaterialResourceId;	///< POD material resource identifier
	typedef uint32_t SkeletonResourceId;	///< POD skeleton resource identifier


	//[-------------------------------------------------------]
	//[ Classes                                               ]
	//[-------------------------------------------------------]
	/**
	*  @brief
	*    Renderable
	*
	*  @note
	*    - Example: Abstract representation of a sub-mesh which is part of an mesh scene item
	*/
	class Renderable final
	{


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
		friend class MaterialResource;	// Must be able to update cached material data


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		RENDERERRUNTIME_API_EXPORT Renderable();
		RENDERERRUNTIME_API_EXPORT Renderable(RenderableManager& renderableManager, const Renderer::IVertexArrayPtr& vertexArrayPtr, const MaterialResourceManager& materialResourceManager, MaterialResourceId materialResourceId, SkeletonResourceId skeletonResourceId, bool drawIndexed, uint32_t startIndexLocation, uint32_t numberOfIndices, uint32_t instanceCount = 1);
		RENDERERRUNTIME_API_EXPORT Renderable(RenderableManager& renderableManager, const Renderer::IVertexArrayPtr& vertexArrayPtr, const MaterialResourceManager& materialResourceManager, MaterialResourceId materialResourceId, SkeletonResourceId skeletonResourceId, bool drawIndexed, const Renderer::IIndirectBufferPtr& indirectBufferPtr, uint32_t indirectBufferOffset = 0, uint32_t numberOfDraws = 1);

		inline ~Renderable()
		{
			unsetMaterialResourceIdInternal();
		}

		//[-------------------------------------------------------]
		//[ Derived data                                          ]
		//[-------------------------------------------------------]
		inline uint64_t getSortingKey() const
		{
			return mSortingKey;
		}

		//[-------------------------------------------------------]
		//[ Data                                                  ]
		//[-------------------------------------------------------]
		inline RenderableManager& getRenderableManager() const
		{
			return mRenderableManager;
		}

		inline Renderer::IVertexArrayPtr getVertexArrayPtr() const
		{
			return mVertexArrayPtr;
		}

		inline void setVertexArrayPtr(const Renderer::IVertexArrayPtr& vertexArrayPtr)
		{
			mVertexArrayPtr = vertexArrayPtr;
			calculateSortingKey();
		}

		inline Renderer::IIndirectBufferPtr getIndirectBufferPtr() const
		{
			return mIndirectBufferPtr;
		}

		inline void setIndirectBufferPtr(const Renderer::IIndirectBufferPtr& indirectBufferPtr)
		{
			mIndirectBufferPtr = indirectBufferPtr;
			calculateSortingKey();
		}

		inline bool getDrawIndexed() const
		{
			return mDrawIndexed;
		}

		inline void setDrawIndexed(bool drawIndexed)
		{
			mDrawIndexed = drawIndexed;
		}

		inline uint32_t getStartIndexLocation() const
		{
			return mStartIndexLocation;
		}

		inline void setStartIndexLocation(uint32_t startIndexLocation)
		{
			mStartIndexLocation = startIndexLocation;
		}

		inline uint32_t getIndirectBufferOffset() const
		{
			return mIndirectBufferOffset;
		}

		inline void setIndirectBufferOffset(uint32_t indirectBufferOffset)
		{
			mIndirectBufferOffset = indirectBufferOffset;
		}

		inline uint32_t getNumberOfIndices() const
		{
			return mNumberOfIndices;
		}

		inline void setNumberOfIndices(uint32_t numberOfIndices)
		{
			mNumberOfIndices = numberOfIndices;
		}

		inline uint32_t getInstanceCount() const
		{
			return mInstanceCount;
		}

		inline void setInstanceCount(uint32_t instanceCount)
		{
			mInstanceCount = instanceCount;
		}

		inline uint32_t getNumberOfDraws() const
		{
			return mNumberOfDraws;
		}

		inline void setNumberOfDraws(uint32_t numberOfDraws)
		{
			mNumberOfDraws = numberOfDraws;
		}

		inline MaterialResourceId getMaterialResourceId() const
		{
			return mMaterialResourceId;
		}

		RENDERERRUNTIME_API_EXPORT void setMaterialResourceId(const MaterialResourceManager& materialResourceManager, MaterialResourceId materialResourceId);

		inline void unsetMaterialResourceId()
		{
			unsetMaterialResourceIdInternal();
			calculateSortingKey();
		}

		inline SkeletonResourceId getSkeletonResourceId() const
		{
			return mSkeletonResourceId;
		}

		inline void setSkeletonResourceId(SkeletonResourceId skeletonResourceId)
		{
			mSkeletonResourceId = skeletonResourceId;
		}

		//[-------------------------------------------------------]
		//[ Cached material data                                  ]
		//[-------------------------------------------------------]
		inline uint8_t getRenderQueueIndex() const
		{
			return mRenderQueueIndex;
		}

		inline bool getCastShadows() const
		{
			return mCastShadows;
		}


	//[-------------------------------------------------------]
	//[ Private methods                                       ]
	//[-------------------------------------------------------]
	private:
		Renderable& operator=(const Renderable&) = delete;
		RENDERERRUNTIME_API_EXPORT void calculateSortingKey();
		RENDERERRUNTIME_API_EXPORT void unsetMaterialResourceIdInternal();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Derived data
		uint64_t						mSortingKey;			///< The sorting key is directly calculated after data change, no lazy evaluation since it's changed rarely but requested often (no branching)
		// Data
		RenderableManager&				mRenderableManager;
		Renderer::IVertexArrayPtr		mVertexArrayPtr;		///< Optional vertex array object (VAO), can be a null pointer
		Renderer::IIndirectBufferPtr	mIndirectBufferPtr;		///< Optional indirect buffer, can be a null pointer
		union
		{
			uint32_t					mStartIndexLocation;	///< Used in case there's no indirect buffer
			uint32_t					mIndirectBufferOffset;	///< Used in case there's an indirect buffer
		};
		uint32_t						mNumberOfIndices;		///< If there's an indirect buffer set, this value is unused
		union
		{
			uint32_t					mInstanceCount;			///< Used in case there's no indirect buffer
			uint32_t					mNumberOfDraws;			///< Used in case there's an indirect buffer
		};
		MaterialResourceId				mMaterialResourceId;
		SkeletonResourceId				mSkeletonResourceId;
		bool							mDrawIndexed;			///< Placed at this location due to padding
		// Cached material data
		uint8_t							mRenderQueueIndex;
		bool							mCastShadows;
		// Internal data
		const MaterialResourceManager*	mMaterialResourceManager;
		int								mMaterialResourceAttachmentIndex;


	};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // RendererRuntime
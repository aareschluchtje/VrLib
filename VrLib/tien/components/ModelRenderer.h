#pragma once

#include "Renderable.h"
#include <string>
#include <map>
namespace vrlib
{
	class Model;
	class Texture;

	namespace tien
	{
		namespace components
		{
			class ModelRenderer : public Renderable
			{
			private:
				class ModelDeferredRenderContext : public Renderable::RenderContext, public Singleton<ModelDeferredRenderContext>
				{
				public:
					enum class RenderUniform
					{
						modelMatrix,
						projectionMatrix,
						viewMatrix,
						normalMatrix,
						s_texture,
						s_normalmap,
						s_specularmap,
						diffuseColor,
						textureFactor,
						shinyness,
					};
					vrlib::gl::Shader<RenderUniform>* renderShader;
					vrlib::Texture* defaultNormalMap;
					virtual void init() override;
					virtual void frameSetup(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix) override;
				};
				class ModelForwardRenderContext : public Renderable::RenderContext, public Singleton<ModelForwardRenderContext>
				{
				public:
					enum class RenderUniform
					{
						modelMatrix,
						projectionMatrix,
						viewMatrix,
						normalMatrix,
						s_texture,
						s_normalmap,
						s_specularmap,
						diffuseColor,
						textureFactor,
						shinyness,
					};
					vrlib::gl::Shader<RenderUniform>* renderShader;
					vrlib::Texture* defaultNormalMap;
					virtual void init() override;
					virtual void frameSetup(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix) override;
				};
				class ModelShadowRenderContext : public Renderable::RenderContext, public Singleton<ModelShadowRenderContext>
				{
				public:
					enum class RenderUniform
					{ 
						modelMatrix,
						projectionMatrix,
						viewMatrix,
						outputPosition
					};
					vrlib::gl::Shader<RenderUniform>* renderShader;
					virtual void init() override;
					virtual void frameSetup(const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix) override;
					virtual void useCubemap(bool) override;
				};

				std::string fileName;
				static std::map<std::string, vrlib::Model*> cache;
			public:
				ModelRenderer(const vrlib::json::Value &json);
//				ModelRenderer(const std::string &fileName);
				~ModelRenderer();

				vrlib::Model* model;

				void drawDeferredPass() override;
				void drawForwardPass() override;
				void drawShadowMap() override;
				json::Value toJson(json::Value &meshes) const override;

				bool castShadow;
				bool cullBackFaces;
				virtual void buildEditor(EditorBuilder* builder, bool folded) override;

			};
		}
	}
}
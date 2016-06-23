#pragma once

#include "Node.h"
#include <set>
#include <VrLib/gl/Vertex.h>
#include <btBulletDynamicsCommon.h>
#include "components/Renderable.h"


namespace vrlib
{
	namespace math { class Ray; }
	namespace tien
	{
		class DebugDraw : public btIDebugDraw
		{
			int debugmode;
		public:
			std::vector<vrlib::gl::VertexP3C4> verts;
			void flush();
			virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
			virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override	{		}
			virtual void reportErrorWarning(const char* warningString) override {	}
			virtual void draw3dText(const btVector3& location, const char* textString) override {	}
			virtual void setDebugMode(int debugMode) override { this->debugmode = debugMode; }
			virtual int getDebugMode() const override { return this->debugmode; }
		};


		class Scene : public Node
		{
		public:
			Scene();
			Scene(const Scene& other);
			Node* cameraNode;

		private:
			bool treeDirty;
			std::set<components::Renderable::RenderContext*> renderContexts;
			std::list<Node*> renderables;
			std::list<Node*> lights;

			std::list<Node*> toInit;

			bool isPreparedForRunning;
			virtual void setTreeDirty(Node* newNode, bool isNewNode) override;
			void updateRenderables();
			void prepareForRun();
			void update(float elapsedTime);

			friend class Renderer;
			friend class Tien;


			btBroadphaseInterface*                  broadphase;
			btDefaultCollisionConfiguration*        collisionConfiguration;
			btCollisionDispatcher*                  dispatcher;
			btSequentialImpulseConstraintSolver*    solver;
		public:
			btDiscreteDynamicsWorld*                world;
			DebugDraw*								debugDrawer;


			bool testBodyCollision(Node* n1, Node* n2);
			void castRay(const math::Ray& ray, std::function<bool(Node* node, const glm::vec3 &hitPosition, const glm::vec3 &hitNormal)> callback) const;


		};
	}
}
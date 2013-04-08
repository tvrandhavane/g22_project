/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  {
    //Ground
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-95.0f, -15.0f), b2Vec2(95.0f, -15.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
    
    //The tilted plank holding the sphere
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.25f,b2Vec2(-33.0f, 52.0f),-70.0f);
	
      b2BodyDef bd;
      //bd.position.Set(-23.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
      
    //The big sphere on top
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 3.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-35.0f, 55.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	
    }
    
    //First tilted plank
    /*{
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.25f,b2Vec2(-21.0f, 38.0f),70.0f);
	
      b2BodyDef bd;
      //bd.position.Set(-23.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }*/
    
    //Second tilted plank
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.25f,b2Vec2(-30.0f, 44.0f),-70.0f);
	
      b2BodyDef bd;
      //bd.position.Set(-23.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    //The horizontal shelf holding the dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-18.0f, 39.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }



    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 2.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i <= 9; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-22.0f + 1.0f * i, 40.0f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
	
	
	b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 34.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-10.0f, 40.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	  
	  /*b2PolygonShape shape1;
      shape1.SetAsBox(4.0f, 0.25f,b2Vec2(-9.0f, 23.0f),70.0f);
	
      b2BodyDef bd;
      //bd.position.Set(-23.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape1, 0.0f);*/
    }




  

    
    //The see-saw system at the left
  /*  {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(-14.0f, 2.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(-14.0f, 3.73f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-14.0f, 3.73f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd3;
      bd3.position.Set(-19.0f, 5.73f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 2.0f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
      
      b2PolygonShape shape3;
      shape3.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd4;
      bd4.position.Set(-9.0f, 5.73f);
      bd4.type = b2_dynamicBody;
      b2Body* body4 = m_world->CreateBody(&bd4);
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 2.0f;
      fd4->shape = new b2PolygonShape;
      fd4->shape = &shape3;
      body4->CreateFixture(fd4);
    }*/
    
	//Horizontal shelf with a train of balls on the left
   /* {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(-30.0f,20.0f), 0.0f);
	
      b2BodyDef bd;
      //bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    //The train of balls on the left
    {
		b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 3.3f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 4; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-34.0f+1.0f*i, 21.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}      
  }
  
	 //The goal box on the left
     {
	  b2BodyDef *bd = new b2BodyDef;
      //bd->type = b2_dynamicBody;
      bd->position.Set(-40,0);
      //bd->fixedRotation = true;
 
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 1.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3,0.2, b2Vec2(0.f,-2.8f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3, b2Vec2(2.5f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,3, b2Vec2(-2.5f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
  }
  
  //The second goal box on the left (after all spheres boune out of the first)
     {
	  b2BodyDef *bd = new b2BodyDef;
      //bd->type = b2_dynamicBody;
      bd->position.Set(-48,0);
      //bd->fixedRotation = true;
 
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 1.0f;
      fd1->restitution = 0.1f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(1.5,0.2, b2Vec2(0.f,-2.8f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3, b2Vec2(1.8f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,3, b2Vec2(-1.8f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
  }*/

	
    //The pendulum that the dominos knock off
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.15f, 0.150f);
	  
	b2BodyDef bd;
	bd.position.Set(-23.5f, 34.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-23.5f, 22.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 4.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-23.5f, 34.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
//ground where collision with pendulum of ball
	{
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 21.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

//ball with which pendulum collides
	  {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-27.0f, 22.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	
    }
// tilted platform for direction of ball
{
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.25f,b2Vec2(-40.0f, 16.0f),-70.0f);
	
      b2BodyDef bd;
      //bd.position.Set(-23.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//straight directng platform
{
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-32.0f, 11.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    
    //The revolving plank that holds the sphere to trigger further simulation
   /* {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.position.Set(5.0f, 36.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(5.0f, 0.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(5.0f, 36.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 4.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(5.0f, 36.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }*/
    
    //The sphere on top that triggers
    /*{
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 2.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 4.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(5.0f, 38.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	
    }*/
    
    //The see-saw system at the bottom
    /*{
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(8.0f, 2.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(8.0f, 3.73f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(8.0f, 3.73f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd3;
      bd3.position.Set(0.0f, 5.73f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 2.0f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
      
      b2PolygonShape shape3;
      shape3.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd4;
      bd4.position.Set(16.0f, 5.73f);
      bd4.type = b2_dynamicBody;
      b2Body* body4 = m_world->CreateBody(&bd4);
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 2.0f;
      fd4->shape = new b2PolygonShape;
      fd4->shape = &shape3;
      body4->CreateFixture(fd4);
    }*/
    
    //Horizontal shelf with a train of balls
   /* {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(24.0f,20.0f), 0.0f);
	
      b2BodyDef bd;
      //bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    //The train of balls
    {
		b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 3.3f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 4; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(25.0f+1.0f*i, 22.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}      
  }*/

   
    //The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(0,5);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(-25.f,-2.8f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3, b2Vec2(-23.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,3, b2Vec2(-27.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(9,5);	
      fd1->density = 43.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-25, 5); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(-16, 5); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-25, 9); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(-16, 9); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

	//The revolving plank that holds the sphere to take the goal


//rotating plank and box

	{
      b2PolygonShape shape;
      shape.SetAsBox(3.0f, 0.25f);
	b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 1.0f;
      fd.friction = 0.2f;
	
	
      b2BodyDef bd;
	bd.type = b2_dynamicBody;
      bd.position.Set(-3.0f, 31.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
	ground->CreateFixture(&fd);
    }
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.position.Set(-3.0f, 30.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(6.0f, 2.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-3.0f, 30.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 4.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-3.0f, 30.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
/*//pulley horizontal motion stopper
{
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-33.5f, 8.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

// tilted platform for first ball
 {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f,b2Vec2(-10.0f, 18.0f),0.4f);
	
      b2BodyDef bd;
      //bd.position.Set(-23.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }*/
    
    //The sphere on top that triggers the goal
    /*{
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 2.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 4.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(45.0f, 16.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	
    }*/
    
    //Final tilted plank
   /* {
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.25f,b2Vec2(50.0f, 7.0f),70.0f);
	
      b2BodyDef bd;
      //bd.position.Set(-23.0f, 35.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }*/
    
     //The goal box
 /*    {
	  b2BodyDef *bd = new b2BodyDef;
      //bd->type = b2_dynamicBody;
      bd->position.Set(44,0);
      //bd->fixedRotation = true;
 
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3,0.2, b2Vec2(0.f,-2.8f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3, b2Vec2(2.5f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,3, b2Vec2(-2.5f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
  }*/

   /* //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    //The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }*/


//last rotating plank and box

	{
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 1.0f;
      fd.friction = 0.2f;
	
	
      b2BodyDef bd;
	bd.type = b2_dynamicBody;
      bd.position.Set(-13.0f, 7.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
	ground->CreateFixture(&fd);
    }
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.position.Set(-13.0f, 6.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(2.0f, .25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-13.0f, 6.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 4.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-13.0f, 6.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

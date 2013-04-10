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
#include <cmath>

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
    
    //Starter
    float x = -40.0f;
    float y = 52.5f;
    {
      
      b2Body* horBar;
      {
        b2PolygonShape shape;
        shape.SetAsBox(5.0f, 0.5f);
      
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(10.0f + x, 0.0f + y);
        horBar = m_world->CreateBody(&bd);
        horBar->CreateFixture(&shape, 10.0f);
      }

      b2Body* verBar;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 5.0f);
      
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(15.0f + x, -5.0f + y);
        verBar = m_world->CreateBody(&bd);
        verBar->CreateFixture(&shape, 10.0f);
      }

      b2Body* hinge;
      {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 0.25f);
      
        b2BodyDef bd;
        bd.position.Set(15.0f + x, 0.0f + y);
        hinge = m_world->CreateBody(&bd);
        hinge->CreateFixture(&shape, 10.0f);
      }
        
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(15.0f + x,0.0f + y);
      jd.Initialize(horBar, verBar, anchor);
      m_world->CreateJoint(&jd);

      b2RevoluteJointDef hingej1;
      b2Vec2 anchor1;
      anchor1.Set(15.0f + x,0.0f + y);
      hingej1.Initialize(hinge, verBar, anchor1);
      m_world->CreateJoint(&hingej1);

      b2RevoluteJointDef hingej2;
      b2Vec2 anchor2;
      anchor2.Set(15.0f + x,0.0f + y);
      hingej2.Initialize(horBar, hinge, anchor2);
      m_world->CreateJoint(&hingej2);

      b2DistanceJointDef constraint;
      constraint.Initialize(horBar, verBar, b2Vec2(10.0f + x, 0.0f + y), b2Vec2(15.0f + x, -5.0f + y));
      constraint.collideConnected = true;
      m_world->CreateJoint(&constraint);
    }
  
    //Ground
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-95.0f, -15.0f), b2Vec2(95.0f, -15.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
    
    //The horizontal shelf holding the dominos
    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-26.0f, 39.0f), b2Vec2(10.0f, 39.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);

    }

    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 2.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 70.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i <= 9; ++i)
    	{
    	  b2BodyDef bd;
    	  bd.type = b2_dynamicBody;
    	  bd.position.Set(-22.0f + 2.3f * i, 40.0f);
    	  b2Body* body = m_world->CreateBody(&bd);
    	  body->CreateFixture(&fd);
    	}
	
	
	b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 200.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(2.5f, 40.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	 
    }

    
    //The pendulum that the dominos knock off
    x = -17.0f;
    y = 28.0f;
    {
      b2Body* b2;
      {
      	b2PolygonShape shape;
      	shape.SetAsBox(0.15f, 0.150f);
      	  
      	b2BodyDef bd;
      	bd.position.Set(0.0f + x, 6.0f + y);
      	b2 = m_world->CreateBody(&bd);
      	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
      	b2PolygonShape shape;
      	shape.SetAsBox(0.5f, 0.5f);
      	  
      	b2BodyDef bd;
      	bd.type = b2_dynamicBody;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.friction = 0.0f;
        fd.density = 20.0f;
        fd.restitution = 1.0f;

      	bd.position.Set(6.0f + x, -1.0f + y);
      	b4 = m_world->CreateBody(&bd);
      	b4->CreateFixture(&fd);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(0.0f + x, 6.0f + y);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

    /*{
      b2EdgeShape shape;
      shape.Set(b2Vec2(-5.0f + x, -16.0f + y), b2Vec2(-5.0f + x,-5.0f + y ));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 3.0f);
    }*/


    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-15.0f + x, -16.0f + y), b2Vec2(10.0f + x,-16.0f + y ));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 3.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-15.0f + x, -16.0f + y), b2Vec2(-15.0f + x,-5.0f + y ));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 3.0f);
    }

    b2Body* verBar;
    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 7.0f);
      
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(6.0f + x, -11.0f + y);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 0.1f;
        fd.friction = 0.1f;
        fd.restitution = 0.0f;
  
        verBar = m_world->CreateBody(&bd);
        verBar->CreateFixture(&fd);
    }


//edges
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-40.0f,23.0f), b2Vec2(-18.0f,23.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-40.0f,23.0f), b2Vec2(-40.0f,27.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-40.0f,27.0f), b2Vec2(-34.0f,23.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    //ball with which pendulum collides
	  {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.3f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-18.0f, 24.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	
    }
// curve

    for(int i = 0; i < 100; i++)
    {
      int r = 6;
      b2EdgeShape shape;
      shape.Set(b2Vec2(-r*cos(i*3.14159/200) - 39.0f,-r*sin(i*3.14159/200) + 14.0f), 
                b2Vec2(-r*cos((i+1)*3.14159/200) - 39.0f,-r*sin((i+1)*3.14159/200) + 14.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-45.0f,14.0f), b2Vec2(-45.0f,18.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

//straight directng platform
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-39.0f,8.0f), b2Vec2(-28.0f,8.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    //The pulley system
    x = -25.0f;
    y = -3.0f;
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(0,5);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(4,0.2, b2Vec2(0.0f + x,-2.8f + y), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3, b2Vec2(4.0f + x,0.0f + y), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,3, b2Vec2(-4.0f + x,0.0f + y), 0);
      fd3->shape = &bs3;

      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 1.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(2,0.2, b2Vec2(0.0f + x,-2.8f + y), 0);
      fd4->shape = &bs4;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(9,5);	
      fd4->density = 5.1;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd4);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(x, 5 + y); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(x + 9, 5 + y); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(x, 9 + y); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(x + 9, 9 + y); // Anchor point for ground 2 in world axis
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
      bd.position.Set(19.5f, 26.0f);
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
      	bd.position.Set(19.5f, 25.0f);
      	b2 = m_world->CreateBody(&bd);
      	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(6.0f, 2.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(19.5f, 25.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 4.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(19.5f, 25.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

//last rotating plank and box

	{
      b2CircleShape shape;
      shape.m_radius = 1.9f;
	    b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 60.0f;
      fd.friction = 0.0f;
	
	
      b2BodyDef bd;
	    bd.type = b2_dynamicBody;
      bd.position.Set(-6.35f, 5.0f);
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
	bd.position.Set(-6.35f, 4.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(8.0f, .25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-6.35f, 4.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 4.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-6.35f, 4.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }



    //replacement for water
    x = 11.0;
    y = -15.0f;

    {

      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(x,y);
      bd->fixedRotation = true;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(0.25,5.0, b2Vec2(-3.0f + x,40.0f + y), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(2.0,1.0, b2Vec2(-1.0f + x,44.0f + y), 0);
      fd2->shape = &bs2;

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      
    }

    
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(x - 10.0f,y), b2Vec2(x + 10.0f,y));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(x - 10.0f,y + 16.0f), b2Vec2(x - 10.0f,y));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(x - 6.0f,y + 16.0f), b2Vec2(x - 6.0f,y + 4.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(x - 6.0f,y + 4.0f), b2Vec2(x + 6.0f,y + 4.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(x + 6.0f,y + 25.0f), b2Vec2(x + 6.0f,y + 4.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(x + 10.0f,y + 25.0f), b2Vec2(x + 10.0f,y));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
    for(int j = 0; j < 15; j++){
      for(int i = 0; i < 25; i++)
      {
        b2Body* spherebody;
    
        b2CircleShape circle;
        circle.m_radius = 0.25;
    
        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 0.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
    
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(x - 9.75f + 0.25*j, y + 0.5 * i);
        spherebody = m_world->CreateBody(&ballbd);
        spherebody->CreateFixture(&ballfd);
     
      }
    }

    for(int j = 0; j < 15; j++){
      for(int i = 0; i < 25; i++)
      {
        b2Body* spherebody;
    
        b2CircleShape circle;
        circle.m_radius = 0.25;
    
        b2FixtureDef ballfd;
        ballfd.shape = &circle;
        ballfd.density = 0.0f;
        ballfd.friction = 0.0f;
        ballfd.restitution = 0.0f;
    
        b2BodyDef ballbd;
        ballbd.type = b2_dynamicBody;
        ballbd.position.Set(x + 6.25f + 0.25*j, y + 0.5 * i);
        spherebody = m_world->CreateBody(&ballbd);
        spherebody->CreateFixture(&ballfd);
     
      }
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(2.00f, 0.25f);
       b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 1.0f;
      fd.friction = 0.2f;
  
  
      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(x - 8.0f, y + 15.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
      ground->CreateFixture(&fd);
    }


    

    {
      b2PolygonShape shape;
      shape.SetAsBox(1.90f, 0.25f);
       b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 1.0f;
      fd.friction = 0.2f;
  
  
      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(x + 8.0f, y + 15.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
      ground->CreateFixture(&fd);
    }
  }

    

  

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

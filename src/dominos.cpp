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

    //!<B>1. L Shaped Rod</B>
     /*! L shaped rod consists of two rods or bars which are of b2 Body to which the pointer variable are "horBar" 
     & "verBar".
     A variable "shape" is used to set the fixtures to both the rods.
     Each of the rod is 5 units in length and 0.5 units in width , horizontal and vertical bars are initially placed 
     at cordinates (-30,52.5) and (-25,47.5) respectively and both are set to be dynamic bodies.Hinge is shown up as a 
     small square and the hinge is set up at (-25,52.5).
     Revolutionary joints consisiting of three anchors are set up also three anchors are set up which joins up the three 
     bars at different joints, Also a constraint is also made between horizontal and vertical rod .
     */
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

    //!<B>2. Ground </B>
    /*! Ground is represented by a variable of type b2Body to which the pointer variable "b1" points.
    A variable "shape" of type b2EdgeShape is used to set the fixtures to ground.
    The ground is a line segment starting at vertex (-95,-15) and ending at vertex (95,-15). (Vertices are variables 
    of type b2Vec2.)Variable "bd" of type b2BodyDef is used to pass the ground object to the 
    world object to create the ground body.
    */
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-95.0f, -15.0f), b2Vec2(95.0f, -15.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
    
    //The horizontal shelf holding the dominos
    //!<B>3. Horizontal shelf holding dominos</B>
    /*!
    There is a horizontal shelf, on which the dominos are kept.
    A variable "shape" of type b2EdgeShape is used to set the fixtures to the shelf.
    Variable "bd" of type b2BodyDef is used to pass the shelf object to the world object to create the shelf.
    "ground" is a pointer to the variable of the type b2Body which represents the horizontal shelf.
    Horizontal shelf is a line of length 36m.
    The shelf is centered at point (-8,39)
    */

    {

      b2EdgeShape shape;
      shape.Set(b2Vec2(-26.0f, 39.0f), b2Vec2(10.0f, 39.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);

    }

    //Dominos

    //!<B>4. Dominos </B>
    /*!
    10 Dominos are kept on the top shelf which are knocked off by a pendulum.
    A variable "shape" of type b2PolygonShape is used to create a domino.
    Variable "fd" of type b2PolygonShape is used to set fixtures of a domino.
    A domino has density 20 and friction coefficient of 0.1.
    Variable "bd" of type b2BodyDef is used to pass the domino object to the world object to create the domino. 
    This process is looped 10 times to create 10 dominos.
    */

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
	
  //Sphereball that the dominos kicks off

  //!<B>5. First Sphere ball</B>
  /*!
    A ball is created with radius 1 unit with a pointer to b2Body as "spherebody" and the fixtures are given to the ball 
    through ballfd with density as 200 the ball is set up as a dynamic body ans is initially placed at (2.5,40).
    Variable "ballbd" of type b2BodyDef is used to pass the ball object to the world object to create the spherical ball.
    */

	
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

    //!<B>6. The pendulum that knocks the dominos off</B>
    /*!
    The pendulum consists of three parts, a joint (represented by variable "jd" of type b2RevoluteJoint) and two bodies 
    (represented by two b2Body type variables "b2" and "b4"). 
    The joint jd forces bodies b2 and b4 to share a common anchor point represented by the b2Vec2 type variable "anchor".
    Body b2 is a static box used to provide a static point.
    It is a box of dimensions 0.5m X 3m.
    Body b4 is the bob of the pendulum. 
    It is a square box of dimensions 0.15 X 0.150m. 
    The bob is a dynamic body. 
    Anchor is a point chosen(-17m,34m) such that the pendulum bob has a swift motion and hits the top of the first domino 
    during the course of its motion. Pendulum is initially at a extreme position and is withheld there with the help of a 
    vertical bar which has a coefficient of friction to hold the pendulum at rest.
    */
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

    //Horizontal platform below pendulum
    /*!<B>7. Horizontal platform</B>
    /*!This sets up a horizontal platform below the pendulum on which is kept a vertical bar meant for keeping the
    pendulum at rest initially the platform runs between the coordinates (-32,12) , (-7,12).The length of this platform
    is 25.
    */


    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-15.0f + x, -16.0f + y), b2Vec2(10.0f + x,-16.0f + y ));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 3.0f);
    }

    //Vertical line between wedge and horizontal platform.
    //!<B>8. Vertical line between wedge and horizontal platform.</B>
    /*!This sets up a vertical line between triangular wedge and horizontal platform whose purpose is to prevent 
    the vertical bar to fall on the ground i.e. it restricts the motion of the vertical bar the vertical bar is of length
    11 and runs between coordinates(-32,12) , (-32,23).Object bd b2BodyDef is passed to the world object to create this.
    */

    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-15.0f + x, -16.0f + y), b2Vec2(-15.0f + x,-5.0f + y ));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 3.0f);
    }

    //Vertical bar 
    //!<B>9. Vertical Bar to hold pendulum at rest</B>
    /*Here we create a vertical bar that is meant for holding the pendulum initially at rest at its extreme position.
    It is a box of height 7 and width 0.5 and is a dynamic body with object fd settting its fixtures like density to 0.1 
    coefficient of friction as 0.1 and is initially placed at (-11,17).
    */


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


//Triangular wedge
  //!<B>9. Triangular wedge</B>
  /* Here we set up a triangular wedge by making up three edges one vertical , one horizontal and one diagonal joining
  the both.Horizontal edge is of length 22 and lies between (-40,23) , (-18,23) the vertical edge lies between (-40,23) ,
  (-40,27) and is of length 4 units and the third edge joining both lies between (-40,27) , (-34,23) all three edges 
  are made up by passing bd object to the world.
  */



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
    //!<B>10. Sphere ball with which pendulum collides</B>
  /*!
    A ball is created with radius 1 unit with a pointer to b2Body as "spherebody" and the fixtures are given to the ball 
    through ballfd with density as 0.3 the ball is set up as a dynamic body ans is initially placed at (-18,24).
    Variable "ballbd" of type b2BodyDef is used to pass the ball object to the world object to create the spherical ball.
    */


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
  //!<B>11. Curved path used to guide the ball</B>
  /*! Here we create a curved path joining 100 small edges preceeded by a long straight edge and followed by long 
  straight horizontal platform of length 11 units, the point where any edge 
  ends is used as the starting point for the next edge there by constituting a curved path the coordinates are evaluated 
  using trigonometric calculations an functions like sine and cosine are used to give the sense of curvature to path
  the library used for these functions is cmath , object "bd" is passed to worls to create curvature.
  */


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
    //!<B>12. The Pulley System</B>
    /*!
    Variable "bd" of type b2BodyDef is used to pass the box and bar 
    which are on either sides of pully to the world object to create the objects. 
    It sets up the position of the open box on one side of the pulley to (0,5).
    The rotation of the open box and bar is restricted by setting the fixedRotation variable to true.
    <p>1) The Open Box: <br/>
    The open box is composed of three bars. 
    The variables "bs1", "bs2" and "bs3" are used  to give shape and position to the three bars. 
    Variables "fd1", "fd2" and "fd3" of type b2FixtureDef are used to give them their fixtures
    (density(1), friction(0.5) and restitution(0)).
    The function "SetAsBox" is used to form the bar shape, 
    with first two arguements as dimensions of the bar(8mX0.4m, 0.4mx6m and 0.4mX6m respectively for 3 bars) and  
    the next arguement as the position of the centre of the bar and finally the angle at which it is tilted.
    Here we are using SetAsBox three times to complete up the box as the three different bars.
    A pointer variable "box1" to the object of type b2BodyDef finally creates up the box and 
    applies the fixtures to all the three bars and creates them on the screen. </p>
    <p>2) The Bar: <br/>
    A pointer variable "box2" to the object of type b2BodyDef creates up the bar on the other side of the pulley and sets its position 
    as (9m, 5m) and sets its density to 5.1 and finally "CreateFixture" creates it on the screen.</p>
    <p>3) Pulley Joint: <br/>
    A pointer variable "myjoint" pointing to the object of type b2PulleyJointDef 
    joins the open box and the bar using four anchors situated at (-25m, 2m) , (-16m, 2m) , (-25m, 6m) and (-16m, 6m)
    ,finishing up the pulley system.</p>
    */

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

	//The revolving plank that holds the bar

  //!<B>13. Revolving plank holding the bar</B>
    /*Firstly a box is made of dimensions(3m, 0.25m) and its density is set as 1 and friction coefficient is 0.2 and the
    initial position is set as (19.5,26) object "bd" is passed to the world to create the bar.Now a very small square shaped
    box is made up which is used to show up the hinge point of the horizontal rotationary platform its size is (0.25,0.25)
    and is initially placed at (19.5, 25) ,finally object "bd" is passed to world for creating the object.Now at last 
    our main horizontal rotationary box is made which can rotate about the small box to which it is hinged,The dimensions 
    of the box are (6m x 2.5m) and is placed at (19.5, 25) and the anchor is set up at (19.5,25) between objects b2 & b4.
    */

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
      //!<B>14. The revolving horizontal platform containing ball</B>
    /*!
    <p>The bar of the pulley hits the revolving platform. To design the revolving platform, 
    first of all we have to define shape of horizontal platform and that thing is done using variable named as "shape".
    Here shape is defined as b2PolygonShape and SetAsBox turns that "shape" into box shape.
    The SetAsBox function takes the half-width and half-height. 
    So in this case the shape is 16 units wide (x-axis) and 0.5 units tall (y-axis).</p>
    Small square of dimension(0.25x0.25) is made up which is used to show up th hinge and is placed in middle of the bar 
    at coordinates (-6.35, 4) , now a spherical ball of radius 1.9 and high density 60  is placed at coordinates 
    (-6.35,5) and the object "bd" is passed to world which creates up spherical ball.Now the anchor joint is set up between 
    "b2" and "b4" which acts as the anchor and the coordinates of the anchor are set up as (-6.35,4).
    */


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

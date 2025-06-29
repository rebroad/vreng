//---------------------------------------------------------------------------
// VREng (Virtual Reality Engine)	https://github.com/philippedax/vreng
//
// Copyright (C) 1997-2009 Philippe Dax
// Telecom-Paris (Ecole Nationale Superieure des Telecommunications)
//
// VREng is a free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public Licence as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// VREng is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//---------------------------------------------------------------------------
// body.hpp
//---------------------------------------------------------------------------
#ifndef BODY_HPP
#define BODY_HPP

#include "object.hpp"	// Pos
#include "bap.hpp"
#include "fap.hpp"
#include "off.hpp"	// Off
#include "obj.hpp"	// Obj

// Body
#define B_HEIGHT	1.70
#ifdef OFF_SCALING	//see off.hpp
#define BD_SCALE	40.41	//0.02476  // 1/40.41
#else
#define BD_SCALE	1
#endif


/**
 * Phalanx2 class
 */
class Phalanx2 {
 private:
  static const float PHALANX2_LEN;

 public:
  float length;			///< phalanx length

  Phalanx2();			///< constructor
  ~Phalanx2() {}		///< destructor

  int init();
  /**< Init Phalanx2 */
};

/**
 * Phalanx class
 */
class Phalanx {
 private:
  static const float PHALANX_LEN;

 public:
  float length;			///< phalanx length
  float aflexion;		///< phalanx flexion angle
  class Phalanx2 *phalanx2;	///< phalanx2 ptr

  Phalanx(Phalanx2 *phalanx2);	///< constructor
  ~Phalanx() {}			///< destructor

  int init();
  /**< Init phalanx */

  void flexion(float a);
  /**< Bend phalanx */
};

/**
 * Finger class
 */
class Finger {
 private:
  static const float FINGER_LEN;

 public:
  float length;			///< finger lenght
  float aflexion;		///< finger flexion angle
  float aabduct;		///< finger abduct angle
  class Phalanx *phalanx;	///< phalanx ptr

  Finger(Phalanx *phalanx);	///< constructor
  ~Finger() {}			///< destructor

  int init();
  /**< Init finger */

  void flexion(float a);
  /**< Bend finger */

  void abduct(float a);
  /**< Tilt finger */
};

/**
 * Hand class // Wrist
 */
class Hand {
 private:
  static const float HAND_LEN;

 public:
  float length;			///< hand length
  float aflexion;		///< hand flexion angle
  float aabduct;		///< hand abduct angle
  float atorsion;		///< hand torsion angle
  class Finger *fingers[5];	///< five fingers

  Hand(Finger **finger);	///< constructor
  ~Hand() {}			///< destructor

  int init();
  /**< Init hand */

  void flexion(float a);
  /**< Bend hand */

  void abduct(float a);
  /**< Tilt hand */

  void torsion(float a);
  /**< Turn hand */
};

/**
 * Forearm class // Elbow
 */
class Forearm {
 private:
  static const float FOREARM_LEN;
  static const float ELBOW_RAD;

 public:
  float length;			///< forearm length
  float aflexion;		///< elbow flexion angle
  float atorsion;		///< elbow torsion angle
  class Hand *hand;		///< hand ptr

  Forearm(Hand *hand);		///< constructor
  ~Forearm() {}			///< destructor

  int init();
  /**< Init forearm */

  void flexion(float a);
  /**< Bend elbow */

  void torsion(float a);
  /**< Turn elbow */
};

/**
 * Arm class
 */
class Arm {
 private:
  static const float ARM_LEN;

 public:
  float length;			///< arm length
  float aflexion;		///< arm flexion angle
  float aabduct;		///< arm abduct angle
  float atorsion;		///< arm torsion angle
  class Forearm *forearm;	///< forearm ptr

  Arm(Forearm *forearm);	///< constructor
  ~Arm() {}			///< destructor

  int init();
  /**< Init arm */

  void flexion(float a);
  /**< Rote arm */

  void abduct(float a);
  /**< Raise arm */

  void torsion(float a);
  /**< Turn arm */
};

/**
 * Shoulder class
 */
class Shoulder {
 private:
  static const float SHOULDER_RAD;

 public:
  float radius;			///< shoulder radius
  float aflexion;		///< shoulder flexion angle
  float aabduct;		///< shoulder abduct angle
  class Arm *arm;		///< arm ptr

  Shoulder(Arm *arm);		///< constructor
  ~Shoulder() {}		///< destructor

  int init();
  /**< Init shoulder */

  void flexion(float distance);
  /**< Avance shoulder */

  void abduct(float distance);
  /**< Raise shoulder */
};

/**
 * HeadBody class
 */
class HeadBody {
 private:
  static const float HEAD_RAD;

 public:
  float radius;			///< head radius
  float aflexion;		///< head flexion angle
  float aabduct;		///< head abduct angle
  float atorsion;		///< head torsion angle

  HeadBody();			///< constructor
  ~HeadBody() {}		///< destructor

  int init();
  /**< Init head */

  void flexion(float a);
  /**< Bend head */

  void abduct(float a);
  /**< Tilt head */

  void torsion(float a);
  /**< Turn head */
};

/**
 * Neck class
 */
class Neck {
 private:
  static const float NECK_LEN;

 public:
  float length;			///< neck length
  float aflexion;		///< neck flexion angle
  float aabduct;		///< neck abduct angle
  float atorsion;		///< neck torsion angle
  class HeadBody *head;		///< head ptr

  Neck(HeadBody *head);		///< constructor
  ~Neck() {}			///< destructor

  int init();
  /**< Init neck */

  void flexion(float a);
  /**< Bend neck */

  void abduct(float a);
  /**< Tilt neck */

  void torsion(float a);
  /**< Turn neck */
};

/**
 * Foot class // Ankle
 */
class Foot {
 private:
  static const float FOOT_LEN;

 public:
  float length;			///< foot length
  float aflexion;		///< foot flexion angle
  float aabduct;		///< foot abduct angle
  float atorsion;		///< foot torsion angle

  Foot();			///< constructor
  ~Foot() {}			///< destructor

  int init();
  /**< Init foot */

  void flexion(float a);
  /**< Bend foot */

  void abduct(float a);
  /**< Tilt foot */

  void torsion(float a);
  /**< Turn foot */
};

/**
 * Shin class // Knee
 */
class Shin {
 private:
  static const float SHIN_LEN;

 public:
  float length;			///< shin length
  float aflexion;		///< knee flexion angle
  float atorsion;		///< knee torsion angle
  class Foot *foot;		///< foot ptr

  Shin(Foot *foot);		///< constructor
  ~Shin() {}			///< destructor

  int init();
  /**< Init shin */

  void flexion(float a);
  /**< Bend knee */

  void torsion(float a);
  /**< Turn knee */
};

/**
 * Thigh class // Hip
 */
class Thigh {
 private:
  static const float THIGH_LEN;

 public:
  float length;			///< thigh length
  float aflexion;		///< thigh flexion angle
  float aabduct;		///< thigh abduct angle
  float atorsion;		///< thigh torsion angle
  class Shin *shin;		///< shin ptr

  Thigh(Shin *shin);		///< constructor
  ~Thigh() {}			///< destructor

  int init();
  /**< Init thigh */

  void flexion(float a);
  /**< Rote thigh */

  void abduct(float a);
  /**< Raise thigh */

  void torsion(float a);
  /**< Turn thigh */
};

/**
 * Chest class
 */
class Chest {
 private:
  static const float CHEST_LEN;

 public:
  float length;			///< chest length
  float aflexion;		///< chest flexion angle
  float aabduct;		///< chest abduct angle
  float atorsion;		///< chest torsion angle

  Chest();			///< constructor
  //Chest(Thigh **thighs, Shoulder **shoulders, Neck *neck);
  ~Chest() {}			///< destructor

  //int init(class Body *body);
  /**< Init chest */

  void flexion(float a);
  /**< Roll chest */

  void abduct(float a);
  /**< Tilt chest */

  void torsion(float a);
  /**< Turn chest */
};


/**
 * Body-Parts structure
 */
struct sBodyParts {
  uint8_t model;	///< model type used
  bool loaded;		///< flag loaded or not
  float scale;		///< scale
  float scales[3];	///< scales
  int texid;		///< texture number
  float color[3];	///< color
  class Off *off;	///< Off ptr
  class Obj *obj;	///< Obj ptr
  char url[URL_LEN];	///< url of this part
  char texurl[URL_LEN]; ///< texture url of this part
};

struct sBodyToken {
  char name[16];  	///< name of this part
  uint8_t num;		///< part number
};

/**
 * Join-points structure
 */
struct sJP {
  float *x;
  float *y;
  float *z;
};

/**
 * Body class
 */
class Body {
  friend class Humanoid;

 private:
  /* join points numbers */
  enum jp_num {
    JP_UPPER_NECK,	// 0
    JP_LOWER_NECK,	// 1
    JP_SPINAL,		// 2
    JP_PELVIC,		// 3
    JP_SHOULDER_L,	// 4
    JP_ELBOW_L,		// 5
    JP_WRIST_L,		// 6
    JP_SHOULDER_R,	// 7
    JP_ELBOW_R,		// 8
    JP_WRIST_R,		// 9
    JP_HIP_L,		// 10
    JP_KNEE_L,		// 11
    JP_ANKLE_L,		// 12
    JP_HIP_R,		// 13
    JP_KNEE_R,		// 14
    JP_ANKLE_R,		// 15
    JP_MAX		// 16
  };

  uint8_t bd_draws;		///< number of drawable parts
  uint8_t bd_model;		///< model type used (Off, Obj,...)
  GLint bd_dlist;		///< body display-list
  float bd_tx, bd_ty, bd_tz;	///< body translations
  float bd_rx, bd_ry, bd_rz;	///< body rotations
  float bd_scale;		///< body scale factor
  float bd_skin[3];		///< skin color
  float bd_cloth[3];		///< cloth color
  float bd_color[3];		///< color
  char *url;			///< body url

  // body parts
  HeadBody *head;		///< 1 head
  Neck     *neck;		///< 1 neck
  Chest    *chest;		///< 1 chest
  Thigh    *thigh_r;		///< right thigh
  Thigh    *thigh_l;		///< left thigh
  Shin     *shin_r;		///< right shin
  Shin     *shin_l;		///< left shin
  Foot     *foot_r;		///< right foot
  Foot     *foot_l;		///< left foot
  Shoulder *shoulder_r;		///< right shoulder
  Shoulder *shoulder_l;		///< left shoulder
  Arm      *arm_r;		///< right arm
  Arm      *arm_l;		///< left arm
  Forearm  *forearm_r;		///< right forearm
  Forearm  *forearm_l;		///< left forearm
  Hand     *hand_r;		///< right hand
  Hand     *hand_l;		///< left hand
  Finger   *fingers_r[5];	///< 5 right fingers
  Finger   *fingers_l[5];	///< 5 left fingers
  Phalanx2 *phalanx2[10];	///< 10 phalanx2
  Phalanx  *phalanx[10];	///< 10 phalanx

  struct sBodyParts *bd_parts;	///< body parts array

 public:

  /* body drawable parts */
  enum body_parts {
    BD_HEAD,		// 00
    BD_NECK,		// 01
    BD_CHEST,		// 02
    BD_PELVIC,		// 03
    BD_ARM_L,		// 04
    BD_FARM_L,		// 05
    BD_HAND_L,		// 06
    BD_ARM_R,		// 07
    BD_FARM_R,		// 08
    BD_HAND_R,		// 09
    BD_THIGH_L,		// 10
    BD_SHIN_L,		// 11
    BD_FOOT_L,		// 12
    BD_THIGH_R,		// 13
    BD_SHIN_R,		// 14
    BD_FOOT_R,		// 15
    BD_ABDOMEN,		// 16
    BD_COLLAR_L,	// 17
    BD_COLLAR_R,	// 18
    BD_BELT,		// 19
    BD_THUMB_L,		// 20
    BD_INDEX_L,		// 21
    BD_MIDDLE_L,	// 22
    BD_RING_L,		// 23
    BD_PINKY_L,		// 24
    BD_THUMB_R,		// 25
    BD_INDEX_R,		// 26
    BD_MIDDLE_R,	// 27
    BD_RING_R,		// 28
    BD_PINKY_R,		// 29
    BD_SKIRT,		// 30
    BD_PARTS		// 31
  };

  struct sJP jp;		///< jointpoints.
  class Bap *bap;		///< bap ptr.
  class Face *face;		///< face ptr.
  class Object *object;		///< object ptr.

  Body();
  Body(const char *url);	///< constructor.

  ~Body();			///< destructor.

  void init();
  /**< Inits body. */

  void play();
  /**< Animates a body param. */

  //notused void animHead(float deg, uint8_t axis);
  //notused void animNeck(float deg, uint8_t axis);
  //notused void animChest(float deg, uint8_t axis);
  //notused void animLeg(float deg, uint8_t side, uint8_t axis);
  //notused void animShin(float deg, uint8_t side, uint8_t axis);
  //notused void animFoot(float deg, uint8_t side, uint8_t axis);
  //notused void animArm(float deg, uint8_t side, uint8_t axis);
  //notused void animForearm(float deg, uint8_t side, uint8_t axis);
  //notused void animHand(float deg, uint8_t side, uint8_t axis);
  //notused /**< Animation members. */
  //notused void anim(int param);
  //notused /**< Plays a body param (without bap server). */
  //notused void animReset();

  void render(Pos& pos);
  /**< Renders body and v3d face. */

  void loadBodyParts(FILE *f);
  /**< Loads body's drawable parts. */

  void setColors(float *_skin, float *_cloth);
  /**< Sets colors for skin and cloth. */

 private:
  void load(const char *url);
  /**< Loads body joint points. */

  static void reader(void *o, class Http *http);
  /**< Reads joint points. */

  void draw();
  /**< Draws body's drawable parts in displaylists. */

  void render(uint8_t part);
  /**< Renders a part of the body. */

  bool isPart(uint8_t part);
  /**< Returns true if body part exists. */

  void jpT(int part);
  /**< Translates to the Joint Point. */

  void jpRX(int param);
  void jpRY(int param);
  void jpRZ(int param);
  /**< Rotates around the Joint Point. */

  char * getTok(char *l, int *tok);
  char * skipEqual(char *l);
};

#endif

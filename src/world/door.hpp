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
// door.hpp
//---------------------------------------------------------------------------
#ifndef DOOR_HPP
#define DOOR_HPP

#include "object.hpp"

#define DOOR_TYPE	3
#define DOOR_NAME	"Door"


/**
 * Door class
 */
class Door: public Object {
 private:
  uint8_t mecanism;	///< mecanism
  float aopen;		///< open angle
  float aclose;		///< close angle
  float xopen;		///< open horizontal
  float xclose;		///< close horizontal
  float zopen;		///< open vertical
  float zclose;		///< close vertical
  float speed;		///< angular speed (radian)
  V3 center;		///< center position
  V3 size;		///< dimension

 public:
  // mecanisms
  enum {
    NOMECANISM,
    ANGULAR,
    SLIDING,
    VERTICAL
  };
  // properties
  enum {
    PROPHNAME,
    PROPXY,
    PROPZ,
    PROPAZ,
    PROPS
  };
  // states
  enum {
    NONE,
    OPENED,	///< opened
    CLOSED,	///< closed
    LOCKED,	///< locked
    UNLOCKED	///< unlocked
  };

  static const OClass oclass;	///< class variable

  const OClass* getOClass() {return &oclass;}

  Door(char *l);	///< Constructor
  ~Door();		///< Destructor

  static void funcs();	///< init funclist

  static Object * (creator)(char *l);
  /**< Create from fileline */

  void imposed(float lasting);
  /**< Makes changes on position */

  void timing(time_t, time_t, float *lasting);
  /**< Updates time */

  bool publish(const Pos &oldpos);
  /**< Publishes position */

  bool intersect(Object *pcur, Object *pold);
  /**< When an collision occurs */

 private:
  void parser(char *l);
  /**< Parses file line */

  void open();
  void close();
  void lock();
  void unlock();

  // GUI callbacks
  static void open_cb(Door *o, void *d, time_t s, time_t u);
  static void close_cb(Door *o, void *d, time_t s, time_t u);
  static void lock_cb(Door *o, void *d, time_t s, time_t u);
  static void unlock_cb(Door *o, void *d, time_t s, time_t u);
};

#endif

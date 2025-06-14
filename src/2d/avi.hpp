//---------------------------------------------------------------------------
// VREng (Virtual Reality Engine)       https://github.com/philippedax/vreng
// 
// Copyright (C) 1997-2012 Philippe Dax
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
// avi.hpp
//---------------------------------------------------------------------------
#ifndef AVI_HPP
#define AVI_HPP


#define DATASTART 2060 /* where first frame starts */
#define MAXIDX 800000 /* should be sufficient since AVI size is < 2 GB */
#define MAX_LIST_DEPTH 10

#ifndef VIDEO_MODE_PAL
/* from <linux/videodev.h> */
#define VIDEO_MODE_PAL          0
#define VIDEO_MODE_NTSC         1
#endif

/* The error codes delivered by avi_read_header */
#define ERR_EOF     1
#define ERR_NO_AVI  2
#define ERR_NO_MJPG 3
#define ERR_NO_PCM  4
#define ERR_NO_VIDS 5

/* Some FOURCCs */
#if WORDS_BIGENDIAN
#define MAKEFOURCC(a,b,c,d) ( ((a)<<24) | ((b)<<16) | ((c)<<8) | (d) )
#else
#define MAKEFOURCC(a,b,c,d) ( (a) | ((b)<< 8) | ((c)<<16) | ((d)<<24) )
#endif
#define RIFFtag MAKEFOURCC('R','I','F','F')
#define LISTtag MAKEFOURCC('L','I','S','T')
#define strhtag MAKEFOURCC('s','t','r','h')
#define strftag MAKEFOURCC('s','t','r','f')

#define WAVE_FORMAT_UNKNOWN             (0x0000)
#define WAVE_FORMAT_PCM                 (0x0001)
#define WAVE_FORMAT_ADPCM               (0x0002)
#define WAVE_FORMAT_IBM_CVSD            (0x0005)
#define WAVE_FORMAT_ALAW                (0x0006)
#define WAVE_FORMAT_MULAW               (0x0007)
#define WAVE_FORMAT_OKI_ADPCM           (0x0010)
#define WAVE_FORMAT_DVI_ADPCM           (0x0011)
#define WAVE_FORMAT_DIGISTD             (0x0015)
#define WAVE_FORMAT_DIGIFIX             (0x0016)
#define WAVE_FORMAT_YAMAHA_ADPCM        (0x0020)
#define WAVE_FORMAT_DSP_TRUESPEECH      (0x0022)
#define WAVE_FORMAT_GSM610              (0x0031)
#define IBM_FORMAT_MULAW                (0x0101)
#define IBM_FORMAT_ALAW                 (0x0102)
#define IBM_FORMAT_ADPCM                (0x0103)

/* The Flags in AVI File header */
#define AVIF_HASINDEX           0x00000010      // Index at end of file
#define AVIF_MUSTUSEINDEX       0x00000020
#define AVIF_ISINTERLEAVED      0x00000100
#define AVIF_TRUSTCKTYPE        0x00000800      // Use CKType to find key frames
#define AVIF_WASCAPTUREFILE     0x00010000
#define AVIF_COPYRIGHTED        0x00020000


/**
 * Avi class
 */
class Avi {
 public:
  Avi();
  Avi(const char *url);
  ~Avi();

  FILE * getFile() const;
  int32_t read_header();
  int32_t read_data(uint8_t *vidbuf, uint32_t max_vid, int32_t *retlen);
  void getInfos(uint16_t *_width, uint16_t *_height, float *_fps) const;

 private:
  FILE *fp;
  char *url;
  class Cache *cache;

  int idx[MAXIDX];

  /* The following variables are exported for interpretation after avi_read_header */
  double fps;
  uint16_t width;
  uint16_t height;

  void defaults();

  static void reader(void *_avi, class Http *http);
};

#endif

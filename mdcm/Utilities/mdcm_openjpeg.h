/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef MDCM_OPENJPEG_H
#define MDCM_OPENJPEG_H

#include "mdcmTypes.h"

#ifdef MDCM_USE_SYSTEM_OPENJPEG
#include <openjpeg.h>
#else
#include <mdcmopenjpeg/src/lib/openjp2/openjpeg.h>
#endif

#endif

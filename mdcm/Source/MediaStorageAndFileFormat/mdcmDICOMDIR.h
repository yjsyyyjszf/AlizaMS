/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef MDCMDICOMDIR_H
#define MDCMDICOMDIR_H

#include "mdcmFileSet.h"

namespace mdcm
{
/**
 * \brief DICOMDIR class
 *
 * \details Structured for handling DICOMDIR
 */
class MDCM_EXPORT DICOMDIR
{
public:
  DICOMDIR() {}
  DICOMDIR(const FileSet & fs) : _FS(fs) {}

private:
  FileSet _FS;
};

} // end namespace mdcm

#endif //MDCMDICOMDIR_H

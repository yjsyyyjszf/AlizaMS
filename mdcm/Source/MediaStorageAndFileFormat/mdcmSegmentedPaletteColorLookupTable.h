/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef MDCMSEGMENTEDPALETTECOLORLOOKUPTABLE_H
#define MDCMSEGMENTEDPALETTECOLORLOOKUPTABLE_H

#include "mdcmLookupTable.h"

namespace mdcm
{

/**
 * \brief SegmentedPaletteColorLookupTable class
 */
class MDCM_EXPORT SegmentedPaletteColorLookupTable : public LookupTable
{
public:
  SegmentedPaletteColorLookupTable();
  ~SegmentedPaletteColorLookupTable();
  void Print(std::ostream &) const {}

  /// Initialize a SegmentedPaletteColorLookupTable
  void SetLUT(LookupTableType type, const unsigned char *array,
    unsigned int length);

};

} // end namespace mdcm

#endif //MDCMSEGMENTEDPALETTECOLORLOOKUPTABLE_H

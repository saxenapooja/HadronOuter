#ifndef HODetId_H
#define HODetId_H

/** \class HIId
 *  DetUnit identifier for Hadron-Outer.
 *  
 *  \author Pooja Saxena
 */

#include <DataFormats/DetId/interface/DetId.h>

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include <iosfwd>

//class
class HOId : public HcalDetId {
  
 private:
  int ieta_  ;
  int iphi_  ;
  double Emin_, Emax_;

 public:
  /// Default constructor. 
  /// Fills the common part in the base and leaves 0 in all other fields
  HOId();
  
  /// Construct from a packed id. It is required that the packed id represents
  /// valid HO DetId (proper Detector & SubDet fields), otherwise an exception is thrown.
  //  HOId(uint32_t id);
  //  HOId(HcalDetId id);
  
  /// Construct from fully qualified identifier.
  //  HOId(int tower_ieta, int tower_iphi);
  HOId(HcalDetId  det, int tower_ieta, int tower_iphi);
  HOId(DetId gen);

  signed eta() const;
  unsigned phi() const;
  int wheel()   const;
  int sector() const;
  double Emin() const;
  double Emax() const;
  
  static const int maxEta = 15;
  static const int minEta = -15;
  static const int maxPhi = 72;
  static const int minPhi = 1;
  
  static const int minSectorId =     0; // 0 for DT
  static const int maxSectorId =    11; // 14 for DT
  static const int minWheelId  =    -2;
  static const int maxWheelId  =     2;

 protected:
  // Perform a consistency check of the id with a HO Id
  // It throws an exception if this is not the case
  //  void checkHOId();
  void checkId(HcalDetId &det);
};

std::ostream& operator<<( std::ostream& os, const HOId& id );
#endif


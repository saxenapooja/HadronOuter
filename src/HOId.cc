/** \file
 *  See header file for a description of this class.
 *
 *  \author G. Cerminara - Pooja Saxena
 */

#include "HadronOuter/HO/interface/HOId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
//#include "DataFormats/FWLite/interface/Event.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/Exception.h"
#include <ostream>
#include "DataFormats/Provenance/interface/EventAuxiliary.h"

using namespace std;
using namespace edm;

HOId::HOId() : DetId(DetId::Hcal, HcalSubdetector::HcalOuter){}


HOId::HOId(uint32_t id) {
  checkHOId();               // Check this is a valid id for HO
}

HOId::HOId(DetId id) {
  checkHOId();               // Check this is a valid id for HO
}


HOId::HOId(int ieta, int iphi): ieta_(ieta), iphi_(iphi) {
  checkHOId();

  // Check that arguments are within the range
  if (ieta      < maxEta     || ieta   > minEta ||
      iphi      < maxPhi     || iphi   > maxPhi) {
    throw cms::Exception("InvalidDetId") << "HOId ctor:" 
					 << " Invalid parameters: " 
					 << " ieta:"<< ieta
					 << " iphi:"<< iphi
					 << std::endl;
  }
}



void HOId::checkHOId() {
  if (det()!=DetId::Hcal || subdetId()!=HcalSubdetector::HcalOuter) {
    throw cms::Exception("InvalidDetId") << "HOId ctor:"
					 << " det: " << det()
					 << " subdet: " << subdetId()
					 << " is not a valid HO id";  
  }
}


int HOId::bx(const edm::Event& iEvent) {
  bunchcrossing_ = iEvent.eventAuxiliary().bunchCrossing();
  return bunchcrossing_;
}

unsigned HOId::phi() const{
  return iphi_;
}


signed HOId::eta() const{
  return ieta_;
}

double HOId::Emin() const{
  return Emin_;
}


double HOId::Emax() const{
  return Emax_;
}


int HOId::wheel() const {
  int ring_ = 0;
  if(ieta_ < -10)
    ring_ = -2;
  else  if((ieta_ > -11) && (ieta_ < -4))
    ring_ = -1;
  else  if((ieta_ > -5) && (ieta_ < 5))
    ring_ = 0;
  else if((ieta_ > 4) && (ieta_ < 11))
    ring_ = 1;
  else if(ieta_ > 10)
    ring_ = 2;
  else throw cms::Exception("HOId")
	 << "Wheel is not assigned correct" << ring_ << " !!\n";
  return ring_;
}


int HOId::sector() const {
  int sector_ = 0;  //started it from: 0-12 as DT has the same local definition
  if (iphi_ > 71 && iphi_ < 5  ) sector_ =0;
  else  if (iphi_ > 4  && iphi_ < 11 ) sector_ =1;
  else if (iphi_ > 10 && iphi_ < 17 ) sector_ =2;
  else if (iphi_ > 16 && iphi_ < 23 ) sector_ =3;
  else if (iphi_ > 22 && iphi_ < 29 ) sector_ =4;
  else if (iphi_ > 28 && iphi_ < 35 ) sector_ =5;
  else if (iphi_ > 34 && iphi_ < 41 ) sector_ =6;
  else if (iphi_ > 40 && iphi_ < 47 ) sector_ =7;
  else if (iphi_ > 46 && iphi_ < 53 ) sector_ =8;
  else if (iphi_ > 52 && iphi_ < 59 ) sector_ =9;
  else if (iphi_ > 58 && iphi_ < 65 ) sector_ =10;
  else if (iphi_ > 64 && iphi_ < 71 ) sector_ =11;
  else throw cms::Exception("HOId")  
	  << "Sector is not assigned correct" << sector_ << " !!\n";  
  return sector_;
}


int HOId::trayId() const {
  int trayId_ = -1;

  if (iphi_%6 == 5 ) trayId_ = 0; //loweset tray
  else if (iphi_%6 == 0 ) trayId_ = 1; //loweset+1
  else if (iphi_%6 == 1 ) trayId_ = 2; //loweset+2
  else if (iphi_%6 == 2 ) trayId_ = 3; //loweset+3
  else if (iphi_%6 == 3 ) trayId_ = 4; //loweset+4
  else if  (iphi_%6 == 4 ) trayId_ = 5; //loweset+5
 
  return trayId_;
}


int HOId::tileId() const {
  int tile = ieta_ * iphi_;
  return  tile;
}


std::ostream& operator<<( std::ostream& os, const HOId & id ) {
  os << " Wheel:"<< id.wheel()
     << " Sector:"<< id.sector()
     << " eta:"<< id.eta()
     << " phi:"<< id.phi(); 
  
  return os;
}




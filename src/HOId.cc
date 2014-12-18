/** \file
 *  See header file for a description of this class.
 *
 *  \autor Pooja Saxena
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

HOId::HOId() : HcalDetId(DetId::Hcal) {} //, HcalSubdetector::HcalOuter){}


// HOId::HOId(uint32_t id) : HcalDetId(id) {
//   DetId id_(Hcal, HcalSubdetector::HcalOuter);
  
//   if (det()!=DetId::Hcal || subdetId()!=HcalSubdetector::HcalOuter) {
//     throw cms::Exception("InvalidDetId") << "This HOId :"
// 					 << " det: " << det()
// 					 << " subdet: " << subdetId()
// 					 << " is not a valid HO id.";  
//   }

//   //checkHOId();          
// }

// HOId::HOId(HcalDetId id) {
//   // DetId id_(Hcal, HcalSubdetector::HcalOuter);
//   //  checkHOId();          
// }


HOId::HOId(DetId gen): HcalDetId(gen) {
  cout<<"gen.det : "<< gen.det() <<", "<< " subdet() : "<< gen.subdetId() << endl;
  if(gen.null()) throw cms::Exception("invalid DetId") << gen.rawId() << std::dec;

  if (!gen.null()) {
    HcalSubdetector subdet=(HcalSubdetector(gen.subdetId()));
    if (gen.det()!= Hcal || subdet!=HcalOuter        ) {
      throw cms::Exception("Invalid DetId") << "Cannot initialize HOId from " 
					    << 	std::hex          << gen.rawId() 
					    <<  " det : "         << gen.det() 
					    <<  " subdet is : "   << gen.subdetId()
					    << std::dec; 
    }  
  }
  //  id_ = gen.rawId();//det(); //rawId();
}


HOId::HOId(HcalDetId gen, int ieta, int iphi): HcalDetId(gen), ieta_(ieta), iphi_(iphi) {
  if(gen.null()) throw cms::Exception("invalid HcalDetId") << gen.rawId() << std::dec;
  if(!gen.null()) { 
    // Check that arguments are within the range
    if (ieta      > maxEta     || ieta   < minEta ||
	iphi      > maxPhi     || iphi   < minPhi) {
      throw cms::Exception("InvalidDetId") << "HOId ctor:" 
					   << " Invalid parameters: " 
					   << " ieta:"<< ieta
					   << " iphi:"<< iphi
					   << std::endl;
    }
  }

  // int depth = 4;
  // id_ |= ((depth&0x1F)<<14) |
  //   ((ieta>0)?(0x2000|(ieta<<7)):((-ieta)<<7)) |
  //   (iphi&0x7F);
  // //  cout<<"After -- id_Det() :" << id_.det() << " id_Subdet() : "<< id_.subdetId()  << std::endl; //  //  cout<<"id_ : " << std::hex<< id_ << endl;
  checkId(gen);  
  //id_ = gen.rawId();
}


void HOId::checkId(HcalDetId &det) {
  if (det.subdet() !=3 || det.depth()!=4) {
    throw cms::Exception("InvalidDetId") << "HOId ctor:"
                                         << " det: "    << det()
					 << " subdet: " <<  det.subdet()
					 << " depth: "  <<  det.depth()
                                         << " is not a valid HO id";
  }
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
  int sector_ = -99;  //started it from: 0-12 as DT has the same local definition
  if (iphi_ < 5  ) sector_ = 0;
  else  if (iphi_ > 4  && iphi_ < 11 ) sector_ =1;
  else if (iphi_ > 10 && iphi_ < 17 )  sector_ =2;
  else if (iphi_ > 16 && iphi_ < 23 ) sector_ =3; 
  else if (iphi_ > 22 && iphi_ < 29 ) sector_ =4;
  else if (iphi_ > 28 && iphi_ < 35 ) sector_ =5;
  else if (iphi_ > 34 && iphi_ < 41 ) sector_ =6;
  else if (iphi_ > 40 && iphi_ < 47 ) sector_ =7;
  else if (iphi_ > 46 && iphi_ < 53 ) sector_ =8;
  else if (iphi_ > 52 && iphi_ < 59 ) sector_ =9;
  else if (iphi_ > 58 && iphi_ < 65 ) sector_ =10;
  else if (iphi_ > 64 && iphi_ < 71 ) sector_ =11;
  else if (iphi_ > 70 )               sector_ = 0;
  else throw cms::Exception("HOId")  
	  << "Sector is not assigned correct" << sector_ << " !!\n";  
  return sector_;
}


std::ostream& operator<<( std::ostream& os, const HOId & id ) {
  os << " Wh:"<< id.wheel()
     << " Se:"<< id.sector()
     << " eta:"<< id.eta()
     << " phi:"<< id.phi(); 
  return os;
}




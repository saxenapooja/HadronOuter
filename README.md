HadronOuter
===========

Code for implementing informatiom from Hadron-outer calorimeter of CMS for the L1 trigger setup.


Validated for:

* CMSSW_7_2_2_patch1


To build:

* scram p CMSSW CMSSW_7_2_2_patch1
* cd CMSSW_7_2_2_patch1/src/
* cmsenv
* git clone https://github.com/saxenapooja/L1MuonHOTrigger.git L1Trigger/L1IntegratedMuonTrigger/
* git clone https://github.com/saxenapooja/HadronOuter.git HadronOuter/HO
* scram b -j20


To run:

* cd L1Trigger/L1IntegratedMuonTrigger/test
* cmsRun run_L1ITMuonBarrelLocalTrigger_cfg.py

Info Page:

* https://twiki.cern.ch/twiki/bin/viewauth/CMS/DtDttfTriggerUpgradeStudies#Technical_Aspects_Data_Samples_a


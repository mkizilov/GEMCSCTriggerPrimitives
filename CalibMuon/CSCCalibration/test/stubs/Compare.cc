// -*- C++ -*-
//
// Package:    Compare
// Class:      Compare
//
/**\class Compare Compare.cc CalibMuon/Compare/src/Compare.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Thomas Nummy,Bld. 32 Room 4-C21,+41227671337,
//         Created:  Thu Oct 29 13:55:15 CET 2009
//
//
//////////////////////////////////READ THIS
/// FIRST//////////////////////////////////////////////////////////
//////////////////"std::bad_alloc exception caught in cmsRun" ERROR when you
/// have text inside the .dat/////
/////////////////files ---->Check them first before running this
/// code!/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// system include files
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// user include files
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class decleration
//

class Compare : public edm::one::EDAnalyzer<> {
public:
  explicit Compare(const edm::ParameterSet &);
  ~Compare() override = default;

private:
  void analyze(const edm::Event &, const edm::EventSetup &) override;

  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Compare::Compare(const edm::ParameterSet &iConfig) {
  // now do what ever initialization is needed
  /*


  */

  //=========== Compare Pedestals =================
  std::cout << "Comparing PEDESTALS, please wait!" << std::endl;

  const int MAX_SIZE = 252288;

  int old_index;
  float old_ped, old_rms;
  std::vector<int> old_index_id;
  std::vector<float> old_peds;
  int new_index;
  float new_ped, new_rms;
  std::vector<int> new_index_id;
  std::vector<float> new_peds;
  std::vector<float> diffPeds;
  std::vector<float> diffGains;

  std::ifstream olddata;
  olddata.open("old_dbpeds.dat", std::ios::in);
  if (!olddata) {
    std::cerr << "Error: old_dbpeds.dat -> no such file!" << std::endl;
    exit(1);
  }

  while (!olddata.eof()) {
    olddata >> old_index >> old_ped >> old_rms;
    old_index_id.push_back(old_index);
    old_peds.push_back(old_ped);
  }
  olddata.close();

  std::ifstream newdata;
  std::ofstream myPedsFile("diffPedsTest.dat", std::ios::out);
  newdata.open("goodPeds.dat", std::ios::in);
  if (!newdata) {
    std::cerr << "Error: goodPeds.dat -> no such file!" << std::endl;
    exit(1);
  }

  while (!newdata.eof()) {
    newdata >> new_index >> new_ped >> new_rms;
    new_index_id.push_back(new_index);
    new_peds.push_back(new_ped);
  }
  newdata.close();

  diffPeds.resize(MAX_SIZE);

  for (int i = 0; i < MAX_SIZE; ++i) {
    for (unsigned int k = 0; k < new_index_id.size() - 1; ++k) {
      if (old_index_id[i] == new_index_id[k]) {
        diffPeds[k] = old_peds[i] / 10. - new_peds[k];
        myPedsFile << old_index_id[i] << "  " << diffPeds[k] << std::endl;
      }
    }
  }

  // ============= Compare Crosstalk ===================
  std::cout << "Comparing CROSSTALK, please wait!" << std::endl;

  old_index = 0;
  float old_xtalk_left, old_xtalk_right, old_int_left, old_int_right;
  old_index_id.clear();
  std::vector<float> old_Rxtalk;
  std::vector<float> old_Lxtalk;
  std::vector<float> old_Rint;
  std::vector<float> old_Lint;
  std::vector<float> diffXtalkR;
  std::vector<float> diffXtalkL;
  std::vector<float> diffIntR;
  std::vector<float> diffIntL;

  std::vector<float> myoldxtalkR;
  std::vector<float> myoldxtalkL;
  std::vector<float> myoldintR;
  std::vector<float> myoldintL;

  new_index = 0;
  float new_xtalk_left, new_xtalk_right, new_int_left, new_int_right;
  new_index_id.clear();
  std::vector<float> new_Rxtalk;
  std::vector<float> new_Lxtalk;
  std::vector<float> new_Rint;
  std::vector<float> new_Lint;

  int counter, counter1;

  std::ifstream olddata1;
  olddata1.open("old_dbxtalk.dat", std::ios::in);
  if (!olddata1) {
    std::cerr << "Error: old_dbxtalk.dat -> no such file!" << std::endl;
    exit(1);
  }

  while (!olddata1.eof()) {
    olddata1 >> old_index >> old_xtalk_left >> old_int_left >> old_xtalk_right >> old_int_right;
    old_index_id.push_back(old_index);
    old_Rxtalk.push_back(old_xtalk_right);
    old_Rint.push_back(old_int_right);
    old_Lxtalk.push_back(old_xtalk_left);
    old_Lint.push_back(old_int_left);
  }
  olddata1.close();

  std::ifstream newdata1;
  std::ofstream myXtalkFile("diffXtalkTest.dat", std::ios::out);

  newdata1.open("goodXtalk.dat", std::ios::in);
  if (!newdata1) {
    std::cerr << "Error: goodXtalk.dat  -> no such file!" << std::endl;
    exit(1);
  }

  while (!newdata1.eof()) {
    newdata1 >> new_index >> new_xtalk_left >> new_int_left >> new_xtalk_right >> new_int_right;
    new_index_id.push_back(new_index);
    new_Rxtalk.push_back(new_xtalk_right);
    new_Rint.push_back(new_int_right);
    new_Lxtalk.push_back(new_xtalk_left);
    new_Lint.push_back(new_int_left);
  }
  newdata1.close();

  diffXtalkR.resize(MAX_SIZE);
  diffXtalkL.resize(MAX_SIZE);
  diffIntR.resize(MAX_SIZE);
  diffIntL.resize(MAX_SIZE);
  myoldxtalkR.resize(MAX_SIZE);
  myoldxtalkL.resize(MAX_SIZE);
  myoldintR.resize(MAX_SIZE);
  myoldintR.resize(MAX_SIZE);

  for (int i = 0; i < MAX_SIZE; ++i) {
    counter = old_index_id[i];
    myoldxtalkR[i] = old_Rxtalk[i];
    myoldxtalkL[i] = old_Lxtalk[i];
    myoldintR[i] = old_Rint[i];
    myoldintR[i] = old_Lint[i];

    for (unsigned int k = 0; k < new_index_id.size() - 1; k++) {
      counter1 = new_index_id[k];
      if (counter == counter1) {
        diffXtalkR[k] = old_Rxtalk[i] / 10000000. - new_Rxtalk[k];
        diffXtalkL[k] = old_Lxtalk[i] / 10000000. - new_Lxtalk[k];
        diffIntR[k] = old_Rint[i] / 100000. - new_Rint[k];
        diffIntL[k] = old_Rint[i] / 100000. - new_Rint[k];
        myXtalkFile << counter << "  " << diffXtalkL[k] << "  " << diffIntL[k] << "  " << diffXtalkR[k] << "  "
                    << diffIntR[k] << "  " << std::endl;
      }
    }
  }

  // ================= Compare Gains ===============
  std::cout << "Comparing GAINS, please wait!" << std::endl;

  old_index = 0;
  float old_slope;
  old_index_id.clear();
  std::vector<float> old_gains;
  std::vector<float> old_intercept;
  std::vector<float> old_chi;

  new_index = 0;
  float new_slope, new_int, new_chi2;
  new_index_id.clear();
  std::vector<float> new_gains;
  std::vector<float> new_intercept;
  std::vector<float> new_chi;

  std::vector<float> myoldgains;

  counter = 0;
  counter1 = 0;
  int old_nrlines = 0;
  int new_nrlines = 0;

  std::ifstream olddata2;
  olddata2.open("old_dbgains.dat", std::ios::in);
  if (!olddata2) {
    std::cerr << "Error: old_dbgains.dat -> no such file!" << std::endl;
    exit(1);
  }

  while (!olddata2.eof()) {
    olddata2 >> old_index >> old_slope;
    old_index_id.push_back(old_index);
    old_gains.push_back(old_slope);
    old_nrlines++;
  }
  olddata2.close();

  std::ifstream newdata2;
  std::ofstream myGainsFile("diffGainsTest.dat", std::ios::out);
  newdata2.open("goodGains.dat", std::ios::in);
  if (!newdata2) {
    std::cerr << "Error: goodGains.dat -> no such file!" << std::endl;
    exit(1);
  }

  while (!newdata2.eof()) {
    newdata2 >> new_index >> new_slope >> new_int >> new_chi2;
    new_index_id.push_back(new_index);
    new_gains.push_back(new_slope);
    new_intercept.push_back(new_int);
    new_chi.push_back(new_chi2);
    new_nrlines++;
  }
  newdata2.close();
  diffGains.resize(MAX_SIZE);
  myoldgains.resize(MAX_SIZE);

  for (int i = 0; i < MAX_SIZE; ++i) {
    counter = old_index_id[i];
    myoldgains[i] = old_gains[i];

    for (unsigned int k = 0; k < new_index_id.size() - 1; k++) {
      counter1 = new_index_id[k];
      if (counter == counter1) {
        diffGains[k] = old_gains[i] / 1000. - new_gains[k];
        myGainsFile << counter << "  " << diffGains[k] << std::endl;
      }
    }
  }

  //=================== Compare Noise Matrix ===============
  std::cout << "Comparing NOISE MATRIX, please wait!" << std::endl;

  old_index = 0;
  float old_elem33, old_elem34, old_elem35, old_elem44, old_elem45, old_elem46, old_elem55, old_elem56;
  float old_elem57, old_elem66, old_elem67, old_elem77;
  old_index_id.clear();
  std::vector<float> old_el33;
  std::vector<float> old_el34;
  std::vector<float> old_el35;
  std::vector<float> old_el44;
  std::vector<float> old_el45;
  std::vector<float> old_el46;
  std::vector<float> old_el55;
  std::vector<float> old_el56;
  std::vector<float> old_el57;
  std::vector<float> old_el66;
  std::vector<float> old_el67;
  std::vector<float> old_el77;

  new_index = 0;
  float new_elem33, new_elem34, new_elem35, new_elem44, new_elem45, new_elem46, new_elem55, new_elem56;
  float new_elem57, new_elem66, new_elem67, new_elem77;
  new_index_id.clear();
  std::vector<float> new_el33;
  std::vector<float> new_el34;
  std::vector<float> new_el35;
  std::vector<float> new_el44;
  std::vector<float> new_el45;
  std::vector<float> new_el46;
  std::vector<float> new_el55;
  std::vector<float> new_el56;
  std::vector<float> new_el57;
  std::vector<float> new_el66;
  std::vector<float> new_el67;
  std::vector<float> new_el77;

  // differences
  std::vector<float> diff_el33;
  std::vector<float> diff_el34;
  std::vector<float> diff_el35;
  std::vector<float> diff_el44;
  std::vector<float> diff_el45;
  std::vector<float> diff_el46;
  std::vector<float> diff_el55;
  std::vector<float> diff_el56;
  std::vector<float> diff_el57;
  std::vector<float> diff_el66;
  std::vector<float> diff_el67;
  std::vector<float> diff_el77;

  // old vectors
  std::vector<float> myoldel33;
  std::vector<float> myoldel34;
  std::vector<float> myoldel35;
  std::vector<float> myoldel44;
  std::vector<float> myoldel45;
  std::vector<float> myoldel46;
  std::vector<float> myoldel55;
  std::vector<float> myoldel56;
  std::vector<float> myoldel57;
  std::vector<float> myoldel66;
  std::vector<float> myoldel67;
  std::vector<float> myoldel77;

  counter = 0;
  counter1 = 0;
  // old_nrlines=0;
  // new_nrlines=0;

  std::ifstream olddata3;
  olddata3.open("old_dbmatrix.dat", std::ios::in);
  if (!olddata3) {
    std::cerr << "Error: old_dbmatrix.dat -> no such file!" << std::endl;
    exit(1);
  }

  while (!olddata3.eof()) {
    olddata3 >> old_index >> old_elem33 >> old_elem34 >> old_elem44 >> old_elem35 >> old_elem45 >> old_elem55 >>
        old_elem46 >> old_elem56 >> old_elem66 >> old_elem57 >> old_elem67 >> old_elem77;
    old_index_id.push_back(old_index);
    old_el33.push_back(old_elem33);
    old_el34.push_back(old_elem34);
    old_el35.push_back(old_elem35);
    old_el44.push_back(old_elem44);
    old_el45.push_back(old_elem45);
    old_el46.push_back(old_elem46);
    old_el55.push_back(old_elem55);
    old_el56.push_back(old_elem56);
    old_el57.push_back(old_elem57);
    old_el66.push_back(old_elem66);
    old_el67.push_back(old_elem67);
    old_el77.push_back(old_elem77);
    // old_nrlines++;
  }
  olddata3.close();

  std::ifstream newdata3;
  std::ofstream myMatrixFile("diffMatrixTest.dat", std::ios::out);
  newdata3.open("goodMatrix.dat", std::ios::in);
  if (!newdata3) {
    std::cerr << "Error: goodMatrix.dat -> no such file!" << std::endl;
    exit(1);
  }

  while (!newdata3.eof()) {
    newdata3 >> new_index >> new_elem33 >> new_elem34 >> new_elem44 >> new_elem35 >> new_elem45 >> new_elem55 >>
        new_elem46 >> new_elem56 >> new_elem66 >> new_elem57 >> new_elem67 >> new_elem77;
    new_index_id.push_back(new_index);
    new_el33.push_back(new_elem33);
    new_el34.push_back(new_elem34);
    new_el35.push_back(new_elem35);
    new_el44.push_back(new_elem44);
    new_el45.push_back(new_elem45);
    new_el46.push_back(new_elem46);
    new_el55.push_back(new_elem55);
    new_el56.push_back(new_elem56);
    new_el57.push_back(new_elem57);
    new_el66.push_back(new_elem66);
    new_el67.push_back(new_elem67);
    new_el77.push_back(new_elem77);
    // new_nrlines++;
  }
  newdata3.close();

  // resize
  diff_el33.resize(MAX_SIZE);
  diff_el34.resize(MAX_SIZE);
  diff_el35.resize(MAX_SIZE);
  diff_el44.resize(MAX_SIZE);
  diff_el45.resize(MAX_SIZE);
  diff_el46.resize(MAX_SIZE);
  diff_el55.resize(MAX_SIZE);
  diff_el56.resize(MAX_SIZE);
  diff_el57.resize(MAX_SIZE);
  diff_el66.resize(MAX_SIZE);
  diff_el67.resize(MAX_SIZE);
  diff_el77.resize(MAX_SIZE);

  myoldel33.resize(MAX_SIZE);
  myoldel34.resize(MAX_SIZE);
  myoldel35.resize(MAX_SIZE);
  myoldel44.resize(MAX_SIZE);
  myoldel45.resize(MAX_SIZE);
  myoldel46.resize(MAX_SIZE);
  myoldel55.resize(MAX_SIZE);
  myoldel56.resize(MAX_SIZE);
  myoldel57.resize(MAX_SIZE);
  myoldel66.resize(MAX_SIZE);
  myoldel67.resize(MAX_SIZE);
  myoldel77.resize(MAX_SIZE);

  for (int i = 0; i < MAX_SIZE; ++i) {
    counter = old_index_id[i];
    myoldel33[i] = old_el33[i];
    myoldel34[i] = old_el34[i];
    myoldel35[i] = old_el35[i];
    myoldel44[i] = old_el44[i];
    myoldel45[i] = old_el45[i];
    myoldel46[i] = old_el46[i];
    myoldel55[i] = old_el55[i];
    myoldel56[i] = old_el56[i];
    myoldel57[i] = old_el57[i];
    myoldel66[i] = old_el66[i];
    myoldel67[i] = old_el67[i];
    myoldel77[i] = old_el77[i];

    for (unsigned int k = 0; k < new_index_id.size() - 1; k++) {
      counter1 = new_index_id[k];
      if (counter == counter1) {
        diff_el33[k] = old_el33[i] / 1000. - new_el33[k];
        diff_el34[k] = old_el34[i] / 1000. - new_el34[k];
        diff_el35[k] = old_el35[i] / 1000. - new_el35[k];
        diff_el44[k] = old_el44[i] / 1000. - new_el44[k];
        diff_el45[k] = old_el45[i] / 1000. - new_el45[k];
        diff_el46[k] = old_el46[i] / 1000. - new_el46[k];
        diff_el55[k] = old_el55[i] / 1000. - new_el55[k];
        diff_el56[k] = old_el56[i] / 1000. - new_el56[k];
        diff_el57[k] = old_el57[i] / 1000. - new_el57[k];
        diff_el66[k] = old_el66[i] / 1000. - new_el66[k];
        diff_el67[k] = old_el67[i] / 1000. - new_el67[k];
        diff_el77[k] = old_el77[i] / 1000. - new_el77[k];
        myMatrixFile << counter << "  " << diff_el33[k] << "  " << diff_el34[k] << "  " << diff_el35[k] << "  "
                     << diff_el44[k] << "  " << diff_el45[k] << "  " << diff_el46[k] << "  " << diff_el55[k] << "  "
                     << diff_el56[k] << "  " << diff_el57[k] << "  " << diff_el66[k] << "  " << diff_el67[k] << "  "
                     << diff_el77[k] << "  " << std::endl;
      }
    }
  }
  std::cout << "DONE with comparison!" << std::endl;
}

//
// member functions
//

// ------------ method called to for each event  ------------
void Compare::analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup) {}

// define this as a plug-in
DEFINE_FWK_MODULE(Compare);

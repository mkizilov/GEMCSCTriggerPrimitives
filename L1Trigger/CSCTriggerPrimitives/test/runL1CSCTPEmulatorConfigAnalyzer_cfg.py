from __future__ import print_function
import sys
import os

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.register ('type',
                  '',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "MC or Data")
options.parseArguments()

# if str(options.type) == "Data": globalTag = 'auto:run2_data'
if str(options.type) == "Data": globalTag = '124X_dataRun3_v10'
elif str(options.type) == "MC": globalTag = 'auto:run2_mc'
else:
    print("Please choose \"Data\" or \"MC\" ")
    sys.exit(1)

import FWCore.ParameterSet.Config as cms

# from Configuration.Eras.Era_Run2_2018_cff import Run2_2018
# process = cms.Process("TEST",Run2_2018)

from Configuration.Eras.Era_Run3_cff import Run3
process = cms.Process("TEST",Run3)

process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("CalibMuon.CSCCalibration.CSCL1TPLookupTableEP_cff")
process.load('L1Trigger.CSCTriggerPrimitives.cscTriggerPrimitiveDigis_cfi')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, globalTag, '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)
process.source = cms.Source("EmptySource")

print("---------------------------------------------------------------------------")
print("Release:", os.environ['CMSSW_VERSION'], ", globaltag:", process.GlobalTag.globaltag.value())
print("---------------------------------------------------------------------------")

process.L1CSCTPEmulatorConfigAnalyzer = cms.EDAnalyzer("L1CSCTPEmulatorConfigAnalyzer",
    alctParam07 = process.cscTriggerPrimitiveDigis.alctPhase1,
    clctParam07 = process.cscTriggerPrimitiveDigis.clctPhase1,
    tmbParam = process.cscTriggerPrimitiveDigis.tmbPhase1,
)

process.p = cms.Path(process.L1CSCTPEmulatorConfigAnalyzer)

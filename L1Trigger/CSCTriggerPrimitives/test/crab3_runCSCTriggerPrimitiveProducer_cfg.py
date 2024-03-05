from CRABClient.UserUtilities import config
config = config()

#section general
config.General.requestName = '2024-02-28_20ZMu'
config.General.workArea = 'crab3_out'#working dir
config.General.transferOutputs = True
config.General.transferLogs = True

#section JobType
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runCSCTriggerPrimitiveProducer_cfg.py'
# config.JobType.maxMemoryMB = 5000
# config.JobType.maxJobRuntimeMin = 2880 # 1440min = 24hours
config.JobType.numCores = 1
# config.JobType.allowUndistributedCMSSW = True
#config.JobType.generator
#config.JobType.pyCfgParams
# config.JobType.inputFiles = ['/afs/cern.ch/work/m/mkizilov/private/CSCEmu_CMSSW_13_0_3/src/L1Trigger/CSCTriggerPrimitives/data']


#section Data
config.Data.inputDataset = '/Muon1/Run2023D-ZMu-PromptReco-v1/RAW-RECO'
# config.Data.userInputFiles = open('Run2023D_Pv2.list').readlines()
config.Data.runRange = '370293'



#config.Data.inputDBS = 'phys03'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
#config.Data.splitting = 'LumiBased'
# config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 1
config.Data.totalUnits = 20
# config.Data.outLFNDirBase = '/store/user/mkizilov/CSC_layer_geom/Run2023BC_IdealGeometry'
config.Data.outLFNDirBase = '/store/user/mkizilov/crab3_out/Trigger/2024-02-28_20ZMu/'
config.Data.publication = False
config.Data.outputDatasetTag = config.General.requestName
config.Site.storageSite = 'T3_CH_CERNBOX'
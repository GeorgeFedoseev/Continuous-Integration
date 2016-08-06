add_test(runMC ${ROOTSYS}/bin/root -b -l "${PROJECT_SOURCE_DIR}/macro/mpd/runMC.C(\"auau.09gev.mbias.98k.ftn14\",\"$VMCWORKDIR/macro/mpd/evetest.root\",0,2)")
SET_TESTS_PROPERTIES (runMC PROPERTIES TIMEOUT "300")
SET_TESTS_PROPERTIES (runMC PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully.")

add_test(recoTPC ${ROOTSYS}/bin/root -b -l ${PROJECT_SOURCE_DIR}/macro/mpd/recoTPC.C)
SET_TESTS_PROPERTIES (recoTPC PROPERTIES TIMEOUT "200")
SET_TESTS_PROPERTIES (recoTPC PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully.")

add_test(reco ${ROOTSYS}/bin/root -b -l ${PROJECT_SOURCE_DIR}/macro/mpd/reco.C)
SET_TESTS_PROPERTIES (reco PROPERTIES TIMEOUT "800")
SET_TESTS_PROPERTIES (reco PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully.")

add_test(proof ${ROOTSYS}/bin/root -b -l "${PROJECT_SOURCE_DIR}/macro/mpd/reco.C(\"$VMCWORKDIR/macro/mpd/evetest.root\",\"mpddst.root\",0,2,\"proof\")")
SET_TESTS_PROPERTIES (proof PROPERTIES TIMEOUT "800")
SET_TESTS_PROPERTIES (proof PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully.")

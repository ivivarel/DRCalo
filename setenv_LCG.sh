#!/bin/sh


export DRCALO_LCGDIR=/cvmfs/sft.cern.ch/lcg/
export DRCALO_LCGVER=LCG_96b
export DRCALO_ARCH=x86_64-centos7
export DRCALO_CMAKEVER=latest
export DRCALO_GCCVER=8
export DRCALO_PYTHIAVER=240

export DRCALO_ARCHCONF=${DRCALO_ARCH}-gcc${DRCALO_GCCVER}-opt
export DRCALO_LCGREL=${DRCALO_LCGDIR}/releases/${DRCALO_LCGVER}


if [ -d ${DRCALO_LCGDIR} ] 
then
    export PATH=${DRCALO_LCGDIR}/contrib/CMake/${DRCALO_CMAKEVER}/Linux-x86_64/bin:$PATH
    source ${DRCALO_LCGDIR}/contrib/gcc/${DRCALO_GCCVER}/${DRCALO_ARCH}/setup.sh

    ROOTINSTDIR=`ls ${DRCALO_LCGREL}/ROOT`
    source ${DRCALO_LCGREL}/ROOT/${ROOTINSTDIR}/${DRCALO_ARCHCONF}/ROOT-env.sh
##### qui probabilmente ci sara' da lavorare
    source /cvmfs/geant4.cern.ch/geant4/10.5.p01/x86_64-centos7-gcc8-opt-MT/CMake-setup.sh
##### forse anche qui 
    HEPMCINSTDIR=`ls ${DRCALO_LCGREL}/hepmc3`
    export HEPMC_DIR=${DRCALO_LCGREL}/hepmc3/${HEPMCINSTDIR}/${DRCALO_ARCHCONF}
    echo HEPMC_DIR=${HEPMC_DIR}
    FASTJETINSTDIR=`ls ${DRCALO_LCGREL}/fastjet`
    export FASTJET_DIR=${DRCALO_LCGREL}/fastjet/3.3.2/${DRCALO_ARCHCONF}
    echo FASTJET_DIR=${FASTJET_DIR}
    export PYTHIA_DIR=/cvmfs/sft.cern.ch/lcg/releases/LCG_96b/MCGenerators/pythia8/${DRCALO_PYTHIAVER}/${DRCALO_ARCHCONF}/
    echo PYTHIA_DIR=${PYTHIA_DIR}
    export PYTHIA8=${DRCALO_LCGREL}/MCGenerators/pythia8/${DRCALO_PYTHIAVER}/${DRCALO_ARCHCONF}
    echo PYTHIA8=${PYTHIA8}
    export PYTHIA8DATA=${DRCALO_LCGREL}/MCGenerators/pythia8/${DRCALO_PYTHIAVER}/${DRCALO_ARCHCONF}/share/Pythia8/xmldoc
    echo PYTHIA8DATA=${PYTHIA8DATA}
    export ROOT_INCLUDE_PATH=${HEPMC_DIR}/include:$ROOT_INCLUDE_PATH
else
    echo 'Cannot find '${LCGDIR}'. LCG will not be available. Maybe try manual setup?'
fi

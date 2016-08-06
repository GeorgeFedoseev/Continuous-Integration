FROM ubuntu:14.04

### apt-get installs

RUN apt-get update
RUN sudo apt-get install cmake cmake-data g++ gcc gfortran \
  build-essential make patch sed libx11-dev libxft-dev \
  libxext-dev libxpm-dev libxmu-dev libglu1-mesa-dev \
  libgl1-mesa-dev ncurses-dev curl bzip2 gzip unzip tar \
  subversion git xutils-dev flex bison lsb-release \
  python-dev libxml2-dev wget libssl-dev \
  libcurl4-openssl-dev automake autoconf libtool -y

### install fairsoft

# clone from Fairsoft Repo
RUN cd /opt; \
  git clone https://github.com/FairRootGroup/FairSoft.git fairsoft; \
  cd fairsoft; \
  git checkout mar15p6; \
  
# create install config file
  sudo rm -rf fs_inst_settings; \        
  echo "compiler=gcc" >> fs_inst_settings; \
  echo "debug=no" >> fs_inst_settings; \
  echo "optimize=yes" >> fs_inst_settings; \
  echo "geant4_download_install_data_automatic=yes" >> fs_inst_settings; \
  echo "geant4_install_data_from_dir=no" >> fs_inst_settings; \
  echo "build_python=yes" >> fs_inst_settings; \
  echo "install_sim=yes" >> fs_inst_settings; \
  echo "SIMPATH_INSTALL=$(pwd)/install" >> fs_inst_settings; \
  echo "platform=linux" >> fs_inst_settings; \

# install FairSoft
  ./configure.sh fs_inst_settings;

# test
ADD * /repo/

RUN cd repo/mpdroot; ls; whoami; \
  mkdir build; \
  . SetEnv.sh; \
  cd build; \
  cmake ..; \
  make -j8 # user 8 cpu cores; \
  . config.sh; \
  root -b ../macro/mpd/runMC.C; 

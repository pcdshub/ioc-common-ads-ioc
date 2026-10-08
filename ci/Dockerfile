# Dockerfile
#
# CI/development image for twincat-ads driver testing.
# Based on Rocky Linux 9 to match the production IOC environment.
#
# Builds all production dependencies (same as the production Dockerfile)
# plus adds test tools: gtest, cppcheck, clang-format, pyads.
#
# This allows the image to both run an IOC and execute unit tests.
#
# Production deps:
#   - EPICS Base  slac-epics/epics-base @ R7.0.3.1-2.0
#   - asyn        slac-epics/asyn       @ R4.42-1.0.0
#   - calc        slac-epics/calc       @ R3.7-1.0.1
#   - seq         slac-epics/seq        @ R2.2.4-1.2
#   - sscan       slac-epics/sscan      @ R2.10.2-1.1.0
#   - autosave    slac-epics/autosave   @ R5.8-2.1.0
#   - caPutLog    slac-epics/caPutLog   @ R3.7-1.0.0
#   - iocAdmin    slac-epics/iocAdmin   @ R3.1.15-1.10.0
#   - motor       slac-epics/motor      @ R6.9-ess-0.0.4
#   - ethercatmc  slac-epics/ethercatmc @ R2.1.0-0.1.5
#   - twincat-ads slac-epics/twincat-ads @ R2.0.0-1.0.0
#
# Test tools:
#   - gtest       epics-modules/gtest   @ v1.0.1
#   - cppcheck    (via dnf)
#   - clang-format (via dnf)
#   - Python 3 + pyads

FROM rockylinux:9

LABEL maintainer="YS Mandza <ysmandza@slac.stanford.edu>"

USER root

# System dependencies 
RUN dnf update -y && \
    dnf install -y epel-release && \
    dnf groupinstall -y 'Development Tools' && \
    dnf install -y \
        git \
        wget \
        perl \
        pcre-devel \
        readline-devel \
        ncurses-devel \
        openssl-devel \
        zlib-devel \
        re2c \
        rpcgen \
        cppcheck \
        clang-tools-extra \
        python3 \
        python3-pip && \
    dnf clean all

# Python dependencies 
RUN pip3 install pyads pre-commit

# Module versions
# Modules that ads-ioc pins in its configure/RELEASE are declared as ARG and
# overridden at build time: .github/workflows/docker.yml parses configure/RELEASE
# and passes each *_MODULE_VERSION as a --build-arg, so the image always matches
# the environment ads-ioc is released against (single source of truth, no drift).
# The defaults below mirror configure/RELEASE and keep a plain `docker build`
# (no build-args) working.
ARG ASYN_MODULE_VERSION=R4.42-1.0.0
ARG AUTOSAVE_MODULE_VERSION=R5.11-2.0.0
ARG CAPUTLOG_MODULE_VERSION=R4.0-1.0.0
ARG ETHERCATMC_MODULE_VERSION=R2.1.0-0.1.5
ARG IOCADMIN_MODULE_VERSION=R3.1.16-1.4.0
ARG MOTOR_MODULE_VERSION=R6.9-ess-0.0.4
ARG ADS_MODULE_VERSION=R2.0.0-1.1.1
ARG STREAMDEVICE_MODULE_VERSION=R2.8.9-1.3.2
ENV ASYN_MODULE_VERSION=${ASYN_MODULE_VERSION} \
    AUTOSAVE_MODULE_VERSION=${AUTOSAVE_MODULE_VERSION} \
    CAPUTLOG_MODULE_VERSION=${CAPUTLOG_MODULE_VERSION} \
    ETHERCATMC_MODULE_VERSION=${ETHERCATMC_MODULE_VERSION} \
    IOCADMIN_MODULE_VERSION=${IOCADMIN_MODULE_VERSION} \
    MOTOR_MODULE_VERSION=${MOTOR_MODULE_VERSION} \
    ADS_MODULE_VERSION=${ADS_MODULE_VERSION} \
    STREAMDEVICE_MODULE_VERSION=${STREAMDEVICE_MODULE_VERSION}

# EPICS base version comes from the IOC's RELEASE_SITE: docker.yml parses
# BASE_MODULE_VERSION from RELEASE_SITE and passes it as a --build-arg (the
# default below mirrors RELEASE_SITE). BASE_MODULE_TAG is the matching git
# branch to clone base from and is not in RELEASE_SITE, so it stays here.
ARG BASE_MODULE_VERSION=R7.0.3.1-2.0
ENV BASE_MODULE_VERSION=${BASE_MODULE_VERSION}

# Versions NOT pinned by ads-ioc (transitive build deps + the test-only gtest)
# — this Dockerfile is their source.
ENV BASE_MODULE_TAG=R7.0.3.1-2.branch
ENV CALC_MODULE_VERSION=R3.7-1.0.1
ENV SEQ_MODULE_VERSION=R2.2.4-1.2
ENV SSCAN_MODULE_VERSION=R2.10.2-1.1.0
ENV GTEST_MODULE_VERSION=v1.0.1

# Git remotes
ENV GIT_MODULE_TOP=https://github.com/slac-epics
ENV GIT_BASE_TOP=${GIT_MODULE_TOP}
ENV GIT_IOC_TOP=https://github.com/pcdshub

ENV EPICS_SITE_TOP=/cds/group/pcds/epics
# Provided here as an ENV (the root RELEASE_SITE we copy in below does not set
# it, unlike the old deps/RELEASE_SITE) so module builds that reference it resolve.
ENV PSPKG_ROOT=/cds/group/pcds/pkg_mgr
ENV BASE_MODULE_PATH=/cds/group/pcds/epics/base/${BASE_MODULE_VERSION}
ENV ASYN_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/asyn/${ASYN_MODULE_VERSION}
ENV AUTOSAVE_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/autosave/${AUTOSAVE_MODULE_VERSION}
ENV CAPUTLOG_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/caPutLog/${CAPUTLOG_MODULE_VERSION}
ENV CALC_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/calc/${CALC_MODULE_VERSION}
ENV ETHERCATMC_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/ethercatmc/${ETHERCATMC_MODULE_VERSION}
ENV IOCADMIN_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/iocAdmin/${IOCADMIN_MODULE_VERSION}
ENV MOTOR_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/motor/${MOTOR_MODULE_VERSION}
ENV SSCAN_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/sscan/${SSCAN_MODULE_VERSION}
ENV SEQ_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/seq/${SEQ_MODULE_VERSION}
ENV GTEST_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/gtest/${GTEST_MODULE_VERSION}
ENV ADS_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/twincat-ads/${ADS_MODULE_VERSION}
ENV STREAMDEVICE_MODULE_PATH=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules/streamdevice/${STREAMDEVICE_MODULE_VERSION}
ENV BECKHOFF_ADS_PATH=/afs/slac.stanford.edu/g/cd/swe/git/repos/package/epics/modules/ADS.git
ENV IOC_PATH=/cds/group/pcds/epics/ioc/
ENV IOC_COMMON_PATH=${IOC_PATH}/common/
ENV EPICS_MODULES=/cds/group/pcds/epics/${BASE_MODULE_VERSION}/modules

# EPICS environment
ENV EPICS_BASE=${BASE_MODULE_PATH}
ENV ASYN=${ASYN_MODULE_PATH}
ENV GTEST=${GTEST_MODULE_PATH}
ENV EPICS_HOST_ARCH=rhel9-x86_64
ENV EPICS_SETUP=/cds/group/pcds/setup
ENV EPICS_CA_REPEATER_PORT=5065
ENV EPICS_PVA_SERVER_PORT=5075
ENV EPICS_PVA_AUTO_ADDR_LIST=YES
ENV EPICS_CA_AUTO_ADDR_LIST=YES
ENV EPICS_PVA_BROADCAST_PORT=5076
ENV EPICS_CA_BEACON_PERIOD=15.0
ENV EPICS_CA_CONN_TMO=30.0
ENV EPICS_CA_MAX_SEARCH_PERIOD=300
ENV EPICS_CA_MAX_ARRAY_BYTES=40000000
ENV EPICS_CA_SERVER_PORT=5064

# Path back-compat (mirrors production)
RUN mkdir -p /reg/g && ln -sf /cds/group/pcds /reg/g/pcds

WORKDIR ${EPICS_SITE_TOP}

# RELEASE_SITE — use the IOC's own root RELEASE_SITE so the image's module
# environment mirrors exactly what ads-ioc is built against (single source).
COPY RELEASE_SITE ${EPICS_MODULES}/RELEASE_SITE
COPY deps/RELEASE_SITE.check ${EPICS_MODULES}/RELEASE_SITE.check

# EPICS Base
RUN git clone --depth 1 \
        --branch ${BASE_MODULE_TAG} \
        ${GIT_BASE_TOP}/epics-base.git \
        ${BASE_MODULE_PATH} && \
    echo "USR_CXXFLAGS_Linux += -std=c++14" >> \
        ${BASE_MODULE_PATH}/configure/CONFIG_SITE && \
    make -C ${BASE_MODULE_PATH} CROSS_COMPILER_TARGET_ARCHS= -j$(nproc) && \
    make -C ${BASE_MODULE_PATH} clean

# Core modules
# libtirpc (required for asyn VXI11)
RUN cd /tmp && \
    wget https://downloads.sourceforge.net/libtirpc/libtirpc-1.3.7.tar.bz2 && \
    tar -xvf libtirpc-1.3.7.tar.bz2 && \
    cd libtirpc-1.3.7 && \
    ./configure --prefix=/usr --disable-gssapi && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    rm -rf /tmp/libtirpc*

RUN git clone --depth 1 --branch ${ASYN_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/asyn.git ${ASYN_MODULE_PATH} && \
    make -C ${ASYN_MODULE_PATH} -j$(nproc) && \
    make -C ${ASYN_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${CALC_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/calc.git ${CALC_MODULE_PATH} && \
    make -C ${CALC_MODULE_PATH} -j$(nproc) && \
    make -C ${CALC_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${IOCADMIN_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/iocAdmin.git ${IOCADMIN_MODULE_PATH} && \
    make -C ${IOCADMIN_MODULE_PATH} -j$(nproc) && \
    make -C ${IOCADMIN_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${AUTOSAVE_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/autosave.git ${AUTOSAVE_MODULE_PATH} && \
    make -C ${AUTOSAVE_MODULE_PATH} -j$(nproc) && \
    make -C ${AUTOSAVE_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${MOTOR_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/motor.git ${MOTOR_MODULE_PATH} && \
    make -C ${MOTOR_MODULE_PATH} -j$(nproc) && \
    make -C ${MOTOR_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${SEQ_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/seq.git ${SEQ_MODULE_PATH} && \
    make -C ${SEQ_MODULE_PATH} RE2C="$(command -v re2c)" -j1 && \
    make -C ${SEQ_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${SSCAN_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/sscan.git ${SSCAN_MODULE_PATH} && \
    echo "USR_INCLUDES += -I/usr/include/tirpc" >> \
        ${SSCAN_MODULE_PATH}/configure/CONFIG_SITE && \
    make -C ${SSCAN_MODULE_PATH} -j$(nproc) && \
    make -C ${SSCAN_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${STREAMDEVICE_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/streamdevice.git ${STREAMDEVICE_MODULE_PATH} && \
    make -C ${STREAMDEVICE_MODULE_PATH} -j$(nproc) && \
    make -C ${STREAMDEVICE_MODULE_PATH} clean

RUN git clone --depth 1 --branch ${CAPUTLOG_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/caPutLog.git ${CAPUTLOG_MODULE_PATH} && \
    make -C ${CAPUTLOG_MODULE_PATH} -j$(nproc) && \
    make -C ${CAPUTLOG_MODULE_PATH} clean

# EtherCAT MC
RUN git clone --depth 1 --branch ${ETHERCATMC_MODULE_VERSION} \
        ${GIT_IOC_TOP}/ethercatmc.git ${ETHERCATMC_MODULE_PATH} && \
    make -C ${ETHERCATMC_MODULE_PATH} -j1 && \
    make -C ${ETHERCATMC_MODULE_PATH} clean

# ADS (twincat-ads)
RUN git clone --depth 1 \
        ${GIT_MODULE_TOP}/ADS.git ${BECKHOFF_ADS_PATH}/ && \
    git clone --recursive --depth 1 \
        --branch ${ADS_MODULE_VERSION} \
        ${GIT_IOC_TOP}/twincat-ads.git ${ADS_MODULE_PATH} && \
    make -C ${ADS_MODULE_PATH} -j1 && \
    make -C ${ADS_MODULE_PATH} clean

# ADS IOC
ENV ADS_IOC_VERSION=R2.0.0
ENV ADS_IOC_ROOT=${IOC_COMMON_PATH}/ads-ioc
ENV ADS_IOC_PATH=${ADS_IOC_ROOT}/${ADS_IOC_VERSION}

# Build this repo's own source (the image is built from it) so the IOC builds
# against the twincat-ads version installed above. The previous step cloned a
# fixed upstream ads-ioc tag, which pinned a different ADS version (1.0.0 vs the
# 1.1.1 this repo installs) and failed the configure/RELEASE check.
COPY . ${ADS_IOC_PATH}
RUN make -C ${ADS_IOC_PATH} && \
    make -C ${ADS_IOC_PATH} clean
    
# gtest — for unit testing
RUN git clone --depth 1 \
        --recurse-submodules \
        --branch ${GTEST_MODULE_VERSION} \
        ${GIT_MODULE_TOP}/gtest.git \
        ${GTEST_MODULE_PATH} && \
    echo "EPICS_BASE=${EPICS_BASE}" > \
        ${GTEST_MODULE_PATH}/configure/RELEASE.local && \
    echo "USR_CXXFLAGS_Linux += -std=c++14" >> \
        ${GTEST_MODULE_PATH}/configure/CONFIG_SITE && \
    make -C ${GTEST_MODULE_PATH} -j$(nproc) && \
    make -C ${GTEST_MODULE_PATH} clean

# PATH
ENV PATH="${BASE_MODULE_PATH}/bin/${EPICS_HOST_ARCH}:${PATH}"

WORKDIR /workspace


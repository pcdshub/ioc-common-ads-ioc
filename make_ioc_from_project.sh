#!/bin/bash

PROJECT_PATH=$1

if [ -z "$(which tcparse-stcmd)" ]; then
    echo "Unable to find tcparse-stcmd in your current environment." > /dev/stderr
    exit 1
fi

if [ -z "$PROJECT_PATH" ]; then
    echo "Usage: $0 {path/to/project_name.tsproj} [ioc_name]" > /dev/stderr
    echo "ioc_name defaults to ioc-{project_name}." > /dev/stderr
    exit 1
fi

if [ ! -f "$PROJECT_PATH" ]; then
    echo "$PROJECT_PATH does not exist." > /dev/stderr
    exit 1
fi

PROJECT_BASENAME=$(basename -- "$PROJECT_PATH")
PROJECT_EXTENSION="${PROJECT_BASENAME##*.}"
PROJECT_FILENAME="${PROJECT_BASENAME%.*}"

IOC_NAME=$2

if [ -z "$IOC_NAME" ]; then
    IOC_NAME="ioc-${PROJECT_FILENAME}"
fi

IOC_PATH="iocBoot/$IOC_NAME"

echo "IOC name: $IOC_NAME"
echo "IOC path: $IOC_PATH"

if [ ! -d "$IOC_PATH" ]; then
    echo "IOC directory does not exist; running makeBaseApp..."
    mkdir -p $IOC_PATH
    cat > $IOC_PATH/Makefile <<'EOF'
TOP = ../..
include $(TOP)/configure/CONFIG
ARCH = $(EPICS_HOST_ARCH)
TARGETS = envPaths
include $(TOP)/configure/RULES.ioc
EOF

fi

pushd $IOC_PATH
echo "Generating the st.cmd:"
tcparse-stcmd -b adsMotion "$PROJECT_PATH" > st.cmd
popd

#!/bin/bash
# Usage: add_route.sh [plc-hostname] [ip-regex]

if [ $# -ne 2 ]; then
    echo "Usage: $0 [plc hostname] [ip regex]" > /dev/stderr
    exit 1
fi

CONDA_BIN=${CONDA_BIN=/cds/group/pcds/pyps/conda/py39/envs/pcds-5.4.1/bin/conda}

if [ ! -f "$CONDA_BIN" ]; then
    echo "Conda unavailable. Skipping route addition." > /dev/stderr
    exit 1
fi

set -e

add_route() {
    local plc_host
    local ioc_hostname
    local ioc_host_ip

    plc_host=$1
    ioc_hostname=$2
    ioc_host_ip=$3
    ioc_host_net_id="${ioc_host_ip}.1.1"

    if [ -z "$plc_host" ]; then
        echo "PLC hostname unspecified" > /dev/stderr
        exit 1
    fi

    if [ -z "$ioc_host_ip" ]; then
        echo "IOC IP address unspecified" > /dev/stderr
        exit 1
    fi

    if [ -z "$ioc_hostname" ]; then
        echo "IOC hostname unspecified" > /dev/stderr
        exit 1
    fi

    echo "Running ads-async to add a route to ${ioc_hostname} for IOC host ${ioc_hostname} (${ioc_host_ip})..."
    set -x
    $CONDA_BIN run ads-async route \
        --route-name="${ioc_hostname}" \
        "${plc_host}" \
        "${ioc_host_net_id}" \
        "${ioc_host_ip}"
    { set +x; } 2> /dev/null
    echo "Done."
}

find_ioc_ip() {
    local ipaddr
    local regex
    regex=$1

    if [ -z "$regex" ]; then
        echo "IOC IP match regex unspecified" > /dev/stderr
        exit 1
    fi

    for ipaddr in $(dig +short "$(hostname)"); do
        if [[ "$ipaddr" =~ ${regex} ]]; then
            echo "$ipaddr"
            return
        fi
    done
}


plc_host=$1
host_ip_regex=$2
ioc_hostname=$(hostname -s)
ioc_ip=$(find_ioc_ip "${host_ip_regex}")

add_route "${plc_host}" "${ioc_hostname}" "${ioc_ip}"

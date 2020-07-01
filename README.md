ADS IOC
=======

`ads-ioc` is an IOC template for Beckhoff TwinCAT ADS-based deployments in the
LCLS PCDS group at SLAC.

That fork contains support for communicating with specifically structured
TwinCAT projects using the ADS protocol.

This is set up to build on the LCLS PCDS NFS-accessible machines. This will not
build on older operating systems such as rhel5 and rhel6. It does not need any
specific environment variable set, just type `make`. You can probably get it to
build in other environments by modifying the `RELEASE_SITE` file appropriately.


Dependencies
============

* [asyn](https://github.com/epics-modules/asyn)
* ads (ESS [m-epics-twincat-ads](https://bitbucket.org/europeanspallationsource/m-epics-twincat-ads))
* EthercatMcSupport (ESS [m-epics-ethercatmc](https://bitbucket.org/europeanspallationsource/m-epics-ethercatmc))
* EPICS motor record (ESS fork [ess-R6.9.x](https://bitbucket.org/europeanspallationsource/m-epics-motor/src/ess-6.9.x/))
* [iocAdmin + devIocStats](https://github.com/epics-modules/iocStats)
* [autosave](https://github.com/epics-modules/autosave)
* [calc](https://github.com/epics-modules/calc)

Logging
=======

Logging configuration is handled externally by way of the shared
`pre_linux.cmd` (i.e., pre-iocInit) script:

```
# Send log messages to logstash:
epicsEnvSet("EPICS_IOC_LOG_INET", "ctl-logsrv01.pcdsn")
epicsEnvSet("EPICS_IOC_LOG_PORT", "7004")

# The following prefix is *required* for logstash to know which IOC is sending
# the message.  This *cannot* be modified without changes to the logstash
# configuration.
iocLogPrefix("IOC=${IOC} ")

# Send caPutLog messages to logstash:
epicsEnvSet("EPICS_CAPUTLOG_HOST", "ctl-logsrv01.pcdsn")
epicsEnvSet("EPICS_CAPUTLOG_PORT", "7011")
```

For now, post-init settings are handled on a per-IOC basis. However, a similar
change may be used in the future for a post-`iocInit()` script which would
enable logging outside of `ads-ioc`:

```
# Enable logging
iocLogInit()

# Configure and start the caPutLogger after iocInit
epicsEnvSet(EPICS_AS_PUT_LOG_PV, "${IOC}:caPutLog:Last")

# caPutLogInit("HOST:PORT", config)
# config options:
#       caPutLogNone       -1: no logging (disable)
#       caPutLogOnChange    0: log only on value change
#       caPutLogAll         1: log all puts
#       caPutLogAllNoFilter 2: log all puts no filtering on same PV
caPutLogInit("${EPICS_CAPUTLOG_HOST}:${EPICS_CAPUTLOG_PORT}", 0)
```

Related tools
=============

* [pytmc](https://github.com/slaclab/pytmc)
* [ads-deploy](https://github.com/slaclab/ads-deploy)

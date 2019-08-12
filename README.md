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

Related tools
=============

* [pytmc](https://github.com/slaclab/pytmc)

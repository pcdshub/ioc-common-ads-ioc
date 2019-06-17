ADS Motion
==========

`ads-motion` is an IOC template for Beckhoff Motion deployments in the LCLS
PCDS group at SLAC. It relies on the fork of the motor module from ESS. That
fork contains support for communicating with specifically structured TwinCAT
projects using the ADS protocol.

Things defined here:
- Templated st.cmd, autosave, and archive files
- Per-axis support records, such as some convenience screen PVs
- IOCAdmin module tools

This is set up to build on the LCLS PCDS NFS-accessible machines. This will not
build on older operating systems such as rhel5 and rhel6. It does not need any
specific environment variable set, just type make. You can probably get it to
build in other environments by modifying the `RELEASE_SITE` file appropriately.

This repository also contains tools to help set up and manage these TwinCAT
projects. These are located in the `tools` directory and include the following
scripts:
- Placeholder for when I add these

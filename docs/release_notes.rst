=================
 Release History
=================

R0.4.0 (2020-12-03)
===================

- Fix for callback queue-related errors at IOC boot
- Add limits and resolution to autosave
- Archive limits
- New minimum pytmc version: 2.7.7
- Add PYTMC_DB_OPTS variable

R0.3.1 (2020-09-18)
===================
- Fix invalid fields from the appinfo database  (`#63 <https://github.com/pcdshub/ads-ioc/pull/63>`__)


R0.3.0 (2020-09-18)
===================

- Add caPutLog and error logging support (`#37 <https://github.com/pcdshub/ads-ioc/issues/37>`__)
- Add task information database (`#60 <https://github.com/pcdshub/ads-ioc/pull/60>`__)
- Add appinfo database (`#62 <https://github.com/pcdshub/ads-ioc/pull/62>`__)
- Fix some macro-related issues.


R0.2.5 (2020-06-17)
===================

-  Fixes .VELO field being locked to maximum velocity on boot, ignoring
   autosave (`#52 <https://github.com/pcdshub/ads-ioc/issues/52>`__)


R0.2.4 (2020-06-09)
===================

-  Add support for ``info node`` archive field tagging
   (`#33 <https://github.com/pcdshub/ads-ioc/issues/33>`__)
-  Add archiving support for motor records, which are now vendored
   (`#30 <https://github.com/pcdshub/ads-ioc/issues/30>`__)
-  Adjusted default ``PREFIX`` to be less likely to clash
-  Add DB_PARAMETERS to ``Makefile`` to make it more obvious
   (`#42 <https://github.com/pcdshub/ads-ioc/issues/42>`__)
-  Fix building master due to db file mishap, auto-create paths with
   default make target
   (`#50 <https://github.com/pcdshub/ads-ioc/issues/50>`__)
-  Added linter targets
   (`#43 <https://github.com/pcdshub/ads-ioc/issues/43>`__)


R0.2.2 (2020-03-03)
===================

-  Fix spaces in project filenames
-  Verify pytmc version prior to running commands


R0.2.1 (2020-02-27)
===================

-  Fixes the archive path


R0.2.0 (2020-02-26)
===================

-  Fix autosave configuration in general
-  Separate Makefile steps to make db/st.cmd generation more flexible
-  Generate archive files automatically with the latest pytmc
-  Add PRODUCTION_IOC flag to allow for easier testing
-  Fix IOC_DATA environment variable
-  Fix EGU field for motor record
-  Allow customization of database macros in Makefile with
   ``DB_PARAMETERS``
-  Increase ADS_MAX_PARAMETERS as a stop-gap solution (a pytmc TODO)


v0.1.7 (2020-01-23)
===================

- Fix issue with ``POINTER TO DUT_MotionStage`` being interpreted incorrectly
  for the st.cmd file. Requires ``pytmc > 2.5.0``


v0.1.5 (2019-10-29)
===================

-  NC axis count fix
-  Makefile fixes - no pragmas required for building
-  Cleanups


v0.1.0 (2019-09-18)
===================

-  Uses DUT_MotionStage instead of ST_MotionStage


v0.0.2 (2019-08-16)
===================

Initial release.

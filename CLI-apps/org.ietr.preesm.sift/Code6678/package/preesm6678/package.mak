#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = preesm6678
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
C:/ti/xdctools_3_25_00_48/packages/xdc/utils.js:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/utils.js
C:/ti/xdctools_3_25_00_48/packages/xdc/xdc.tci:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/xdc.tci
C:/ti/xdctools_3_25_00_48/packages/xdc/template.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/template.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/om2.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/om2.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/xmlgen.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/xmlgen.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/xmlgen2.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/xmlgen2.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/Warnings.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/Warnings.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/IPackage.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/IPackage.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/package.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/package.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/services/global/Clock.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/services/global/Clock.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/services/global/Trace.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/services/global/Trace.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/bld.js:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/bld.js
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/BuildEnvironment.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/BuildEnvironment.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/PackageContents.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/PackageContents.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/_gen.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/_gen.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Library.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Library.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Executable.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Executable.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Repository.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Repository.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Configuration.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Configuration.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Script.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Script.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Manifest.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Manifest.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Utils.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/Utils.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITarget.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITarget.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITarget2.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITarget2.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITarget3.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITarget3.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITargetFilter.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/ITargetFilter.xs
C:/ti/xdctools_3_25_00_48/packages/xdc/bld/package.xs:
package.mak: C:/ti/xdctools_3_25_00_48/packages/xdc/bld/package.xs
package.mak: config.bld
package.mak: package.bld
endif


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_preesm6678.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package preesm6678" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

ifeq (,$(MK_NOGENDEPS))
-include package/package.cfg.dep
endif

package/rel/undefinedpreesm6678package/package.rel.xml: package/package.cfg.xdc.inc
package/package.cfg.xdc.inc: $(XDCROOT)/packages/xdc/cfg/cfginc.js package.xdc
	@$(MSG) generating schema include file list ...
	$(CONFIG) -f $(XDCROOT)/packages/xdc/cfg/cfginc.js preesm6678 $@

test:;
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg .interfaces $(XDCROOT)/packages/xdc/cfg/Main.xs
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,preesm6678
preesm6678.zip: package/package.bld.xml
preesm6678.zip: package/build.cfg
preesm6678.zip: package/package.xdc.inc
preesm6678.zip: package/package.cfg.xdc.inc
ifeq (,$(MK_NOGENDEPS))
-include package/rel/preesm6678.zip.dep
endif
package/rel/preesm6678/preesm6678/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

preesm6678.zip: package/rel/preesm6678.xdc.inc package/rel/preesm6678/preesm6678/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELZIP,package/rel/preesm6678.xdc.inc,package/rel/preesm6678.zip.dep)


release release,preesm6678: all preesm6678.zip
clean:: .clean
	-$(RM) preesm6678.zip
	-$(RM) package/rel/preesm6678.xdc.inc
	-$(RM) package/rel/preesm6678.zip.dep

clean:: .clean
	-$(RM) .libraries .libraries,*
clean:: 
	-$(RM) .dlls .dlls,*
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package



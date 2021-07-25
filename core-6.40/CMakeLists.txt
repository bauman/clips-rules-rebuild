# This follows along creating the objects identified in 
# the makefiles included in the core-6.40 release


set( SOURCE_AGENDA
     agenda.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h crstrtgy.h agenda.h ruledef.h network.h match.h 
  conscomp.h extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h 
  engine.h lgcldpnd.h retract.h memalloc.h modulutl.h scanner.h 
  multifld.h prntutil.h reteutil.h router.h rulebsc.h strngrtr.h 
  sysdep.h watch.h

)
set( SOURCE_ANALYSIS
     analysis.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h cstrnchk.h constrnt.h evaluatn.h cstrnutl.h cstrnops.h 
  exprnpsr.h extnfunc.h expressn.h exprnops.h constrct.h userdata.h 
  moduldef.h utility.h symbol.h scanner.h generate.h analysis.h 
  reorder.h pattern.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h symblcmp.h cstrccom.h memalloc.h modulutl.h prntutil.h 
  router.h rulecstr.h rulepsr.h watch.h

)
set( SOURCE_ARGACCES
     argacces.c setup.h envrnmnt.h entities.h usrsetup.h 
  cstrnchk.h constrnt.h evaluatn.h constant.h extnfunc.h expressn.h 
  exprnops.h constrct.h userdata.h moduldef.h utility.h symbol.h 
  factmngr.h conscomp.h symblcmp.h tmpltdef.h factbld.h network.h 
  match.h ruledef.h agenda.h crstrtgy.h cstrccom.h facthsh.h insfun.h 
  object.h multifld.h objrtmch.h prntutil.h router.h sysdep.h argacces.h

)
set( SOURCE_BLOAD
     bload.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h bsave.h cstrnbin.h constrnt.h exprnpsr.h 
  extnfunc.h symbol.h scanner.h memalloc.h prntutil.h router.h bload.h 
  exprnbin.h sysdep.h symblbin.h

)
set( SOURCE_BMATHFUN
     bmathfun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h exprnpsr.h extnfunc.h symbol.h 
  scanner.h prntutil.h router.h bmathfun.h

)
set( SOURCE_BSAVE
     bsave.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h sysdep.h 
  symblbin.h cstrnbin.h constrnt.h exprnpsr.h scanner.h memalloc.h 
  prntutil.h router.h bsave.h

)
set( SOURCE_CLASSCOM
     classcom.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h argacces.h classfun.h object.h constrnt.h multifld.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  cstrccom.h objrtmch.h scanner.h classcom.h classini.h modulutl.h 
  msgcom.h msgpass.h prntutil.h router.h

)
set( SOURCE_CLASSEXM
     classexm.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h classcom.h cstrccom.h object.h 
  constrnt.h multifld.h symbol.h match.h network.h ruledef.h agenda.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h 
  scanner.h classini.h insfun.h memalloc.h msgcom.h msgpass.h msgfun.h 
  prntutil.h router.h strngrtr.h sysdep.h classexm.h

)
set( SOURCE_CLASSFUN
     classfun.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h classcom.h cstrccom.h object.h constrnt.h multifld.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  objrtmch.h classini.h cstrcpsr.h strngfun.h inscom.h insfun.h 
  insmngr.h memalloc.h modulutl.h scanner.h msgfun.h msgpass.h 
  prntutil.h router.h classfun.h

)
set( SOURCE_CLASSINF
     classinf.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h classcom.h cstrccom.h object.h 
  constrnt.h multifld.h symbol.h match.h network.h ruledef.h agenda.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classexm.h 
  classfun.h scanner.h classini.h memalloc.h insfun.h msgcom.h msgpass.h 
  msgfun.h prntutil.h classinf.h

)
set( SOURCE_CLASSINI
     classini.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classexm.h classfun.h 
  scanner.h classinf.h classpsr.h cstrcpsr.h strngfun.h inscom.h 
  insfun.h memalloc.h modulpsr.h modulutl.h msgcom.h msgpass.h watch.h 
  defins.h insquery.h bload.h exprnbin.h sysdep.h symblbin.h objbin.h 
  objcmp.h objrtbld.h objrtfnx.h classini.h

)
set( SOURCE_CLASSPSR
     classpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h classcom.h cstrccom.h object.h constrnt.h multifld.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  objrtmch.h classfun.h scanner.h clsltpsr.h cstrcpsr.h strngfun.h 
  inherpsr.h memalloc.h modulpsr.h modulutl.h msgpsr.h pprint.h 
  prntutil.h router.h classpsr.h

)
set( SOURCE_CLSLTPSR
     clsltpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  cstrnchk.h cstrnpsr.h cstrnutl.h default.h insfun.h memalloc.h 
  pprint.h prntutil.h router.h clsltpsr.h

)
set( SOURCE_COMMLINE
     commline.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h argacces.h expressn.h exprnops.h constrct.h userdata.h 
  moduldef.h utility.h evaluatn.h cstrcpsr.h strngfun.h exprnpsr.h 
  extnfunc.h symbol.h scanner.h fileutil.h memalloc.h multifld.h 
  pprint.h prcdrfun.h prcdrpsr.h constrnt.h prntutil.h router.h 
  strngrtr.h sysdep.h commline.h

)
set( SOURCE_CONSCOMP
     conscomp.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrccom.h cstrncmp.h constrnt.h 
  exprnpsr.h extnfunc.h symbol.h scanner.h memalloc.h modulcmp.h 
  prntutil.h router.h sysdep.h network.h match.h ruledef.h agenda.h 
  crstrtgy.h conscomp.h symblcmp.h dffnxcmp.h dffnxfun.h tmpltcmp.h 
  tmpltdef.h factbld.h globlcmp.h globldef.h genrccmp.h genrcfun.h 
  objcmp.h object.h multifld.h objrtmch.h

)
set( SOURCE_CONSTRCT
     constrct.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h commline.h cstrcpsr.h strngfun.h 
  exprnpsr.h extnfunc.h symbol.h scanner.h memalloc.h miscfun.h 
  modulutl.h multifld.h prcdrfun.h prcdrpsr.h constrnt.h prntutil.h 
  router.h ruledef.h network.h match.h agenda.h crstrtgy.h conscomp.h 
  symblcmp.h cstrccom.h sysdep.h watch.h

)
set( SOURCE_CONSTRNT
     constrnt.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h extnfunc.h symbol.h memalloc.h 
  multifld.h router.h scanner.h constrnt.h

)
set( SOURCE_CRSTRTGY
     crstrtgy.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  argacces.h memalloc.h pattern.h scanner.h reorder.h reteutil.h

)
set( SOURCE_CSTRCBIN
     cstrcbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h cstrcbin.h

)
set( SOURCE_CSTRCCOM
     cstrccom.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h extnfunc.h evaluatn.h expressn.h exprnops.h constrct.h 
  userdata.h moduldef.h utility.h symbol.h memalloc.h argacces.h 
  multifld.h modulutl.h scanner.h prntutil.h router.h commline.h 
  sysdep.h bload.h exprnbin.h symblbin.h cstrcpsr.h strngfun.h 
  cstrccom.h

)
set( SOURCE_CSTRCPSR
     cstrcpsr.c setup.h envrnmnt.h entities.h usrsetup.h router.h 
  watch.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h prcdrpsr.h constrnt.h exprnpsr.h 
  extnfunc.h symbol.h scanner.h memalloc.h modulutl.h modulpsr.h 
  pprint.h prntutil.h strngrtr.h sysdep.h cstrcpsr.h strngfun.h

)
set( SOURCE_CSTRNBIN
     cstrnbin.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h memalloc.h prntutil.h router.h bload.h utility.h evaluatn.h 
  moduldef.h userdata.h extnfunc.h expressn.h exprnops.h constrct.h 
  symbol.h exprnbin.h sysdep.h symblbin.h bsave.h cstrnbin.h constrnt.h

)
set( SOURCE_CSTRNCHK
     cstrnchk.c setup.h envrnmnt.h entities.h usrsetup.h 
  cstrnutl.h constrnt.h evaluatn.h constant.h extnfunc.h expressn.h 
  exprnops.h constrct.h userdata.h moduldef.h utility.h symbol.h 
  multifld.h prntutil.h router.h classcom.h cstrccom.h object.h match.h 
  network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  objrtmch.h classexm.h inscom.h insfun.h cstrnchk.h

)
set( SOURCE_CSTRNCMP
     cstrncmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h conscomp.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  memalloc.h prntutil.h router.h sysdep.h cstrncmp.h constrnt.h

)
set( SOURCE_CSTRNOPS
     cstrnops.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h constrnt.h evaluatn.h cstrnchk.h cstrnutl.h extnfunc.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  symbol.h memalloc.h multifld.h router.h scanner.h cstrnops.h

)
set( SOURCE_CSTRNPSR
     cstrnpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h cstrnchk.h constrnt.h evaluatn.h cstrnutl.h expressn.h 
  exprnops.h constrct.h userdata.h moduldef.h utility.h memalloc.h 
  pprint.h prntutil.h router.h scanner.h sysdep.h cstrnpsr.h

)
set( SOURCE_CSTRNUTL
     cstrnutl.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h extnfunc.h symbol.h memalloc.h 
  multifld.h router.h scanner.h cstrnutl.h constrnt.h

)
set( SOURCE_DEFAULT
     default.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  constrnt.h evaluatn.h cstrnchk.h cstrnutl.h exprnpsr.h extnfunc.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  symbol.h scanner.h factmngr.h conscomp.h symblcmp.h tmpltdef.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h 
  facthsh.h inscom.h insfun.h object.h multifld.h objrtmch.h pprint.h 
  prntutil.h router.h default.h

)
set( SOURCE_DEFINS
     defins.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h dfinsbin.h defins.h conscomp.h symblcmp.h cstrccom.h 
  object.h constrnt.h multifld.h match.h network.h ruledef.h agenda.h 
  crstrtgy.h objrtmch.h dfinscmp.h argacces.h classcom.h classfun.h 
  scanner.h cstrcpsr.h strngfun.h insfun.h inspsr.h memalloc.h 
  modulpsr.h modulutl.h pprint.h prntutil.h router.h

)
set( SOURCE_DEVELOPR
     developr.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h extnfunc.h symbol.h factmngr.h 
  conscomp.h symblcmp.h tmpltdef.h constrnt.h factbld.h network.h 
  match.h ruledef.h agenda.h crstrtgy.h cstrccom.h facthsh.h inscom.h 
  insfun.h object.h multifld.h objrtmch.h modulutl.h scanner.h 
  prntutil.h router.h classcom.h classfun.h developr.h

)
set( SOURCE_DFFCTBIN
     dffctbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h dffctdef.h conscomp.h symblcmp.h cstrccom.h 
  memalloc.h dffctbin.h cstrcbin.h modulbin.h

)
set( SOURCE_DFFCTBSC
     dffctbsc.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrccom.h cstrcpsr.h strngfun.h 
  dffctdef.h conscomp.h extnfunc.h symbol.h symblcmp.h dffctpsr.h 
  factrhs.h factmngr.h tmpltdef.h constrnt.h factbld.h network.h match.h 
  ruledef.h agenda.h crstrtgy.h facthsh.h scanner.h memalloc.h 
  multifld.h router.h dffctbin.h cstrcbin.h modulbin.h dffctcmp.h 
  dffctbsc.h

)
set( SOURCE_DFFCTCMP
     dffctcmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  dffctdef.h cstrccom.h dffctcmp.h

)
set( SOURCE_DFFCTDEF
     dffctdef.c setup.h envrnmnt.h entities.h usrsetup.h 
  dffctbsc.h dffctdef.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h conscomp.h extnfunc.h expressn.h exprnops.h 
  symbol.h symblcmp.h cstrccom.h dffctpsr.h memalloc.h bload.h 
  exprnbin.h sysdep.h symblbin.h dffctbin.h cstrcbin.h modulbin.h 
  dffctcmp.h

)
set( SOURCE_DFFCTPSR
     dffctpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h cstrcpsr.h strngfun.h dffctbsc.h dffctdef.h conscomp.h 
  symblcmp.h cstrccom.h factrhs.h factmngr.h tmpltdef.h constrnt.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h facthsh.h 
  scanner.h memalloc.h modulutl.h pprint.h prntutil.h router.h 
  dffctpsr.h

)
set( SOURCE_DFFNXBIN
     dffnxbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h cstrcbin.h cstrccom.h memalloc.h modulbin.h 
  dffnxbin.h dffnxfun.h

)
set( SOURCE_DFFNXCMP
     dffnxcmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  dffnxcmp.h dffnxfun.h

)
set( SOURCE_DFFNXEXE
     dffnxexe.c setup.h envrnmnt.h entities.h usrsetup.h 
  constrct.h userdata.h moduldef.h utility.h evaluatn.h constant.h 
  prcdrfun.h prccode.h expressn.h exprnops.h scanner.h symbol.h 
  prntutil.h proflfun.h router.h watch.h dffnxexe.h dffnxfun.h

)
set( SOURCE_DFFNXFUN
     dffnxfun.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h dffnxbin.h dffnxfun.h dffnxcmp.h cstrcpsr.h strngfun.h 
  dffnxpsr.h modulpsr.h scanner.h dffnxexe.h watch.h argacces.h 
  cstrccom.h memalloc.h modulutl.h multifld.h prntutil.h router.h

)
set( SOURCE_DFFNXPSR
     dffnxpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h network.h match.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  symblcmp.h constrnt.h cstrccom.h genrccom.h genrcfun.h cstrcpsr.h 
  strngfun.h dffnxfun.h exprnpsr.h scanner.h memalloc.h modulutl.h 
  pprint.h prccode.h prntutil.h router.h dffnxpsr.h

)
set( SOURCE_DFINSBIN
     dfinsbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h cstrcbin.h defins.h conscomp.h symblcmp.h 
  cstrccom.h object.h constrnt.h multifld.h match.h network.h ruledef.h 
  agenda.h crstrtgy.h objrtmch.h memalloc.h modulbin.h dfinsbin.h

)
set( SOURCE_DFINSCMP
     dfinscmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  defins.h cstrccom.h object.h constrnt.h multifld.h match.h network.h 
  ruledef.h agenda.h crstrtgy.h objrtmch.h dfinscmp.h

)
set( SOURCE_DRIVE
     drive.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  engine.h lgcldpnd.h retract.h incrrset.h memalloc.h prntutil.h 
  reteutil.h router.h drive.h

)
set( SOURCE_EMATHFUN
     emathfun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h extnfunc.h symbol.h miscfun.h 
  prntutil.h router.h emathfun.h

)
set( SOURCE_ENGINE
     engine.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  argacces.h commline.h factmngr.h tmpltdef.h factbld.h facthsh.h 
  inscom.h insfun.h object.h multifld.h objrtmch.h memalloc.h modulutl.h 
  scanner.h prccode.h prcdrfun.h prntutil.h proflfun.h reteutil.h 
  retract.h router.h ruledlt.h sysdep.h watch.h engine.h lgcldpnd.h

)
set( SOURCE_ENVRNBLD
     envrnbld.c setup.h envrnmnt.h entities.h usrsetup.h 
  bmathfun.h evaluatn.h constant.h commline.h emathfun.h engine.h 
  lgcldpnd.h match.h network.h ruledef.h constrct.h userdata.h 
  moduldef.h utility.h expressn.h exprnops.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  retract.h filecom.h iofun.h memalloc.h miscfun.h multifun.h parsefun.h 
  pprint.h prccode.h scanner.h prcdrfun.h prdctfun.h prntutil.h 
  proflfun.h router.h sortfun.h strngfun.h sysdep.h textpro.h watch.h 
  dffctdef.h genrccom.h genrcfun.h dffnxfun.h globldef.h tmpltdef.h 
  factbld.h classini.h object.h multifld.h objrtmch.h envrnbld.h

)
set( SOURCE_ENVRNMNT
     envrnmnt.c setup.h envrnmnt.h entities.h usrsetup.h 
  bmathfun.h evaluatn.h constant.h commline.h emathfun.h engine.h 
  lgcldpnd.h match.h network.h ruledef.h constrct.h userdata.h 
  moduldef.h utility.h expressn.h exprnops.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  retract.h filecom.h iofun.h memalloc.h miscfun.h multifun.h parsefun.h 
  prccode.h scanner.h prcdrfun.h prdctfun.h prntutil.h proflfun.h 
  router.h sortfun.h strngfun.h sysdep.h textpro.h watch.h dffctdef.h 
  genrccom.h genrcfun.h dffnxfun.h globldef.h tmpltdef.h factbld.h 
  classini.h object.h multifld.h objrtmch.h

)
set( SOURCE_EVALUATN
     evaluatn.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h commline.h factmngr.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h tmpltdef.h constrnt.h factbld.h 
  network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h facthsh.h 
  memalloc.h modulutl.h scanner.h router.h prcdrfun.h multifld.h 
  prntutil.h exprnpsr.h proflfun.h sysdep.h dffnxfun.h genrccom.h 
  genrcfun.h object.h objrtmch.h inscom.h insfun.h

)
set( SOURCE_EXPRESSN
     expressn.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h memalloc.h prntutil.h router.h

)
set( SOURCE_EXPRNBIN
     exprnbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h dffctdef.h conscomp.h symblcmp.h cstrccom.h 
  memalloc.h network.h match.h ruledef.h agenda.h crstrtgy.h constrnt.h 
  genrcbin.h genrcfun.h dffnxbin.h dffnxfun.h factmngr.h tmpltdef.h 
  factbld.h facthsh.h tmpltbin.h cstrcbin.h modulbin.h globlbin.h 
  globldef.h objbin.h object.h multifld.h objrtmch.h insfun.h inscom.h

)
set( SOURCE_EXPRNOPS
     exprnops.c setup.h envrnmnt.h entities.h usrsetup.h 
  cstrnchk.h constrnt.h evaluatn.h constant.h cstrnops.h cstrnutl.h 
  extnfunc.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h symbol.h memalloc.h prntutil.h router.h

)
set( SOURCE_EXPRNPSR
     exprnpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrnchk.h constrnt.h memalloc.h 
  modulutl.h symbol.h scanner.h pprint.h prcdrfun.h prntutil.h router.h 
  strngrtr.h network.h match.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  extnfunc.h symblcmp.h cstrccom.h genrccom.h genrcfun.h dffnxfun.h 
  exprnpsr.h

)
set( SOURCE_EXTNFUNC
     extnfunc.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h exprnpsr.h extnfunc.h symbol.h 
  scanner.h factmngr.h conscomp.h symblcmp.h tmpltdef.h constrnt.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h 
  facthsh.h memalloc.h router.h inscom.h insfun.h object.h multifld.h 
  objrtmch.h

)
set( SOURCE_FACTBIN
     factbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h factmngr.h conscomp.h symblcmp.h tmpltdef.h 
  constrnt.h factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h 
  cstrccom.h facthsh.h memalloc.h pattern.h scanner.h reorder.h 
  reteutil.h rulebin.h cstrcbin.h modulbin.h factbin.h

)
set( SOURCE_FACTBLD
     factbld.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h factcmp.h network.h match.h ruledef.h agenda.h 
  symbol.h crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h 
  cstrccom.h pattern.h scanner.h reorder.h factgen.h factlhs.h factmch.h 
  factbld.h factmngr.h tmpltdef.h facthsh.h memalloc.h modulutl.h 
  reteutil.h router.h

)
set( SOURCE_FACTCMP
     factcmp.c setup.h envrnmnt.h entities.h usrsetup.h factbld.h 
  network.h match.h ruledef.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h expressn.h exprnops.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  factmngr.h tmpltdef.h facthsh.h factcmp.h pattern.h scanner.h 
  reorder.h

)
set( SOURCE_FACTCOM
     factcom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h extnfunc.h symbol.h factmngr.h conscomp.h 
  symblcmp.h tmpltdef.h constrnt.h factbld.h network.h match.h ruledef.h 
  agenda.h crstrtgy.h cstrccom.h facthsh.h factrhs.h scanner.h 
  multifld.h pprint.h prntutil.h router.h sysdep.h tmpltutl.h factcom.h

)
set( SOURCE_FACTFILE
     factfile.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h 
  sysdep.h symblbin.h cstrcpsr.h strngfun.h factmngr.h conscomp.h 
  symblcmp.h tmpltdef.h constrnt.h factbld.h network.h match.h ruledef.h 
  agenda.h crstrtgy.h cstrccom.h facthsh.h factrhs.h scanner.h insmngr.h 
  object.h multifld.h objrtmch.h inscom.h insfun.h memalloc.h modulpsr.h 
  modulutl.h prntutil.h router.h strngrtr.h tmpltutl.h factfile.h

)
set( SOURCE_FACTFUN
     factfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h extnfunc.h symbol.h multifld.h prntutil.h 
  router.h sysdep.h tmpltutl.h constrnt.h factmngr.h conscomp.h 
  symblcmp.h tmpltdef.h factbld.h network.h match.h ruledef.h agenda.h 
  crstrtgy.h cstrccom.h facthsh.h factfun.h

)
set( SOURCE_FACTGEN
     factgen.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  constrct.h userdata.h moduldef.h utility.h evaluatn.h exprnpsr.h 
  extnfunc.h expressn.h exprnops.h symbol.h scanner.h factmch.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  symblcmp.h constrnt.h cstrccom.h factmngr.h tmpltdef.h facthsh.h 
  factprt.h factrete.h memalloc.h pattern.h reorder.h prcdrpsr.h 
  reteutil.h router.h sysdep.h tmpltfun.h tmpltlhs.h tmpltutl.h 
  factgen.h

)
set( SOURCE_FACTHSH
     facthsh.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  factmngr.h conscomp.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  tmpltdef.h constrnt.h factbld.h network.h match.h ruledef.h agenda.h 
  crstrtgy.h cstrccom.h facthsh.h memalloc.h multifld.h router.h 
  sysdep.h lgcldpnd.h

)
set( SOURCE_FACTLHS
     factlhs.c setup.h envrnmnt.h entities.h usrsetup.h cstrcpsr.h 
  strngfun.h modulpsr.h evaluatn.h constant.h moduldef.h userdata.h 
  utility.h symbol.h scanner.h modulutl.h pattern.h expressn.h 
  exprnops.h constrct.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h reorder.h 
  pprint.h prntutil.h router.h tmpltdef.h factbld.h tmpltlhs.h 
  tmpltpsr.h tmpltutl.h factmngr.h facthsh.h factlhs.h

)
set( SOURCE_FACTMCH
     factmch.c setup.h envrnmnt.h entities.h usrsetup.h drive.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h match.h network.h ruledef.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  engine.h lgcldpnd.h retract.h factgen.h reorder.h pattern.h scanner.h 
  factrete.h incrrset.h memalloc.h prntutil.h reteutil.h router.h 
  sysdep.h tmpltdef.h factbld.h factmch.h factmngr.h facthsh.h

)
set( SOURCE_FACTMNGR
     factmngr.c setup.h envrnmnt.h entities.h usrsetup.h 
  commline.h default.h constrnt.h evaluatn.h constant.h engine.h 
  lgcldpnd.h match.h network.h ruledef.h constrct.h userdata.h 
  moduldef.h utility.h expressn.h exprnops.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h cstrccom.h retract.h 
  factbin.h factbld.h factcmp.h pattern.h scanner.h reorder.h factcom.h 
  factfile.h factfun.h factmngr.h tmpltdef.h facthsh.h factmch.h 
  factqury.h factrhs.h memalloc.h multifld.h prntutil.h router.h 
  strngrtr.h sysdep.h tmpltbsc.h tmpltfun.h tmpltutl.h watch.h 
  cstrnchk.h

)
set( SOURCE_FACTPRT
     factprt.c setup.h envrnmnt.h entities.h usrsetup.h factgen.h 
  reorder.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h pattern.h symbol.h scanner.h match.h 
  network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h 
  symblcmp.h constrnt.h cstrccom.h prntutil.h router.h factprt.h

)
set( SOURCE_FACTQPSR
     factqpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  exprnpsr.h extnfunc.h evaluatn.h constant.h expressn.h exprnops.h 
  constrct.h userdata.h moduldef.h utility.h symbol.h scanner.h 
  factqury.h factmngr.h conscomp.h symblcmp.h tmpltdef.h constrnt.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h 
  facthsh.h modulutl.h prcdrpsr.h pprint.h prntutil.h router.h 
  strngrtr.h factqpsr.h

)
set( SOURCE_FACTQURY
     factqury.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h memalloc.h exprnpsr.h extnfunc.h 
  symbol.h scanner.h modulutl.h tmpltutl.h constrnt.h factmngr.h 
  conscomp.h symblcmp.h tmpltdef.h factbld.h network.h match.h ruledef.h 
  agenda.h crstrtgy.h cstrccom.h facthsh.h insfun.h object.h multifld.h 
  objrtmch.h factqpsr.h prcdrfun.h prntutil.h router.h factqury.h

)
set( SOURCE_FACTRETE
     factrete.c setup.h envrnmnt.h entities.h usrsetup.h drive.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h match.h network.h ruledef.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  engine.h lgcldpnd.h retract.h factgen.h reorder.h pattern.h scanner.h 
  factmch.h factbld.h factmngr.h tmpltdef.h facthsh.h incrrset.h 
  memalloc.h multifld.h reteutil.h router.h factrete.h

)
set( SOURCE_FACTRHS
     factrhs.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h cstrcpsr.h strngfun.h exprnpsr.h scanner.h modulutl.h 
  modulpsr.h pattern.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h symblcmp.h constrnt.h cstrccom.h reorder.h pprint.h 
  prntutil.h router.h strngrtr.h tmpltpsr.h tmpltdef.h factbld.h 
  tmpltrhs.h tmpltutl.h factmngr.h facthsh.h factrhs.h

)
set( SOURCE_FILECOM
     filecom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h commline.h cstrcpsr.h strngfun.h fileutil.h 
  memalloc.h router.h filecom.h

)
set( SOURCE_FILERTR
     filertr.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  memalloc.h router.h sysdep.h filertr.h

)
set( SOURCE_FILEUTIL
     fileutil.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h commline.h cstrcpsr.h strngfun.h 
  memalloc.h prcdrfun.h pprint.h prntutil.h router.h scanner.h 
  strngrtr.h sysdep.h filecom.h fileutil.h

)
set( SOURCE_GENERATE
     generate.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h exprnpsr.h extnfunc.h symbol.h 
  scanner.h globlpsr.h memalloc.h pattern.h match.h network.h ruledef.h 
  agenda.h crstrtgy.h conscomp.h symblcmp.h constrnt.h cstrccom.h 
  reorder.h prntutil.h router.h generate.h analysis.h

)
set( SOURCE_GENRCBIN
     genrcbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h cstrcbin.h cstrccom.h genrccom.h genrcfun.h 
  conscomp.h symblcmp.h memalloc.h modulbin.h objbin.h object.h 
  constrnt.h multifld.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  objrtmch.h router.h genrcbin.h

)
set( SOURCE_GENRCCMP
     genrccmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  genrccom.h genrcfun.h network.h match.h ruledef.h agenda.h crstrtgy.h 
  constrnt.h cstrccom.h objcmp.h object.h multifld.h objrtmch.h 
  genrccmp.h

)
set( SOURCE_GENRCCOM
     genrccom.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h 
  sysdep.h symblbin.h classcom.h cstrccom.h object.h constrnt.h 
  multifld.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  symblcmp.h objrtmch.h inscom.h insfun.h cstrcpsr.h strngfun.h 
  genrcbin.h genrcfun.h genrccmp.h genrcexe.h genrcpsr.h memalloc.h 
  modulpsr.h scanner.h modulutl.h router.h strngrtr.h watch.h prntutil.h 
  genrccom.h

)
set( SOURCE_GENRCEXE
     genrcexe.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  insfun.h argacces.h genrccom.h genrcfun.h prcdrfun.h prccode.h 
  prntutil.h proflfun.h router.h genrcexe.h

)
set( SOURCE_GENRCFUN
     genrcfun.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h classcom.h cstrccom.h object.h constrnt.h multifld.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  objrtmch.h classfun.h scanner.h argacces.h cstrcpsr.h strngfun.h 
  genrccom.h genrcfun.h genrcexe.h memalloc.h modulutl.h prccode.h 
  prntutil.h router.h

)
set( SOURCE_GENRCPSR
     genrcpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h dffnxfun.h classfun.h object.h constrnt.h multifld.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  cstrccom.h objrtmch.h scanner.h classcom.h cstrcpsr.h strngfun.h 
  exprnpsr.h genrccom.h genrcfun.h immthpsr.h memalloc.h modulutl.h 
  pprint.h prcdrpsr.h prccode.h prntutil.h router.h genrcpsr.h

)
set( SOURCE_GLOBLBIN
     globlbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h globlbsc.h globldef.h conscomp.h symblcmp.h 
  cstrccom.h memalloc.h multifld.h globlbin.h modulbin.h cstrcbin.h

)
set( SOURCE_GLOBLBSC
     globlbsc.c setup.h envrnmnt.h entities.h usrsetup.h 
  constrct.h userdata.h moduldef.h utility.h evaluatn.h constant.h 
  extnfunc.h expressn.h exprnops.h symbol.h globlbin.h modulbin.h 
  cstrcbin.h globldef.h conscomp.h symblcmp.h cstrccom.h globlcmp.h 
  globlcom.h multifld.h watch.h globlbsc.h

)
set( SOURCE_GLOBLCMP
     globlcmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  globldef.h cstrccom.h globlcmp.h

)
set( SOURCE_GLOBLCOM
     globlcom.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h extnfunc.h symbol.h globldef.h 
  conscomp.h symblcmp.h cstrccom.h prntutil.h router.h globlcom.h

)
set( SOURCE_GLOBLDEF
     globldef.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h globlbin.h modulbin.h cstrcbin.h globldef.h conscomp.h 
  symblcmp.h cstrccom.h commline.h globlbsc.h globlcmp.h globlcom.h 
  globlpsr.h memalloc.h modulpsr.h scanner.h modulutl.h multifld.h 
  prntutil.h router.h strngrtr.h

)
set( SOURCE_GLOBLPSR
     globlpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h cstrcpsr.h strngfun.h exprnpsr.h scanner.h globlbsc.h 
  globldef.h conscomp.h symblcmp.h cstrccom.h memalloc.h modulpsr.h 
  modulutl.h multifld.h pprint.h prntutil.h router.h watch.h globlpsr.h

)
set( SOURCE_IMMTHPSR
     immthpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  cstrnutl.h exprnpsr.h genrcpsr.h genrcfun.h memalloc.h prccode.h 
  immthpsr.h

)
set( SOURCE_INCRRSET
     incrrset.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  argacces.h drive.h engine.h lgcldpnd.h retract.h pattern.h scanner.h 
  reorder.h router.h reteutil.h incrrset.h

)
set( SOURCE_INHERPSR
     inherpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  memalloc.h modulutl.h pprint.h prntutil.h router.h inherpsr.h

)
set( SOURCE_INSCOM
     inscom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h classcom.h cstrccom.h object.h constrnt.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  classinf.h commline.h exprnpsr.h insfile.h insfun.h insmngr.h inscom.h 
  insmoddp.h insmult.h inspsr.h lgcldpnd.h memalloc.h msgcom.h msgpass.h 
  msgfun.h prntutil.h router.h strngrtr.h sysdep.h

)
set( SOURCE_INSFILE
     insfile.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h classcom.h cstrccom.h object.h constrnt.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  memalloc.h factmngr.h tmpltdef.h factbld.h facthsh.h inscom.h insfun.h 
  insmngr.h inspsr.h prntutil.h router.h strngrtr.h symblbin.h sysdep.h 
  insfile.h

)
set( SOURCE_INSFUN
     insfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h classcom.h cstrccom.h object.h constrnt.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  cstrnchk.h drive.h engine.h lgcldpnd.h retract.h inscom.h insfun.h 
  insmngr.h memalloc.h modulutl.h msgcom.h msgpass.h msgfun.h prccode.h 
  prntutil.h router.h

)
set( SOURCE_INSMNGR
     insmngr.c setup.h envrnmnt.h entities.h usrsetup.h network.h 
  match.h ruledef.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h expressn.h exprnops.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  drive.h objrtmch.h object.h multifld.h lgcldpnd.h classcom.h 
  classfun.h scanner.h cstrnchk.h engine.h retract.h insfun.h memalloc.h 
  miscfun.h modulutl.h msgcom.h msgpass.h msgfun.h prccode.h prntutil.h 
  router.h sysdep.h insmngr.h inscom.h watch.h

)
set( SOURCE_INSMODDP
     insmoddp.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h extnfunc.h symbol.h inscom.h insfun.h 
  object.h constrnt.h multifld.h match.h network.h ruledef.h agenda.h 
  crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h insmngr.h 
  inspsr.h memalloc.h miscfun.h msgcom.h msgpass.h msgfun.h prccode.h 
  scanner.h prntutil.h router.h insmoddp.h

)
set( SOURCE_INSMULT
     insmult.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h extnfunc.h symbol.h insfun.h object.h constrnt.h 
  multifld.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  symblcmp.h cstrccom.h objrtmch.h msgfun.h msgpass.h multifun.h 
  prntutil.h router.h insmult.h

)
set( SOURCE_INSPSR
     inspsr.c setup.h envrnmnt.h entities.h usrsetup.h classcom.h 
  cstrccom.h moduldef.h userdata.h utility.h evaluatn.h constant.h 
  constrct.h object.h constrnt.h expressn.h exprnops.h multifld.h 
  symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h classinf.h 
  exprnpsr.h pprint.h prntutil.h router.h inspsr.h

)
set( SOURCE_INSQUERY
     insquery.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h classcom.h cstrccom.h object.h 
  constrnt.h multifld.h symbol.h match.h network.h ruledef.h agenda.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h 
  scanner.h exprnpsr.h insfun.h insmngr.h inscom.h insqypsr.h memalloc.h 
  prcdrfun.h prntutil.h router.h insquery.h

)
set( SOURCE_INSQYPSR
     insqypsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h exprnpsr.h scanner.h 
  insquery.h prcdrpsr.h pprint.h prntutil.h router.h strngrtr.h 
  insqypsr.h

)
set( SOURCE_IOFUN
     iofun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h commline.h extnfunc.h symbol.h filertr.h 
  memalloc.h miscfun.h prntutil.h router.h scanner.h strngrtr.h sysdep.h 
  iofun.h

)
set( SOURCE_LGCLDPND
     lgcldpnd.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h engine.h lgcldpnd.h match.h network.h 
  ruledef.h agenda.h symbol.h crstrtgy.h conscomp.h extnfunc.h 
  symblcmp.h constrnt.h cstrccom.h retract.h factmngr.h tmpltdef.h 
  factbld.h facthsh.h memalloc.h pattern.h scanner.h reorder.h 
  reteutil.h router.h

)
set( SOURCE_MAIN
     main.c clips.h setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h memalloc.h cstrcpsr.h strngfun.h 
  fileutil.h envrnbld.h extnfunc.h symbol.h commline.h prntutil.h 
  router.h filertr.h strngrtr.h iofun.h sysdep.h bmathfun.h exprnpsr.h 
  scanner.h miscfun.h watch.h modulbsc.h bload.h exprnbin.h symblbin.h 
  bsave.h ruledef.h network.h match.h agenda.h crstrtgy.h conscomp.h 
  symblcmp.h constrnt.h cstrccom.h rulebsc.h engine.h lgcldpnd.h 
  retract.h drive.h incrrset.h rulecom.h dffctdef.h dffctbsc.h 
  tmpltdef.h factbld.h tmpltbsc.h tmpltfun.h factmngr.h facthsh.h 
  factcom.h factfun.h globldef.h globlbsc.h globlcom.h dffnxfun.h 
  genrccom.h genrcfun.h classcom.h object.h multifld.h objrtmch.h 
  classexm.h classfun.h classinf.h classini.h classpsr.h defins.h 
  inscom.h insfun.h insfile.h insmngr.h msgcom.h msgpass.h

)
set( SOURCE_MEMALLOC
     memalloc.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h memalloc.h prntutil.h router.h utility.h evaluatn.h 
  moduldef.h userdata.h

)
set( SOURCE_MISCFUN
     miscfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h exprnpsr.h extnfunc.h symbol.h scanner.h 
  memalloc.h multifld.h prntutil.h router.h sysdep.h dffnxfun.h 
  factfun.h factmngr.h conscomp.h symblcmp.h tmpltdef.h constrnt.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h 
  facthsh.h tmpltutl.h miscfun.h

)
set( SOURCE_MODULBIN
     modulbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h cstrcbin.h memalloc.h modulbin.h

)
set( SOURCE_MODULBSC
     modulbsc.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h 
  sysdep.h symblbin.h modulbin.h cstrcbin.h modulcmp.h multifld.h 
  prntutil.h router.h modulbsc.h

)
set( SOURCE_MODULCMP
     modulcmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  sysdep.h modulcmp.h

)
set( SOURCE_MODULDEF
     moduldef.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h 
  sysdep.h symblbin.h modulbin.h cstrcbin.h memalloc.h modulbsc.h 
  modulcmp.h modulpsr.h scanner.h prntutil.h router.h

)
set( SOURCE_MODULPSR
     modulpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrcpsr.h strngfun.h extnfunc.h 
  symbol.h memalloc.h modulutl.h scanner.h pprint.h prntutil.h router.h 
  bload.h exprnbin.h sysdep.h symblbin.h modulpsr.h

)
set( SOURCE_MODULUTL
     modulutl.c setup.h envrnmnt.h entities.h usrsetup.h 
  cstrcpsr.h strngfun.h memalloc.h modulpsr.h evaluatn.h constant.h 
  moduldef.h userdata.h utility.h symbol.h scanner.h pprint.h prntutil.h 
  router.h sysdep.h watch.h expressn.h exprnops.h constrct.h modulutl.h

)
set( SOURCE_MSGCOM
     msgcom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h sysdep.h 
  symblbin.h classcom.h cstrccom.h object.h constrnt.h multifld.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  objrtmch.h classfun.h scanner.h classinf.h msgpsr.h insfun.h 
  insmoddp.h msgfun.h msgpass.h memalloc.h prccode.h prntutil.h router.h 
  watch.h msgcom.h

)
set( SOURCE_MSGFUN
     msgfun.c setup.h envrnmnt.h entities.h usrsetup.h classcom.h 
  cstrccom.h moduldef.h userdata.h utility.h evaluatn.h constant.h 
  constrct.h object.h constrnt.h expressn.h exprnops.h multifld.h 
  symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h inscom.h 
  insfun.h memalloc.h msgcom.h msgpass.h prccode.h prntutil.h router.h 
  msgfun.h

)
set( SOURCE_MSGPASS
     msgpass.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h classcom.h cstrccom.h object.h constrnt.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  commline.h exprnpsr.h inscom.h insfun.h memalloc.h msgcom.h msgpass.h 
  msgfun.h prccode.h prcdrfun.h prntutil.h proflfun.h router.h 
  strngfun.h

)
set( SOURCE_MSGPSR
     msgpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h classcom.h cstrccom.h object.h constrnt.h multifld.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  objrtmch.h classfun.h scanner.h cstrcpsr.h strngfun.h cstrnchk.h 
  exprnpsr.h insfun.h memalloc.h modulutl.h msgcom.h msgpass.h msgfun.h 
  pprint.h prccode.h prntutil.h router.h strngrtr.h msgpsr.h

)
set( SOURCE_MULTIFLD
     multifld.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h evaluatn.h exprnops.h expressn.h constrct.h userdata.h 
  moduldef.h utility.h memalloc.h object.h constrnt.h multifld.h 
  symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  extnfunc.h symblcmp.h cstrccom.h objrtmch.h scanner.h prntutil.h 
  router.h strngrtr.h

)
set( SOURCE_MULTIFUN
     multifun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h exprnpsr.h extnfunc.h symbol.h 
  scanner.h memalloc.h multifld.h multifun.h object.h constrnt.h match.h 
  network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  cstrccom.h objrtmch.h pprint.h prcdrpsr.h prcdrfun.h prntutil.h 
  router.h

)
set( SOURCE_OBJBIN
     objbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h classcom.h cstrccom.h object.h constrnt.h 
  multifld.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  symblcmp.h objrtmch.h classfun.h scanner.h classini.h cstrcbin.h 
  cstrnbin.h insfun.h memalloc.h modulbin.h msgcom.h msgpass.h msgfun.h 
  prntutil.h router.h objrtbin.h objbin.h

)
set( SOURCE_OBJCMP
     objcmp.c setup.h envrnmnt.h entities.h usrsetup.h conscomp.h 
  constrct.h userdata.h moduldef.h utility.h evaluatn.h constant.h 
  extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h classcom.h 
  cstrccom.h object.h constrnt.h multifld.h match.h network.h ruledef.h 
  agenda.h crstrtgy.h objrtmch.h classfun.h scanner.h classini.h 
  cstrncmp.h objrtfnx.h sysdep.h objrtcmp.h objcmp.h

)
set( SOURCE_OBJRTBIN
     objrtbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h classfun.h object.h constrnt.h multifld.h match.h 
  network.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h 
  cstrccom.h objrtmch.h scanner.h classcom.h memalloc.h insfun.h 
  pattern.h reorder.h reteutil.h rulebin.h cstrcbin.h modulbin.h 
  objrtbin.h

)
set( SOURCE_OBJRTBLD
     objrtbld.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  cstrnutl.h cstrnchk.h cstrnops.h drive.h inscom.h insfun.h insmngr.h 
  memalloc.h pattern.h reorder.h prntutil.h reteutil.h rulepsr.h 
  exprnpsr.h objrtgen.h objrtfnx.h pprint.h router.h objrtbin.h 
  objrtcmp.h objrtbld.h

)
set( SOURCE_OBJRTCMP
     objrtcmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  classcom.h cstrccom.h object.h constrnt.h multifld.h match.h network.h 
  ruledef.h agenda.h crstrtgy.h objrtmch.h objrtfnx.h pattern.h 
  scanner.h reorder.h sysdep.h objrtcmp.h

)
set( SOURCE_OBJRTFNX
     objrtfnx.c setup.h envrnmnt.h entities.h usrsetup.h 
  classcom.h cstrccom.h moduldef.h userdata.h utility.h evaluatn.h 
  constant.h constrct.h object.h constrnt.h expressn.h exprnops.h 
  multifld.h symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h extnfunc.h symblcmp.h objrtmch.h classfun.h scanner.h 
  bload.h exprnbin.h sysdep.h symblbin.h drive.h engine.h lgcldpnd.h 
  retract.h memalloc.h prntutil.h reteutil.h router.h objrtfnx.h

)
set( SOURCE_OBJRTGEN
     objrtgen.c setup.h envrnmnt.h entities.h usrsetup.h 
  classfun.h object.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h constrnt.h expressn.h exprnops.h multifld.h 
  symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  extnfunc.h symblcmp.h cstrccom.h objrtmch.h scanner.h classcom.h 
  objrtfnx.h objrtgen.h reorder.h pattern.h

)
set( SOURCE_OBJRTMCH
     objrtmch.c setup.h envrnmnt.h entities.h usrsetup.h 
  classfun.h object.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h constrnt.h expressn.h exprnops.h multifld.h 
  symbol.h match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h 
  extnfunc.h symblcmp.h cstrccom.h objrtmch.h scanner.h classcom.h 
  memalloc.h drive.h engine.h lgcldpnd.h retract.h incrrset.h objrtfnx.h 
  prntutil.h reteutil.h ruledlt.h reorder.h pattern.h router.h insmngr.h 
  inscom.h insfun.h

)
set( SOURCE_PARSEFUN
     parsefun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrcpsr.h strngfun.h exprnpsr.h 
  extnfunc.h symbol.h scanner.h memalloc.h multifld.h pprint.h 
  prcdrpsr.h constrnt.h prntutil.h router.h strngrtr.h parsefun.h

)
set( SOURCE_PATTERN
     pattern.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  constrnt.h evaluatn.h cstrnchk.h cstrnutl.h exprnpsr.h extnfunc.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  symbol.h scanner.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h symblcmp.h cstrccom.h memalloc.h pprint.h prntutil.h 
  reteutil.h router.h rulecmp.h pattern.h reorder.h

)
set( SOURCE_PPRINT
     pprint.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  memalloc.h sysdep.h utility.h evaluatn.h moduldef.h userdata.h 
  pprint.h

)
set( SOURCE_PRCCODE
     prccode.c setup.h envrnmnt.h entities.h usrsetup.h memalloc.h 
  constant.h globlpsr.h expressn.h exprnops.h constrct.h userdata.h 
  moduldef.h utility.h evaluatn.h exprnpsr.h extnfunc.h symbol.h 
  scanner.h multifld.h object.h constrnt.h match.h network.h ruledef.h 
  agenda.h crstrtgy.h conscomp.h symblcmp.h cstrccom.h objrtmch.h 
  pprint.h prcdrpsr.h prntutil.h router.h prccode.h

)
set( SOURCE_PRCDRFUN
     prcdrfun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h constrnt.h cstrnchk.h cstrnops.h 
  exprnpsr.h extnfunc.h symbol.h scanner.h memalloc.h multifld.h 
  prcdrpsr.h router.h prcdrfun.h globldef.h conscomp.h symblcmp.h 
  cstrccom.h

)
set( SOURCE_PRCDRPSR
     prcdrpsr.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h constrnt.h cstrnchk.h cstrnops.h 
  cstrnutl.h exprnpsr.h extnfunc.h symbol.h scanner.h memalloc.h 
  modulutl.h multifld.h pprint.h prntutil.h router.h prcdrpsr.h 
  globldef.h conscomp.h symblcmp.h cstrccom.h globlpsr.h

)
set( SOURCE_PRDCTFUN
     prdctfun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h exprnpsr.h extnfunc.h symbol.h 
  scanner.h multifld.h router.h prdctfun.h

)
set( SOURCE_PRNTUTIL
     prntutil.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrcpsr.h strngfun.h factmngr.h 
  conscomp.h extnfunc.h symbol.h symblcmp.h tmpltdef.h constrnt.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h 
  facthsh.h inscom.h insfun.h object.h multifld.h objrtmch.h insmngr.h 
  memalloc.h multifun.h router.h scanner.h strngrtr.h sysdep.h 
  prntutil.h

)
set( SOURCE_PROFLFUN
     proflfun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h classcom.h cstrccom.h object.h 
  constrnt.h multifld.h symbol.h match.h network.h ruledef.h agenda.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h objrtmch.h dffnxfun.h 
  genrccom.h genrcfun.h memalloc.h msgcom.h msgpass.h router.h sysdep.h 
  proflfun.h

)
set( SOURCE_REORDER
     reorder.c setup.h envrnmnt.h entities.h usrsetup.h cstrnutl.h 
  constrnt.h evaluatn.h constant.h extnfunc.h expressn.h exprnops.h 
  constrct.h userdata.h moduldef.h utility.h symbol.h memalloc.h 
  pattern.h scanner.h match.h network.h ruledef.h agenda.h crstrtgy.h 
  conscomp.h symblcmp.h cstrccom.h reorder.h prntutil.h router.h 
  rulelhs.h

)
set( SOURCE_RETEUTIL
     reteutil.c setup.h envrnmnt.h entities.h usrsetup.h drive.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h match.h network.h ruledef.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  engine.h lgcldpnd.h retract.h incrrset.h memalloc.h pattern.h 
  scanner.h reorder.h prntutil.h router.h rulecom.h reteutil.h

)
set( SOURCE_RETRACT
     retract.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  argacces.h drive.h engine.h lgcldpnd.h retract.h memalloc.h prntutil.h 
  reteutil.h router.h

)
set( SOURCE_ROUTER
     router.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h extnfunc.h symbol.h filertr.h memalloc.h 
  prntutil.h scanner.h strngrtr.h sysdep.h router.h

)
set( SOURCE_RULEBIN
     rulebin.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  bload.h exprnbin.h sysdep.h symblbin.h bsave.h engine.h lgcldpnd.h 
  retract.h memalloc.h pattern.h scanner.h reorder.h reteutil.h 
  rulebsc.h rulebin.h cstrcbin.h modulbin.h

)
set( SOURCE_RULEBLD
     rulebld.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  constrct.h userdata.h moduldef.h utility.h evaluatn.h drive.h 
  expressn.h exprnops.h match.h network.h ruledef.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  incrrset.h memalloc.h pattern.h scanner.h reorder.h prntutil.h 
  reteutil.h router.h rulebld.h rulepsr.h watch.h

)
set( SOURCE_RULEBSC
     rulebsc.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h drive.h match.h network.h ruledef.h agenda.h 
  symbol.h crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h 
  cstrccom.h engine.h lgcldpnd.h retract.h multifld.h reteutil.h 
  router.h watch.h rulebin.h cstrcbin.h modulbin.h rulecmp.h rulebsc.h

)
set( SOURCE_RULECMP
     rulecmp.c setup.h envrnmnt.h entities.h usrsetup.h factbld.h 
  network.h match.h ruledef.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h expressn.h exprnops.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  pattern.h scanner.h reorder.h reteutil.h rulecmp.h

)
set( SOURCE_RULECOM
     rulecom.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h crstrtgy.h agenda.h ruledef.h network.h match.h 
  conscomp.h extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h 
  engine.h lgcldpnd.h retract.h incrrset.h memalloc.h multifld.h 
  pattern.h scanner.h reorder.h prntutil.h reteutil.h router.h ruledlt.h 
  sysdep.h watch.h rulebin.h cstrcbin.h modulbin.h rulecom.h

)
set( SOURCE_RULECSTR
     rulecstr.c setup.h envrnmnt.h entities.h usrsetup.h 
  analysis.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h reorder.h pattern.h symbol.h scanner.h 
  match.h network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h 
  symblcmp.h constrnt.h cstrccom.h cstrnchk.h cstrnops.h cstrnutl.h 
  prcdrpsr.h prntutil.h router.h rulepsr.h rulecstr.h

)
set( SOURCE_RULEDEF
     ruledef.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  drive.h engine.h lgcldpnd.h retract.h memalloc.h pattern.h scanner.h 
  reorder.h reteutil.h rulebsc.h rulecom.h rulepsr.h ruledlt.h bload.h 
  exprnbin.h sysdep.h symblbin.h rulebin.h cstrcbin.h modulbin.h 
  rulecmp.h

)
set( SOURCE_RULEDLT
     ruledlt.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  bload.h exprnbin.h sysdep.h symblbin.h drive.h engine.h lgcldpnd.h 
  retract.h memalloc.h pattern.h scanner.h reorder.h reteutil.h 
  ruledlt.h

)
set( SOURCE_RULELHS
     rulelhs.c setup.h envrnmnt.h entities.h usrsetup.h agenda.h 
  ruledef.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h expressn.h exprnops.h network.h match.h conscomp.h 
  extnfunc.h symbol.h symblcmp.h constrnt.h cstrccom.h crstrtgy.h 
  argacces.h cstrnchk.h exprnpsr.h scanner.h memalloc.h pattern.h 
  reorder.h pprint.h prntutil.h router.h rulelhs.h

)
set( SOURCE_RULEPSR
     rulepsr.c setup.h envrnmnt.h entities.h usrsetup.h analysis.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h reorder.h pattern.h symbol.h scanner.h match.h 
  network.h ruledef.h agenda.h crstrtgy.h conscomp.h extnfunc.h 
  symblcmp.h constrnt.h cstrccom.h cstrcpsr.h strngfun.h cstrnchk.h 
  cstrnops.h engine.h lgcldpnd.h retract.h exprnpsr.h incrrset.h 
  memalloc.h modulutl.h prccode.h prcdrpsr.h pprint.h prntutil.h 
  router.h rulebld.h rulebsc.h rulecstr.h ruledlt.h rulelhs.h watch.h 
  tmpltfun.h factmngr.h tmpltdef.h factbld.h facthsh.h bload.h 
  exprnbin.h sysdep.h symblbin.h rulepsr.h

)
set( SOURCE_SCANNER
     scanner.c setup.h envrnmnt.h entities.h usrsetup.h constant.h 
  memalloc.h pprint.h prntutil.h router.h symbol.h sysdep.h utility.h 
  evaluatn.h moduldef.h userdata.h scanner.h

)
set( SOURCE_SORTFUN
     sortfun.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h dffnxfun.h extnfunc.h symbol.h memalloc.h 
  multifld.h sysdep.h sortfun.h

)
set( SOURCE_STRNGFUN
     strngfun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h commline.h cstrcpsr.h strngfun.h 
  engine.h lgcldpnd.h match.h network.h ruledef.h agenda.h symbol.h 
  crstrtgy.h conscomp.h extnfunc.h symblcmp.h constrnt.h cstrccom.h 
  retract.h exprnpsr.h scanner.h memalloc.h miscfun.h multifld.h 
  prcdrpsr.h pprint.h prntutil.h router.h strngrtr.h sysdep.h drive.h

)
set( SOURCE_STRNGRTR
     strngrtr.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h memalloc.h prntutil.h router.h sysdep.h strngrtr.h 
  utility.h evaluatn.h moduldef.h userdata.h

)
set( SOURCE_SYMBLBIN
     symblbin.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h bload.h extnfunc.h symbol.h exprnbin.h 
  sysdep.h symblbin.h bsave.h cstrnbin.h constrnt.h exprnpsr.h scanner.h 
  memalloc.h router.h

)
set( SOURCE_SYMBLCMP
     symblcmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h conscomp.h extnfunc.h symbol.h 
  symblcmp.h cstrncmp.h constrnt.h cstrccom.h exprnpsr.h scanner.h 
  memalloc.h prntutil.h router.h sysdep.h

)
set( SOURCE_SYMBOL
     symbol.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h memalloc.h multifld.h prntutil.h router.h 
  sysdep.h symbol.h

)
set( SOURCE_SYSDEP
     sysdep.c setup.h envrnmnt.h entities.h usrsetup.h memalloc.h 
  sysdep.h

)
set( SOURCE_TEXTPRO
     textpro.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h commline.h extnfunc.h symbol.h memalloc.h 
  prntutil.h router.h sysdep.h textpro.h

)
set( SOURCE_TMPLTBIN
     tmpltbin.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h bsave.h cstrnbin.h constrnt.h factbin.h factbld.h network.h 
  match.h ruledef.h agenda.h crstrtgy.h conscomp.h symblcmp.h cstrccom.h 
  factmngr.h tmpltdef.h facthsh.h memalloc.h tmpltpsr.h tmpltutl.h 
  tmpltbin.h cstrcbin.h modulbin.h

)
set( SOURCE_TMPLTBSC
     tmpltbsc.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrccom.h cstrcpsr.h strngfun.h 
  extnfunc.h symbol.h factrhs.h factmngr.h conscomp.h symblcmp.h 
  tmpltdef.h constrnt.h factbld.h network.h match.h ruledef.h agenda.h 
  crstrtgy.h facthsh.h scanner.h memalloc.h multifld.h router.h 
  tmpltbin.h cstrcbin.h modulbin.h tmpltcmp.h tmpltpsr.h tmpltutl.h 
  tmpltbsc.h

)
set( SOURCE_TMPLTCMP
     tmpltcmp.c setup.h envrnmnt.h entities.h usrsetup.h 
  conscomp.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constant.h extnfunc.h expressn.h exprnops.h symbol.h symblcmp.h 
  cstrncmp.h constrnt.h factcmp.h network.h match.h ruledef.h agenda.h 
  crstrtgy.h cstrccom.h pattern.h scanner.h reorder.h tmpltdef.h 
  factbld.h tmpltcmp.h

)
set( SOURCE_TMPLTDEF
     tmpltdef.c setup.h envrnmnt.h entities.h usrsetup.h 
  cstrccom.h moduldef.h userdata.h utility.h evaluatn.h constant.h 
  constrct.h cstrnchk.h constrnt.h exprnops.h expressn.h memalloc.h 
  modulpsr.h symbol.h scanner.h modulutl.h network.h match.h ruledef.h 
  agenda.h crstrtgy.h conscomp.h extnfunc.h symblcmp.h pattern.h 
  reorder.h router.h tmpltbsc.h tmpltdef.h factbld.h tmpltfun.h 
  factmngr.h facthsh.h tmpltpsr.h tmpltutl.h bload.h exprnbin.h sysdep.h 
  symblbin.h tmpltbin.h cstrcbin.h modulbin.h tmpltcmp.h

)
set( SOURCE_TMPLTFUN
     tmpltfun.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h commline.h cstrnchk.h constrnt.h 
  default.h exprnpsr.h extnfunc.h symbol.h scanner.h factmngr.h 
  conscomp.h symblcmp.h tmpltdef.h factbld.h network.h match.h ruledef.h 
  agenda.h crstrtgy.h cstrccom.h facthsh.h factrhs.h memalloc.h 
  modulutl.h multifld.h pprint.h prcdrpsr.h prntutil.h reorder.h 
  pattern.h router.h sysdep.h tmpltlhs.h tmpltrhs.h tmpltutl.h 
  tmpltfun.h

)
set( SOURCE_TMPLTLHS
     tmpltlhs.c setup.h envrnmnt.h entities.h usrsetup.h 
  constant.h constrct.h userdata.h moduldef.h utility.h evaluatn.h 
  constrnt.h exprnpsr.h extnfunc.h expressn.h exprnops.h symbol.h 
  scanner.h factrhs.h factmngr.h conscomp.h symblcmp.h tmpltdef.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h 
  facthsh.h memalloc.h modulutl.h pattern.h reorder.h pprint.h 
  prntutil.h router.h tmpltutl.h tmpltlhs.h

)
set( SOURCE_TMPLTPSR
     tmpltpsr.c setup.h envrnmnt.h entities.h usrsetup.h bload.h 
  utility.h evaluatn.h constant.h moduldef.h userdata.h extnfunc.h 
  expressn.h exprnops.h constrct.h symbol.h exprnbin.h sysdep.h 
  symblbin.h cstrcpsr.h strngfun.h cstrnchk.h constrnt.h cstrnpsr.h 
  cstrnutl.h default.h exprnpsr.h scanner.h factmngr.h conscomp.h 
  symblcmp.h tmpltdef.h factbld.h network.h match.h ruledef.h agenda.h 
  crstrtgy.h cstrccom.h facthsh.h memalloc.h modulutl.h pattern.h 
  reorder.h pprint.h prntutil.h router.h tmpltbsc.h watch.h tmpltpsr.h

)
set( SOURCE_TMPLTRHS
     tmpltrhs.c setup.h envrnmnt.h entities.h usrsetup.h default.h 
  constrnt.h evaluatn.h constant.h extnfunc.h expressn.h exprnops.h 
  constrct.h userdata.h moduldef.h utility.h symbol.h factrhs.h 
  factmngr.h conscomp.h symblcmp.h tmpltdef.h factbld.h network.h 
  match.h ruledef.h agenda.h crstrtgy.h cstrccom.h facthsh.h scanner.h 
  memalloc.h modulutl.h pprint.h prntutil.h router.h tmpltfun.h 
  tmpltlhs.h tmpltutl.h tmpltrhs.h

)
set( SOURCE_TMPLTUTL
     tmpltutl.c setup.h envrnmnt.h entities.h usrsetup.h 
  argacces.h expressn.h exprnops.h constrct.h userdata.h moduldef.h 
  utility.h evaluatn.h constant.h cstrnchk.h constrnt.h extnfunc.h 
  symbol.h memalloc.h modulutl.h scanner.h multifld.h prntutil.h 
  router.h sysdep.h tmpltbsc.h tmpltdef.h conscomp.h symblcmp.h 
  factbld.h network.h match.h ruledef.h agenda.h crstrtgy.h cstrccom.h 
  tmpltfun.h factmngr.h facthsh.h tmpltpsr.h watch.h tmpltutl.h

)
set( SOURCE_USERDATA
     userdata.c setup.h envrnmnt.h entities.h usrsetup.h 
  userdata.h

)
set( SOURCE_USERFUNCTIONS
     userfunctions.c clips.h setup.h envrnmnt.h entities.h 
  usrsetup.h argacces.h expressn.h exprnops.h constrct.h userdata.h 
  moduldef.h utility.h evaluatn.h constant.h memalloc.h cstrcpsr.h 
  strngfun.h fileutil.h envrnbld.h extnfunc.h symbol.h commline.h 
  prntutil.h router.h filertr.h strngrtr.h iofun.h sysdep.h bmathfun.h 
  exprnpsr.h scanner.h miscfun.h watch.h modulbsc.h bload.h exprnbin.h 
  symblbin.h bsave.h ruledef.h network.h match.h agenda.h crstrtgy.h 
  conscomp.h symblcmp.h constrnt.h cstrccom.h rulebsc.h engine.h 
  lgcldpnd.h retract.h drive.h incrrset.h rulecom.h dffctdef.h 
  dffctbsc.h tmpltdef.h factbld.h tmpltbsc.h tmpltfun.h factmngr.h 
  facthsh.h factcom.h factfun.h globldef.h globlbsc.h globlcom.h 
  dffnxfun.h genrccom.h genrcfun.h classcom.h object.h multifld.h 
  objrtmch.h classexm.h classfun.h classinf.h classini.h classpsr.h 
  defins.h inscom.h insfun.h insfile.h insmngr.h msgcom.h msgpass.h

)
set( SOURCE_UTILITY
     utility.c setup.h envrnmnt.h entities.h usrsetup.h commline.h 
  evaluatn.h constant.h factmngr.h conscomp.h constrct.h userdata.h 
  moduldef.h utility.h extnfunc.h expressn.h exprnops.h symbol.h 
  symblcmp.h tmpltdef.h constrnt.h factbld.h network.h match.h ruledef.h 
  agenda.h crstrtgy.h cstrccom.h facthsh.h memalloc.h multifld.h 
  prntutil.h router.h sysdep.h

)
set( SOURCE_WATCH
     watch.c setup.h envrnmnt.h entities.h usrsetup.h argacces.h 
  expressn.h exprnops.h constrct.h userdata.h moduldef.h utility.h 
  evaluatn.h constant.h extnfunc.h symbol.h memalloc.h router.h watch.h

)
add_library(  agenda ${SOURCE_AGENDA}  )  
add_library(  analysis ${SOURCE_ANALYSIS}  )  
add_library(  argacces ${SOURCE_ARGACCES}  )  
add_library(  bload ${SOURCE_BLOAD}  )  
add_library(  bmathfun ${SOURCE_BMATHFUN}  )  
add_library(  bsave ${SOURCE_BSAVE}  )  
add_library(  classcom ${SOURCE_CLASSCOM}  )  
add_library(  classexm ${SOURCE_CLASSEXM}  )  
add_library(  classfun ${SOURCE_CLASSFUN}  )  
add_library(  classinf ${SOURCE_CLASSINF}  )  
add_library(  classini ${SOURCE_CLASSINI}  )  
add_library(  classpsr ${SOURCE_CLASSPSR}  )  
add_library(  clsltpsr ${SOURCE_CLSLTPSR}  )  
add_library(  commline ${SOURCE_COMMLINE}  )  
add_library(  conscomp ${SOURCE_CONSCOMP}  )  
add_library(  constrct ${SOURCE_CONSTRCT}  )  
add_library(  constrnt ${SOURCE_CONSTRNT}  )  
add_library(  crstrtgy ${SOURCE_CRSTRTGY}  )  
add_library(  cstrcbin ${SOURCE_CSTRCBIN}  )  
add_library(  cstrccom ${SOURCE_CSTRCCOM}  )  
add_library(  cstrcpsr ${SOURCE_CSTRCPSR}  )  
add_library(  cstrnbin ${SOURCE_CSTRNBIN}  )  
add_library(  cstrnchk ${SOURCE_CSTRNCHK}  )  
add_library(  cstrncmp ${SOURCE_CSTRNCMP}  )  
add_library(  cstrnops ${SOURCE_CSTRNOPS}  )  
add_library(  cstrnpsr ${SOURCE_CSTRNPSR}  )  
add_library(  cstrnutl ${SOURCE_CSTRNUTL}  )  
add_library(  default ${SOURCE_DEFAULT}  )  
add_library(  defins ${SOURCE_DEFINS}  )  
add_library(  developr ${SOURCE_DEVELOPR}  )  
add_library(  dffctbin ${SOURCE_DFFCTBIN}  )  
add_library(  dffctbsc ${SOURCE_DFFCTBSC}  )  
add_library(  dffctcmp ${SOURCE_DFFCTCMP}  )  
add_library(  dffctdef ${SOURCE_DFFCTDEF}  )  
add_library(  dffctpsr ${SOURCE_DFFCTPSR}  )  
add_library(  dffnxbin ${SOURCE_DFFNXBIN}  )  
add_library(  dffnxcmp ${SOURCE_DFFNXCMP}  )  
add_library(  dffnxexe ${SOURCE_DFFNXEXE}  )  
add_library(  dffnxfun ${SOURCE_DFFNXFUN}  )  
add_library(  dffnxpsr ${SOURCE_DFFNXPSR}  )  
add_library(  dfinsbin ${SOURCE_DFINSBIN}  )  
add_library(  dfinscmp ${SOURCE_DFINSCMP}  )  
add_library(  drive ${SOURCE_DRIVE}  )  
add_library(  emathfun ${SOURCE_EMATHFUN}  )  
add_library(  engine ${SOURCE_ENGINE}  )  
add_library(  envrnbld ${SOURCE_ENVRNBLD}  )  
add_library(  envrnmnt ${SOURCE_ENVRNMNT}  )  
add_library(  evaluatn ${SOURCE_EVALUATN}  )  
add_library(  expressn ${SOURCE_EXPRESSN}  )  
add_library(  exprnbin ${SOURCE_EXPRNBIN}  )  
add_library(  exprnops ${SOURCE_EXPRNOPS}  )  
add_library(  exprnpsr ${SOURCE_EXPRNPSR}  )  
add_library(  extnfunc ${SOURCE_EXTNFUNC}  )  
add_library(  factbin ${SOURCE_FACTBIN}  )  
add_library(  factbld ${SOURCE_FACTBLD}  )  
add_library(  factcmp ${SOURCE_FACTCMP}  )  
add_library(  factcom ${SOURCE_FACTCOM}  )  
add_library(  factfile ${SOURCE_FACTFILE}  )  
add_library(  factfun ${SOURCE_FACTFUN}  )  
add_library(  factgen ${SOURCE_FACTGEN}  )  
add_library(  facthsh ${SOURCE_FACTHSH}  )  
add_library(  factlhs ${SOURCE_FACTLHS}  )  
add_library(  factmch ${SOURCE_FACTMCH}  )  
add_library(  factmngr ${SOURCE_FACTMNGR}  )  
add_library(  factprt ${SOURCE_FACTPRT}  )  
add_library(  factqpsr ${SOURCE_FACTQPSR}  )  
add_library(  factqury ${SOURCE_FACTQURY}  )  
add_library(  factrete ${SOURCE_FACTRETE}  )  
add_library(  factrhs ${SOURCE_FACTRHS}  )  
add_library(  filecom ${SOURCE_FILECOM}  )  
add_library(  filertr ${SOURCE_FILERTR}  )  
add_library(  fileutil ${SOURCE_FILEUTIL}  )  
add_library(  generate ${SOURCE_GENERATE}  )  
add_library(  genrcbin ${SOURCE_GENRCBIN}  )  
add_library(  genrccmp ${SOURCE_GENRCCMP}  )  
add_library(  genrccom ${SOURCE_GENRCCOM}  )  
add_library(  genrcexe ${SOURCE_GENRCEXE}  )  
add_library(  genrcfun ${SOURCE_GENRCFUN}  )  
add_library(  genrcpsr ${SOURCE_GENRCPSR}  )  
add_library(  globlbin ${SOURCE_GLOBLBIN}  )  
add_library(  globlbsc ${SOURCE_GLOBLBSC}  )  
add_library(  globlcmp ${SOURCE_GLOBLCMP}  )  
add_library(  globlcom ${SOURCE_GLOBLCOM}  )  
add_library(  globldef ${SOURCE_GLOBLDEF}  )  
add_library(  globlpsr ${SOURCE_GLOBLPSR}  )  
add_library(  immthpsr ${SOURCE_IMMTHPSR}  )  
add_library(  incrrset ${SOURCE_INCRRSET}  )  
add_library(  inherpsr ${SOURCE_INHERPSR}  )  
add_library(  inscom ${SOURCE_INSCOM}  )  
add_library(  insfile ${SOURCE_INSFILE}  )  
add_library(  insfun ${SOURCE_INSFUN}  )  
add_library(  insmngr ${SOURCE_INSMNGR}  )  
add_library(  insmoddp ${SOURCE_INSMODDP}  )  
add_library(  insmult ${SOURCE_INSMULT}  )  
add_library(  inspsr ${SOURCE_INSPSR}  )  
add_library(  insquery ${SOURCE_INSQUERY}  )  
add_library(  insqypsr ${SOURCE_INSQYPSR}  )  
add_library(  iofun ${SOURCE_IOFUN}  )  
add_library(  lgcldpnd ${SOURCE_LGCLDPND}  )  
add_library(  main ${SOURCE_MAIN}  )  
add_library(  memalloc ${SOURCE_MEMALLOC}  )  
add_library(  miscfun ${SOURCE_MISCFUN}  )  
add_library(  modulbin ${SOURCE_MODULBIN}  )  
add_library(  modulbsc ${SOURCE_MODULBSC}  )  
add_library(  modulcmp ${SOURCE_MODULCMP}  )  
add_library(  moduldef ${SOURCE_MODULDEF}  )  
add_library(  modulpsr ${SOURCE_MODULPSR}  )  
add_library(  modulutl ${SOURCE_MODULUTL}  )  
add_library(  msgcom ${SOURCE_MSGCOM}  )  
add_library(  msgfun ${SOURCE_MSGFUN}  )  
add_library(  msgpass ${SOURCE_MSGPASS}  )  
add_library(  msgpsr ${SOURCE_MSGPSR}  )  
add_library(  multifld ${SOURCE_MULTIFLD}  )  
add_library(  multifun ${SOURCE_MULTIFUN}  )  
add_library(  objbin ${SOURCE_OBJBIN}  )  
add_library(  objcmp ${SOURCE_OBJCMP}  )  
add_library(  objrtbin ${SOURCE_OBJRTBIN}  )  
add_library(  objrtbld ${SOURCE_OBJRTBLD}  )  
add_library(  objrtcmp ${SOURCE_OBJRTCMP}  )  
add_library(  objrtfnx ${SOURCE_OBJRTFNX}  )  
add_library(  objrtgen ${SOURCE_OBJRTGEN}  )  
add_library(  objrtmch ${SOURCE_OBJRTMCH}  )  
add_library(  parsefun ${SOURCE_PARSEFUN}  )  
add_library(  pattern ${SOURCE_PATTERN}  )  
add_library(  pprint ${SOURCE_PPRINT}  )  
add_library(  prccode ${SOURCE_PRCCODE}  )  
add_library(  prcdrfun ${SOURCE_PRCDRFUN}  )  
add_library(  prcdrpsr ${SOURCE_PRCDRPSR}  )  
add_library(  prdctfun ${SOURCE_PRDCTFUN}  )  
add_library(  prntutil ${SOURCE_PRNTUTIL}  )  
add_library(  proflfun ${SOURCE_PROFLFUN}  )  
add_library(  reorder ${SOURCE_REORDER}  )  
add_library(  reteutil ${SOURCE_RETEUTIL}  )  
add_library(  retract ${SOURCE_RETRACT}  )  
add_library(  router ${SOURCE_ROUTER}  )  
add_library(  rulebin ${SOURCE_RULEBIN}  )  
add_library(  rulebld ${SOURCE_RULEBLD}  )  
add_library(  rulebsc ${SOURCE_RULEBSC}  )  
add_library(  rulecmp ${SOURCE_RULECMP}  )  
add_library(  rulecom ${SOURCE_RULECOM}  )  
add_library(  rulecstr ${SOURCE_RULECSTR}  )  
add_library(  ruledef ${SOURCE_RULEDEF}  )  
add_library(  ruledlt ${SOURCE_RULEDLT}  )  
add_library(  rulelhs ${SOURCE_RULELHS}  )  
add_library(  rulepsr ${SOURCE_RULEPSR}  )  
add_library(  scanner ${SOURCE_SCANNER}  )  
add_library(  sortfun ${SOURCE_SORTFUN}  )  
add_library(  strngfun ${SOURCE_STRNGFUN}  )  
add_library(  strngrtr ${SOURCE_STRNGRTR}  )  
add_library(  symblbin ${SOURCE_SYMBLBIN}  )  
add_library(  symblcmp ${SOURCE_SYMBLCMP}  )  
add_library(  symbol ${SOURCE_SYMBOL}  )  
add_library(  sysdep ${SOURCE_SYSDEP}  )  
add_library(  textpro ${SOURCE_TEXTPRO}  )  
add_library(  tmpltbin ${SOURCE_TMPLTBIN}  )  
add_library(  tmpltbsc ${SOURCE_TMPLTBSC}  )  
add_library(  tmpltcmp ${SOURCE_TMPLTCMP}  )  
add_library(  tmpltdef ${SOURCE_TMPLTDEF}  )  
add_library(  tmpltfun ${SOURCE_TMPLTFUN}  )  
add_library(  tmpltlhs ${SOURCE_TMPLTLHS}  )  
add_library(  tmpltpsr ${SOURCE_TMPLTPSR}  )  
add_library(  tmpltrhs ${SOURCE_TMPLTRHS}  )  
add_library(  tmpltutl ${SOURCE_TMPLTUTL}  )  
add_library(  userdata ${SOURCE_USERDATA}  )  
add_library(  userfunctions ${SOURCE_USERFUNCTIONS}  )  
add_library(  utility ${SOURCE_UTILITY}  )  
add_library(  watch ${SOURCE_WATCH}  )  


if(WIN32)
    add_definitions(-DWIN_MVC=1)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_library(  clips SHARED  x.c)
    target_link_libraries(clips agenda analysis argacces bload bmathfun bsave classcom classexm classfun classinf classini classpsr clsltpsr commline conscomp constrct constrnt crstrtgy cstrcbin cstrccom cstrcpsr cstrnbin cstrnchk cstrncmp cstrnops cstrnpsr cstrnutl default defins developr dffctbin dffctbsc dffctcmp dffctdef dffctpsr dffnxbin dffnxcmp dffnxexe dffnxfun dffnxpsr dfinsbin dfinscmp drive emathfun engine envrnbld envrnmnt evaluatn expressn exprnbin exprnops exprnpsr extnfunc factbin factbld factcmp factcom factfile factfun factgen facthsh factlhs factmch factmngr factprt factqpsr factqury factrete factrhs filecom filertr fileutil generate genrcbin genrccmp genrccom genrcexe genrcfun genrcpsr globlbin globlbsc globlcmp globlcom globldef globlpsr immthpsr incrrset inherpsr inscom insfile insfun insmngr insmoddp insmult inspsr insquery insqypsr iofun lgcldpnd main memalloc miscfun modulbin modulbsc modulcmp moduldef modulpsr modulutl msgcom msgfun msgpass msgpsr multifld multifun objbin objcmp objrtbin objrtbld objrtcmp objrtfnx objrtgen objrtmch parsefun pattern pprint prccode prcdrfun prcdrpsr prdctfun prntutil proflfun reorder reteutil retract router rulebin rulebld rulebsc rulecmp rulecom rulecstr ruledef ruledlt rulelhs rulepsr scanner sortfun strngfun strngrtr symblbin symblcmp symbol sysdep textpro tmpltbin tmpltbsc tmpltcmp tmpltdef tmpltfun tmpltlhs tmpltpsr tmpltrhs tmpltutl userdata userfunctions utility watch)
    add_library(  clips-static  x.c )
    target_link_libraries(clips-static agenda analysis argacces bload bmathfun bsave classcom classexm classfun classinf classini classpsr clsltpsr commline conscomp constrct constrnt crstrtgy cstrcbin cstrccom cstrcpsr cstrnbin cstrnchk cstrncmp cstrnops cstrnpsr cstrnutl default defins developr dffctbin dffctbsc dffctcmp dffctdef dffctpsr dffnxbin dffnxcmp dffnxexe dffnxfun dffnxpsr dfinsbin dfinscmp drive emathfun engine envrnbld envrnmnt evaluatn expressn exprnbin exprnops exprnpsr extnfunc factbin factbld factcmp factcom factfile factfun factgen facthsh factlhs factmch factmngr factprt factqpsr factqury factrete factrhs filecom filertr fileutil generate genrcbin genrccmp genrccom genrcexe genrcfun genrcpsr globlbin globlbsc globlcmp globlcom globldef globlpsr immthpsr incrrset inherpsr inscom insfile insfun insmngr insmoddp insmult inspsr insquery insqypsr iofun lgcldpnd main memalloc miscfun modulbin modulbsc modulcmp moduldef modulpsr modulutl msgcom msgfun msgpass msgpsr multifld multifun objbin objcmp objrtbin objrtbld objrtcmp objrtfnx objrtgen objrtmch parsefun pattern pprint prccode prcdrfun prcdrpsr prdctfun prntutil proflfun reorder reteutil retract router rulebin rulebld rulebsc rulecmp rulecom rulecstr ruledef ruledlt rulelhs rulepsr scanner sortfun strngfun strngrtr symblbin symblcmp symbol sysdep textpro tmpltbin tmpltbsc tmpltcmp tmpltdef tmpltfun tmpltlhs tmpltpsr tmpltrhs tmpltutl userdata userfunctions utility watch)
    add_executable(clipscli main.c)

    if(static-cli)
        set_property(TARGET clipscli PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")  # static link MSVC Runtime
        target_link_libraries(clipscli clips-static )
    else()
        target_link_libraries(clipscli clips )
    endif()
    install(TARGETS clipscli clips clips-static
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
    
else()

    
    add_library(clips SHARED ${SOURCE_FILES})
    add_library(clips-static ${SOURCE_FILES})
    set_target_properties(clips PROPERTIES LINK_FLAGS_RELEASE -s)
    set_target_properties(clips-static PROPERTIES LINK_FLAGS_RELEASE -s)
    target_link_libraries(clips m)
    target_link_libraries(clips-static m)
    add_executable(clipscli main.c)
    if(static-cli)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        set(BUILD_SHARED_LIBS OFF)
        set(CMAKE_EXE_LINKER_FLAGS "-static -s")
        target_link_libraries(clipscli clips-static )
    else()
        set(CMAKE_EXE_LINKER_FLAGS "-s")
        target_link_libraries(clipscli clips )
    endif()
    install(FILES ${HEADER_FILES} DESTINATION include)
    install(TARGETS clipscli clips clips-static
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()